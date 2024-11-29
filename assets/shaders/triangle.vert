#version 330

// This vertex shader should be used to render a triangle whose normalized device coordinates are:
// (-0.5, -0.5, 0.0), ( 0.5, -0.5, 0.0), ( 0.0,  0.5, 0.0)
// And it also should send the vertex color as a varying to the fragment shader where the colors are (in order):
// (1.0, 0.0, 0.0), (0.0, 1.0, 0.0), (0.0, 0.0, 1.0)

out Varyings {
    vec3 color;
} vs_out;

// Currently, the triangle is always in the same position, but we don't want that.
// So two uniforms should be added: translation (vec2) and scale (vec2).
// Each vertex "v" should be transformed to be "scale * v + translation".
// The default value for "translation" is (0.0, 0.0) and for "scale" is (1.0, 1.0).

uniform vec2 translation = vec2(0.0, 0.0);
uniform vec2 scale = vec2(1.0, 1.0);

//TODO: (Req 1) Finish this shader

void main(){
    //triangle we will have of vertices (-0.5, -0.5, 0.0), ( 0.5, -0.5, 0.0), ( 0.0,  0.5, 0.0)
    vec3 triangle[3] = vec3[3](
        vec3(-0.5, -0.5, 0.0),
        vec3( 0.5, -0.5, 0.0), 
        vec3( 0.0,  0.5, 0.0)
    );
    //colors for each vertex (1.0, 0.0, 0.0), (0.0, 1.0, 0.0), (0.0, 0.0, 1.0)
    vec3 colors[3] = vec3[3](
        vec3(1.0, 0.0, 0.0), 
        vec3(0.0, 1.0, 0.0), 
        vec3(0.0, 0.0, 1.0)
    );
    //get each vertex by gl_VertexID that get the index of the vertex now

    vec3 vertex = triangle[gl_VertexID];
    //apply scale and transformation
    vertex.xy =vertex.xy* scale+translation;

    // return in gl_Position the position in 4d with w=1
    gl_Position = vec4(vertex, 1.0);
    //return the color of the vertex in the struct of vs_out
    vs_out.color = colors[gl_VertexID];

}