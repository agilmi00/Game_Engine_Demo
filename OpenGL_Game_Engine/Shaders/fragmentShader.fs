#version 330 core
#define MAX_DIRECTIONAL_LIGHTS 1
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

struct DirectionalLight {
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 diffuse;
};
struct PointLight {
    vec3 position;
    float diffuseIntensity;
    float maxRadius;
    vec3 diffuse;
};
struct SpotLight {
    vec3 position;
    vec3 rotation;
    float diffuseIntensity;
    float maxRadius;
    vec3 diffuse;
};
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform int numberDirectionalLights;
uniform int numberPointLights;
uniform int numberSpotLights;


in vec4 color;
in vec3 normal;
in vec3 fragPos;
in vec2 textCoord;

out vec4 fragColor;



uniform vec3 lightColor;
uniform vec3 lightColorAmbient;
uniform vec3 lightPos;

uniform vec3 viewPos;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_height0;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float CalcSmoothAttenuation(vec3 lightDir, float maxRadius);

    
void main()
{
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 norm = normalize(normal);

    vec3 result = vec3(0.f);

    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        result += (CalcDirectionalLight(directionalLights[i], norm, fragPos, viewDir));
    }
    for (int i = 0; i < numberPointLights; i++)
    {
        result += (CalcPointLight(pointLights[i], norm, fragPos, viewDir));
    }
    for (int i = 0; i < numberSpotLights; i++)
    {
        result += (CalcSpotLight(spotLights[i], norm, fragPos, viewDir)) * texture(texture_diffuse0, textCoord).rgb;
    }
    
    fragColor = vec4(result, 1.0);
}
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.diffuse * (light.ambientIntensity/10) * vec3(texture(texture_diffuse0, textCoord));
    
    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * light.diffuseIntensity * diff * vec3(texture(texture_diffuse0, textCoord));

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = (light.diffuseIntensity/3) * spec * vec3(texture(texture_specular0, textCoord));
    
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    
    vec3 lightDir = (light.position - fragPos);

    float attenuation = CalcSmoothAttenuation(lightDir, light.maxRadius);
    lightDir = normalize(lightDir);

    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 diffuse = light.diffuse * (light.diffuseIntensity * 6) * attenuation * diff * vec3(texture(texture_diffuse0, textCoord));

//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    float spec = dot(viewDir, reflectDir);
    
    vec3 specular = (light.diffuseIntensity * 2) * light.diffuse * spec * attenuation * vec3(texture(texture_specular0, textCoord));
    
    return (diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{

    vec3 lightDir = (light.position - fragPos);
    lightDir = normalize(lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    float spotFactor = dot(lightDir, normalize(light.rotation));
    float epsilon = (cos(light.maxRadius/4) - cos(light.maxRadius));
    float attenuation = clamp((spotFactor - cos(light.maxRadius))/epsilon, 0.0, 1.0);

    float attenuation2 = CalcSmoothAttenuation(lightDir, light.maxRadius);
    vec3 diffuse = (light.diffuse * (light.diffuseIntensity * 10) * diff * attenuation) * vec3(texture(texture_diffuse0, textCoord));
//    vec3 specular = (light.diffuseIntensity/5) * attenuation * vec3(texture(texture_specular0, textCoord));
    
    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = (light.diffuseIntensity * 2) * light.diffuse * spec * attenuation * vec3(texture(texture_specular0, textCoord));
    
    return (diffuse + specular);

}
float CalcSmoothAttenuation(vec3 lightDir, float maxRadius)
{
    
    float squareRadius = dot(lightDir, lightDir);
    vec2 attenConst = vec2(maxRadius*maxRadius, maxRadius);
    if (squareRadius > attenConst.x) {
        return 0;
    }
    return (clamp((squareRadius / attenConst.x) * ((2* (sqrt(squareRadius)) / attenConst.y) - 3.0) + 1.0, 0.0, 1.0));
}
