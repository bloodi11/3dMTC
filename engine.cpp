#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

WorkSpace::WorkSpace(QString path){
    std::ifstream file;
    std::string line;
    Vertex vertex_temp;
    int i = 0;

    file.open(path.toStdString());
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            auto temp_x = std::make_unique<std::vector<float>>();
            auto temp_y = std::make_unique<std::vector<float>>();
            auto temp_z = std::make_unique<std::vector<float>>();

            std::getline(file, line);
               if(line[0] == 'v' && line[1] == ' '){
                    i = 0;
                    for(auto x : line){
                        if(line[i] <= 9 && line[i] >= 0) {
                            temp_x->push_back(&line[i]);
                            i += 1;
                        }else if(line[i] == ' ' && temp_x->size() >= 7){
                            i += 1;
                            temp_y->push_back(&line[i]);
                        }else if(line[i] == ' ' && temp_y->size() >= 7){
                            i += 1;
                            temp_z->push_back(&line[i]);
                        }

                    }

                    vertex_temp.setX(std::stof(temp_x));
                    vertex_temp.setY(std::stof(temp_y));
                    vertex_temp.setZ(std::stof(temp_z));
                    vertexDataVector.push_back(vertex_temp);

                    temp_x.reset();
                    temp_y.reset();
                    temp_z.reset();
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
