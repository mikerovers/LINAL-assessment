#ifndef LINAL_ASSESSMENT_MESH_H
#define LINAL_ASSESSMENT_MESH_H

#include <string>
#include "obj/objload.h"

class MyMesh
{
public:
    void load(std::string fileName);
    std::unique_ptr<obj::Model> model;
};


#endif //LINAL_ASSESSMENT_MESH_H
