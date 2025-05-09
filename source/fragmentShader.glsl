#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightDir;   // light direction
uniform vec3 lightColor; // light color
uniform vec3 objectColor;

void main()
{
    // Ambient light
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(-lightDir); // opposite of light direction
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
