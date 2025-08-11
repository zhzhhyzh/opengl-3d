#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float x = 1;
float y = 1;
float z = 1;

int qno = 1;

float rotate = 0;
float updown = 0;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 'x' || wParam == 'X') {
			x *= -1;
		}
		else if (wParam == 'y' || wParam == 'Y') {
			y *= -1;
		}
		else if (wParam == 'z' || wParam == 'Z') {
			z *= -1;
		}
		else if (wParam == '1') {
			qno = 1;
		}
		else if (wParam == '2') {
			qno = 2;
		}
		else if (wParam == '3') {
			qno = 3;
		}
		else if (wParam == '4') {
			qno = 4;
		}
		else if (wParam == '5') {
			qno = 5;
		}

		else if (wParam == '6') {
			qno = 6;
		}

		else if (wParam == '7') {
			qno = 7;
		}
		else if (wParam == VK_LEFT)
		{
			rotate += 0.5;
		}

		else if (wParam == VK_RIGHT)
		{
			rotate -= 0.5;

		}

		else if (wParam == VK_UP)
		{
			if(updown + 0.5 <= 90) {
				updown += 0.5;
			}
		}

		else if (wParam == VK_DOWN)
		{
			if (updown - 0.5 >=0) {
				updown -= 0.5;
			}
			

		}
		else if (wParam == VK_SPACE)
		{
			rotate = 0;
			updown = 0;


		}

		
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void drawCube(float size, float initialPoint) {
	glBegin(GL_QUADS);
	//Face 1 here Front Face
	glColor3f(1, 0, 0);
	glVertex3f(initialPoint, initialPoint, size);
	glVertex3f(size, initialPoint, size);
	glVertex3f(size, initialPoint, initialPoint);
	glVertex3f(initialPoint, initialPoint, initialPoint);

	// Face 2 here Any Connected to Face 1 (Right and top is rejected) **Meaning is need to connect the last vertex of face 1. This is the left
	glColor3f(0, 1, 0);

	glVertex3f(initialPoint, initialPoint, initialPoint);
	glVertex3f(initialPoint, size, initialPoint);
	glVertex3f(initialPoint, size, size);
	glVertex3f(initialPoint, initialPoint, size);

	// Face 3 This is top
	glColor3f(0, 0,1);

	glVertex3f(initialPoint, initialPoint, size);
	glVertex3f(initialPoint, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, initialPoint, size);

	// Face 4 This is right
	glColor3f(1, 1, 0);

	glVertex3f(size, initialPoint, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, initialPoint);
	glVertex3f(size, initialPoint, initialPoint);

	// Face 5 This is bottom
	glColor3f(1, 0, 1);

	glVertex3f(size, initialPoint, initialPoint);
	glVertex3f(initialPoint, initialPoint, initialPoint);
	glVertex3f(initialPoint, size, initialPoint);
	glVertex3f(size, size, initialPoint);

	// Face 6 This is bottom
	glColor3f(0,1,1);

	glVertex3f(size, size, initialPoint);
	glVertex3f(initialPoint, size, initialPoint);
	glVertex3f(initialPoint, size, size);
	glVertex3f(size, size, size);
	glEnd();
}

void drawPyramid(float size) {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(3.0);
	glRotatef(0.1, x, y, z);

	glBegin(GL_LINE_LOOP);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);

	glColor3f(1, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, 0);



	glEnd();
}



