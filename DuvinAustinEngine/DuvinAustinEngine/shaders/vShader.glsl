#version 430

// Model Coordinates
layout (location = 0) in vec3 position;
layout (location = 3) in vec3 vertNorm;
layout (location = 6) in vec2 modelUV;

layout (location = 1) uniform mat4 cameraMat;
//layout (location = 2) uniform mat4 modelWorldMat;

layout (location = 8) uniform mat4 worldmodel;

// World Coordinates
out vec3 fragLoc;
out vec3 fragNorm;
out vec2 fragUV;

vec4 worldPosition;
vec4 worldNorm;

void main()
{
	fragUV = modelUV;
	fragLoc = position;
	fragNorm = vertNorm;

	// Set position to model world space
	worldPosition = vec4(fragLoc, 1);
	worldPosition = worldmodel * worldPosition;

	// Set normals to model world space
	worldNorm = vec4(fragNorm, 1);
	worldNorm = transpose(inverse(worldmodel)) * worldNorm;

	// Set original vectors equal to model world vectors
	fragLoc = worldPosition.xyz;
	fragNorm = worldNorm.xyz;

	gl_Position = cameraMat * worldPosition;//vec4(position, 1);
}