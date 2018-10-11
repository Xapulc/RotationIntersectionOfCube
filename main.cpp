#include <iostream>
#include "R2Graph.h"
#include "R3Graph.h"
#include "DrawInterWindow.h"	

int main() {	
	using namespace std;
	
	double A, B, C, x, y, z;
	
#if 0
	cout << "Enter vector ";
	cin >> A >> B >> C;
	if (A*A + B*B + C*C < 1e-16)
	{
		cout << "You entered null vector" << endl;
		return -1;
	}
	cout << "Enter starting point ";
	cin >> x >> y >> z;
#else
	A = 1;
	B = 1;
	C = 1;
	x = 0.5;
	y = 0.5;
	z = 0.5;
#endif
    
    if (!GWindow::initX()) {
        std::cout << "Could not connect to X-server" << std::endl;
        return -1;
    }

    DrawInterWindow w;
    w.setPlane(InterPlane(A, B, C, x, y, z));
    double aspect = (double) GWindow::screenMaxX() /
        (double) GWindow::screenMaxY();
    double width = 30.;
    int height = width / aspect;
    w.createWindow(
        I2Rectangle(             
            I2Point(10, 10),        
            GWindow::screenMaxX()/2,
            GWindow::screenMaxY()/2    
        ),
        R2Rectangle(                       
            R2Point(-width/2., -height/2.),
            width, height      
         )
    );
    
    w.setBackground("LightGray");
    
    GWindow::messageLoop();
    
    GWindow::closeX();
}
	
