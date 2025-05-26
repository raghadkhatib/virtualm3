#include <windows.h>		
#include <fstream>
#include <gl.h>			
#include <glu.h>			
#include <glaux.h>		
#include <cmath>
#include"texture.h"
#include <fstream>
#include "Model_3ds.h"
#include"satellite_header.h"
#include "3DTexture.h"
#include <camera.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")
#pragma comment(lib, "windowscodecs.lib")


HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
int SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN, imag3, imag5, imag6,imag4, imagb, image0, image1, image2;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	// skybox
	//SKYFRONT = LoadTexture("up1.bmp", 255);
	SKYBACK = LoadTexture("2.bmp", 255);
	SKYLEFT = LoadTexture("1.bmp");
	SKYRIGHT = LoadTexture("1.bmp", 255);
	SKYUP = LoadTexture("3.bmp", 255);
	SKYDOWN = LoadTexture("4.bmp", 255);
	image0 = LoadTexture("photo0.bmp");
	image1 = LoadTexture("photooo1.bmp");
	image2 = LoadTexture("photoo2.bmp");
	imag3 = LoadTexture("imag3.bmp", 255);
	imag4 = LoadTexture("choose5.bmp", 255);
	imagb = LoadTexture("photob.bmp", 255);
	imag5 = LoadTexture("space.bmp", 255);
	imag6 = LoadTexture("earth.bmp", 255);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	return TRUE;										// Initialization Went OK
}

////////////////////source veriabl
GLfloat choose = 0, welcomet = 0;
Satellite s1 = Satellite();
Satellite s2 = Satellite();
Satellite s3 = Satellite();
Satellite s4 = Satellite();
//GLfloat r[]={25000000,20000000,15000000,10000000,7000000,6900000};
//GLfloat fi[]={0.0002 ,0.000226,0.00026,0.00032,0.0004,0.00038};
//GLfloat fi2[]={0.0002 ,0.000226,0.00026,0.00032,0.0004,0.00038};

GLfloat r[] = { 0, 0, 0, 0, 0 };
GLfloat fi[] = { 0, 0, 0, 0, 0 };
GLfloat fii = 0;

GLfloat count = 0, masafa = 0, mas1 = 0, mas2 = 0, mtotal = 0, ps1 = 0, ps2 = 0, vxnew = 0, vynew = 0, ps11 = 0, ps22 = 0, onetime = 0;
int i = 0, ii = 0;
///////////////////////////////////////////
void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();
	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

