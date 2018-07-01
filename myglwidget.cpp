#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = -1072;
    yRot = 48;
    zRot = -1824;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(650, 650);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    initializeGLFunctions();
    //QColor clearColor(230,230,250);
    qglClearColor(Qt::black);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat qaAmbient[] = { 1.0, 1.0, 1.0, 0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbient);


}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10, +10, -10, +10, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);


}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        //setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::LeftButton) {
        //setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::changeScale(float scale){
    _scale -= scale;
}

void MyGLWidget::scalePlus(){
    _scale += 0.1f;
    updateGL();
}

void MyGLWidget::scaleMinus(){
   if(_scale < 0.2){ /*do nothing*/ }
   else{
    _scale -= 0.1f;
    updateGL();
   }
}

void MyGLWidget::drawGrid(int HALF_GRID_SIZE)
{
    glBegin(GL_LINES);
    glColor3f(255, 255, 0);
    for(int i = -HALF_GRID_SIZE; i<=HALF_GRID_SIZE; i++)
    {
        glVertex3f((float)i,(float)-HALF_GRID_SIZE,0);
        glVertex3f((float)i,(float)HALF_GRID_SIZE,0);

        glVertex3f((float)-HALF_GRID_SIZE,(float)i,0);
        glVertex3f((float)HALF_GRID_SIZE,(float)i,0);
    }
    glEnd();


}

void MyGLWidget::draw()
{
    if(workspace == nullptr) { drawGrid(1000); }
    else if(workspace != nullptr){
      glScalef(_scale, _scale, _scale);
      glBegin(GL_TRIANGLES);
      for(auto&& element : workspace->f_data){
             auto v1 = workspace->v_data.at(element.index_v1 - 1);
             auto v2 =  workspace->v_data.at(element.index_v2 - 1);
             auto v3 =  workspace->v_data.at(element.index_v3 - 1);

             auto n1 = workspace->vn_data.at(element.index_vn1 - 1);
             auto n2 = workspace->vn_data.at(element.index_vn2 - 1);
             auto n3 = workspace->vn_data.at(element.index_vn3 - 1);

             glVertex3f(v1._x, v1._y, v1._z);
             glNormal3f(n1._x, n1._y, n1._z);
             //std::cout<< "G1 X" << v2._y << " G1 Y" << v2._x <<std::endl;
             //std::cout <<" G1 Z" << v2._z <<std::endl;
             //std::cout<< "G1 X" << v2._x << " G1 Y" << v2._y << " G1 Z" << v2._z <<std::endl;
             //std::cout<< "G1 X" << v3._x << " G1 Y" << v3._y << " G1 Z" << v3._z <<std::endl;

             glVertex3f(v2._x, v2._y, v2._z);
             glNormal3f(n2._x, n2._y, n2._z);

             glVertex3f(v3._x, v3._y, v3._z);
             glNormal3f(n3._x, n3._y, n3._z);
        }
        glEnd();

        drawGrid(100);




    }
    //std::cout << xRot << "   " << yRot << "  " << zRot << std::endl;
}
