#include "window.h"

Window::Window()
{
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
}

void Window::zoomIn(){
    double passoX = 0.1*(xMax-xMin);
    double passoY = 0.1*(yMax-yMin);
    xMin += passoX;
    xMax -= passoX;
    yMin += passoY;
    yMax -= passoY;
}

void Window::zoomOut(){
    double passoX = 0.1*(xMax-xMin);
    double passoY = 0.1*(yMax-yMin);
    xMin -= passoX;
    yMin -= passoY;
    xMax += passoX;
    yMax += passoY;
}

void Window::moveLeft(){
    double passoX = 0.1*(xMax-xMin);
    xMin -= passoX;
    xMax -= passoX;
}

void Window::moveRight(){
    double passoX = 0.1*(xMax-xMin);
    xMin += passoX;
    xMax += passoX;
}

void Window::moveDown(){
    double passoY = 0.1*(yMax-yMin);
    yMin -= passoY;
    yMax -= passoY;
}

void Window::moveUp(){
    double passoY = 0.1*(yMax-yMin);
    yMin += passoY;
    yMax += passoY;
}

double Window::fx(double x){
    return (x - xMin) * 640 / (xMax - xMin);
}

double Window::fy(double y){
    return (yMax - y) * 480 / (yMax - yMin);
}
