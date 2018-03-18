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
    Vertex v_temp;
    Vertex vt_temp;
    Vertex vn_temp;
    Vertex f_temp;
    std::string trash;



    file.open(path.toStdString());
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            std::getline(file, line);
            std::istringstream in(line);

            in >> token;
            if(token == "v" && token != "vt" && token != "vn"){
                in >> v_temp._x >> v_temp._y >> v_temp._z;
                v_data.push_back(v_temp);
            }
            if(token == "vt" && token != "v" && token != "vn"){
                in >> vt_temp._x >> vt_temp._y >> vt_temp._z;
                vt_data.push_back(vt_temp);
            }
            if(token == "vn" && token != "vt" && token != "v"){
                in >> vn_temp._x >> vn_temp._y >> vn_temp._z;
                vn_data.push_back(vn_temp);
            }
            if(token == "f"){
                in >> f_temp._x >> trash >> f_temp._y >> trash >> f_temp._z;
                f_data.push_back(f_temp);
            }


        } //WHILE
    file.close();


 /* TEST >>>>> */ for(auto x : v_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
    for(auto x : vt_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
     for(auto x : vn_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
     for(auto x : f_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
}

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
