#pragma once

#include <QMutex>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "RobotFrame.h"
#include "vtkRobotModel.h"

class QWidget;
typedef void* PDATA_M;

class ScanVisualizer
{
public:
	ScanVisualizer();
	virtual ~ScanVisualizer();

	void inline SetVtkWindow(QWidget *vtkWin){
		mVtkWindow = vtkWin;
	}

	//��ʼ�������� ��ӱ�Ҫ������ϵ �����
	void MainInit();
	void SetRobot(RobotFrame &frm);
	
	void ScanTaskInit();
	//�Ե����ʽֱ����ʾ ÿ�������ʾNmax���㣬�����򽵲���
	void ScanTaskDispPoints(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, int Nmax = 400);
	//�����������ٶ�����ɨ��֮��ĵ��ƻ���ƽ��
	void ScanTaskDispSurface(pcl::PointCloud<pcl::PointXYZRGB>::Ptr sliceA, pcl::PointCloud<pcl::PointXYZRGB>::Ptr sliceB);
	void ScanTaskClear();
	void ScanTaskEnd();	//ֹͣɨ��  ȥ����ɢ��

private:
	void addSphere(float radius, float posXYZ[3]);
	void addCoordinateSystem();
	void addGround();
	void addRobot();

	QWidget *mVtkWindow;
	vtkRobotModel mRobot;
	PDATA_M mScanTaskData;
	QMutex mutex;	//���������Ϊ�˷�ֹ��������߳�ֱ�ӻ������
	bool mScanning; 

};

//	int RegistrationAndEstimate();
//	int MoveToCTCoordinate(double bulletXYZ[3], double tailXYZ[3]);

//Eigen::Matrix4d GetRegTransformation() const;	//Mt should be used as:   Coordinate(Robot) = Mt * Coordinate(CT)
