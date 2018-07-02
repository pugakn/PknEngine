attribute vec4 Position;
attribute vec2 Coords;

varying vec2 vecUVCoords;
varying vec4 Pos;

uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;

void main(){
	vecUVCoords = Coords;	
	Pos = Position;
	gl_Position = Pos;
}