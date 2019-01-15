#ifndef LINAL_ASSESSMENT_BULLET_H
#define LINAL_ASSESSMENT_BULLET_H

#include "Matrix.h"

class Bullet : public Matrix
{
public:
    explicit Bullet(const Matrix &other);
    void act() override;
    const Vector3D &getDirection() const;
    void setDirection(const Vector3D &direction);
    int getLifetime() const;
    void setLifetime(int lifetime);
private:
    Vector3D direction;
    int lifetime;
};


#endif //LINAL_ASSESSMENT_BULLET_H
