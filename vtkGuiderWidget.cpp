#include "vtkSmartPointer.h"
#include "vtkLineWidget.h"

#include "vtkGuiderWidget.h"


vtkGuiderWidget::vtkGuiderWidget()
{
	vtkSmartPointer<vtkLineWidget> lineWidget = vtkSmartPointer<vtkLineWidget>(vtkLineWidget::New());
	//������С��

}


vtkGuiderWidget::~vtkGuiderWidget()
{


}
