#pragma once
#ifndef HAND_HEADER
#define HAND_HEADER
#include "graphicsObject.h"


class Hand : public GraphicsObject
{
public:
    Hand() {};
    ~Hand() {};

    void initGeom();
    void setHeightPosition(float height);
    int render();

private:
    float       bottomPosition;
};

#endif