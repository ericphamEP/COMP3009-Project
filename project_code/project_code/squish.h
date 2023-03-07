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
    int render();



private:
    Vertices    m_vertices;
    Indices		m_indices_tri;
    Indices		m_indices_quad;
};

#endif