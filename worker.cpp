#include <GL/glew.h>
#include "worker.h"
#include "glwidget.h"
#include "shader.h"
#include <iostream>
#include <QDebug>
#include <QRect>
using namespace  std;


const glm::vec3 Worker::INVALID_VEC3(99999.f,99999.f,99999.f);
Worker::Worker(GLWidget *w):m_GLWidget(w)
{
        m_shader = nullptr;
        m_VBO = 0;
        m_VAO = 0;
        m_rotateStart = INVALID_VEC3;
        m_transformation = glm::mat4(1.f);
        initializeTriangles();
}

Worker::~Worker()
{
    if (m_shader)
        delete m_shader;
}

void Worker::initializeTriangles()
{
    m_shader = new Shader("../GraphicsLab/v.vert", "../GraphicsLab/f.frag");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5,0.5,0.5,1);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    {
        float vertices[]={
            0,0,0,
            1,0,0,
            0,1,0,

            1,0,0,
            0,1,0,
            0,0,1
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        int loc = m_shader->get_attrib_location("v_pos");
        glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
        glEnableVertexAttribArray(loc);
        loc = m_shader->get_attrib_location("v_color");
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)(sizeof(float)*3*3));
        glEnableVertexAttribArray(loc);
    }
    glBindVertexArray(0);
}

void Worker::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
    glm::mat4 mv = glm::lookAt(
                glm::vec3(0.f, 0.f, 100.f),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.f, 1.f, 0.f)
                );
    float fovy = atan(1.0f/100.f) *2.f;
    float aspect = (float)w/(float)h;
    glm::mat4 pj = glm::perspective(fovy, aspect, 1.f, 1000.f);
    m_modelViewProjection = pj * mv;
}

void Worker::drawTriangle()
{
        m_shader->use();
        glBindVertexArray(m_VAO);
        glm::mat4 mat = m_modelViewProjection * m_transformation;
        glUniformMatrix4fv(m_shader->get_uniform_location("modelViewProjection"), 1, GL_FALSE, &mat[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_shader->unuse();
}

void Worker::paintGL()
{
    glClear(
            GL_COLOR_BUFFER_BIT|
            GL_DEPTH_BUFFER_BIT
           );
    drawTriangle();
}


void Worker::mouseMoveEvent(QMouseEvent *e)
{
    if (INVALID_VEC3 != m_rotateStart && e->modifiers() == Qt::ControlModifier) {
            QRect rect = m_GLWidget->rect();
            float x = e->pos().x();
            float y = rect.height() - e->pos().y() -1;
            x = x / rect.width() *2.f - 1.f;
            y = y / rect.height() *2.f -1.f;
            float z = x *x + y*y;
            if (z >= 1.f) {
                    x/=sqrt(z);
                    y/=sqrt(z);
                    z= 0;
            }else{
                    z = sqrt(1.f - z);
            }
            glm::vec3 rotateEnd;
            rotateEnd[0]  = x;
            rotateEnd[1]  = y;
            rotateEnd[2]  = z;

            glm::vec3 axis = glm::cross(m_rotateStart, rotateEnd);
            float angle = glm::dot(m_rotateStart, rotateEnd);
            if (angle >1.f)
                    angle = 1.f;
            else if (angle <-1.f)
                    angle = -1.f;
            angle = acos(angle);
            m_transformation =  glm::rotate(glm::mat4(1.f), angle, axis) * m_transformation;
            m_rotateStart = rotateEnd;
            m_GLWidget->update();
    }
}

void Worker::mousePressEvent(QMouseEvent *e)
{
        if (e->modifiers() == Qt::ControlModifier) {
                QRect rect = m_GLWidget->rect();
                float x = e->pos().x();
                float y = rect.height() - e->pos().y() -1;
                x = x / rect.width() *2.f - 1.f;
                y = y / rect.height() *2.f -1.f;
                float z = x *x + y*y;
                if (z >= 1.f) {
                        x/=sqrt(z);
                        y/=sqrt(z);
                        z= 0;
                }else{
                        z = sqrt(1.f - z);
                }
                m_rotateStart[0]  = x;
                m_rotateStart[1]  = y;
                m_rotateStart[2]  = z;
        }
}

void Worker::mouseReleaseEvent(QMouseEvent *e)
{
        m_rotateStart = INVALID_VEC3;
}

void Worker::wheelEvent(QWheelEvent *e)
{
        if (e->delta() > 0){
                glm::mat4 scale = glm::mat4(0.9f);
                scale[3][3] = 1.f;
                m_transformation *= scale;
        }else if (e->delta() < 0){
                glm::mat4 scale = glm::mat4(1.1f);
                scale[3][3] = 1.f;
                m_transformation *= scale;
        }
        m_GLWidget->update();
}
