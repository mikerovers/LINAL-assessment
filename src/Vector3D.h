#ifndef LINAL_ASSESSMENT_VECTOR3D_H
#define LINAL_ASSESSMENT_VECTOR3D_H


class Vector3D
{
public:
    explicit Vector3D(double x = 0, double y = 0, double z = 0);
    Vector3D&operator+(const Vector3D &other);
    Vector3D&operator-(const Vector3D &other);
    Vector3D&operator*(int scalar);
    void print() const;
    double length() const;
    void normalize();

    double getX() const { return x; }
    double getY() const { return y; };
    double getZ() const { return z; };
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setZ(double newZ) { z = newZ; }
private:
    double x;
    double y;
    double z;
};


#endif //LINAL_ASSESSMENT_VECTOR3D_H
