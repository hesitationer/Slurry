#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_Slurry.h"

/*
ViSP ������۱궨
Eigen����������� ����ʽ��ֵ ��� spline

λ��
�Լ����� RobotPose3D
#include <visp3/core/vpPoseVector.h>	vpPoseVector
#include <mrpt/poses/CPose3D.h>			mrpt::poses::CPose3D
#include <mrpt/math/lightweight_geom_data.h>  mrpt::math::TPose3D

��ѧ��ʹ��<visp3/core/vpMath.h>
MRPTδʹ�� ǰ���˶�ѧ PnP���� spline�����(����)
*/

class RobotControllerDialog;
class SystemParameter;
class LaserDialog;
class PathRecorder;
class RobotPath;
class ScanVisualizer;
using cv::Mat;

class Slurry : public QMainWindow
{
	Q_OBJECT
public:
	friend class CTImageVisualization;
	Slurry(QWidget *parent = 0);
	~Slurry();
	
	void initCalibSelect();
	Ui::SlurryClass ui;

public slots:
	void closeEvent(QCloseEvent *event) override;
	void about();
	void aboutQt();

	void cameraInit();
	void cameraDisplay();
	void openCalibDialog();
	void openRobotControlDialog();
	void openToolDialog();
	void openLaserDialog();

	//���Ժ��� ���ڽ���ǰ���λ�ñ��浽�ļ�
	void saveCameraPose();
	void test1();
	void test2();

private:
	void slurryInit();
	void createPointsGenerator();

//Scan &tool slots
public slots:
	void stop();
	void scanTeach();
	void scanTeachTest();
	void scanStart();
	void scanClear();
	void scanSaveData();
	void scanLoadData();
	void toolDispWidget(bool tooggled);
	void toolIntoPosition();
	void toolMoveForward1cm();
	void toolMoveBackward1cm();

private:
	PathRecorder *recorder;
	ScanVisualizer *scanVisualizer;
	friend class FrmProcessorScan;
	
//CT Image Visualization.cpp
public slots:
	void ctInit();
	void ctDisplay();
	void ctLoadDICOM();
	void ctLoadImage3D();
	void ctSaveImage3D();
	void ctReconstruct();
	void ctRegistration();
	void ctShowSkin(bool show);
	void ctDebug();

signals:
	void lineWidgetMove(double *P1, double *P2);

public slots:
	void lineWidgetTransform(double *P1, double *P2);	//����������ڽ�CT����ϵ�ĵ����ֱ��任����е������ϵ����m_regMatrix��Ϊ�任����
	void lineWidgetNoTransform(double *P1, double *P2);	//ֱ������targetP����ϵ

private:
	QString ctFileName;
	bool m_ctMatched;
	void *m_ctData;
	double m_regMatrix[3][4];
	double targetP1[3], targetP2[3];
protected:
	void timerEvent(QTimerEvent *event);
};

