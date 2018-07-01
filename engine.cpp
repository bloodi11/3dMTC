#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include "mainwindow.h"
#include <QTextEdit>


void JobReader::readTxt(WorkSpace& workSpace, QString& pathToRead){
    std::ifstream file;
    std::string line;
    std::string token;

    file.open(pathToRead.toStdString());
    if (!file.is_open()){
        std::cerr << "cannot open file cause it not exist" << std::endl;
        exit(404);
    } else
        while (file.good()){
            std::getline(file, line);
            std::istringstream in(line);

            in >> token;

            if(token == "v"){
                auto v_temp = std::make_unique<Vertex>();
                in >> v_temp->_x >> v_temp->_y >> v_temp->_z;
                workSpace.v_data.push_back(*v_temp);

            }
            //________________________________________________NO USE VT (VERTEX-TEXTURES POSITION) FOR THIS PROJECT
            /*else if(token == "vt"){
                auto vt_temp = std::make_unique<Vertex>();
                in >> vt_temp->_x >> vt_temp->_y >> vt_temp->_z;
                vt_data.push_back(*vt_temp);
            }*/
            else if(token == "vn"){
                auto vn_temp = std::make_unique<Vertex>();
                in >> vn_temp->_x >> vn_temp->_y >> vn_temp->_z;
                workSpace.vn_data.push_back(*vn_temp);

            }
            else if(token == "f"){
                auto f_temp = std::make_unique<FaceSet>();
                auto vn_index_temp = std::make_unique<float>();

                auto con1 = std::make_unique<std::string>();
                auto con2 = std::make_unique<std::string>();
                auto con3 = std::make_unique<std::string>();

                in >> f_temp->index_v1 >> *con1;
                in >> f_temp->index_v2 >> *con2;
                in >> f_temp->index_v3 >> *con3;

                std::istringstream subIn1(*con1);
                std::getline(subIn1, *con1, '/');
                subIn1 >> *vn_index_temp;
                f_temp->index_vn1 = *vn_index_temp;


                std::istringstream subIn2(*con2);
                std::getline(subIn2, *con2, '/');
                subIn2 >> *vn_index_temp;
                f_temp->index_vn2 = *vn_index_temp;

                std::istringstream subIn3(*con3);
                std::getline(subIn3, *con3, '/');
                subIn3 >> *vn_index_temp;
                f_temp->index_vn3 = *vn_index_temp;

                workSpace.f_data.push_back(*f_temp);

            }

        } //WHILE
    file.close();
    workSpace.f_data.pop_back();

}

void JobConstructPlane::calculateEquation(Plane& plane){
        float wX = plane.getV2()._x - plane.getV1()._x;
        float wY = plane.getV2()._y - plane.getV1()._y;
        float wZ = plane.getV2()._z - plane.getV1()._z;
        std::vector<float> w = {wX, wY, wZ};

        float eX = plane.getV3()._x - plane.getV1()._x;
        float eY = plane.getV3()._y - plane.getV1()._y;
        float eZ = plane.getV3()._z - plane.getV1()._z;
        std::vector<float> e = {eX, eY, eZ};

        std::vector<float> cp = {w.at(1)*e.at(2) - w.at(2)*e.at(1),
                                 w.at(2)*e.at(0) - w.at(0)*e.at(2),
                                 w.at(0)*e.at(1) - w.at(1)*e.at(0)};
       float a = cp.at(0);
       float b = cp.at(1);
       float c = cp.at(2);
       float d = -(a * plane.getV1()._x + b * plane.getV1()._y + c * plane.getV1()._z);

       plane.getPlaneEq().push_back(a);
       plane.getPlaneEq().push_back(b);
       plane.getPlaneEq().push_back(c);
       plane.getPlaneEq().push_back(d);
}

