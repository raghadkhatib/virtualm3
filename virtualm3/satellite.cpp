#include "satellite_header.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <cmath>
#include <texture.h>
#include <fstream>

Satellite::Satellite()
{
g = 0.0000000000667, mearth = 5.97*(10 ^ 24);
mmoon = 3000, ti = 1.0,  x2 = 0, y = 0, y2 = 0,
vx = 0, vy = 0,rmoon=2; 
teta = 0.0f, w = 0, t1 = 0.0f, t2 = 0.01, dt = 10*90000000000, v = 0;
view = 0, dx, dy,fi2=0;
first=0;
x = 0,r =0,fi = 0,fr=0;
pointcount = 0;
c=0.47; a=3.14*rmoon*rmoon; T=2272.039; Rr=287.05;
}
  
void drawSphere(double r, int lats, int longs) {
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

void Satellite :: generate(float rj, float fj, float fj2)
{
//we have 3 views , first: view 0 to get v0 ,second:view1 to run, third view2 to change orbit

		////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////in satalite class////////////////////////////

		if (first==0)
		{ 
        this->r=rj; this->x=rj; this->fi=fj;
		first++;
		}

		if (fj2 != 0 && view != 10){
			this->fi2 = fj2;
			view = 2;
		}

		if (view == 0)
		{

			glPushMatrix();
			vy = (fi*ti*ti / mmoon);
			vx = (-1 * g*mearth*ti / (r*r));
			view = 1;
			glPopMatrix();
		}
		else if (view == 1)
		{
			glPushMatrix();
			vx += ((-1 * g*mearth*cos(teta))*dt / (r*r)) +((-1 * fr*dt*cos(tetav) / mmoon));
			vy += ((-1 * g*mearth*sin(teta))*dt / (r*r)) +((-1 * fr*dt*sin(tetav) / mmoon));
			v = sqrtf((vx*vx) + (vy*vy));
			x2 = (vx*dt) + x;
			y2 = (vy*dt) + y;
			r = sqrtf((x2*x2) + (y2*y2));
			w = v / r;
			teta += (w*dt);
			tetam = atan((y - y2) / (x - x2));
			dx = x2 - x;
			dy = y2 - y;
			if(dx<0)
			{
				tetav = 3.14+ tetam;	
			}
			else if (dy < 0)
			{
				tetav = (2*(3.14))+tetam;
			}
			else
			{
				tetav = tetam;
			}
			
			x = x2; y = y2;

			if(r>7090000)
			{
			//fr=0.5*(0.47)*(3.14*r*r)*(0)*(v*v);
			p=0;
			d=p/(Rr*T);
			fr=0.5*c*a*d*v*v;
			}

			else if(7090000>=r && r>=6400000)
			{
			//fr=0.5*(0.47)*(3.14*r*r)*(7.0000000000666491726)*(v*v);
			p=0.0005;
			d=p/(Rr*T);
			fr=0.5*c*a*d*v*v;
			}

			glPopMatrix();
		}
		else if (view == 2)
		{
		glPushMatrix();
	
		{
		vy += ((-1 * g*mearth*sin(teta))*t2 / (r*r)) + ((fi2*t2*t2*sin(tetav ) / mmoon));
		vx += ((-1 * g*mearth*cos(teta))*t2 / (r*r)) + ((fi2*t2*t2*cos(tetav ) / mmoon));
		v = sqrtf((vx*vx) + (vy*vy));
		x2 = (vx*dt) + x;
		y2 = (vy*dt) + y;
		r = sqrtf((x2*x2) + (y2*y2));
		w = v / r;
		teta += (w*dt);
		tetam = atan((y - y2) / (x - x2));
		dx = x2 - x;
		dy = y2 - y;
		if (dx<0)
		{
			tetav = 3.14 + tetam;
		}
		else if (dy < 0)
		{
			tetav = (2 * (3.14)) + tetam;
		}
		else
		{
			tetav = tetam;
		}
		x = x2; y = y2;
			view = 1;
		}
		glPopMatrix();
		}

		///////////////////drawing 
		glPushMatrix(); {
			if(r<6400000 && view!=10){
			v=0;   ///ÇÐÇ æÕá ááÇÑÖ ÇáÓÑÚÉ ÕÝÑ æ ÛíäÇ ÞíãÉ Çá Ýíæ ãÔÇä ãÇ ÊÊÛíÑ ÇáÇÍÏÇËíÇÊ 
			view=10;
			}
			
			//glColor3f(0.6, 0, 0.9);
			glScaled(0.0000015, 0.0000015, 0.0000015);
			////////////////////////////////draw orbit
			if (r != 0 && pointcount<1000){
				if(x2>0 && y2>-500000 && y2<500000)
				{pointcount = 0;}
				else{
				pointcount += 1;
				pointx[pointcount] = x2;
				pointy[pointcount] = y2;
				}
			}
			glPushMatrix();
			glColor3f(0.9, 0.8, 0.9);
			glPointSize(5);
			glBegin(GL_POINTS);
			for (int counter = 0; counter<pointcount; counter += 1)
			{
				glVertex3f(pointx[counter], pointy[counter], 0);
			}
			glEnd();
			glPopMatrix();
			/////////////////moon draw 
			glColor3f(255, 255, 255);
			glTranslated(x2, y2, 0);
			glPushMatrix(); {
				glRotated(teta*57.3248407643, 0, 0, 1);
				//////////////////
				//draw Satalite
				glPushMatrix(); {
					glTranslated(-1500000, -1000000, 0);
					glBegin(GL_QUADS);
					glVertex3f(0.0f, 2000000.0f, 0); // top left
					glVertex3f(3000000.0f, 2000000.00f, 0); // top right 
					glVertex3f(3000000.0f, 0.0f, -0); //bottom right
					glVertex3f(0.0f, 0.0f, 0); //bottom left
					glEnd();
					glColor3f(0.6, 0, 0.9);
					glBegin(GL_QUADS);
					glVertex3f(1200000, 1500000, 0); // top left
					glVertex3f(2500000, 1500000, 0); // top right 
					glVertex3f(2500000, 500000, -0); //bottom right
					glVertex3f(1200000, 500000, 0); //bottom left
					glEnd();
					glBegin(GL_QUADS);
					glVertex3f(300000, 1500000, 0); // top left
					glVertex3f(800000, 1500000, 0); // top right 
					glVertex3f(800000, 500000, 0); //bottom right
					glVertex3f(300000, 500000, 0); //bottom left
					glEnd();



					glColor3f(1, 0, 1);
					//down
					glLineWidth(5);
					glBegin(GL_LINES);
					glVertex3f(1500000, 0, 0);
					glVertex3f(1800000, -1000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(1500000, 0, -100);
					glVertex3f(1200000, -1000000, 0);
					glEnd();

					glBegin(GL_LINES);
					glVertex3f(700000, -1000000, 0);
					glVertex3f(2300000, -1000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, -1000000, 0);
					glVertex3f(700000, -5000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(2300000, -1000000, 0);
					glVertex3f(2300000, -5000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, -5000000, 0);
					glVertex3f(2300000, -5000000, 0);
					glEnd();



					glBegin(GL_LINES);
					glVertex3f(1500000, -1000000, 0);
					glVertex3f(1500000, -5000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, -2000000, 0);
					glVertex3f(2300000, -2000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, -3000000, 0);
					glVertex3f(2300000, -3000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, -4000000, 0);
					glVertex3f(2300000, -4000000, 0);
					glEnd();

					//up
					glBegin(GL_LINES);
					glVertex3f(1500000, 2000000, 0);
					glVertex3f(1800000, 3000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(1500000, 2000000, 0);
					glVertex3f(1200000, 3000000, 0);
					glEnd();

					glBegin(GL_LINES);
					glVertex3f(700000, 3000000, 0);
					glVertex3f(2300000, 3000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, 3000000, 0);
					glVertex3f(700000, 7000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(2300000, 3000000, 0);
					glVertex3f(2300000, 7000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, 7000000, 0);
					glVertex3f(2300000, 7000000, 0);
					glEnd();

					glBegin(GL_LINES);
					glVertex3f(1500000, 3000000, 0);
					glVertex3f(1500000, 7000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, 4000000, 0);
					glVertex3f(2300000, 4000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, 5000000, 0);
					glVertex3f(2300000, 5000000, 0);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(700000, 6000000, 0);
					glVertex3f(2300000, 6000000, 0);
					glEnd();
					glPopMatrix(); }

				////////////////////
				////////////////////draw  g forc 
				glColor3f(0, 1, 0);
				glLineWidth(6);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(-4000000, 0, 0);
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3f(-4000000, -500000, 0);
				glVertex3f(-4000000, 500000, 0);
				glVertex3f(-4800000, 0, 0);
				glEnd();
				glPopMatrix(); }
			/////////////////////draw v ÔÚÇÚ ÇáÓÑÚÉ 
			glPushMatrix();
			glRotated(tetav*57.3248407643, 0, 0, 1);
			glColor3f(1, 0, 0);
			glLineWidth(6);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(v * 160000000000000, 0, 0);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3f(v * 160000000000000, -500000, 0);
			glVertex3f(v * 160000000000000, 500000, 0);
			glVertex3f((v * 160000000000000)+800000, 0, 0);
			glEnd();
			//////////////////////draw fr
			if (fr != 0){
				glColor3f(1, 1, 0.2);
				glLineWidth(6);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(-3000000, 0, 0);
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3f(-3000000, -700000, 0);
				glVertex3f(-3000000, 700000, 0);
				glVertex3f(-4500000 , 0, 0);
				glEnd();
			}
			glPopMatrix();
			///
			glPopMatrix();

		}

		////////////////////////////////////////////////end satalite class /////////////////
		////////////////////////////////////////////////////////////////////////////////////
}
