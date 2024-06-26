#version 330 core

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   sampler2D emission;
   float shininess;
};

struct DirLight {
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight {    
   vec3 position;
   
   float constant;
   float linear;
   float quadratic;  

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};  

struct SpotLight{
   vec3 position;
   vec3 direction;

   float cutOff; // For spotlight light
   float outerCutOff;

   float constant;
   float linear;
   float quadratic;  

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


#define NR_POINT_LIGHTS 4  

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform Material material;
uniform float time;
uniform vec3 viewPos;

in vec3 FragPos; // In world space
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
   vec3 norm = normalize(Normal);
   vec3 viewDir = normalize(viewPos-FragPos);
   
   // phase 1: Directional lighting
   vec3 result = calcDirLight(dirLight, norm, viewDir);
   // phase 2: Point lights
   for(int i = 0; i < NR_POINT_LIGHTS; i++)
      result += calcPointLight(pointLights[i], norm, FragPos, viewDir);

   result += calcSpotLight(spotLight, norm, FragPos, viewDir);

   // Emission light
   // vec3 emission = mix(vec3(0.f), vec3(texture(material.emission, vec2(TexCoords.x, TexCoords.y + time * 0.2))), floor(vec3(1.f) - texture(material.specular, TexCoords).r)); // the floor() result is equal to 1 if the specular value is null, 0 otherwise


   FragColor = vec4(result, 1.0f);

}



vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
   vec3 lightDir = normalize(-light.direction);

   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   
   // combine results
   vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
   return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);
   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // attenuation
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));    
   // combine results
   vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
   ambient  *= attenuation;
   diffuse  *= attenuation;
   specular *= attenuation;
   return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);

   // Spotlight
   float theta     = dot(lightDir, normalize(-light.direction));
   float epsilon   = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // attenuation
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));    
   // combine results
   vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
   ambient  *= attenuation;
   diffuse  *= attenuation * intensity;
   specular *= attenuation * intensity;
   return (ambient + diffuse + specular);
}