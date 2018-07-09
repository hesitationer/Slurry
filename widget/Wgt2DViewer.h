#ifndef WGT2DVIEWER_H
#define WGT2DVIEWER_H

#include <QtWidgets>
#include "RWidget.h"
#include <QMap>
#include <QToolTip>
#include <QString>
#include <QToolButton>
#include <QRectF>
#include <ipccommon>
#include "RColorTable.h"
#include <itkImage.h>
#include "TTransformer.h"

class RSeries;
class RSlice;
class RROI;
class RPlan;
class RDose;

class RInteractionBase;

class RMeasureObjBase;
class RMeasureAreaObj;
class RMeasureLengthAngleObj;
//////////////////////////////////////////////////////////////////////////
// common-interaction-related declearations
class RCrossHairInteraction;
class RMeasureAreaInteraction;
class RMeasureLengthAngleInteraction;
class RZoomPanInteraction;
class RWWWLInteraction;
//////////////////////////////////////////////////////////////////////////
// register-related declearations
class RROIInteraction;
class RMarkerInteraction;
class RRegTranslateInteraction;
class RRegRotationInteraction;
//////////////////////////////////////////////////////////////////////////
// contour-related declearations
class RPolygonPointContourInteraction;
class RSplinePointContourInteraction;
class RFreeHandPointContourInteraction;
class RSmartContourPointInteraction;
class RBrushContourInteraction;
class RTranslateContour2DInteraction;
class RRotateContour2DInteraction;
class RScaleContour2DInteraction;
class RRegionGrowing2DInteraction;
class RRegionGrowing3DInteraction;
class RDeformContourInteraction;
class RDeformContour3DInteraction;
//////////////////////////////////////////////////////////////////////////

typedef itk::Vector< float, 3 > VectorPixelType;
typedef itk::Image< VectorPixelType, 3 > Displacement3DFieldType;
typedef Displacement3DFieldType::Pointer Displacement3DFieldPointer;
typedef itk::Image< VectorPixelType, 2 > Displacement2DFieldType;
typedef Displacement2DFieldType::Pointer Displacement2DFieldPointer;

class Wgt2DViewer : public RWidget
{
	Q_OBJECT

public:
	Wgt2DViewer(QWidget *parent = 0, bool standalone = true);
	~Wgt2DViewer();

	// ����/��ȡ��ǰ���ڵ���ͼ����
	SETANDGETMACRO(ViewDirection, E_ViewDirection);

	// ��ȡǰ��ͼ���ָ��
	RSlice *getPrimaryRawSlice();

	// �������������صĺ���
	void addMeasureAreaObj(RMeasureAreaObj* &obj);
	void removeMeasureAreaObj(int index);
	void clearMeasureAreaObjs();
	QVector<RMeasureAreaObj*> getMeasureAreaObjs();

	// ����/�ǶȲ���������صĺ���
	void addMeasureLengAngleObj(RMeasureLengthAngleObj*obj);
	void removeMeasureLengAngleObj(int index);
	void clearMeasureLengAngleObjs();
	QVector<RMeasureLengthAngleObj*> getMeasureLengAngleObjs();

	// ���߲���������صĺ���
	void addMeasureCurveObj(RMeasureLengthAngleObj*obj);
	void removeMeasureCurveObj(int index);
	void clearMeasureCurveObjs();
	QVector<RMeasureLengthAngleObj*> getMeasureCurveObjs();

	// ��ȡ���������б�־λ
	bool getHidePrimarySeriesStatus();
protected:
	//////////////////////////////////////////////////////////////////////////
	// measure obj-related declearations
	friend class RMeasureObjBase;
	friend class RMeasureAreaObj;
	friend class RMeasureLengthAngleObj;
	//////////////////////////////////////////////////////////////////////////
	// common-interaction-related declearations
	friend class RCrossHairInteraction;
	friend class RMeasureAreaInteraction;
	friend class RMeasureLengthAngleInteraction;
	friend class RZoomPanInteraction;
	friend class RWWWLInteraction;
	//////////////////////////////////////////////////////////////////////////
	// register-related declearations
	friend class RROIInteraction;
	friend class RMarkerInteraction;
	friend class RRegTranslateInteraction;
	friend class RRegRotationInteraction;
	//////////////////////////////////////////////////////////////////////////
	// contour-related declearations
	friend class RSplinePointContourInteraction;
	friend class RFreeHandPointContourInteraction;
	friend class RSmartContourPointInteraction;
	friend class RPolygonPointContourInteraction;
	friend class RBrushContourInteraction;
	friend class RTranslateContour2DInteraction;
	friend class RRotateContour2DInteraction;
	friend class RScaleContour2DInteraction;
	friend class RRegionGrowing2DInteraction;
	friend class RRegionGrowing3DInteraction;
	friend class RDeformContourInteraction;
	friend class RDeformContour3DInteraction;