void JobConstructPlane::constructPlane(WorkSpace& workspace){
    for(auto&& element : workspace.f_data){
            auto v1 = workspace.v_data.at(element.index_v1 - 1);
            auto v2 =  workspace.v_data.at(element.index_v2 - 1);
            auto v3 =  workspace.v_data.at(element.index_v3 - 1);

            auto plane_tempV = std::make_unique<Plane>(v1, v2, v3);

            calculateEquation(*plane_tempV);

            workspace.plane_dataV.push_back(*plane_tempV);
            std::cout << plane_tempV->getPlaneEq().at(0) << " " << plane_tempV->getPlaneEq().at(1) << " " <<plane_tempV->getPlaneEq().at(2) << " " << plane_tempV->getPlaneEq().at(3) <<std::endl;
     }
}

bool JobPlaneDetect::detectPlaneX(float actualX,float actualY, float actualZ, WorkSpace& workspace){ /*IN PROGRESS*/
    float x;
    for(auto&& plane : workspace.plane_dataV){
        x = (-plane.getPlaneEq().at(3) - plane.getPlaneEq().at(1)*actualY - plane.getPlaneEq().at(2)*actualZ) / float(plane.getPlaneEq().at(0));
        if(x != INFINITY && x > 0){
            workspace.stopPoint = x;
            return true;
        }
    }
    return false;
}

bool JobPlaneDetect::detectPlaneY(float actualX,float actualY, float actualZ, WorkSpace& workspace){ /*IN PROGRESS*/
    float y;
    for(auto&& plane : workspace.plane_dataV){
        y = (-plane.getPlaneEq().at(3) - plane.getPlaneEq().at(0)*actualX - plane.getPlaneEq().at(2)*actualZ) / float(plane.getPlaneEq().at(1));
        if(y != INFINITY && y > 0){
            workspace.stopPoint = y;
            return true;
        }
    }
    return false;
}

WorkSpace::WorkSpace(QString& path){
     readTxt(*this, path);
    _model.findBounds(*this);
    _material.setMaterialParamX(_model.getXDistance());
    _material.setMaterialParamY(_model.getYDistance());
    _material.setMaterialParamZ(_model.getZDistance());
    constructPlane(*this);

}

Model::Model(){

}

void Model::findBounds(WorkSpace& workSpace){
    //find high x
    xH = -100;
    for(auto&& element :  workSpace.v_data){
        if(xH < element._x) xH = element._x;
    }

    //find low x
    xL = 100;
    for(auto&& element : workSpace.v_data){
        if(xL > element._x) xL = element._x;
    }

    //find high x
    yH = -100;
    for(auto&& element : workSpace.v_data){
        if(yH < element._y) yH = element._y;
    }

    //find low y
    yL = 100;
    for(auto&& element : workSpace.v_data){
        if(yL > element._y) yL = element._y;
    }

    //find high z
    zH = -100;
    for(auto&& element : workSpace.v_data){
        if(zH < element._z) zH = element._z;
    }

    //find low z
    zL = 100;
    for(auto&& element : workSpace.v_data){
        if(zL > element._z) zL = element._z;
    }

    xDistance = abs(xH - xL);
    yDistance = abs(yH - yL);
    zDistance = abs(zH - zL);
}

float& Model::getXLow(){
    return xL;
}

float& Model::getXHigh(){
    return xH;
}

float& Model::getYLow(){
    return yL;
}

float& Model::getYHigh(){
    return yH;
}

float& Model::getZLow(){
    return zL;
}

float& Model::getZHigh(){
    return zH;
}

float& Model::getXDistance(){
    return xDistance;
}

float& Model::getYDistance(){
    return yDistance;
}

float& Model::getZDistance(){
    return zDistance;
}

Material::Material(){

}

void Material::setMaterialParamX(float x){
    _materialX = x;
}


void Material::setMaterialParamY(float y){
    _materialY = y;
}


void Material::setMaterialParamZ(float z){
    _materialZ = z;
}

void Material::setStep(float step){
    _step = step;
}

float Material::getX(){
    return _materialX;
}

float Material::getY(){
    return _materialY;
}

float Material::getZ(){
    return _materialZ;
}

float Material::getStep(){
    return _step;
}


Plane::Plane(Vertex v1, Vertex v2, Vertex v3){
    _v1 = v1;
    _v2 = v2;
    _v3 = v3;
}

std::vector<float>& Plane::getPlaneEq(){
    return planeEq;
}

