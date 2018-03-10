#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

WorkSpace::WorkSpace(QString path){
    std::ifstream file;
    std::string line;
    std::string token;
    Vertex vertex_temp;


    file.open(path.toStdString());
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            std::getline(file, line);
            std::istringstream in(line);

            in >> token;
            if(line[0] == 'v' && line[1] == ' '){
                in >> vertex_temp._x >> vertex_temp._y >> vertex_temp._z;
                vertexDataVector.push_back(vertex_temp);
            }

        } //WHILE
    file.close();


 /* TEST >>>>> */ for(auto x : vertexDataVector) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
}

/*TemporaryData::TemporaryData(){

}

void TemporaryData::actualizeTempVertex(){
    temp_vertex.setX();
}*/

Vertex::Vertex(){

}

Vertex::Vertex(float x, float y, float z){
    setX(x);
    setY(y);
    setZ(z);
}

void Vertex::setX(float x){
    _x = x;
}


void Vertex::setY(float y){
    _y = y;
}


void Vertex::setZ(float z){
    _z = z;
}

float Vertex::getX(){
    return _x;
}

float Vertex::getY(){
    return _y;
}

float Vertex::getZ(){
    return _z;
}
