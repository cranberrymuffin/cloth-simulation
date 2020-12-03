#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include <QGLFormat>
#include <QFileDialog>
#include <iostream>
#include "lib/CS123XmlSceneParser.h"
#include "camera/CamtransCamera.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);

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



