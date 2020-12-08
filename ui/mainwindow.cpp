#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include <QGLFormat>
#include <QFileDialog>
#include <iostream>
#include "lib/CS123XmlSceneParser.h"
#include "camera/CamtransCamera.h"
#include <QMessageBox>
#include "Settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);

    QSettings qtSettings("CS123", "CS123");

    dataBind();

  /*QGridLayout *gridLayout = new QGridLayout(ui->canvas3D);
  m_canvas3D = new SupportCanvas3D(qglFormat, this);
  gridLayout->addWidget(m_canvas3D, 0, 0);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileScene()
{
    QString file = QFileDialog::getOpenFileName(this, QString(), "/course/cs123/data/");
    if (!file.isNull()) {
        if (file.endsWith(".xml")) {
            CS123XmlSceneParser parser(file.toLatin1().data());
            if (parser.parse()) {
                ui->view->loadSceneviewSceneFromParser(parser);
//                //ui->showSceneviewInstead->setChecked(true);

//                // Set the camera for the new scene
//                CS123SceneCameraData camera;
//                if (parser.getCameraData(camera)) {
//                    camera.pos[3] = 1;
//                    camera.look[3] = 0;
//                    camera.up[3] = 0;

//                    CamtransCamera *cam = ui->view->getCamtransCamera();
//                    cam->orientLook(camera.pos, camera.look, camera.up);
//                    cam->setHeightAngle(camera.heightAngle);
//                }

//                if (settings.useOrbitCamera) {
//                    ui->cameraOrbitCheckbox->setChecked(false);
//                }

              //  activateCanvas3D();
            } else {
                QMessageBox::critical(this, "Error", "Could not load scene \"" + file + "\"");
            }
        }

    }
}

void MainWindow::settingsChanged() {
    //ui->canvas2D->settingsChanged();
    //float checkp = settings.particleMass;
    ui->view->settingsChanged();
}

void MainWindow::dataBind() {
    // Cloth dock
#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}

    BIND(FloatBinding::bindSliderAndTextbox(
        ui->particleMassSlider, ui->particleMassTextbox, settings.particleMass, 1, 25))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->structuralSlider, ui->structuralTextbox, settings.structural, 0, 50000))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->shearSlider, ui->shearTextbox, settings.shear, 0, 50000))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->bendSlider, ui->bendTextbox, settings.bend, 0, 50000))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->dampingSlider, ui->dampingTextbox, settings.damping, 0, 15))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->viscousSlider, ui->viscousTextbox, settings.viscous, 0, 15))
    BIND(BoolBinding::bindCheckbox(ui->gravityCheckbox, settings.hasGravity))

#undef BIND

}