	void screen2PrimaryIndex(const QPointF &screen, QPointF &image, bool &resultvalid);
	void screen2SecondaryIndex(const QPointF &screen, QPointF &image, bool &resultvalid);
	void screen2SecondaryPoint(const QPointF &screen, QPointF &image, bool &resultvalid);
	void screen2DoseIndex(const QPointF &screen, QPointF &image, bool &resultvalid);
	void screen2DosePoint(const QPointF &screen, QPointF &image, bool &resultvalid);
	void primaryIndex2Screen(const QPointF &image, QPointF &screen, bool &resultvalid);
	void secondaryIndex2Screen(const QPointF &image, QPointF &screen, bool &resultvalid);
	void doseIndex2Screen(const QPointF &image, QPointF &screen, bool &resultvalid);
	void screen2SpacePoint(const QPointF &screen, RVector3F &space, bool &resultvalid);
	void spacePoint2Screen(const RVector3F &space, QPointF &image, bool &resultvalid);

public slots:
	void slot_SetSeriesFocus(RVector3F focus);

	void slot_SetSeries(RSeries* primary, RSeries* secondary = NULL);
	void slot_SynSeries(RSeries* primary, RSeries* secondary = NULL);

	void slot_SetDose(RDose* s);
	void slot_SynDose(RDose* s);

	// �����ں���ʾģʽ
	void slot_SetFusionViewMode(E_FusionMode v);
	void slot_SynFusionViewMode(E_FusionMode v);

	// �����ں���ʾģʽ����ߴ�
	void slot_SetFusionViewGridSize(int v);
	void slot_SynFusionViewGridSize(int v);

	// �����ں���ʾģʽ������ż��ת��־λ
	void slot_SetFusionViewPatternFliped(bool v);
	void slot_SynFusionViewPatternFliped(bool v);

	// ���ڸı���ʾͼ������ű���
	void slot_SetDrawRectScale(float scale);
	void slot_SynDrawRectScale(float scale);

	// ƽ�ƻ��ƾ���
	void slot_SetDrawRectOffset(QPointF offset);

	// ����ģʽ
	void slot_SetInteractionMode(E_InteractionMode v);
	void slot_SynInteractionMode(E_InteractionMode mode, bool v);

	// �� Index ���
	void slot_ChangeToNearestIndexSlice_Previous();
	void slot_ChangeToNearestIndexSlice_Next();

	// ͸���ȵ�ͬ��
	void slot_SetOpacity(int percentage);
	void slot_SynOpacity(int percentage);

	// �������������б�־λ
	void slot_SetHidePrimarySeries(bool v);
	void slot_SynHidePrimarySeries(bool v);

signals:
	void sgnl_SynHidePrimarySeries(bool v);
	void sgnl_SynSeries(RSeries* priamry, RSeries* secondary);
	void sgnl_SynDose(RDose *s);
	void sgnl_SynFusionViewMode(E_FusionMode v);
	void sgnl_SynFusionViewGridSize(int v);
	void sgnl_SynFusionViewPatternFliped(bool v);
	void sgnl_SynDrawRectScale(float scale);
	void sgnl_SynInteractionMode(E_InteractionMode mode, bool v);
	void sgnl_SynMarkers(RLayer &v);
	void sgnl_SynOpacity(int percentage);

