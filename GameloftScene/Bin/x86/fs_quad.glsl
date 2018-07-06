#version 330 core
uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;

varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;

uniform sampler2D tex0;

void main(){
	gl_FragColor = texture2D(tex0,vecUVCoords);
	gl_FragDepth = gl_FragCoord.z;
}




