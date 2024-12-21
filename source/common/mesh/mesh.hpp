#pragma once

#include <glad/gl.h>
#include "vertex.hpp"
#include <iostream>

namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: (Req 2) Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            elementCount = static_cast<GLsizei>(elements.size()); 
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

    
            //  Generate VBO,EBO,VAO 
            //need to store data on gpu memory it is array of each element is position color normal then repeat for each vertex
            glGenBuffers(1, &VBO);   

            glGenBuffers(1, &EBO);      
            glGenVertexArrays(1, &VAO); 
            //by allowing you to store the configuration of vertex attributes and bindings in a single object
            glBindVertexArray(VAO);
            //make it the active buffer Any subsequent operations on GL_ARRAY_BUFFER will affect VBO.
            glBindBuffer(GL_ARRAY_BUFFER, VBO); 
            //make it the active buffer Any subsequent operations on GL_Element_ARRAY_BUFFER will affect EBO.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            //static_draw the data will be written once and used many times for drawing
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
            
            //1 The index of the vertex attribute same as the location specified in glEnableVertexAttribArray
            //2 The number of components per attribute 3,4 xyz xyzw
            //3The data type of each component
            //4 Specifies whether the data should be normalized
            // 5 The stride the byte offset between consecutive vertex attributes this defines the distance between the start of one vertex and the start of the next.
            //6 The offset of the first component of this attribute in the structure it is the byte offset from the beginning of the structure Vertex to the normal attribute.

            glEnableVertexAttribArray(ATTRIB_LOC_POSITION); 
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
           
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR); 
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glBindVertexArray(0); 
        }

        // this function should render the mesh
        void draw()
        {
            // TODO: (Req 2) Write this function
        std::cout << "Drawing Mesh" << std::endl;
            glBindVertexArray(VAO);
            //draw triangles,count,unsigned,no offset
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void *)0);
            glBindVertexArray(0); 
            std::cout << "Mesh Drawn" << std::endl;
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // TODO: (Req 2) Write this function
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}