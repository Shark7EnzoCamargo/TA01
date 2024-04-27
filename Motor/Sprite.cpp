#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>

Sprite::~Sprite()
{
    if (vboID != 0) {
        glDeleteBuffers(1, &vboID);
    }
}

void Sprite::init(float x, float y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    if (vboID == 0) {
        glGenBuffers(1, &vboID);
    }

    Vertex vertexData[6];

    vertexData[0].setPosition(x + width, y + height);
    vertexData[0].setColor(255, 0, 0, 255);  

    vertexData[1].setPosition(x, y + height);
    vertexData[1].setColor(0, 255, 0, 255);  

    vertexData[2].setPosition(x, y);
    vertexData[2].setColor(0, 0, 255, 255);  

    vertexData[3].setPosition(x, y);
    vertexData[3].setColor(0, 0, 255, 255);  

    vertexData[4].setPosition(x + width, y);
    vertexData[4].setColor(255, 255, 0, 255);  

    vertexData[5].setPosition(x + width, y + height);
    vertexData[5].setColor(255, 0, 0, 255);  

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::Sprite()
{
}