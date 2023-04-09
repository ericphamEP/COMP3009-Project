#pragma once

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

// INCLUDES
#include "GL/nuss_vector.h"
#include "shader.h"

// STRUCTURES

typedef struct pointLight {
	Vector3f lightIntensity;		// light intensity
	Vector3f ambientIntensity;		// intesity of ambient colour
	Vector3f worldPos;				// position of the light in the world
	float specularPower;			// specular light power factor
	int enableAmbientLight;			// determines whether to use the ambient light compnent
	int enableDiffuseLight;			// determines whether to use the diffuse light compnent
	int enableSpecularLight;		// determines whether to use the specular light compnent
} PointLight;

// attenuation = 1/(a + b * d + c * d * d)
typedef struct attenuation {
	float a;
	float b;
	float c;
}Attenuation;

typedef struct spotLight {
	Vector3f lightIntensity;		// light intensity
	Vector3f ambientIntensity;		// intesity of ambient colour
	Vector3f worldPos;				// location of spot light
	Vector3f lightDirection;		// direction of spot light
	float spotdDistLimit;			// distance limit of the spot light
	float cosSpotAlpha;				// cos of max opening of spot light (angle alpha)
	float specularPower;			// specular light power factor
}SpotLight;


//DEFINES
#define POINT_LIGHT 1
#define SPOT_LIGHT 2


class Light
{
public:
	Light();
	~Light();
	int loadPointLight(Shader shader);
	int setPointLight(PointLight light);
	int setSpotLight(SpotLight light);
	int enablePointLightCompnents(int enableAmbientLight, int enableDiffuseLight, int enableSpecularLight);
	int toggleLightComponents(int ambient, int diffuse, int specular);
	void specularIntensity(float delta);

private:
	PointLight pointLight;
};

#endif