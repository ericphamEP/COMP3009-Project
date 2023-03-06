#pragma once
#ifndef BOX_HEADER
#define BOX_HEADER

//=============================================================================
// cube.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a.  class for rendering a subobject in a hierarchical object.  In this case it is a floor in a building 
//
//
// Description:
//--------------
//  This class defines a floor in a two story building. 
//
//	The base geometry is a cube
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================


// INCLUDES 

#include "graphicsObject.h"
#include "model.h"


class Box : public GraphicsObject
{
public:
    Box() {};
    ~Box() {};

    void initGeom();
    int render();



private:
    Vertices    m_vertices;
    Indices		m_indices;
};

#endif