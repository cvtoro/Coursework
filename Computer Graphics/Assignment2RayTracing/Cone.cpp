/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The cone class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cone.h"
#include <math.h>

float Cone::switchT(float t, float t1, float t2){
	float temp;
	 if(fabs(t-t1) < 1.e-2 ){
	 	temp = t2;
	 }

	else{
		temp = t1;
	}
	return temp;
}

/**
* Cone's intersection method.  The input is a ray (pos, dir). 
*/
float Cone::intersect(Vector pos, Vector dir)
{
	float k = (radius/ height) * (radius/ height);
	float A = pos.x - center.x;
	float B = height + center.y - pos.y ;
	float C = pos.z - center.z;
	
	float a = (dir.x * dir.x) + (dir.z * dir.z) - (k*k)*(dir.y*dir.y);
	float b = 2* (A*dir.x + C*dir.z + k*k*B*dir.y);
	float c = (A*A + C*C - k*k*B*B);

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
	

//test whether the intersection point is above or below the cone height,
//test the second point for possible intersection    
   Vector point = Vector(0,0,0);
	point = pos + dir*t;
	//if intersection point is above the cone height, return the background color
	if (point.y > center.y + height) {
		return - 1.0;


	}

	//if intersection point is below the cone's center
	if (point.y < center.y ) {
		//grab second intersection point
		float temp = switchT(t, t1, t2);
		point = pos + dir*temp;
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
* Assumption: The input point p lies on the cone.
*/
Vector Cone::normal(Vector p)
{
	//normalized normal vector
    float theta = atan(radius/ height);
    float phi = atan((p.x - center.x) / (p.z - center.z));
    Vector n = Vector(sin(phi)*cos(theta), sin(theta), cos(phi)*cos(theta));
    n.normalise();
    return n;
}




