#version 430 core
in vec2 texCoord;

in vec3 N;
in vec3 L;
in vec3 E;

out vec4 fColor;

uniform sampler2D texture0;


void main()
{
	vec3 light = vec3(1);
	vec3 n = normalize(N);
	vec3 l = normalize(L);
	vec3 e = normalize(E);

	float ambientStrength = 0.2;
	vec3 ambient = light * ambientStrength;

	float diff = max(dot(n, l), 0.0);
	vec3 diffuse = light * diff;

	float specularStrength = 1.5;
	vec3 r = reflect(-l, n);
	float spec = pow(max(dot(e, r), 0.0), 100);
	vec3 specular = specularStrength * spec * light;

	vec3 result = (ambient + diffuse + specular);

	fColor = texture(texture0, texCoord) * vec4(result, 1);
}