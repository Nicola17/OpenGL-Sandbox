#version 330 core

in vec4 VertexPosition;
in vec3 VertexNormal;
in vec4 VertexColor;

out vec4 Color;

void main(){
    Color = vec4(normalize(abs(VertexNormal)),1.0);
    gl_Position = gl_ModelViewProjectionMatrix * VertexPosition;
}


