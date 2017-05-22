/*
 *   Implementation of class AppWindow for the RTR demo App
 *   Author: Hartmut Schirmacher
 *
 */

#include <assert.h>
#include <QThread>
#include <QApplication>
#include <QKeyEvent>
#include <QTime>
#include "appwindow.h"
#include "ui_appwindow.h"
#include "scene.h"

AppWindow::AppWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);

    connect(ui->quitButton, &QPushButton::clicked, []{ qApp->quit(); });

    connect(ui->modelComboBox, &QComboBox::currentTextChanged,
            [this](const QString& txt) { scene().changeModel(txt); } );

    connect(ui->bandsComboBox, &QComboBox::currentTextChanged,
            [this](const QString& txt) { scene().changeBands(txt); } );

    connect(ui->materialComboBox, &QComboBox::currentTextChanged,
            [this](const QString& txt) { scene().changeMaterial(txt);} );

    connect(ui->wobbleCheckBox, &QCheckBox::stateChanged,
            [this](int state) { scene().setWobble(state > 0); });

    connect(ui->rotateCheckBox, &QCheckBox::stateChanged,
            [this](int state) { scene().setRotate(state > 0); });

    connect(ui->rSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) { scene().setR(value); });

    connect(ui->gSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) { scene().setG(value); });

    connect(ui->bSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) { scene().setB(value); });

    connect(ui->bSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) { scene().setB(value); });

    connect(ui->radiusSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value) { scene().setDotRadius((float) value); });

    connect(ui->densitySpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value) { scene().setDotDensity((float) value); });
}

AppWindow::~AppWindow()
{
    delete ui;
}





Scene &AppWindow::scene()
{
    return ui->openGLWidget->scene();
}

void AppWindow::showUI() {
    ui->ui_container->show();
    // default pixel margins (on Mac)
    ui->appWindowLayout->setContentsMargins(12,12,12,12);
}

void AppWindow::on_cb_animation_stateChanged(int arg1)
{


}


void AppWindow::hideUI()
{
    ui->ui_container->hide();
    // zero pixel margins, for borderless OpenGL window
    ui->appWindowLayout->setContentsMargins(0,0,0,0);
}


void AppWindow::keyPressEvent(QKeyEvent *event)
{
    assert(event);

    // specific key events the app reacts to
    switch(event->key()) {

    // key 'h': show/hide UI
    case Qt::Key_H:
        ui->ui_container->isHidden()? showUI() : hideUI();
        break;

    // key 'q': quit app
    case Qt::Key_Q:
        qApp->quit();
        break;

    // rotate world
    case Qt::Key_Left:
        scene().worldTransform().rotate(-5, QVector3D(0,1,0));
        ui->openGLWidget->update();

        break;
    case Qt::Key_Right:
        scene().worldTransform().rotate(5, QVector3D(0,1,0));
        ui->openGLWidget->update();
        break;
    case Qt::Key_Up:
        scene().worldTransform().rotate(-5, QVector3D(1,0,0));
        ui->openGLWidget->update();
        break;
    case Qt::Key_Down:
        scene().worldTransform().rotate(5, QVector3D(1,0,0));
        ui->openGLWidget->update();
        break;



    // translate camera
    case Qt::Key_I:
        scene().camera().translateViewPoint(QVector3D(0,0,-0.1f));
        ui->openGLWidget->update();
        break;
    case Qt::Key_O:
        scene().camera().translateViewPoint(QVector3D(0,0,+0.1f));
        ui->openGLWidget->update();

       // int k  = ui->cb_animation->stateChanged(k);

        //qDebug() << "Checkbox Status is" << k ;
        break;

    } // switch
}



