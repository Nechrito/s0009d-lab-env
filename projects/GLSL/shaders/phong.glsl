#shader vertex
#version 430 core
layout (location = 0) in vec4 inPos;
layout (location = 1) in vec4 inNormal;
layout (location = 2) in vec2 inTextureCoords;

out vec3 ModelPosition;
out vec3 Normal;
out vec2 TextureCoords;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat4 Model;

void main()
{
	gl_Position = Projection * ModelView * vec4(inPos.x, inPos.y, inPos.z, 1.0);
	ModelPosition = vec3(Model * inPos);
	Normal = mat3(transpose(inverse(Model))) * inNormal.xyz;
    TextureCoords = inTextureCoords;
}

#shader fragment
#version 430 core

struct Material 
{
	vec3 AmbientColor;
	vec3 DiffuseColor;
	vec3 SpecularColor;
	float SpecularExponent;
	float OpticalDensity;
	float Dissolve;
	float Illumination;
};

struct Textures
{
	sampler2D Diffuse;
	sampler2D Normal;
	sampler2D Specular;
	sampler2D Mask;
};

struct DirectLightAttributes
{
	vec3 direction;
};

struct SpotLightAttributes
{
	vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float outerCutOff;
	float innerCutOff;
};

struct PointLightAttributes 
{
	float constant;
	float linear;
	float quadratic;
};

struct Light
{
	vec3 Color;
	vec3 Position;
	vec3 Direction;
	float Intensity;
};

out vec4 ResultColor;

in vec3 ModelPosition;
in vec3 Normal;
in vec2 TextureCoords;

uniform vec3 CameraPosition;
uniform Material material;
uniform Textures textures;

// lightning members
uniform float GammaValue;
uniform int LightType;
uniform Light light; 

uniform DirectLightAttributes directAttribs;
uniform PointLightAttributes  pointAttribs;
uniform SpotLightAttributes   spotAttribs;

vec3  saturate(vec3  value) { return clamp(value, 0, 1); }
vec4  saturate(vec4  value) { return clamp(value, 0, 1); }
float saturate(float value) { return clamp(value, 0, 1); }

vec4 Combine(vec3 ambient, vec3 diffuse, vec3 specular);

vec4 GetDirectLight(vec3 l, vec3 n, vec3 v);
vec4 GetPointLight (vec3 l, vec3 n, vec3 v);
vec4 GetSpotLight  (vec3 l, vec3 n, vec3 v);

void main()
{
    vec3 v = normalize(CameraPosition - ModelPosition);
    vec3 l = normalize(light.Position - ModelPosition);
	vec3 n = normalize(Normal);

	switch (LightType)
	{
		case 0: ResultColor = GetDirectLight(l, n, v); break;
		case 1: ResultColor = GetPointLight (l, n, v); break;
		case 2: ResultColor = GetSpotLight  (l, n, v); break;
	}
}

vec4 Combine(vec3 ambient, vec3 diffuse, vec3 specular)
{
	vec4 modelColor = texture(textures.Diffuse, TextureCoords);

	// combines the colors with the texture, whereas the colours are clamped by the light intensity
    vec3 saturated = (ambient + diffuse + specular) * light.Intensity * modelColor.rgb;
	
	vec3 gammaCorrection = vec3(1.0 / GammaValue);

	return vec4(pow(saturated, gammaCorrection), modelColor.a);
}

// Emits parallel light rays in a single direction towards infinity
vec4 GetDirectLight(vec3 l, vec3 n, vec3 v)
{
	vec3 ambient = vec3(0.1) * light.Color * material.AmbientColor;
    vec3 diffuse = light.Color * material.DiffuseColor * max(dot(n, l), 0.0); 
 
	// Specular highlights, reflects the light direction around our Normals,
	// then we retrieve the distance between the reflection and view which decides the strength 
    vec3 reflection = reflect(l, -n);  
    float lambertian = pow(max(dot(v, reflection), 0.0), material.SpecularExponent);
    vec3 specular = lambertian * light.Color * material.SpecularColor;  

	return Combine(ambient, diffuse, specular);
}

// Imagine a light bulb, emits light in all directions 
vec4 GetPointLight(vec3 l, vec3 n, vec3 v)
{
	vec3 ambient = vec3(0.1) * light.Color * material.AmbientColor;
    vec3 diffuse = light.Color * material.DiffuseColor * max(dot(n, l), 0.0); 
 
    vec3 reflection = reflect(l, -n);  
    float lambertian = pow(saturate(dot(v, reflection)), material.SpecularExponent);
    vec3 specular = lambertian * light.Color * material.SpecularColor;  

	// attenuation
	float dist = length(light.Position - ModelPosition);
	float attenuation = 1.0 / (pointAttribs.constant + pointAttribs.linear * dist + pointAttribs.quadratic * (dist * dist));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return Combine(ambient, diffuse, specular);
}

vec4 GetSpotLight(vec3 l, vec3 n, vec3 v)
{
	vec3 ambient = vec3(0.1) * light.Color * material.AmbientColor;

    vec3 diffuse = light.Color * material.DiffuseColor * max(dot(n, l), 0.0); 

	vec3 reflection = reflect(-l, n);  
    vec3 specular = pow(max(dot(v, reflection), 0.0), material.SpecularExponent) * light.Color * material.SpecularColor;

	// Soft edges
	float theta = dot(l, normalize(-spotAttribs.direction));
	float epsilon = spotAttribs.innerCutOff - spotAttribs.outerCutOff;
	float intensity = clamp((theta - spotAttribs.outerCutOff) / epsilon, 0.0, 1.0); 
	diffuse *= intensity;
	specular *= intensity;

	// Attenuation
	float dist = length(light.Position - ModelPosition);
	float attenuation = 1.0f / (spotAttribs.constant + spotAttribs.linear * dist + spotAttribs.quadratic * (dist * dist));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return Combine(ambient, diffuse, specular);
}