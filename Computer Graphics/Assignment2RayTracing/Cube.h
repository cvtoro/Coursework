/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_CUBE
#define H_CUBE

#include "Object.h"
#include "Plane.h"
#include <vector>
using namespace std;

/**
 * Defines a simple Cube located at 'center' 
 * with the specified side length
 */
class Cube : public Object
{

private:
    Vector center;
    float side;


public:	
	Cube()
		: center(Vector()), side(1)  //Default constructor creates a unit cube
	{
		color = Color::WHITE;
	};
	
    Cube(Vector c, float sid, Color col, vector<Object*>* sceneObjs)
		: center(c), side(sid)
	{
	
		float s = side/2;
		//float d = 0.5;
		color = col;
		Vector cntr = Vector(c.x, c.y, c.z + s); 
		//plane 1 facing positive z
		Plane *face1 = new Plane(Vector(cntr.x - s, cntr.y - s, cntr.z), Vector(cntr.x + s, cntr.y - s, cntr.z),
			Vector(cntr.x +s, cntr.y + s, cntr.z), Vector(cntr.x -s, cntr.y + s, cntr.z), color);
			sceneObjs->push_back(face1);
		//facing -z
		cntr = Vector(c.x, c.y , c.z -s);

		Plane *face2 = new Plane(Vector(cntr.x - s, cntr.y - s, cntr.z), Vector(cntr.x + s, cntr.y - s, cntr.z),
		Vector(cntr.x +s, cntr.y + s, cntr.z), Vector(cntr.x -s, cntr.y + s, cntr.z), color);
		sceneObjs->push_back(face2);

		//facing + x
		cntr = Vector(c.x + s, c.y , c.z);

		Plane *face3 = new Plane(Vector(cntr.x, cntr.y - s, cntr.z+s), Vector(cntr.x, cntr.y - s, cntr.z-s),
		Vector(cntr.x, cntr.y + s, cntr.z-s), Vector(cntr.x, cntr.y + s, cntr.z+s), color);
		sceneObjs->push_back(face3);

		//facing -x
		cntr = Vector(c.x - s, c.y , c.z);

		Plane *face4 = new Plane(Vector(cntr.x, cntr.y - s, cntr.z+s), Vector(cntr.x, cntr.y - s, cntr.z-s),
		Vector(cntr.x, cntr.y + s, cntr.z-s), Vector(cntr.x, cntr.y + s, cntr.z+s), color);
		sceneObjs->push_back(face4);

		//facing + y
		cntr = Vector(c.x , c.y + s , c.z);

		Plane *face5 = new Plane(Vector(cntr.x-s, cntr.y, cntr.z+s), Vector(cntr.x+s, cntr.y , cntr.z+s),
		Vector(cntr.x+s, cntr.y, cntr.z-s), Vector(cntr.x-s, cntr.y, cntr.z-s), color);
		sceneObjs->push_back(face5);

		//facing - y
		cntr = Vector(c.x , c.y - s , c.z);

		Plane *face6 = new Plane(Vector(cntr.x-s, cntr.y, cntr.z+s), Vector(cntr.x+s, cntr.y , cntr.z+s),
		Vector(cntr.x+s, cntr.y, cntr.z-s), Vector(cntr.x-s, cntr.y, cntr.z-s), color);
		sceneObjs->push_back(face6);


	};

	float intersect(Vector pos, Vector dir);

	Vector normal(Vector p);

};

#endif //!H_CUBE
