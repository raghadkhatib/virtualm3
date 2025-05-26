#pragma once
class Satellite
{
public:
float g, mearth;
float mmoon, ti , x , x2, y , y2 , vx , vy ,rmoon; 
float  teta , w , t1 , t2 , dt , v ;
float view, dx, dy,tetav,tetam ;
int first;
float r,fi,fi2;
float  pointx[1200], pointy[1200];
int pointcount ;
float frx,fry;
float fr, f,c,a,d,p,Rr,T;

Satellite();

void generate(float rj, float fj, float fj2);
};