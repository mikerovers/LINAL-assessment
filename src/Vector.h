#ifndef LINAL_ASSESSMENT_VECTOR_H
#define LINAL_ASSESSMENT_VECTOR_H

#include <math.h>

class Vector
{
public:
    Vector(double x = 0, double = 0);
    Vector&operator+(const Vector &other);
    Vector&operator-(const Vector &other);
    Vector&operator*(const int scalar);

    double length() const;
    void normalize();

    double getX() const;
    double getY() const;
private:
    double x;
    double y;
};


#endif //LINAL_ASSESSMENT_VECTOR_H
