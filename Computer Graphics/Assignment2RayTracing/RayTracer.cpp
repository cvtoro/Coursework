// ========================================================================
// COSC 363  Computer Graphics  Lab07
// A simple ray tracer
// ========================================================================

#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.h"
#include "Sphere.h"
#include "Color.h"
#include "Plane.h"
#include "Cube.h"
#include "Object.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Image.h"
#include <memory>
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#elif defined __linux__
	#include <GL/glut.h>
#else
#error "unknown platform"
#endif

using namespace std;

# define PI           3.14159265358979323846  /* pi */

const float WIDTH = 20.0;
const float HEIGHT = 20.0;
const float EDIST = 40.0;
const int PPU = 30;     //Total 600x600 pixels
const int MAX_STEPS = 10;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;

Image* texture1;
Image* texture2;
GLuint txId;

vector<Object*> sceneObjects;

Vector light;
Color backgroundCol;




//A useful struct
struct PointBundle
{
	Vector point;
	int index;
	float dist;
};

/*
* This function compares the given ray with all objects in the scene
* and computes the closest point  of intersection.
*/
PointBundle closestPt(Vector pos, Vector dir)
{
    Vector  point(0, 0, 0);
	float min = 10000.0;

	PointBundle out = {point, -1, 0.0};

    for(int i = 0;  i < sceneObjects.size();  i++)
	{
        float t = sceneObjects[i]->intersect(pos, dir);
		if(t > 0)        //Intersects the object
		{
			point = pos + dir*t;
	
			if(t < min)
			{
				out.point = point;
				out.index = i;
				out.dist = t;
				min = t;
			}
		}
	}

	return out;
}


 
Image* loadImage(char* filename){
	Image* newImage = new Image();
	// char imageName = 'deathStar.bmp';
	newImage->read_bmp_file(filename);
	return newImage;

}
/*
* Computes the colour value obtained by tracing a ray.
* If reflections and refractions are to be included, then secondary rays will
* have to be traced from the point, by converting this method to a recursive
* procedure.
*/

Color trace(Vector pos, Vector dir, int step)
{
	Color colorSum;
	Color col;
    PointBundle q = closestPt(pos, dir);

    if(q.index == -1) return backgroundCol;        //no intersection



	Vector n = sceneObjects[q.index]->normal(q.point);
	Vector l = light - q.point;
	Vector v(-dir.x, -dir.y, -dir.z);

	 //texture mapping for a sphere, get color based on a texture
	if(q.index == 0 || q.index == 1){
		//find u, v, texture coordinates
		Sphere* s = dynamic_cast<Sphere*>(sceneObjects[q.index]);
		Vector cntr = s->center;
		Vector n = Vector(cntr.x, cntr.y + 5, cntr.z);
		Vector Vn = n - cntr;
		Vn.normalise();

		Vector e = Vector(cntr.x, cntr.y, cntr.z+5);
		Vector Ve = e - cntr;
		Ve.normalise();

		Vector Vp = q.point - cntr;
		Vp.normalise();

		float phi = acos( -Vn.dot(Vp));
		float v = phi / PI;


		float theta = acos( Vp.dot(Ve) / sin(phi)) / (2 * PI);

		float u;
		if (  Vn.cross(Ve).dot(Vp)  > 0 ){
			u = theta;
		}
		else{
			u = 1 - theta;
		}
		//shift the texture to wrap around
		u = u + 0.5;
		if (u > 1){
			u -= 1;
		}
		//get texture1's coordintaes
		if(q.index == 1){

			int x = (int)(u * texture1->width) - 1;
			int y = (int)(v * texture1->height ) - 1;
			int p = (y * texture1->width + x)*3;

			if (p > 0 ){
			//divide by 255 to get values from 0 to 1
			col = Color(texture1->data[p]/255.0, 
		                texture1->data[p+1]/255.0,
		                texture1->data[p+2]/255.0, 1);
			}
		}
		//get texture2s coordinates
		else{
			int x = (int)(u * texture2->width) - 1;
			int y = (int)(v * texture2->height ) - 1;
			int p = (y * texture2->width + x)*3;

			if (p > 0 ){
			//divide by 255 to get values from 0 to 1
			col = Color(texture2->data[p]/255.0, 
		                texture2->data[p+1]/255.0,
		                texture2->data[p+2]/255.0, 1);
			}
		}

	

	}
	else{
	 col = sceneObjects[q.index]->getColor(); //Object's colour
	}




	//lighting calculations
	Vector lightVector = light - q.point;
	float lightDist = lightVector.length();
	lightVector.normalise();

	//check if object in shadow, direct a ray from q.point to light source
	PointBundle s = closestPt(q.point, lightVector);
	if(s.index > -1 && s.dist < lightDist){
		colorSum = col.phongLight(backgroundCol, 0.0, 0.0, col.transparency);
	}
	else{
		l.normalise();
		float lDotn = l.dot(n);
		if (lDotn <= 0){

			colorSum = col.phongLight(backgroundCol, 0.0, 0.0, col.transparency);

		}

		else{
			Vector r = ((n*2) * lDotn) - l;
			r.normalise();
			float rDotv = r.dot(v);
			float spec;
			if(rDotv < 0) spec = 0.0;
			else spec = pow(rDotv, 10);
			colorSum = col.phongLight(backgroundCol, lDotn, spec, col.transparency);
		}
	}




	//Reflection
	if( q.index == 0  && step < MAX_STEPS){
	    Vector reflectionVector = (n*2)*(n.dot(v)) - v;
		reflectionVector.normalise();
		Color reflectionCol = trace(q.point, reflectionVector, step+1);
		float reflCoeff = 0.5;
		
		colorSum.combineColor(reflectionCol, reflCoeff);

	}

	bool inside = false; 
    if (dir.dot(n) > 0) n =  Vector(-n.x, -n.y, -n.z), inside = true; 
	//reflection + refraction
	if(col.transparency < 1 && step < MAX_STEPS){
	    Vector reflectionVector = (n*2)*(n.dot(v)) - v;
		reflectionVector.normalise();
		Color reflectionCol = trace(q.point, reflectionVector, step+1);
		float reflCoeff = 0.5;
			
		float ior = 1.33, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?

 		float dDotN = -dir.dot(n);
        float cosTheta = 1 - (eta * eta) * (1 - dDotN*dDotN);
        Vector refrdir = (dir * eta) + (n*(eta *  dDotN - sqrt(cosTheta)));
        Color refraction = trace(q.point, refrdir, step + 1);

		colorSum.combineColor(refraction, 1);
		colorSum.combineColor(reflectionCol, reflCoeff);
	

		
	}
	//make the cylinder transparent
	if(q.index == 9){
		//pass the array through without refracting
		Color refraction = trace(q.point, dir, step + 1);
		colorSum.combineColor(refraction, 1);

	}

	return colorSum;


}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each pixel as quads.
//---------------------------------------------------------------------------------------
void display()
{


	
	int widthInPixels = (int)(WIDTH * PPU);
	int heightInPixels = (int)(HEIGHT * PPU);
	float pixelSize = 1.0/PPU;
	float halfPixelSize = pixelSize/2.0;
	float x1, y1, xc, yc;
	//eye position
	Vector eye(0., 4., 10.);



	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);  //Each pixel is a quad.

	for(int i = 0; i < widthInPixels; i++)	//Scan every "pixel"
	{
		x1 = XMIN + i*pixelSize;
		xc = x1 + halfPixelSize;
		for(int j = 0; j < heightInPixels; j++)
		{
			y1 = YMIN + j*pixelSize;
			yc = y1 + halfPixelSize;

		    Vector dir(xc, yc, -EDIST);	//direction of the primary ray

		    dir.normalise();			//Normalise this direction
    	



		    Color col =  trace (eye, dir, 1); //Trace the primary ray and get the colour value
		  
		
			glColor3f(col.r, col.g, col.b);
		    

		
		
			glVertex2f(x1, y1);				//Draw each pixel with its color value
			glVertex2f(x1 + pixelSize, y1);
			glVertex2f(x1 + pixelSize, y1 + pixelSize);
			glVertex2f(x1, y1 + pixelSize);
        }
    }


    glEnd();
    glFlush();
}