	void sgnl_TranslateTransform(TTransformer::ObjectPointer);
	void sgnl_RotateTransform(TTransformer::ObjectPointer);

protected:
	void paintEvent(QPaintEvent * event);
	void resizeEvent(QResizeEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void enterEvent(QEvent *in);
	void leaveEvent(QEvent *out);
	void contextMenuEvent(QContextMenuEvent *event);

	void initialize(bool standalone);
	bool isContourInteraction(RInteractionBase *v);
	// �����ʺϴ��ڴ�С����ʾ����
	float getFitToWindowScale();
	float getFitToWindowScale(QSize windowSize);
	// ������ʾ������ƫ����
	void resetScaleAndOffset();
	// ���ɻ��ƾ���
	void generatePrimaryDrawRect();
	void generateSecondaryDrawRect();
	void generateDoseDrawRect();

	// ���Ʋο�ͼ��
	void paintPrimaryImage(QPainter& painter);
	// ���Ƹ���ͼ��
	void paintSecondaryImage(QPainter& painter);
	// ���Ƽ���ͼ��
	void paintDoseImage(QPainter& painter);
	// ������׼���λ��������
	void paintDisplacementField(QPainter& painter);
	// ���ƽ���ģʽ�µĻ����¼�
	void paintInteractionEvent(QPainter& painter);
	// ���ƽ���ʮ����
	void paintFocusLine(QPainter& painter);
	// ���Ʋ�������
	void paintMeasureTools(QPainter& painter);
	// �����ı���Ϣ
	void paintSeriesInfo(QPainter& painter);
	// ����ROI
	void paintROI(QPainter& painter);
	// ���Ʊ�ǵ�
	void paintMarkPoints(QPainter& painter);
	// ����������
	void paintContours(QPainter& painter);
	// ������������
	void paintBeams(QPainter& painter);

	// ��ȡ��ǰ���λ��
	float getPrimarySlicePos(bool& ok);

protected slots:
	// ��ݰ�ť��Ӧ��
	void slot_Button_CrossHair_toggled(bool v);
	void slot_Button_ZoomPan_toggled(bool v);
	void slot_Button_WWWL_toggled(bool v);
	void slot_Button_Measure_toggled(bool v);

protected:
	static float m_Max_Scale; // �����ʾ����
	static float m_Min_Scale; // ��С��ʾ����
	static float UnitLength[15];

	// ���н���ģʽ��ָ��
	E_InteractionMode					m_CurrentInteractionMode;
	RInteractionBase*					m_CurrentInteraction;

	RCrossHairInteraction*				m_CrossHairInteraction;
	RMeasureAreaInteraction*			m_MeasureAreaInteraction;
	RMeasureLengthAngleInteraction*		m_MeasureLengthAngleInteraction;
	RZoomPanInteraction*				m_ZoomPanInteraction;
	RWWWLInteraction*					m_WWWLInteraction;

	RROIInteraction*					m_ROIInteraction;
	RMarkerInteraction*					m_MarkerInteraction;
	RRegTranslateInteraction*			m_RegTranslateInteraction;
	RRegRotationInteraction*			m_RegRotationInteraction;

	RPolygonPointContourInteraction*	m_PolygonPointInteraction;
	RFreeHandPointContourInteraction*	m_FreeHandPointInteraction;
	RSmartContourPointInteraction*		m_SmartContourPointInteraction;
	RSplinePointContourInteraction*		m_SplinePointInteraction;
	RBrushContourInteraction*			m_BrushInteraction;
	RTranslateContour2DInteraction*		m_TranslateContour2DInteraction;
	RRotateContour2DInteraction*		m_RotateContour2DInteraction;
	RScaleContour2DInteraction*			m_ScaleContour2DInteraction;
	RRegionGrowing2DInteraction*		m_RegionGrowing2DInteraction;
	RRegionGrowing3DInteraction*		m_RegionGrowing3DInteraction;
	RDeformContourInteraction*			m_DeformContourInteraction;
	RDeformContour3DInteraction*		m_DeformContour3DInteraction;

	// ��ݰ�ť
	QToolButton*						m_Button_CrossHair;
	QToolButton*						m_Button_ZoomPan;
	QToolButton*						m_Button_WWWL;
	QToolButton*						m_Button_Measure;
	QAction*							m_ActCrossHair;
	QAction*							m_ActZoomPan;
	QAction*							m_ActWWWL;
	QAction*							m_ActMeasure;

	// �Ҽ��˵�
	QMenu*								m_PopMenu;
	QAction*							m_ActReset;
	QAction*							m_ActRegistTranslate;
	QAction*							m_ActRegistRotate;
	QAction*							m_ActRegistCenterAlign;

	// ��������(�������ݸı������)
	E_ViewDirection						m_ViewDirection;						// ��ǰ��������ʾ����ͼ����
	QPointF								m_CursorPos;							// �����Ļλ��
	float								m_Opacity;								// �ں���ʾ������͸����(1->0:������->������)
	E_FusionMode						m_FusionViewMode;						// �ں���ʾģʽ
	int									m_FusionView_GridSize;					// �ں���ʾ����ߴ�(��Ļ����)
	bool								m_FusionView_PatternFliped;				// �ں���ʾ������ż��ת��־λ
	bool								m_HidePrimarySeries;					// �Ա���ͼ�½�����������ʱ���øñ�־λ�����������У�

	// ��������(�����ݸı������)
	RSeries*							m_PrimarySeries;						// �ο�����
	RSeries*							m_SecondarySeries;						// ��������
	RPlan*								m_Plan;									// ���Ƽƻ�
	RDose*								m_Dose;									// ��������
	QRectF								m_PrimaryDrawRect;						// �ο�ͼ���ڴ����еĻ��ƾ���
	QRectF								m_SecondaryDrawRect;					// ����ͼ���ڴ����еĻ��ƾ���
	QRectF								m_DoseDrawRect;							// ����ͼ���ڴ����еĻ��ƾ���
	float								m_DrawRectScale;						// ���ƾ��ε����ű���
	QPointF								m_DrawRectOffset;						// ���ƾ��ε�λ�ƣ��� mm Ϊ��λ

	// ��������(����ĳЩ����ģʽ����Ч������)
	QVector<RMeasureAreaObj*>			m_MeasureAreaObjs;						// �����������
	QVector<RMeasureLengthAngleObj*>	m_MeasureLengAngleObjs;					// ����/�ǶȲ�������
	QVector<RMeasureLengthAngleObj*>	m_MeasureCurveObjs;						// ����/�ǶȲ�������
	float								m_MaxShowedDistance;					// �����ʾλ��
	float								m_MinShowedDistance;					// ��С��ʾλ��
};

#endif // WGT2DVIEWER_H
