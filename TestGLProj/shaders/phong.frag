 #version 440 core
 in vec3 N;
 in vec3 L;
 in vec3 E;
 in vec3 H;
 in vec4 eyeposition;

 uniform vec4 lightPosition;
 uniform mat4 Projection;
 uniform mat4 ModelView;

 uniform vec4 lightDiffuse; //intensity
 uniform vec4 lightSpecular; //shininess
 uniform vec4 lightAmbient;//color

 uniform vec4 surfaceDiffuse;
 uniform vec4 surfaceSpecular;
 uniform vec4 surfaceAmbient;
 uniform vec4  surfaceEmissive;

  uniform float shininess;

 out vec4 color2;
void main()
{
     vec3 Normal = normalize(N);
     vec3 Light  = normalize(L);
     //vec3 Light  = normalize(lightPosition - eyePosition).xyz;
     vec3 Eye    = normalize(E);
     vec3 Half   = normalize(H);
     

    float Kd = max(dot(Normal, Light), 0.0);
    float Ks = pow(max(dot(Half, Normal), 0.0), 80.0);
    float Ka = 1.0;

    //vec4 diffuse  = Kd * vec4(1,1,1,1); // white
    //vec4 specular = Ks * vec4(0,0,0,1); // black

    vec4 diffuse  = Kd * lightDiffuse*surfaceDiffuse;
    vec4 specular = Ks * lightSpecular*surfaceSpecular;
    vec4 ambient  = Ka * lightAmbient*surfaceAmbient;


    //color2 = diffuse + specular;
    gl_FragColor = surfaceEmissive + ambient + ( diffuse + specular);
}
