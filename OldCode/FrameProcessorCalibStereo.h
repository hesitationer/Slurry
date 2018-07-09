#pragma once

#include <opencv2/core.hpp>
#include <QAtomicInt>
#include <QMutex>
#include <QElapsedTimer>
#include "FrameProcessor.h"


/*

�������֡�ص����� �����ͬʱ�ɼ� 
��ȡ���̸����˫Ŀ����
��ȡ������������㼤��ƽ��
��CalibrationDialog��Ͻ���

Dialog->Processor: ���� ���� ����
Processor->Dialog: ������� �궨���
������ɾ����signal-slot֮��������Զ��Ͽ�
*/

class FrameProcessorCalibStereo : public QObject, public FrameProcessor
{
	Q_OBJECT

public:
	FrameProcessorCalibStereo();
	~FrameProcessorCalibStereo();

	void ProcessGrayA(FramePacket *fp);
	void ProcessColorA(FramePacket *fp);

	void StartCalibration();
	bool CapturePoints();
	bool SolveCameraMatrix();
	void SaveCameraMatrix();

	std::string GetResultString();
	bool isEnoughFrames();

signals:
	void DispInDialogGray(cv::Mat img);
	void DispInDialogColor(cv::Mat img);

	void DispInMainWindowGray(cv::Mat img);
	void DispInMainWindowColor(cv::Mat img);

private:
	void resetAll();


	enum STAGE{ STAGE_STOP, STAGE_DETECT };
	CameraParameter camGrayParam, camColorParam;
	StereoParameter stereoParam;

	cv::Size boardSize;
	int nrFrames;
	QAtomicInt stage;
	cv::Size imageSize;
	QMutex mutex;
	qint64 prevTimestamp;
	QElapsedTimer timestamper;

	std::vector<std::vector<cv::Point2f>>  imagePointsGray, imagePointsColor;
	std::vector<cv::Point2f> pointBufGray, pointBufColor;
	std::vector<std::vector<cv::Point3f> > objectPoints;

	//Used in preview after undistort
	cv::Mat prevImgGray, prevImgColor;



};
