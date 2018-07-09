#pragma once

#include "FrameProcessor.h"


class FrmProcessorDisp :public QObject, public FrameProcessor 
{
	Q_OBJECT
public:
	FrmProcessorDisp();
	~FrmProcessorDisp();

	void ProcessColorA(FramePacket *fp);
	void ProcessColorB(FramePacket *fp);

	//void ProcessGrayA(FramePacket *fp);
	//void Process(FramePacket *fp);

	//����signal slot������ ��Ŀ��ؼ�����ʱ�Զ��Ͽ�����
signals:
	void DispInMainWindowColorA(cv::Mat img);
	void DispInMainWindowColorB(cv::Mat img);

private:

};

