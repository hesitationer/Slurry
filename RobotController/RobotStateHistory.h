#pragma once
#include <QQueue>
#include "RobotStateRT.h"


class RobotStateHistory
{
public:
	const static int QUEUE_LENGTH = 25;
	const static int SYNC_INPUT_LINE = 3;
	const static int SYNC_SIGNAL_WIDTH = 36;	//ms
	const static int SYNC_SIGNAL_COUNT_A = 4;	//��е��8msһ���� 36ms�ۺ�4-5����
	const static int SYNC_SIGNAL_COUNT_B = 5;
	
	RobotStateHistory();
	~RobotStateHistory();

	void add(RobotStateRT *state);
	bool getSyncSignal(double& _t);
	int size();
	bool findSyncSignal(double &time);
	bool findSyncSignal(RobotFrame &frame);
	bool findStateInTimeStamp(double time, RobotStateRT &state);


private:
	double lastSignal;
	QQueue<RobotStateRT> states;
	int width_count;
	double signal_start;
	QMutex mutex;
};

