#ifndef WORKER_H
#define WORKER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <QMouseEvent>

class Shader;

class GLWidget;
class Worker
{
public:
        Worker(GLWidget *w);
        virtual ~Worker();
        virtual void paintGL();
        virtual void resizeGL(int w, int h);
        virtual void mouseMoveEvent(QMouseEvent *e);
        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseReleaseEvent(QMouseEvent *e);
        virtual void wheelEvent(QWheelEvent *e);
private:
        void drawTriangle();
        void initializeTriangles();
private:
        unsigned m_VBO, m_VAO;
protected:
        glm::mat4 m_modelViewProjection;
        glm::mat4 m_transformation;
        Shader *m_shader;
        GLWidget *m_GLWidget;
        glm::vec3 m_rotateStart;
        static const glm::vec3 INVALID_VEC3;
};

#endif // WORKER_H
