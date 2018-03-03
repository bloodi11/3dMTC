#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

WorkSpace::WorkSpace(QString path){
    std::ifstream file;
    std::string line;
    Vertex vertex_temp;

    file.open(path.toStdString());
    if (file.is_open()){
            while (!file.eof()){
                getline(file, line);
                if(line.at(0) == 'v'){
                    if(line.at(2) == '-')  vertex_temp.setX(-std::stof(line.at(3)));
                        else vertex_temp.setX(std::stof(line.at(2)));
                    if(line.at(11) == '-') vertex_temp.setY(-std::stof(line.at(12)));
                        else vertex_temp.setY(std::stof(line.at(11)));
                    if(line.at(20) == '-')  vertex_temp.setZ(-std::stof(line.at(21)));
                        else vertex_temp.setZ(std::stof(line.at(20)));

                    vertexVector.push_back(vertex_temp);
                }
                }
            }
        file.close();

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
