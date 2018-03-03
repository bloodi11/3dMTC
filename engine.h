#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

class Vertex{
private:
    float _x;
    float _y;
    float _z;

public:
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
    std::vector<Vertex> vertexDataVector;

public:
    WorkSpace(QString path);
};




#endif // ENGINE_H
