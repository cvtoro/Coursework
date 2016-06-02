/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cube.h"
#include <math.h>
#include "Plane.h"


/**
* Cube's intersection method.  The input is a ray (pos, dir). 
*/
float Cube::intersect(Vector pos, Vector dir)
{

	return 0.0;
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the cube.
*/
Vector Cube::normal(Vector p)
{

	return Vector(0,0,0);
}
