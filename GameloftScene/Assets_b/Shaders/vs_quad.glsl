attribute vec3 Position;
attribute vec3 Normal;
attribute vec2 Coords;

varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;

uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;

void main(){
	vecUVCoords = Coords;	
	//vecUVCoords.y *= -1;
	WorldPos = World * vec4(Position,1);
	Pos = WVP * vec4(Position,1);
	gl_Position = Pos;
}