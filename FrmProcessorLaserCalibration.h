#pragma once

#include <opencv2/core.hpp>
#include <QAtomicInt>
#include <QMutex>
#include <QElapsedTimer>
#include "FrameProcessor.h"


/*

�������֡�ص����� �����ͬʱ�ɼ� 
ʹ��PnP�����������̸�ƽ�� ��ȡ������������㼤��ƽ��

��CalibrationDialog��Ͻ���
Dialog->Processor: ���� ���� ����
Processor->Dialog: ������� �궨���
������ɾ����signal-slot֮��������Զ��Ͽ�
*/




class FrmProcessorLaserCalibration : public QObject, public FrameProcessor
{
	Q_OBJECT

public:
	FrmProcessorLaserCalibration();
	~FrmProcessorLaserCalibration();

	void ProcessColorA(FramePacket *fp);
	void ProcessColorB(FramePacket *fp);

	void Preview();
	void StartCalibration();
	void StopCalibration();
	bool CapturePoints();
	bool SolveLaserPlane();

	int framesCaptured() const;
	std::string GetResultString();

signals:
	void DispInDialogBig(cv::Mat img);
	void DispInDialogSmall(cv::Mat img);

	void DispInMainWindowA(cv::Mat img);
	void DispInMainWindowB(cv::Mat img);

private:
	void resetAll();


	QAtomicInt stage;
	const cv::Size boardSize;
	enum STAGE{ STAGE_STOP, STAGE_PREVIEW, STAGE_CAPTURE };
	qint64 prevTimestamp;
	QElapsedTimer timestamper;

	struct _DATA{
		Mat cameraMatrix, distCoeffs;	  // vector of distortion coefficients

		QMutex mutex;
		//����tmp������˫���� ������ż֡ά�ֱ�����һ����
		Mat PnpImg, PnpImgTmp;
		Mat diff;
		Mat chessPointsBuf, chessPointsBufTmp;
		Mat laserPoints3D;
		Mat laserPlane;
		int nCapture;

		_DATA();
		~_DATA();
		void _procEven(cv::Mat& src);
		void _procOdd(cv::Mat& src, cv::Mat& div2, const cv::Size& boardSize);
		bool _capture();
		bool _solve();
		void _clear();
	};

	struct _DATA m_A, m_B;
};