void initialize()
{
	//Iniitialize background colour and light's position
	backgroundCol = Color::GRAY;
	light = Vector(10.0, 40.0, -5.0);

	//Add objects to the list of scene objects here.
	Sphere *sphere1 = new Sphere( Vector(8,6,-50), 3.0, Color:: RED);
	sceneObjects.push_back(sphere1);

	Sphere *sphere2 = new Sphere(Vector( - 5, 4, -110), 15.0,  Color:: BLUE);
	sceneObjects.push_back(sphere2);

	Sphere *sphere3 = new Sphere(Vector(-10,0,-60), 4.0, Color(0, 0, 0, 0.4));
	sceneObjects.push_back(sphere3);


	Cube *cube1 = new Cube(Vector(9, -2, -50 ), 5.0, Color(0,0.6,0.6,1), &sceneObjects);

	Cylinder* cyl = new Cylinder(Vector(-5, 10, -30), 2.0, 3.0, Color(0,0.2,0,1));
	sceneObjects.push_back(cyl);

	Cone* con = new Cone(Vector(3, 10,-30), 2, 2.0, Color::WHITE);
	sceneObjects.push_back(con);


	//code for creating a checkered floor
	Color white = Color::WHITE;
	Color cyan = Color(0,1,1, 1);
	Color color = white;

	bool changeColor = true;
	int length = 5;
	int x = 12;
	int z = 50;
	int ogZ = z;

	for (int i = 0; i < 5; i++){
		
		for(int j = 0; j < 7; j++){

			Plane *plane = new Plane(Vector(-x, -10, -z), Vector(-x + length, -10, -z),
			Vector(-x+ length,-10, -z - 2*length), Vector(-x, -10, -z - 2*length), color);
			sceneObjects.push_back(plane);
			z+= length; 
			if (changeColor){
				color = cyan;
				changeColor = !changeColor;
			}
			else{
				color = white;
				changeColor = !changeColor;
			}

		}
	z = ogZ;
	x -= length;


	}	

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Raytracing");
 	texture1 = loadImage("WinterisComing.bmp");
 	texture2 = loadImage("Landscape.bmp");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();

	

    return 0;
}
