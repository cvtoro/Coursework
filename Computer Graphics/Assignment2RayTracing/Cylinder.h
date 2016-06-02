/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The cylinder class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_CYLINDER
#define H_CYLINDER

#include "Object.h"

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class Cylinder : public Object
{

private:
    Vector center;
    float radius;
    float height;
    static float switchT(float t, float t1, float t2);

public:

	Cylinder()
		: center(Vector()), radius(1)  //Default constructor creates a unit sphere
	{
		color = Color::WHITE;
	};
	
    Cylinder(Vector c, float r, float h,Color col)
		: center(c), radius(r), height(h)
	{
		color = col;
	};

	float intersect(Vector pos, Vector dir);

	Vector normal(Vector p);

	float getHeight();

	Vector getCenter();



};


    
 


#endif //!H_CYLINDER
