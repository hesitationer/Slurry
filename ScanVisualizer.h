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
	void ScanMainInit();
	void SetRobot(RobotFrame &frm);
	
	void ScanTaskInit();
	//���øú�������һ��ɨ������� ÿ10���ۻ� ������������ӻ� eyenorm�������߷��� ���������ָ��ɨ��ͷ
	void ScanTaskShotPoints(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, Eigen::Vector3f eyeNorm);	//��λm
	void ScanTaskShotPoints(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud);
	void ScanTaskDisplayPoints(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud);	//�Ե����ʽֱ����ʾ �ٶ��� ����Debugʹ��
	void ScanTaskClear();
	void ScanTaskEnd();	//ֹͣɨ��  ���ܽ���һЩ���ݵĺ���
	void ScanSaveData();
	void ScanLoadData(QWidget *window);

	int RegistrationAndEstimate();
	int MoveToCTCoordinate(double bulletXYZ[3], double tailXYZ[3]);

	Eigen::Matrix4d GetRegTransformation() const;	//Mt should be used as:   Coordinate(Robot) = Mt * Coordinate(CT)

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

