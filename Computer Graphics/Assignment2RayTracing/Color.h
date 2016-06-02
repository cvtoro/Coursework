/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The color class
*  A simple colour class with a set of operations including
*    phong lighting.
-------------------------------------------------------------*/

#ifndef H_COLOR
#define H_COLOR

class Color
{

public:
    float r, g, b, transparency;
	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color GRAY;

    Color()
		: r(1), g(1), b(1), transparency(1)
	{}	;
	
    Color(float rCol, float gCol, float bCol, float t)
		: r(rCol), g(gCol), b(bCol), transparency(t)
	{} ;

    void scaleColor(float scaleFactor);

    void combineColor(Color col);

    void combineColor(Color col, float scaleFactor);

	Color phongLight(Color ambientCol, float diffuseTerm,  float specularTerm, float trans);
};
#endif
