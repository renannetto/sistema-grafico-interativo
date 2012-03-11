#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
    Window();
    void zoomIn();
    void zoomOut();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    double fx(double x);
    double fy(double y);
private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // WINDOW_H
