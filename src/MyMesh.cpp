#include "MyMesh.h"

void MyMesh::load(std::string fileName)
{
    model = std::make_unique<obj::Model>(obj::loadModelFromFile(fileName));
//    std::cout << *model << std::endl;
}
