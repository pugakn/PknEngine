uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;
uniform vec4 CameraPosition;

varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;
varying vec4 Norm;

uniform sampler2D tex0;

vec3 CalculateDiffuse(float NdL, vec3 albedoColor){
	return NdL * albedoColor;
}
vec3 CalculateSpecular(float NdH, vec3 specularColor ) {
  return pow(NdH,2) * specularColor;
}
vec3 CalculateLight(vec3 lightPos, vec3 lightColor,vec3 albedo,vec3 specularColor, vec3 eyeDir){
	vec3 lightDir = normalize(lightPos - WorldPos);
	float lightRadius = 10;
	
	vec3 H = normalize(eyeDir+lightDir);
	
	float NdL = saturate(dot(Norm, lightDir));
	float NdH = saturate(dot( Norm, H ));
	
	vec3 diffuse = CalculateDiffuse(NdL,albedo);
	vec3 specular = CalculateSpecular(NdH,specularColor);
	return NdL * lightColor * (diffuse + specular);
}

void main(){
    vec3 AmbientColor = vec3(0.1,0.1,0.1);
	
	vec3 lightPos = vec3(0,5,5);
    vec3 eyeDir = normalize(CameraPosition - WorldPos);
	vec3 Albedo = texture2D(tex0,vecUVCoords).xyz;
	vec3 SpecularColor = vec3(1,1,1);
	
	vec3 Ambient = AmbientColor * Albedo;
	vec3 light1 = CalculateLight(lightPos,vec3(1,1,1),Albedo,vec3(1,1,1),eyeDir);
	
	gl_FragColor =  vec4(light1 + Ambient  ,1);
}




