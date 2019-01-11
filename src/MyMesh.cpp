#include "MyMesh.h"

MyMesh::MyMesh(std::string fileName)
{
    model = std::make_unique<obj::Model>(obj::loadModelFromFile(fileName));
}
