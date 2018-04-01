#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "mainwindow.h"

WorkSpace::WorkSpace(QString path){
    std::ifstream file;
    std::string line;
    std::string token;
    Vertex v_temp;
    Vertex vt_temp;
    Vertex vn_temp;
    FaceSet f_temp;



    file.open(path.toStdString());
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            std::getline(file, line);
            std::istringstream in(line);

            in >> token;

            if(token == "v"){
                in >> v_temp._x >> v_temp._y >> v_temp._z;
                v_data.push_back(v_temp);
            }
            else if(token == "vt"){
                in >> vt_temp._x >> vt_temp._y >> vt_temp._z;
                vt_data.push_back(vt_temp);
            }
            else if(token == "vn"){
                in >> vn_temp._x >> vn_temp._y >> vn_temp._z;
                vn_data.push_back(vn_temp);
            }
            else if(token == "f"){
                auto con1 = std::make_unique<std::string>();
                auto con2 = std::make_unique<std::string>();
                auto con3 = std::make_unique<std::string>();
                float vn_index_temp;

                in >> f_temp.index_v1 >> *con1;
                in >> f_temp.index_v2 >> *con2;
                in >> f_temp.index_v3 >> *con3;

                std::istringstream subIn1(*con1);
                std::getline(subIn1, *con1, '/');
                subIn1 >> vn_index_temp;
                f_temp.index_vn1 = vn_index_temp;
               // std::cout << "STRING" << vn_index_temp <<std::endl;

                std::istringstream subIn2(*con2);
                std::getline(subIn2, *con2, '/');
                subIn2 >> vn_index_temp;
                f_temp.index_vn2 = vn_index_temp;

                std::istringstream subIn3(*con3);
                std::getline(subIn3, *con3, '/');
                subIn3 >> vn_index_temp;
                f_temp.index_vn3 = vn_index_temp;

                f_data.push_back(f_temp);
               /* std::cout << "IA" << f_temp.index_vn1 <<std::endl;
                std::cout << "IB" << f_temp.index_vn2 <<std::endl;
                std::cout << "IC" << f_temp.index_vn3 <<std::endl;*/


            }

        } //WHILE

    file.close();
    f_data.pop_back();
/* TEST >>>>> */ for(auto x : v_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
    for(auto x : vt_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
     for(auto x : vn_data) std::cout << x.getX() << ' ' << x.getY() << ' ' << x.getZ() << std::endl;
     for(auto x : f_data) std::cout << x.index_v1 << ' ' << x.index_v2 << ' ' << x.index_v3 << std::endl;
     std::cout << "VN DATA NOW" << std::endl;
     for(auto x : f_data) std::cout << x.index_vn1 << ' ' << x.index_vn2 << ' ' << x.index_vn3 << std::endl;
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
