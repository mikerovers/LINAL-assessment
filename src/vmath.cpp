#include "vmath.h"

Vector3D getMiddle(Vector3D topLeft, Vector3D bottomRight)
{
    Vector3D m{};

    m.setX((topLeft.getX() + bottomRight.getX()) / 2);
    m.setY((topLeft.getY() + bottomRight.getY()) / 2);
    m.setZ((topLeft.getZ() + bottomRight.getZ()) / 2);

    return m;
}