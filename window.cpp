#include "window.h"

Window::Window()
{
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
}

void Window::zoomIn(){
    if(xMax - xMin > 41 && yMax - yMin > 31){
        xMin += 20;
        xMax -= 20;
        yMin += 15;
        yMax -= 15;
    }
}

void Window::zoomOut(){
    xMin -= 20;
    yMin -= 15;
    xMax += 20;
    yMax += 15;
}

void Window::moveLeft(){
    xMin -= 20;
    xMax -= 20;
}

void Window::moveRight(){
    xMin += 20;
    xMax += 20;
}

void Window::moveDown(){
    yMin -= 15;
    yMax -= 15;
}

void Window::moveUp(){
    yMin += 15;
    yMax += 15;
}

double Window::fx(double x){
    return (x - xMin) * 640 / (xMax - xMin);
}

double Window::fy(double y){
    return (yMax - y) * 480 / (yMax - yMin);
}
