#include <GL/glew.h>
#include "glwidget.h"
#include <cstdlib>
#include <cmath>
#include "worker.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
        QSurfaceFormat format;
        format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
        setFormat(format);
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
        if(glewInit() != GLEW_OK){
                exit(-1);
        }
        glEnable(GL_DEPTH_TEST);
        setWorker(std::shared_ptr<Worker>(new Worker(this)));
}

void GLWidget::resizeGL(int w, int h)
{
        m_worker->resizeGL(w,h);
}

void GLWidget::setWorker(std::shared_ptr<Worker> worker)
{
        m_worker = worker;
}

void GLWidget::paintGL()
{
        m_worker->paintGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
        m_worker->mouseMoveEvent(e);
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
        m_worker->mousePressEvent(e);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
        m_worker->mouseReleaseEvent(e);
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
        m_worker->wheelEvent(e);
}