Vertex& Plane::getV1(){
    return _v1;
}

Vertex& Plane::getV2(){
    return _v2;
}

Vertex& Plane::getV3(){
    return _v3;
}

void JobConvert::parseToGCode(std::shared_ptr<WorkSpace> workSpace){ /* TEST, IN PROGRESS */
    code.append("G90 \n");
    std::cout << "convert start" << std::endl;


    //start
    float step = workSpace->_material.getStep();
    float stepconst = step;
    float zActual = workSpace->_material.getZ();
    float xActual = 0;
    float yActual = 0;
    int xLayers = workSpace->_material.getX() / step;
    //int yLayers = workSpace->yDistance / step;
    int zLayers = workSpace->_material.getZ() / step;


    code.append("G0 Z" + std::to_string(workSpace->_material.getZ() + 1) + "\n");
    code.append("G0 X" + std::to_string(-1) + "\n");
    code.append("G0 Y" + std::to_string(workSpace->_material.getY() - 1) + "\n");
    code.append("G1 Z" + std::to_string(workSpace->_material.getZ()) + "\n");
    code.append("G1 X" + std::to_string(0) + "\n");
    code.append("G1 Y" + std::to_string(workSpace->_material.getY()) + "\n");
    for(int z = 0; z <= zLayers; z++){   /*NEW LAYER*/
           step = 0;
           //yActual = 0;
           for(int x = 0; x <= xLayers / 2; x++){
                       if(detectPlaneX(step, workSpace->_material.getY(), z, *workSpace) == true){
                           code.append("G1 X" + std::to_string(workSpace->stopPoint) + "\n");
                           if(detectPlaneY(step, workSpace->_material.getY(), z, *workSpace) == true){
                               code.append("G1 Y" + std::to_string(workSpace->stopPoint) + "\n");
                           }
                           else if(detectPlaneY(step, workSpace->_material.getY(), z, *workSpace) == false){
                               code.append("G1 Y" + std::to_string(0) + "\n");
                           }
                       }
                       else if(detectPlaneX(step, workSpace->_material.getY(), z, *workSpace) == false){
                           code.append("G1 X" + std::to_string(step) + "\n");
                           if(detectPlaneY(step, workSpace->_material.getY(), z, *workSpace) == true){
                               code.append("G1 Y" + std::to_string(workSpace->stopPoint) + "\n");
                           }
                           else if(detectPlaneY(step, workSpace->_material.getY(), z, *workSpace) == false){
                               code.append("G1 Y" + std::to_string(0) + "\n");
                           }
                       }

                       step = step + stepconst;

                       if(detectPlaneX(step, 0, z, *workSpace) == true){
                           code.append("G1 X" + std::to_string(step) + "\n");
                           if(detectPlaneY(step, 0, z, *workSpace) == true){
                                code.append("G1 Y" + std::to_string(workSpace->stopPoint) + "\n" );
                       }
                       else if(detectPlaneY(step, 0, z, *workSpace) == false){
                           code.append("G1 Y" + std::to_string(workSpace->_material.getY()) + "\n" );
                       }
                       }
                       else if(detectPlaneX(step, 0, z, *workSpace) == false){
                           code.append("G1 X" + std::to_string(step) + "\n");
                           if(detectPlaneY(step, 0, z, *workSpace) == true){
                                code.append("G1 Y" + std::to_string(workSpace->stopPoint) + "\n" );
                           }
                           else if(detectPlaneY(step, 0, z, *workSpace) == false){
                               code.append("G1 Y" + std::to_string(workSpace->_material.getY()) + "\n" );
                           }
                       }


               step = step + stepconst;
           }
           if(zActual == 0) break;
           zActual = zActual - stepconst;
           code.append("G1 Z" + std::to_string(zActual) + "\n");
       }
}

Process::Process(){

}

Vertex::Vertex(){

}

Vertex::Vertex(float x, float y, float z){
    setX(x);
    setY(y);
    setZ(z);
}

void Vertex::setX(float& x){
    _x = x;
}


void Vertex::setY(float& y){
    _y = y;
}


void Vertex::setZ(float& z){
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
