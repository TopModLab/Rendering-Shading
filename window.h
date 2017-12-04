#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <qspinbox.h>
#include <qpushbutton.h>

class QSlider;
class QSpinBox;
class QDoubleSpinBox;
class QPushButton;

//class GLWidget;
class MainWidget;
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider(float min, float max, float step);
	QSpinBox *createSpinBox(float min, float max);
	QDoubleSpinBox *createDoubleSpinBox(float min, float max, float step);
	QPushButton *createButton(const QString&  buttonname);
    //GLWidget *glWidget;
	MainWidget *mainWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
	QSlider *RefIndSlider;
	QSpinBox *KaBoxR, *KaBoxG, *KaBoxB;
	QSpinBox *KdBoxR, *KdBoxG, *KdBoxB;
	QSpinBox *KsBoxR, *KsBoxG, *KsBoxB;
	QDoubleSpinBox *KdMaterial, *KsMaterial;
	QPushButton *exportButton;
};

#endif