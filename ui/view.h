#ifndef VIEW_H
#define VIEW_H

#include "GL/glew.h"
#include <qgl.h>
#include <QTime>
#include <QTimer>
#include <lib/CS123XmlSceneParser.h>
#include "camera/CamtransCamera.h"

class OpenGLScene;
class SceneviewScene;

class View : public QGLWidget {
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();
    void loadSceneviewSceneFromParser(CS123XmlSceneParser &parser);
    CamtransCamera* getCamtransCamera();

private:
    QTime m_time;
    QTimer m_timer;
    bool m_captureMouse;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void initializeScene();

    std::unique_ptr<OpenGLScene> m_currentScene;
    std::unique_ptr<CamtransCamera> m_defaultPerspectiveCamera;
    bool firstFrame;

    float tick_counter;


private slots:
    void tick();
};

#endif // VIEW_H
