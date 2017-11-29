#version 330 core

//by Yao Luo 11/29/17

in vec3 Normal;
in vec3 Position;

struct SpecPara{
    float specMax;
    float specMin;
};

struct Material{
    vec4 ambient;//Ka color
    mat4 diffuse;//Kd color
    mat4 specular;//Ks color
    SpecPara specp;
    float kd;
    float ks;
    //vec4 refractInd;//(refractive index, FresnelA, FresnelB, FresnelC)
};

struct Light{
    vec3 position;
    vec4 color;
};

uniform vec3 cameraPos;
uniform Material material;
uniform Light light;
uniform samplerCube skybox;

uniform float ratio;
uniform float a;
uniform float b;
uniform float c;

void main()
{
    // ambient
    vec4 ambient = material.ambient;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - Position);
    float td = dot(norm, lightDir)*0.5 + 0.5;
    vec4 diffuse = (material.kd * td)  * (material.diffuse * light.color);
    
    // specular
    vec3 viewDir = normalize(cameraPos - Position);
    vec3 reflectDirLs = reflect(-lightDir, norm); //light sourse reflection
    float ts = smoothstep(material.specp.specMin,material.specp.specMax,dot(viewDir, reflectDirLs)*0.5+0.5);//interpolate between [0,1]
    vec4 specular = (material.ks * ts)  * (material.specular * light.color);
    
    // Set fragment color from texture
    vec3 I = normalize(Position - cameraPos);
    vec3 RayReflect = reflect(I, normalize(Normal));
    vec3 RayRefract = refract(I, normalize(Normal),ratio);
    vec4 ColorReflect = vec4(texture(skybox, RayReflect).rgb, 1.0);
    vec4 ColorRefract = vec4(texture(skybox, RayRefract).rgb, 1.0);
    //x*(1-a) + y*a
    // incident angle
    float Iang = dot(normalize(Normal), -I);
    float FInd = 0.0;
    if (Iang < 0){
      gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    }
    else {
      if((1-Iang) < b){
        FInd = -(a/b) * (1-Iang) + a;
      }
      else{
        if((1-Iang) < c){
          FInd = (1-Iang-b)/(c-b);
        }
        else{
          FInd = 1.0;
        }
      }
      vec4 mixRef = mix(ColorRefract, ColorReflect, FInd);
      vec4 result = ambient + diffuse + specular + material.ks * mixRef;
      result = result * vec4(1/result.w);
      gl_FragColor = result;
    }
}