///////////////////////////////////////////////////////////////////////////////
void drawSphere2(double r, int lats, int longs) {
	//The parameters lat defines how many horizontal lines you want to have in
	//your sphere and lon how many vertical lines.
	//r is the radius of your sphere.
	float M_PI = 3.14;
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}
/////////////////////////
void keyr(bool* keys){////////// to choose r
	if (keys['A']){
		i += 1;
		r[i] = 25000000;  //meters
		choose = 11;
	}

	else if (keys['B']){
		i += 1;
		r[i] = 20000000;
		choose = 11;
	}
	else if (keys['C']){
		i += 1;
		r[i] = 15000000;
		choose = 11;
	}
	else if (keys['D']){
		i += 1;
		r[i] = 10000000;
		choose = 11;
	}
	else if (keys['E']){
		i += 1;
		r[i] = 7000000;
		choose = 11;
	}
}
///////////////////////////////////////////////////////////////
void keyfi(bool* keys){////////// to choose fi
	if (keys['A']){
		ii += 1;
		fi[ii] = 0.0002;  //meters
		choose = 3;
	}

	else if (keys['B']){
		ii += 1;
		fi[ii] = 0.000226;
		choose = 3;
	}
	else if (keys['C']){
		ii += 1;
		fi[ii] = 0.00026;
		choose = 3;
	}
	else if (keys['D']){
		ii += 1;
		fi[ii] = 0.00032;
		choose = 3;
	}
	else if (keys['E']){
		ii += 1;
		fi[ii] = 0.0004;
		choose = 3;
	}
	s2.dt = 10 * 100000000000;
}
///////////////////////////////////////////////////////////////////////
void keyfi2(bool* keys){////////// to choose fi2

	if (keys['A']){
		fii = 0.1;  //meters
		choose = 3;
	}

	else if (keys['B']){
		fii = 0.01;
		choose = 3;
	}
	else if (keys['C']){
		fii = 0.001;
		choose = 3;
	}
	else if (keys['D']){
		fii = 0.0001;
		choose = 3;
	}
	else if (keys['E']){
		fii = 0.0004;
		choose = 3;
	}

}
//////////////////////////////////////////////////////////
//////////////////////////////
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	if (choose == 0){      //////welcome

		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, image0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		welcomet += 1;
		if (welcomet == 125){
			welcomet = 0;
			choose = 1;
		}
	}
	else if (choose == 1){  ////choose r  distance between moon and earth center
		keyr(keys);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, image1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	else if (choose == 11){  ////choose r  distance between moon and earth center
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imagb);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		welcomet += 1;
		if (welcomet == 10){
			welcomet = 0;
			choose = 2;
		}
	}
	else if (choose == 2){  ////choose fi effect on the  moon 
		glPushMatrix();
		keyfi(keys);
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, image2);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	else if (choose == 3){
		if (keys[VK_SPACE]){     // ÇáÇÚÏÇÏÇÊ
			choose = 4;
		}
		glTranslatef(0, 0, -100);
		/////////
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imag5);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(45, -25, 40);
		glTexCoord2f(1, 1);  glVertex3f(45, -18, 40);
		glTexCoord2f(0, 1);  glVertex3f(35, -18, 40);
		glTexCoord2f(0, 0);   glVertex3f(35, -25, 40);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		///////skybox
		glPushMatrix();
		Draw_Skybox(0, 0, 100, 100, 80, 200);
		glPopMatrix();
		///////////////////////earth
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imag6);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(7, -7, 0);
		glTexCoord2f(1, 1);  glVertex3f(7, 7, 0);
		glTexCoord2f(0, 1);  glVertex3f(-7, 7, 0);
		glTexCoord2f(0, 0);   glVertex3f(-7, -7, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		/////
		/*glPushMatrix();
		glColor3f(0, 0.3, 1);
		glTranslated(0, 0, 0);
		drawSphere2(7, 20, 30);
		glPopMatrix();*/
		//////////////////////
		glPushMatrix();
		s1.generate(r[1], fi[1], fii);
		if (r[2] != 0){
			s2.generate(r[2], fi[2], fii);
			glPushMatrix();
			mas1 = (s1.x2 - s2.x2);
			mas2 = (s1.y2 - s2.y2);
			masafa = sqrt((mas1*mas1) + (mas2*mas2));
			if (masafa < (s1.rmoon + s2.rmoon+1000) && onetime == 0){
				mtotal = s1.mmoon + s2.mmoon;
				ps1 = s1.mmoon*s1.vx;
				ps2 = s2.mmoon*s2.vx;
				vxnew = (ps1 + ps2) / mtotal;
				ps11 = s1.mmoon*s1.vy;
				ps22 = s2.mmoon*s2.vy;
				vynew = (ps11 + ps22) / mtotal;
				s1.vx = vxnew;
				s2.vx = vxnew;
				s1.vy = vynew;
				s2.vy = vynew;
				s1.dt = 10 * 100000000000;
				s2.dt = 10 * 100000000000;
				onetime = 1;
			}
			glPopMatrix();
		}
		if (r[3] != 0){
			s3.generate(r[3], fi[3], fii);
		}
		if (r[4] != 0){
			s4.generate(r[4], fi[4], fii);
		}
		if (fii != 0){
			count += 1;
			if (count == 1){
				fii = 0;
				count = 0;
			}
		}
		glPopMatrix();
	}


	else if (choose == 4){  ////choose fi effect on the  moon  or add another moon
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imag3);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(53, -40.0f, -100.0f);
		glTexCoord2f(1, 1);  glVertex3f(53, 40.0f, -100.0f);
		glTexCoord2f(0, 1);  glVertex3f(-53.0f, 40.0f, -100.0f);
		glTexCoord2f(0, 0);   glVertex3f(-53.0f, -40.0f, -100.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		if (keys['A']){      //add fi to all moon ,swich on engine
			choose = 13;
		}
		if (keys['B']){     // add MOON
			choose = 12;
		}
		if (keys['C']){     //// START  AGAIN    íÊã ÊÕÝíÑ ÇáÞíã æ ÇáÚæÏÉ á ÇÎÊÑ R  
			r[1] = 0; r[2] = 0; r[3] = 0; r[4] = 0; r[5] = 0;
			fi[1] = 0; fi[2] = 0; fi[3] = 0; fi[4] = 0; fi[5] = 0;
			s1.first = 0; s2.first = 0; s3.first = 0; s4.first = 0;
			s1.x = 0; s2.x = 0; s3.x = 0; s4.x = 0;
			s1.y = 0; s2.y = 0; s3.y = 0; s4.y = 0;
			s1.view = 0; s2.view = 0; s3.view = 0; s4.view = 0;
			s1.teta = 0; s2.teta = 0; s3.teta = 0; s4.teta = 0;
			i = 0; ii = 0;
			onetime = 0;
			choose = 1;
		}
	}
	////////////////////////////////////
	else if (choose == 5){  ////choose r  distance between moon and earth center
		keyfi2(keys);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imag4);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	/////////////////////////////
	else if (choose == 12){  ////choose r  distance between moon and earth center
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imagb);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		welcomet += 1;
		if (welcomet == 10){
			welcomet = 0;
			choose = 1;
		}
	}
	///////////////////////////////
	else if (choose == 13){  ////choose r  distance between moon and earth center
		glPushMatrix();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, imagb);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);  glVertex3f(1.45, -0.75, -1.8);
		glTexCoord2f(1, 1);  glVertex3f(1.45, 0.75, -1.8);
		glTexCoord2f(0, 1);  glVertex3f(-1.45, 0.75, -1.8);
		glTexCoord2f(0, 0);   glVertex3f(-1.45, -0.75, -1.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		welcomet += 1;
		if (welcomet == 10){
			welcomet = 0;
			choose = 5;
		}
	}






	glFlush();											// Done Drawing The Quad	

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Madhat NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
