uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;
uniform mat4 LightVP;
uniform vec4 CameraPosition;
uniform vec4 LightPositions[2];
uniform vec4 LightColors[2];
uniform vec4 LightRadius[2];


varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;
varying vec4 Norm;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform samplerCube tex2;

void main(){
	vec3 I = normalize(WorldPos - CameraPosition);
    vec3 R = reflect(I, Norm);
	//R.x = -R.x;
	vec3 Env = textureCube(tex2,R).xyz;
	gl_FragColor =  vec4(Env.xyz,1);
}




