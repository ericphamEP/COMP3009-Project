#pragma once
#ifndef SQUISH_HEADER
#define SQUISH_HEADER

#include "graphicsObject.h"


class Squish : public GraphicsObject
{
public:
    Squish() {};
    ~Squish() {};

    void initGeom(char*);
    void optimizeScale();
    void setScale(float, float, float);
    void updateSquish();
    float getTopPosition();
    int render(Shader shader);

    void setScaleMagnitude(float x, float y, float z);
    void incrementScaleMagnitude(float x, float y, float z);
    void setScaleFactor(float f);
    void incrementScaleFactor(float f);
    void incrementMinSquishFactor(float f);
    void incrementMaxSquishFactor(float f);
    void setAutoMode(bool m);
    void toggleAutoMode();
    void startSquish();

private:
    bool        squishDown;
    bool        paused;
    bool        autoMode;
    Vector3f    initScale;
    Vector3f    scaleMagnitude; // "acceleration" of scaling relative to each axis
    float       scaleFactor;    // "speed boost" to acceleration
    float       minSquishFactor;
    float       maxSquishFactor;
};

#endif