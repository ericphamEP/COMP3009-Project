#include "stdio.h"
#include "stdlib.h"
#include "Light.h"


Light::Light()
{

}

Light::~Light()
{

}

// Purpose: loads the light information to the shader
int Light::loadPointLight(Shader shader)
{

	// load point light
	shader.copyIntToShader(POINT_LIGHT, "gLightType");

	// load the ambient light
	shader.copyFloatVectorToShader((float*)&pointLight.ambientIntensity, 1, 3, "gPointLight.ambientIntensity");

	// load the light intensity
	shader.copyFloatVectorToShader((float*)&pointLight.lightIntensity, 1, 3, "gPointLight.lightIntensity");
	// load the light position
	shader.copyFloatVectorToShader((float*)&pointLight.worldPos, 1, 3, "gPointLight.worldPos");
	// load the specular light power
	shader.copyFloatToShader(pointLight.specularPower, "gPointLight.specularPower");
	// load which light components to use
	shader.copyIntToShader(pointLight.enableAmbientLight, "enableAmbientLight");
	shader.copyIntToShader(pointLight.enableDiffuseLight, "enableDiffuseLight");
	shader.copyIntToShader(pointLight.enableSpecularLight, "enableSpecularLight");

	return 0;
}

// Set the point light
int Light::setPointLight(PointLight light)
{
	pointLight.lightIntensity = light.lightIntensity;
	pointLight.ambientIntensity = light.ambientIntensity;
	pointLight.worldPos = light.worldPos;
	pointLight.specularPower = light.specularPower;
	return 0;
}

// Set the point light components
int Light::enablePointLightCompnents(int enableAmbientLight, int enableDiffuseLight, int enableSpecularLight)
{
	pointLight.enableAmbientLight = enableAmbientLight;
	pointLight.enableDiffuseLight = enableDiffuseLight;
	pointLight.enableSpecularLight = enableSpecularLight;
	return 0;
}

// Set the spot light
int Light::setSpotLight(SpotLight light)
{
	return 0;
}

// Toggle light components
int Light::toggleLightComponents(int ambient, int diffuse, int specular) {
	int a, d, s;
	
	a = (ambient + pointLight.enableAmbientLight) % 2;
	d = (diffuse + pointLight.enableDiffuseLight) % 2;
	s = (specular + pointLight.enableSpecularLight) % 2;

	enablePointLightCompnents(a, d, s);
	return 0;
}

// Adjust specular intensity
void Light::specularIntensity(float delta) {
	if ((pointLight.specularPower + delta) < 0) {
		pointLight.specularPower = 0;
	}
	else {
		pointLight.specularPower += delta;
	}
	printf("specular intensity: %.2f\n", pointLight.specularPower);
}
