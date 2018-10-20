#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
class GLWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
private:
        void setMenu();
private:
        Ui::MainWindow *ui;
        GLWidget * m_centralWidget;
};

#endif // MAINWINDOW_H
