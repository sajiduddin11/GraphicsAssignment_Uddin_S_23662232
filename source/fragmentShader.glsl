#version 330 core

in vec3 FragPos;  
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;  // Add the view position (camera position)

void main()
{
    // Normalize inputs
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-lightDir);  // light coming *from* the direction

    // Ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;  // You can adjust this value
    vec3 viewDir = normalize(viewPos - FragPos);  // Calculate the view direction
    vec3 reflectDir = reflect(-lightDirection, norm);  // Reflect light direction over normal
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Calculate specular intensity
    vec3 specular = specularStrength * spec * lightColor;

    // Final color
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
