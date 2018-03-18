#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
#include <memory>
#include "engine.h"

class MyGLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    std::shared_ptr<WorkSpace> workspace;

    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    void paintGL();

signals:

public slots:

protected:
    void initializeGL();
    //void paintGL();
    void resizeGL(int width, int height);

    void draw();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    Vertex v1;
    Vertex v2;
    Vertex v3;

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
};

#endif // MYGLWIDGET_H
