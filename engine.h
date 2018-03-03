#ifndef ENGINE_H
#define ENGINE_H
#include <vector>

class WorkSpace{
private:
    std::vector<Vertex> vertexVector;

public:
    WorkSpace();
};

class Vertex{
private:
    float _x;
    float _y;
    float _z;

public:
    Vertex();
    Vertex(float x, float y, float z);

};



#endif // ENGINE_H
