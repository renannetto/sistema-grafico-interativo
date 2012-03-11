#include "window.h"

Window::Window()
{
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
}

void Window::zoomIn(){
    xMin += 2.5;
    yMin += 2.5;
    xMax -= 2.5;
    yMax -= 2.5;
}

void Window::zoomOut(){
    xMin -= 2.5;
    yMin -= 2.5;
    xMax += 2.5;
    yMax += 2.5;
}

void Window::moveLeft(){
    xMin -= 5;
    xMax -= 5;
}

void Window::moveRight(){
    xMin += 5;
    xMax += 5;
}

void Window::moveDown(){
    yMin -= 5;
    yMax -= 5;
}

void Window::moveUp(){
    yMin += 5;
    yMax += 5;
}

double Window::fx(double x){
    return (x - xMin) * 640 / (xMax - xMin);
}

double Window::fy(double y){
    return (yMax - y) * 480 / (yMax - yMin);
}
