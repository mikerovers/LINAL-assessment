#ifndef LINAL_ASSESSMENT_MESH_H
#define LINAL_ASSESSMENT_MESH_H

#include <string>
#include "obj/objload.h"

class MyMesh
{
public:
    explicit MyMesh(std::string fileName);
    obj::Model &getModel()
    { return *model; }
private:
    std::unique_ptr<obj::Model> model;
};


#endif //LINAL_ASSESSMENT_MESH_H
