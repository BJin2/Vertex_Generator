#version 430 core
in vec2 texCoord;

in vec3 N;
in vec3 E;

out vec4 fColor;

uniform sampler2D texture0;
uniform vec3 lightPosition[2];
uniform highp mat4 V;

void main()
{
	vec3 result = vec3(0);
	for(int i = 0; i < 2; i++)
	{
		vec3 LPC = (V * vec4(lightPosition[i], 1)).xyz;
		vec3 L = LPC + E;
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

		result += (ambient + diffuse + specular);
	}
	fColor = texture(texture0, texCoord) * vec4(result, 1);
}