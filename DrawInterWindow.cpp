#include "DrawInterWindow.h"

void DrawInterWindow::printHelp() {
    printf("You can rotate cube by mouse and arrows\n"
           "You can increase and decrease cube by mouse, Z and X\n");
}

I2Point DrawInterWindow::project(R3Point &pt) {
	R3Point prPoint = curRot(pt);
	int prX = winSize.x / 5;
	int prY = winSize.y / 5;
	return I2Point(round(prX*((-1./2)*prPoint.getX() + prPoint.getY()) + 2*prX),
				   round(prY*((sqrt(3)/2)*prPoint.getX() - prPoint.getZ()) + 3*prY));
}

void DrawInterWindow::setPlane(const InterPlane &plane) {
	this->plane = plane;
}

void DrawInterWindow::onExpose(XEvent&) {
	winSize.x = getWindowRect().width();
	winSize.y = getWindowRect().height();
	setForeground(getBackground());
    fillRectangle(m_RWinRect);
	draw();
}

void DrawInterWindow::onKeyPress(XEvent& event) {
    Rotation E;
    R3Point Oz(0, 0, 1);
    R3Point Oy(0, 1, 0);
    double phi = M_PI / 60;
    KeySym key;
    char keyName[256];
    XLookupString(&(event.xkey), keyName, 255, &key, 0);
	switch ((int) key) {
		case 113:    // q
			destroyWindow();
			break;
		case 32:     // space
			curRot = E;
			break;
		case 65361:  //left
			curRot = E.rotate(Oz, -phi) * curRot;
			break;
		case 65362:  //up
			curRot = E.rotate(Oy, -phi) * curRot;
			break;
		case 65363:  //right
			curRot = E.rotate(Oz, phi) * curRot;
			break;
		case 65364:  //down
			curRot = E.rotate(Oy, phi) * curRot;
			break;
	    case 122:    //Z
	        curRot = E.inrease(1.03) * curRot;
        case 120:    //X
            curRot = E.inrease(0.97) * curRot;
		default:
			break;
	}
	//printf("Key: %d\n", (int) key);
	redraw();
}

void DrawInterWindow::onButtonPress(XEvent& event) {
    Rotation E;
    switch (event.xbutton.button) {
        case Button4:
            //printf("Scrolled up\n");
            curRot = E.inrease(1.03) * curRot;
            redraw();
            break;
        case Button5:
            //printf("Scrolled down\n");
            curRot = E.inrease(0.97) * curRot;
            redraw();
            break;
        default:
            curMousePos = I2Point(event.xbutton.x, event.xbutton.y);
            break;
    }
}

void DrawInterWindow::onMotionNotify(XEvent& event) {
	if (event.xmotion.state & Button1Mask) {
		I2Point oldMousePos = curMousePos;
		curMousePos.x = event.xbutton.x;
		curMousePos.y = event.xbutton.y;
		int dx = curMousePos.x - oldMousePos.x;
		int dy = curMousePos.y - oldMousePos.y;
		Rotation E;
		R3Point Oz(0, 0, 1);
		R3Point Oy(0, 1, 0);
		double phi = M_PI / 180;
		curRot = E.rotate(Oz, dx * phi) * curRot;
		curRot = E.rotate(Oy, dy * phi) * curRot;
		redraw();
		draw();
	}
}

void DrawInterWindow::draw() {
	setBackground("LightGray");
	
	drawAxes();
	
	setForeground("green");
	drawInter();
	
	setForeground("SeaGreen");
	drawCube();
}
	
void DrawInterWindow::drawAxes() {
	R3Point zero = {0, 0, 0};
	R3Point Ox = {2, 0, 0};
	R3Point Oy = {0, 2, 0};
	R3Point Oz = {0, 0, 2};
	
	setForeground("red");
	drawLine(project(zero), project(Ox));
	
	setForeground("blue");
	drawLine(project(zero), project(Oy));
	
	setForeground("black");
	drawLine(project(zero), project(Oz));
}

void DrawInterWindow::drawCube() {
	R3Point p1 = {0, 0, 0};
	R3Point p2 = {0, 0, 1};
	R3Point p3 = {0, 1, 0};
	R3Point p4 = {0, 1, 1};
	R3Point p5 = {1, 0, 0};
	R3Point p6 = {1, 0, 1};
	R3Point p7 = {1, 1, 0};
	R3Point p8 = {1, 1, 1};

	drawLine(project(p1), project(p2));
	drawLine(project(p1), project(p3));
	drawLine(project(p1), project(p5));
	drawLine(project(p3), project(p4));
	
	drawLine(project(p4), project(p2));
	drawLine(project(p2), project(p6));
	drawLine(project(p3), project(p7));
	drawLine(project(p5), project(p6));
	
	drawLine(project(p5), project(p7));
	drawLine(project(p6), project(p8));
	drawLine(project(p7), project(p8));
	drawLine(project(p4), project(p8));
}
	
void DrawInterWindow::drawInter() {
	R3Point *pts = plane.interWithCube();
	
	for(int i = 0; i < 10; i++)
		for(int j = i+1; j < 11; j++)
			for(int k = j+1; k < 12; k++) {
				if (pts[i].inCube() && pts[j].inCube()
					&& pts[k].inCube()) {
					I2Point *buf = new I2Point[3];
					buf[0] = project(pts[i]);
					buf[1] = project(pts[j]);
					buf[2] = project(pts[k]);
					
					fillPolygon(buf, 3);
					
					delete [] buf;
				}
			}
	delete [] pts;
}
