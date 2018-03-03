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
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            std::getline(file, line);
                if(line[0] == 'v' && line[1] == ' '){
                    if(line[2] == '-')  vertex_temp.setX( - std::stof(&line[3]));
                        else vertex_temp.setX(std::stof(&line[2]));
                    if(line[11] == '-') vertex_temp.setY( - std::stof(&line[12]));
                        else vertex_temp.setY(std::stof(&line[11]));
                    if(line[20] == '-')  vertex_temp.setZ( - std::stof(&line[21]));
                        else vertex_temp.setZ(std::stof(&line[20]));

                    vertexDataVector.push_back(vertex_temp);

                    if(line[0] == 'v' && line[1] == 't') break;
               }

        }
    file.close();

   /* TEST >>>>> */ for(auto x : vertexDataVector) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
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