void drawRobotArm() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();
	glPushMatrix();
	glRotatef(rotate, 1, 1, 1);

	glLineWidth(3.0);
	//Left cube
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-0.8, 0, 0);
	glVertex3f(-0.8, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glEnd();

	// Back Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.8, 0.5, -0.25);
	glVertex3f(-0.8, 0, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, 0.5, -0.25);
	glEnd();

	// Top Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.8, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, -0.25);
	glVertex3f(-0.8, 0.5, -0.25);
	glEnd();

	// Bottom Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.8, 0, -0.25);
	glVertex3f(-0.8, 0, 0);
	glEnd();

	// Left Side Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.8, 0, 0);
	glVertex3f(-0.8, 0, -0.25);
	glVertex3f(-0.8, 0.5, -0.25);
	glVertex3f(-0.8, 0.5, 0);
	glEnd();

	// Right Side Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, 0, 0);
	glEnd();
	//glPopMatrix();
	glRotatef(updown,0,0,1);
	glPushMatrix();
	//right cube
	

	glBegin(GL_LINE_LOOP);

	// Front Face
	glVertex3f(0, 0, 0);
	glVertex3f(0.8, 0, 0);
	glVertex3f(0.8, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//lft Side Face
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//Bottom Face
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.8, 0, -0.25);
	glVertex3f(0.8, 0, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//rght Side Face
	glVertex3f(0.8, 0, 0);
	glVertex3f(0.8, 0, -0.25);
	glVertex3f(0.8, 0.5, -0.25);
	glVertex3f(0.8, 0.5, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//Top Face
	glVertex3f(0.8, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, -0.25);
	glVertex3f(0.8, 0.5, -0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//Back Face
	glVertex3f(0.8, 0.5, -0.25);
	glVertex3f(0.8, 0, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, 0.5, -0.25);







	glEnd();
	glPopMatrix();
	glPopMatrix();


}

void p4Demo() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glRotatef(0.1, x,y,z);
	drawCube(0.5, 0);
	drawCube(-0.5, 0);

	drawCube(-0.3, -0.6);
	drawCube(0.3, 0.6);
}

void drawSphere(double r) {
	GLUquadricObj* sphere = NULL; //create the quadric obj pointer
	sphere = gluNewQuadric(); // create the quadric ob in the memory
	gluQuadricDrawStyle(sphere, GLU_LINE); // make it line to view

	gluSphere(sphere, r, 30, 30);//draw sphere
	gluDeleteQuadric(sphere); // Delete object and free memory

}

void drawTrueSphere(double r) {
	GLUquadricObj* sphere = NULL; //create the quadric obj pointer
	sphere = gluNewQuadric(); // create the quadric ob in the memory
	//gluQuadricDrawStyle(sphere, GLU_LINE); // make it line to view

	gluSphere(sphere, r, 30, 30);//draw sphere
	gluDeleteQuadric(sphere); // Delete object and free memory

}

void drawCylinder(double br, double tr, double h) {
	GLUquadricObj* cylinder = NULL; //create the quadric obj pointer
	cylinder = gluNewQuadric(); // create the quadric ob in the memory
	gluQuadricDrawStyle(cylinder, GLU_LINE); // make it line to view

	gluCylinder(cylinder, br, tr, h, 10, 10);//draw sphere (base bottom, base top, height, slice, space
	gluDeleteQuadric(cylinder); // Delete object and free memory


}

void drawTrueCylinder(double br, double tr, double h) {
	GLUquadricObj* cylinder = NULL; //create the quadric obj pointer
	cylinder = gluNewQuadric(); // create the quadric ob in the memory
	//gluQuadricDrawStyle(cylinder, GLU_LINE); // make it line to view

	gluCylinder(cylinder, br, tr, h, 10, 10);//draw sphere (base bottom, base top, height, slice, space
	gluDeleteQuadric(cylinder); // Delete object and free memory


}

void drawCone(double tr, double h) {
	GLUquadricObj* cone = NULL; //create the quadric obj pointer
	cone = gluNewQuadric(); // create the quadric ob in the memory
	gluQuadricDrawStyle(cone, GLU_LINE); // make it line to view

	gluCylinder(cone, 0, tr, h, 10, 10);//draw sphere (base bottom, base top, height, slice, space
	gluDeleteQuadric(cone); // Delete object and free memory


}


void drawTrueCone(double tr, double h) {
	GLUquadricObj* cone = NULL; //create the quadric obj pointer
	cone = gluNewQuadric(); // create the quadric ob in the memory
	//gluQuadricDrawStyle(cone, GLU_LINE); // make it line to view

	gluCylinder(cone, 0, tr, h, 10, 10);//draw sphere (base bottom, base top, height, slice, space
	gluDeleteQuadric(cone); // Delete object and free memory


}
void p4BSphere() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glRotatef(rotate, 1, 1, 1);
	glColor3f(1, 0, 0);
	glLineWidth(3.0);
	drawSphere(0.2);





}



void p4BCylinder() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glRotatef(rotate, 1, 1, 1);
	glColor3f(1, 0, 0);
	glLineWidth(3.0);

	drawCylinder(0.5, 0.5, 1);



}

void p4BCone() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glRotatef(rotate, 1, 1, 1);
	glColor3f(1, 0, 0);
	glLineWidth(3.0);

	drawCone( 0.5, 1);



}

void icecream() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(0.8, 0.63, 0.43);
	glLineWidth(3.0);

	glRotatef(0.1, 0,1,0);

	glPushMatrix();
	glTranslatef(0, -0.95, 0);

	
	glPushMatrix();

	glRotatef(95, -0.5, 0, 0);


	drawTrueCone(0.5, 1);

	glColor3f(1,1,1);

	

	drawCone(0.5, 1);
	glPopMatrix();
	glPopMatrix();

	glColor3f(0.95,0.89,0.67);
	glPushMatrix();
	glTranslatef(0, 0.05, -0.08);
	drawTrueSphere(0.425);
	glPopMatrix();

	glColor3f(1,0.71,0.77);
	glPushMatrix();
	glTranslatef(0, 0.45, -0.08);
	drawTrueSphere(0.425);
	glPopMatrix();

	glColor3f(0.25, 0.1, 0);
	glPushMatrix();
	glTranslatef(0.3, 0.7, -0.22);
	drawTrueSphere(0.1);
	glPopMatrix();

	glColor3f(1, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.25, 1.025, -0.22);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	glRotatef(-30, 0, 1, 0);
	drawTrueCylinder(0.05, 0.05, 0.25);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glColor3f(1, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-0.25, 0.8, -0.22);

	glPushMatrix();
	glRotatef(5,1,0,0);
	drawTrueCylinder(0.1, 0.1, 0.25);
	glPopMatrix();
	glPopMatrix();




}

void display()
{
	switch (qno) {
	case 1:
		p4Demo();
		break;
	case 2:
		drawPyramid(0.5);
		break;
	case 3:
		drawRobotArm();
		break;
	case 4:
		p4BSphere();
		break;

	case 5:
		p4BCylinder();
		break;

	case 6:
		p4BCone();
		break;
	case 7:
		icecream();
		break;


		
	}


}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------