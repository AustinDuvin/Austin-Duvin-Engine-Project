#version 430


layout (location = 5) uniform vec3 cameraPos;

layout (location = 4) uniform vec3 lightLoc;

layout (location = 7) uniform sampler2D myTexture;

in vec3 fragLoc;
in vec3 fragNorm;
in vec2 fragUV;

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 V = normalize(cameraPos - fragLoc);
	vec3 H = normalize(V + L);
	vec3 N = normalize(fragNorm);

	float ambient = 0.1f;
	float diffuse = max(dot(L, N), 0);
	float specular = pow(max(dot(H, N), 0), 16);
	
	float brightness = ambient + diffuse + specular;

	vec4 texValue = texture(myTexture, fragUV);
	vec3 color = texValue.rgb;
	float alpha = texValue.a;

	gl_FragColor = vec4(brightness * color, alpha);
}