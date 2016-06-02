/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The cylinder class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cylinder.h"
#include <math.h>

float Cylinder::switchT(float t, float t1, float t2){
	float temp;
	 if(fabs(t-t1) <  1.e-4 ){
	 	temp = t2;
	 }

	else{
		temp = t1;
	}
	return temp;
}

/**
* Cylinder's intersection method.  The input is a ray (pos, dir). 
*/
float Cylinder::intersect(Vector pos, Vector dir)
{

	//quadratic formula to solve for t


	float a = (dir.x * dir.x) + (dir.z * dir.z);
	float b = 2* (dir.x * (pos.x - center.x) + dir.z*(pos.z - center.z));
	float c = (pos.x - center.x) * (pos.x - center.x) + 
			  (pos.z - center.z) * (pos.z - center.z) -
			  radius * radius;

	float delta = (b*b)- 4*a*c;

	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;

	float t1 = (-b - sqrt(delta ))/ (2*a);
	float t2 = (-b + sqrt( delta ))/ (2*a);

	if(fabs(t1) < 0.001 )
    {
        if (t2 > 0) return t2;
        else t1 = -1.0;
    }
    if(fabs(t2) < 0.001 ) t2 = -1.0;

    float t = (t1 < t2)? t1: t2;
	

//test whether the intersection point is above or below the cylinder height,
//test the second point for possible intersection    
   Vector point = Vector(0,0,0);
	point = pos + dir*t;
	//point of intersection above the cylinder
	if (point.y > center.y + height) {
		//grab second intersection point

		float temp = switchT(t, t1, t2);
		//check if valid point
		point = pos + dir*temp;
		if (point.y < center.y + height && point.y > center.y ) {
		
			return temp;

		}
		else{
			return -1.0;
		}


	}

	point = pos + dir* t;
	//point of intersection below the cylinder 
	if (point.y < center.y ) {
		//grab second intersection point
		float temp = switchT(t, t1, t2);
		point = pos + dir*temp;
		//check if valid point
		if (point.y <= center.y + height && point.y >= center.y ) {
			return temp;

		}
		else{
			return -1.0;
		}
	
	

	}

	return t;
}



/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the cylinder.
*/
Vector Cylinder::normal(Vector p)
{
	//normalized normal vector
	Vector n = Vector((p.x - center.x)/radius, 0.0, (p.z - center.z) / radius);
    return n;
}

float Cylinder::getHeight(){
	return height;
}

Vector Cylinder::getCenter(){
	return center;
}



