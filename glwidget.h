#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <memory>
#include <QWheelEvent>
class Worker;

class GLWidget: public QOpenGLWidget
{
 public:
        GLWidget(QWidget * parent = nullptr);
        ~GLWidget();
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
        void mouseMoveEvent(QMouseEvent *e) override;
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void wheelEvent(QWheelEvent *e) override;
        void setWorker(std::shared_ptr<Worker> worker);
private:
        std::shared_ptr<Worker> m_worker;
};

#endif // GLWIDGET_H
