#pragma once

#include <QAtomicInt>
#include <QMutex>
#include <QElapsedTimer>
#include <opencv2/core.hpp>
#include "RobotFrame.h"

#include "FrameProcessor.h"


/*
����������ڲ����궨�����۱궨 һ�α궨һ�����
�������֡�ص����� ����ɼ�֡����ȡ�����㡢����궨  Ȼ������һ�����

Dialog����Processor: ���� ���� װ������
Processor����Dialog: ��ʾ
������ɾ����signal-slot֮��������Զ��Ͽ�

*/

class FrmProcessorCameraCalibration :public QObject, public FrameProcessor
{
	Q_OBJECT
public:
	FrmProcessorCameraCalibration();
	~FrmProcessorCameraCalibration();

	void ProcessColorA(FramePacket *fp);
	void ProcessColorB(FramePacket *fp);
	
	void StartCalibration(int camSel);
	void Preview();
	void StopCalibration();
	void StopAndShow(cv::Mat img);
	bool CapturePoints();
	bool Solve(CameraParameter &param);

	int framesCaptured() const;
	void debugUndistort();

signals:
	void DispInDialogBig(cv::Mat img);
	void DispInDialogSmall(cv::Mat img);

	void DispInMainWindowA(cv::Mat img);
	void DispInMainWindowB(cv::Mat img);

private:
	//��ǰ�ؼ����Ƿ�����һ�����ɼ���ͬ
	bool framesAreDifferent();
	void resetAll();


	QAtomicInt stage;
	enum STAGE{ STAGE_STOP, STAGE_PREVIEW, STAGE_CAPTURE_A, STAGE_CAPTURE_B };
	CalibrationSetting calibSets;

	cv::Size imageSize;
	QElapsedTimer timestamper;
	QMutex mutex;
	qint64 prevTimestamp;

	std::vector<std::vector<cv::Point2f>>  imagePoints;
	std::vector<cv::Point2f> pointBuf;
	std::vector<RobotFrame>  robotMtcp;
	//Used in preview after undistort
	cv::Mat prevImg;
	
};
