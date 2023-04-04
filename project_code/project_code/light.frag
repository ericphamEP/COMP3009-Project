
#version 330  


//******************************************************************
// DEFINES
#define POINT_LIGHT 1
#define SPOT_LIGHT  2




//******************************************************************
// STRUCTURES

struct fragData{
	vec3 normal;
	vec3 worldPos; 
	vec4 colour;
	vec2 texCoords;
} ;

// object material 
struct material {
	vec3 ambientMaterial;		// ambient material properties
	vec3 diffuseMaterial;		// diffuse material properties
	vec3 specularMaterial;		// specular material properties
	vec3 internalRadion;		// internal radiation of colour;
};

 
// Point light properties
struct pointLight {		
	vec3 lightIntensity;		// light intensity
	vec3 ambientIntensity;		// intesity of ambient colour
	vec3 worldPos;				// position of light world coordinates
	float specularPower;		// specular light power factor
} ;

// directional light properties
struct directionalLight {
	vec3 lightIntensity;		// light intensity
	vec3 ambientIntensity;		// intesity of ambient colour
	vec3 lightDirection;		// direciton of light
	float specularPower;		// specular light power factor
};

// light attenuation  
// attenuation = 1/(a + b * d + c * d * d)
struct attenuation {
	float a; 
	float b; 
	float c;
};  
 
  
// spot light properties
struct spotLight {
	vec3 lightIntensity;		// light intensity
	vec3 ambientIntensity;		// intesity of ambient colour
	vec3 worldPos;				// location of spot light
	vec3 lightDirection;			// direction of spot light
	float spotDistLimit;		// distance limit of the spot light
	float cosSpotAlpha;			// cos of max opening of spot light (angle alpha)
	float specularPower;		// specular light power factor
}; 


//******************************************************************
// UNIFORM Variables


uniform vec3 gEyeWorldPos;					// camera/user location 
uniform pointLight gPointLight;				// point light 
uniform directionalLight gDirectionalLight;  // directonal light
uniform spotLight gSpotLight;
uniform int gLightType;	// == 1 is a point light; == 2 spot light;  == 3 directional light;  
uniform material gMaterial;			// material of object

uniform int enableAmbientLight; //0 is off, 1 is on
uniform int enableDiffuseLight;
uniform int enableSpecularLight;

uniform sampler2D texSampler; 

//******************************************************************
// VARIABLES

//in fragData{
//	vec3 normal;
//	vec3 worldPos; 
//	vec4 colour;
//} frag;
in fragData frag;  // fragment properties from the vertex shader

out vec4 outColour; // output colour

//******************************************************************
// FUNCTIONS

//-----------------------------------------------------------
// Calculate ambient light contribution
vec3 calcAmbientLight( material m,  directionalLight l)  
{  
    vec3 colour;
	
	// calculate teh abmient light contribution 
	colour = m.ambientMaterial * l.ambientIntensity * l.lightIntensity;

	return(colour);
    
}  
  
  
//-----------------------------------------------------------
// Calculate diffuse contribution
vec3 calcDiffuseLight(
	 material m, // the objct diffuse matrial
	vec3 lightVector, // the light vector, 
	vec3 normal, // the normal 
	vec3 lightIntensity)		// the diffuse light intensity  
{  
    vec3 colour;
	
	// compute the diffuse factor
	float diffuseFactor = dot(normalize(normal), -normalize(lightVector));

	// the colour contribution of the diffuse light 
	colour = m.diffuseMaterial * lightIntensity * diffuseFactor;

	return(colour);
}  
  
  
//-----------------------------------------------------------
// Calculate specular contribution
vec3 calcSpecularLight(
	 material m,	// the specular matrial
	vec3 lightVector,	// the light vector, 
	vec3 normal,		// the normal 
	vec3 lightIntensity, // the specular light intensity  
	vec3 eyeWorldPos,	// the eye/camera position
	float specPower)		//specular power
{  
	vec3 colour = vec3(0,0,0);
	
	// compute  the eye vector 
	vec3 eyeVector = normalize(-eyeWorldPos);

	// compute  the reflection vector
	vec3 reflection = reflect(-normalize(lightVector), normalize(normal));

	// compute the specular impact 
	float specImpact = pow(max(dot(reflection, eyeVector), 0.0), specPower);

	// copute the colour
	colour = lightIntensity * m.specularMaterial * specImpact;

	return(colour);
}  

//-----------------------------------------------------------
// Point light calculation

vec3 calcPointLight( material m,  pointLight l,  fragData frag, vec3 eyeWorldPos)  
{

	vec3 colour = vec3(0,0,0);
	vec3 ambientLight = vec3(0,0,0);
	vec3 diffuseLight = vec3(0,0,0);
	vec3 specularLight = vec3(0,0,0);

	vec3 lightVector = frag.worldPos - l.worldPos;

	// obtain the ambient light
	if(enableAmbientLight == 1){
		 ambientLight = m.ambientMaterial * l.ambientIntensity * l.lightIntensity;
	}

	// obtain the diffuse light
	if(enableDiffuseLight == 1){
		diffuseLight = calcDiffuseLight(m, lightVector, frag.normal, l.lightIntensity);
	}

	// obtain the specular light
	if(enableSpecularLight == 1){
		specularLight = calcSpecularLight(m, lightVector, frag.normal, l.lightIntensity, eyeWorldPos, l.specularPower);
	}

	// sum all the ligths contributions (make sure that RGB are not greater than 1)
	//	factor in the light attentuation

	vec4 textureColor = texture2D(texSampler, vec2(frag.texCoords.x, 1.0-frag.texCoords.y));

	colour = (ambientLight + diffuseLight + specularLight) * (textureColor.xyz/textureColor.w);

	return(colour);
} 





//-----------------------------------------------------------

  
void main() 
{ 
	vec4 colour = vec4(1.0, 0.5, 0.0, 1.0);
	switch(gLightType) {
	case POINT_LIGHT:
		colour = vec4(calcPointLight(gMaterial, gPointLight, frag, gEyeWorldPos), 1.0);
		break;
	case SPOT_LIGHT:
		
		break;
	}
	
	outColour = colour;
}
