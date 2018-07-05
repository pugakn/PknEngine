attribute vec3 Position;
attribute vec3 Normal;
attribute vec2 Coords;


varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;
varying vec4 Norm;

uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;
uniform vec4 CameraPosition;

void main(){
	vecUVCoords = Coords;	
	WorldPos = World*vec4(Position,1);
	Pos = WVP * vec4(Position,1);
	Norm = World * vec4(Normal,1);
	gl_Position = Pos;
}