#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>

class QResizeEvent;
class Window;

//! Diese Klasse stellt letzten Endes die Verbindung zwischen OpenGL und dem Windowing-System bzw. Qt her.
//! Qt stellt darüber eine Fläche zur Verfügung, in die mit OpenGL gezeichet werden kann.
class OpenGLWidget : public QWidget
{
private:
    QWidget* mOpenGLWindowWidget;
    Window* mOpenGLWindow;

public:
    explicit OpenGLWidget(QWidget* parent = 0);
    virtual ~OpenGLWidget();
    Window* getOpenGLWindow();
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // OPENGLWIDGET_H
