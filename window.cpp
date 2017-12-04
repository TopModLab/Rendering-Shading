#include <QtGui>

#include "mainwidget.h"
#include "window.h"

Window::Window()
{
    mainWidget = new MainWidget;//GLWidget;
	mainWidget->resize(640,480);
	/*
    xSlider = createSlider(-10,10,16);
    ySlider = createSlider(-10,10,16);
    zSlider = createSlider(-10,10,16);
	*/
	xSlider = createSlider(0,1,100);
    ySlider = createSlider(0,1,100);
    zSlider = createSlider(0,1,100);
	RefIndSlider = createSlider(0.5,2,10);

	KaBoxR = createSpinBox(0,255);
	KaBoxG = createSpinBox(0,255);
	KaBoxB = createSpinBox(0,255);

	KdBoxR = createSpinBox(0,255);
	KdBoxG = createSpinBox(0,255);
	KdBoxB = createSpinBox(0,255);

	KsBoxR = createSpinBox(0,255);
	KsBoxG = createSpinBox(0,255);
	KsBoxB = createSpinBox(0,255);

	KdMaterial = createDoubleSpinBox(0,1000,0.1);
	KsMaterial = createDoubleSpinBox(0,1000,0.1);

	exportButton = createButton("export");

	/*
    connect(xSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setXTransation(int)));
    connect(mainWidget, SIGNAL(xTransationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setYTransation(int)));
    connect(mainWidget, SIGNAL(yTransationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setZTransation(int)));
    connect(mainWidget, SIGNAL(zTransationChanged(int)), zSlider, SLOT(setValue(int)));
	*/
	connect(xSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setaInd(int)));
    connect(mainWidget, SIGNAL(aIndChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setbInd(int)));
    connect(mainWidget, SIGNAL(bIndChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setcInd(int)));
    connect(mainWidget, SIGNAL(cIndChanged(int)), zSlider, SLOT(setValue(int)));
	connect(RefIndSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setRefInd(int)));
	connect(mainWidget, SIGNAL(RefIndChanged(int)),RefIndSlider, SLOT(setValue(int)));
	
	connect(KaBoxR, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKaR(int)));
    connect(mainWidget, SIGNAL(kaRChanged(int)), KaBoxR, SLOT(setValue(int)));
	connect(KaBoxG, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKaG(int)));
    connect(mainWidget, SIGNAL(kaGChanged(int)), KaBoxG, SLOT(setValue(int)));
	connect(KaBoxB, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKaB(int)));
    connect(mainWidget, SIGNAL(kaBChanged(int)), KaBoxB, SLOT(setValue(int)));

	connect(KdBoxR, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKdR(int)));
    connect(mainWidget, SIGNAL(kdRChanged(int)), KdBoxR, SLOT(setValue(int)));
	connect(KdBoxG, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKdG(int)));
    connect(mainWidget, SIGNAL(kdGChanged(int)), KdBoxG, SLOT(setValue(int)));
	connect(KdBoxB, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKdB(int)));
    connect(mainWidget, SIGNAL(kdBChanged(int)), KdBoxB, SLOT(setValue(int)));

	connect(KsBoxR, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKsR(int)));
    connect(mainWidget, SIGNAL(ksRChanged(int)), KsBoxR, SLOT(setValue(int)));
	connect(KsBoxG, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKsG(int)));
    connect(mainWidget, SIGNAL(ksGChanged(int)), KsBoxG, SLOT(setValue(int)));
	connect(KsBoxB, SIGNAL(valueChanged(int)), mainWidget, SLOT(setKsB(int)));
    connect(mainWidget, SIGNAL(ksBChanged(int)), KsBoxB, SLOT(setValue(int)));

	connect(KdMaterial, SIGNAL(valueChanged(double)), mainWidget, SLOT(setKdMaterial(double)));
    connect(mainWidget, SIGNAL(KdMaterialChanged(double)), KsBoxB, SLOT(setValue(double)));
	connect(KsMaterial, SIGNAL(valueChanged(double)), mainWidget, SLOT(setKsMaterial(double)));
    connect(mainWidget, SIGNAL(KsMaterialChanged(double)), KsBoxB, SLOT(setValue(double)));

	connect(exportButton, SIGNAL(released()), mainWidget, SLOT(handleButton()));

    QHBoxLayout *KaLayout = new QHBoxLayout;
	QLabel *labelKaR = new QLabel;
	labelKaR->setText("Ambient Color: R");
	KaLayout->addWidget(labelKaR);
	KaLayout->addWidget(KaBoxR);
	QLabel *labelKaG = new QLabel;
	labelKaG->setText("G");
	KaLayout->addWidget(labelKaG);
	KaLayout->addWidget(KaBoxG);
	QLabel *labelKaB = new QLabel;
	labelKaB->setText("B");
	KaLayout->addWidget(labelKaB);
	KaLayout->addWidget(KaBoxB);
	QHBoxLayout *KdLayout = new QHBoxLayout;
	QLabel *labelKdR = new QLabel;
	labelKdR->setText("Diffuse Color : R");
	KdLayout->addWidget(labelKdR);
	KdLayout->addWidget(KdBoxR);
	QLabel *labelKdG = new QLabel;
	labelKdG->setText("G");
	KdLayout->addWidget(labelKdG);
	KdLayout->addWidget(KdBoxG);
	QLabel *labelKdB = new QLabel;
	labelKdB->setText("B");
	KdLayout->addWidget(labelKdB);
	KdLayout->addWidget(KdBoxB);
	QHBoxLayout *KsLayout = new QHBoxLayout;
	QLabel *labelKsR = new QLabel;
	labelKsR->setText("Specular Color: R");
	KsLayout->addWidget(labelKsR);
	KsLayout->addWidget(KsBoxR);
	QLabel *labelKsG = new QLabel;
	labelKsG->setText("G");
	KsLayout->addWidget(labelKsG);
	KsLayout->addWidget(KsBoxG);
	QLabel *labelKsB = new QLabel;
	labelKsB->setText("B");
	KsLayout->addWidget(labelKsB);
	KsLayout->addWidget(KsBoxB);
	QHBoxLayout *MaterialLayout = new QHBoxLayout;
	QLabel *labelMaterialKd = new QLabel;
	labelMaterialKd->setText("Material Kd:");
	MaterialLayout->addWidget(labelMaterialKd);
	MaterialLayout->addWidget(KdMaterial);
	QLabel *labelMaterialKs = new QLabel;
	labelMaterialKs->setText("Material Ks:");
	MaterialLayout->addWidget(labelMaterialKs);
	MaterialLayout->addWidget(KsMaterial);
	QHBoxLayout *RrefLayout = new QHBoxLayout;
	RrefLayout->addWidget(xSlider);
	RrefLayout->addWidget(ySlider);
	RrefLayout->addWidget(zSlider);
	RrefLayout->addWidget(RefIndSlider);
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addLayout(RrefLayout);
	rightLayout->addLayout(KaLayout);
	rightLayout->addLayout(KdLayout);
	rightLayout->addLayout(KsLayout);
	rightLayout->addLayout(MaterialLayout);
	rightLayout->addWidget(exportButton);
	QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mainWidget);
	mainLayout->addLayout(rightLayout);
	/*
    mainLayout->addWidget(xSlider);
    mainLayout->addWidget(ySlider);
    mainLayout->addWidget(zSlider);
	mainLayout->addWidget(RefIndSlider);
	*/
    setLayout(mainLayout);
	/*
    xSlider->setValue(0*16);
    ySlider->setValue(0*16);
    zSlider->setValue(-5*16);
	*/
	xSlider->setValue(0.3*100);
    ySlider->setValue(0.3*100);
	zSlider->setValue(0.6*100);
	RefIndSlider->setValue(1*10);
	KaBoxR->setValue(119);
	KaBoxG->setValue(53);
	KaBoxB->setValue(54);
	KdBoxR->setValue(202);
	KdBoxG->setValue(101);
	KdBoxB->setValue(91);
	KsBoxR->setValue(218);
	KsBoxG->setValue(227);
	KsBoxB->setValue(206);
	KdMaterial->setValue(5.0);
	KsMaterial->setValue(10.0);
    setWindowTitle(tr("Hello GL"));
}

QSlider *Window::createSlider(float min, float max, float step)
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(min*step, max*step);
    slider->setSingleStep(step);
    slider->setPageStep(1 * step);
    slider->setTickInterval(1 * step);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSpinBox *Window::createSpinBox(float min, float max){
	QSpinBox *spinbox = new QSpinBox;
	spinbox->setRange(min,max);
	return spinbox;
}

QDoubleSpinBox *Window::createDoubleSpinBox(float min, float max, float step){
	QDoubleSpinBox *doublespinbox = new QDoubleSpinBox;
	doublespinbox->setRange(min,max);
	doublespinbox->setSingleStep(step);
	return doublespinbox;
}

QPushButton *Window::createButton(const QString& buttonName){
	QPushButton *button = new QPushButton(buttonName,this);
	return button;

}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
		mainWidget->keyPressEvent(e);
        QWidget::keyPressEvent(e);
}
