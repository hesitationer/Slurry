#include <cassert>
#include <QDebug>
#include "RobotStateRT.h"
#include "RobotStateHistory.h"

RobotStateHistory::RobotStateHistory():
width_count(0), lastSignal(-1),
signal_start(-1)
{
	states.reserve(QUEUE_LENGTH);
}


RobotStateHistory::~RobotStateHistory()
{

}



int RobotStateHistory::size()
{
	mutex.lock();
	int n = states.size();
	mutex.unlock();
	return n;
}

/*
��е�۲�������8ms ���뷽����ʵ�ʿ���Ǿ�ȷ36ms ����Ŀ�ȷ�ӳ��λ��
    |   |   |   |   |   |  
	|                 |
����߶���Ϊ�ֽ���  ��������5  ��������4
	|   |   |   |   |   |
   |                 |
�������

   |   |   |   |   |   |
    |                 |

*/

void RobotStateHistory::add(RobotStateRT *state)
{
	mutex.lock();
	while (states.size() >= QUEUE_LENGTH)
	{
		states.dequeue();
	}
	states.enqueue(*state);
	std::vector<bool> inputbits = state->getDigitalInputBits();
	if (inputbits[SYNC_INPUT_LINE])
	{
		if (width_count == 0)
			signal_start = state->getTime();
		width_count++;
	}
	else if (width_count == SYNC_SIGNAL_COUNT_A ||
		width_count == SYNC_SIGNAL_COUNT_B){
		assert(signal_start > 0);
	//	qDebug() << "Signal width: " << width_count;
		lastSignal = (state->getTime() + signal_start) / 2 - SYNC_SIGNAL_WIDTH /1000 / 2;
		signal_start = -1;
		width_count = 0;
	}
	else if (width_count > 0)
	{
		//Bad signal
		qDebug() << "Bad Signal " << width_count;
		signal_start = -1;
		width_count = 0;
	}
	else
	{
		signal_start = -1;
		width_count = 0;
	}
	mutex.unlock();
}

//time��������ʱ�̵Ļ�е�۵�ʱ�� ���+-2ms
bool RobotStateHistory::getSyncSignal(double& _t)
{
	QMutexLocker locker(&mutex);
	if (states.isEmpty())
		return false;
	if (states.head().getTime() - lastSignal > QUEUE_LENGTH * 0.008)	//̫���� ��Ч
	{
		return false;
	}
	_t = lastSignal;
	return true;
}

bool RobotStateHistory::findSyncSignal(double &time)
{
	mutex.lock();	
	QListIterator<RobotStateRT> itor(states);
	int signalWidth;
	while (itor.hasNext())
	{
		RobotStateRT &stateFalling = const_cast<RobotStateRT&>(itor.next());
		std::vector<bool> inputbits = stateFalling.getDigitalInputBits();
		if (inputbits[SYNC_INPUT_LINE])
		{
			//����ĸ��ź� ���½���
			signalWidth = 1;
			while (itor.hasNext())
			{
				RobotStateRT &stateRaising = const_cast<RobotStateRT&>(itor.next());
				time = stateRaising.getTime();
				inputbits = stateRaising.getDigitalInputBits();
				if (inputbits[SYNC_INPUT_LINE])
				{
					signalWidth++;
				}
				else if (signalWidth == SYNC_SIGNAL_COUNT_A ||
					signalWidth == SYNC_SIGNAL_COUNT_B)
				{
					time = (stateRaising.getTime() + stateFalling.getTime()) / 2 - (double)SYNC_SIGNAL_WIDTH/1000/2;		//����s
					mutex.unlock();
					return true;
				}
				else
				{
					qDebug() << "Signal width: " << signalWidth;
					mutex.unlock();
					return false;
				}
			}
		}
	}
	mutex.unlock();
	return false;
}


bool RobotStateHistory::findStateInTimeStamp(double _t, RobotStateRT &_state)
{
	QMutexLocker locker(&mutex);

	QListIterator<RobotStateRT> itor(states);
	int _ss = 0;
	RobotStateRT s1;
	while (itor.hasNext())
	{
		RobotStateRT &state = const_cast<RobotStateRT&>(itor.next());
		if (state.getTime() >= _t)
		{
			_ss = 1;
			s1 = state;
			break;
		}
	}
	if (_ss == 0)
	{
		return false;
	}else
	{
			itor.previous();
			if (!itor.hasPrevious())
				return false;
			RobotStateRT &s2 = const_cast<RobotStateRT&>(itor.previous());
			double t1 = ::abs(s1.getTime() - _t);
			double t2 = ::abs(s2.getTime() - _t);
			_state = t1<t2? s1:s2;	//�Ҹ��ӽ���
			return true;
	}
	return false;
}

bool RobotStateHistory::findSyncSignal(RobotFrame &frame)
{
	QMutexLocker locker(&mutex);

	double t;
	if (!findSyncSignal(t))
	{
		return false;
	}
	else
	{
		RobotStateRT state;
		if (findStateInTimeStamp(t, state))
		{
			frame = state.getFrame();
			return true;
		}
		else
		{
			return false;
		}
	}
}
