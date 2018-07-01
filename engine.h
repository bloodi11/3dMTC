#ifndef ENGINE_H
#define ENGINE_H
#include <QOpenGLWidget>
#include <vector>
#include <memory>
#include <string>
#include "mainwindow.h"
#include <QTextEdit>

class WorkSpace;
class Plane;

class JobReader{
protected:
    void readTxt(WorkSpace& workSpace, QString& pathToRead);

public:

};

class JobConstructPlane{
protected:
    void constructPlane(WorkSpace& workspace);
    void calculateEquation(Plane& plane);

public:

};

class Vertex{
private:

public:
    float _x;
    float _y;
    float _z;

    Vertex();
    Vertex(float x, float y, float z);

    void setX(float& x);
    void setY(float& y);
    void setZ(float& z);
    float getX();
    float getY();
    float getZ();

};

class FaceSet{
private:

public:
    float index_v1;
    float index_v2;
    float index_v3;

    float index_vn1;
    float index_vn2;
    float index_vn3;
};

class Model{
private:
    float xL;
    float xH;
    float yL;
    float yH;
    float zL;
    float zH;

    float xDistance;
    float yDistance;
    float zDistance;

public:
    Model();

    void findBounds(WorkSpace& workSpace);

    float& getXLow();
    float& getXHigh();
    float& getYLow();
    float& getYHigh();
    float& getZLow();
    float& getZHigh();
    float& getXDistance();
    float& getYDistance();
    float& getZDistance();

};


class Material{
private:
    float _materialX;
    float _materialY;
    float _materialZ;

    float _step;

public:
    Material();

    void setMaterialParamX(float x);
    void setMaterialParamY(float y);
    void setMaterialParamZ(float z);
    void setStep(float step);

    float getStep();
    float getX();
    float getY();
    float getZ();
};

class WorkSpace : protected JobReader, protected JobConstructPlane{
private:

public:
    std::vector<Vertex> v_data;
    std::vector<Vertex> vt_data;
    std::vector<Vertex> vn_data;
    std::vector<FaceSet> f_data;

    std::vector<Plane> plane_dataV;

    Model _model;
    Material _material;

    float stopPoint;

    WorkSpace(QString& path);

};

class Plane{
private:
    Vertex _v1;
    Vertex _v2;
    Vertex _v3;
    std::vector<float> planeEq; /* [A, B, C, D] >>> Ax + By + Cz = D */

public:
    Plane(Vertex v1, Vertex v2, Vertex v3);

    std::vector<float>& getPlaneEq();
    Vertex& getV1();
    Vertex& getV2();
    Vertex& getV3();


};



class JobPlaneDetect{
private:

public:
    bool detectPlaneX(float actualX, float actualY, float actualZ, WorkSpace& workspace);
    bool detectPlaneY(float actualX, float actualY, float actualZ, WorkSpace& workspace);
};


class JobConvert : public JobPlaneDetect{
private:

public:
    std::string code;

    void parseToGCode(std::shared_ptr<WorkSpace> workSpace);
};

class Process : public JobConvert {
private:

public:
    Process();

    std::shared_ptr<WorkSpace> _workspace;
};

#endif // ENGINE_H
