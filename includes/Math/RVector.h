#ifndef RVector_H
#define RVector_H

class RVector
{
private:
public:
    RVector();
    RVector(float x, float y, float z = 0);
    ~RVector();
    float x;
    float y;
    float z;

    // 2D transformations
    void Translate(float ix, float iy);
    void Rotate(float angle);
};

#endif