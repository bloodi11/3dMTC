#ifndef ENGINE_H
#define ENGINE_H
#include <QOpenGLWidget>
#include <vector>
#include <memory>
#include <string>
#include "mainwindow.h"


class Vertex{
private:

public:
    float _x;
    float _y;
    float _z;

    Vertex();
    Vertex(float x, float y, float z);

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    float getX();
    float getY();
    float getZ();

};



class WorkSpace{
private:

public:
    std::vector<Vertex> v_data;
    std::vector<Vertex> vt_data;
    std::vector<Vertex> vn_data;
    std::vector<Vertex> f_data;

    WorkSpace(QString path);
};


#endif // ENGINE_H
