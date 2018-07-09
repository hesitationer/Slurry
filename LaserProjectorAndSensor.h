#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>

class LaserProjectorAndSensor: public QObject
{
	Q_OBJECT
public:
	virtual ~LaserProjectorAndSensor();
	static LaserProjectorAndSensor *GetInstance();
	static bool isConstructed();

	void LaserOn();
	void LaserOff();

	void Trigger1On();
	void Trigger1Off();
	
	void Trigger2On();
	void Trigger2Off();

	void TrigbotOn();
	void TrigbotOff();
	
	void FlickerRunFast();
	void FlickerRunSlow();
	void FlickerStop();

	void MeterRun();
	void MeterStop();
	void MeterStatus();

	void MeterMark();	//Meter����һ�δ����Ҫ1��  ʹ�øú�����ǲ���ʱ��
	bool MeterChanged();	//ʹ�øú����ж���û���µĲ������ݵ���

//	double GetDistance();
private:
	LaserProjectorAndSensor();
	LaserProjectorAndSensor(LaserProjectorAndSensor &);
	void operator=(LaserProjectorAndSensor &);
	void write(const QByteArray &writeData);

	void resolve(QByteArray &ba);
	int m_bytesLeft;
	QByteArray  m_readData;
	char flickerSlowFreq, flickerFastFreq, flckerIntervalFast, flckerIntervalSlow;

	static LaserProjectorAndSensor *pInst;

//	��Qt�Ĵ���
private slots:
	void handleReadyRead();
	void handleBytesWritten(qint64 bytes);
	void handleTimeout();
	void handleError(QSerialPort::SerialPortError serialPortError);

};
