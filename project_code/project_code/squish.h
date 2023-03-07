#pragma once
#ifndef SQUISH_HEADER
#define SQUISH_HEADER

// INCLUDES 

#include "graphicsObject.h"
#include "geometry_common.h"


class Squish : public GraphicsObject
{
public:
    Squish() {};
    ~Squish() {};

    void initGeom(char*);
    void setScale(float, float, float);
    void updateSquish(float);
    int render();



private:
    float       bottomPosition;
    bool        squishDown;
    Vector3f    initScale;
    Vertices    m_vertices;
    Indices		m_indices_tri;
    Indices		m_indices_quad;
    Indices		m_indices_pent;
};

#endif