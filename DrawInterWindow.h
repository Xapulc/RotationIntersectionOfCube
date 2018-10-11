#ifndef DRAWINTERWINDOW_H
#define DRAWINTERWINDOW_H

#include "gwindow.h"
#include "R3Graph.h"
#include "Rotation.h"
#include <iostream>

class DrawInterWindow: public GWindow {
private:
	InterPlane plane;
	R3Point curMousePos;
	Rotation curRot;
	I2Point project(R3Point &pt);
	I2Point winSize = I2Point(getWindowRect().width(), getWindowRect().height());
	
public:
	virtual void onExpose(XEvent& event);
	virtual void onKeyPress(XEvent& event);
	//virtual void onButtonMotion(XEvent& event);
	
	void setPlane(const InterPlane &plane);
	
	void draw();
	void drawAxes();
	void drawCube();
	void drawInter();
};

#endif