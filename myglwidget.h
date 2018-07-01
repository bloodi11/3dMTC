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

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void draw();
    void drawGrid(int HALF_GRID_SIZE);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void changeScale(float scale);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void scalePlus();
    void scaleMinus();

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
   // Vertex v1;
   // Vertex v2;
   // Vertex v3;

    //Vertex n1;
  //  Vertex n2;
  //  Vertex n3;

    int xRot;
    int yRot;
    int zRot;

    float _scale = 0.2f;

    QPoint lastPos;
};

#endif // MYGLWIDGET_H
