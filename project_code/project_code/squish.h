#pragma once
#ifndef SQUISH_HEADER
#define SQUISH_HEADER

// INCLUDES 

#include "graphicsObject.h"


class Squish : public GraphicsObject
{
public:
    Squish() {};
    ~Squish() {};

    void initGeom(char*);
    void optimizeScale();
    void setScale(float, float, float);
    void updateSquish(float);
    float getTopPosition();
    int render();
    int render(Shader shader);



private:
    bool        squishDown;
    Vector3f    initScale;
};

#endif