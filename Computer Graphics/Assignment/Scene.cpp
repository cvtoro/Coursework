//  ========================================================================
//
//
//Cecilia Villatoro
//Assignment 1
// COSC363: Computer Graphics (2016);  University of Canterbury.
//alien space port scene
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
#include "Alien.h"


// #include "loadTGA.h"
#include "loadBMP.h"
using namespace std;
#define RADPERDEG 0.0174533



//--Globals ---------------------------------------------------------------
float xTranslate = 60.0;
float yTranslate = 15.0;
float zTranslate = 0.0;
float lightx = -0.8;
float lighty = 4.7;
float lightz = 1;

// int cam_hgt = yTranslate; //Camera height
int cam_hgt = 10; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float theta = 20.0;
float planetAngle = 10.0;
int walk = 1;
GLUquadricObj*	q;
int changeLight = 1;
int rotate = 1;
bool forward = true;
GLuint txId[6];
int camForward = -100;
GLuint skyboxTex[6];
GLUquadricObj* s;
GLUquadricObj* c;
GLUquadricObj* plat;
int red = 255;
int green = 51;
int blue = 139;
Alien a;
Alien a3;
Alien a4;
Alien a5;
Alien a6;
float shipSpeed = 0.1;
bool moveSpaceship = false;
float upElevator = 0;
bool ElevatorMoveUpwards = true;
bool dynamo = false;
int elapsedTime = 0;
int dynamoAngle = 0;
double dynamoSpeed = 0;
bool alienView = false;
int alienIndex = 0;

void loadTexture()
{

	glGenTextures(6, txId);   //
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	// loadTGA("PlanetTexture.tga");
	loadBMP("neptune.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[1]);
	// loadTGA("PlanetTexture.tga");
	loadBMP("jupiter.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, txId[2]);
	// loadTGA("PlanetTexture.tga");
	loadBMP("stars.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[3]);
	loadBMP("hangar.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[4]);
	loadBMP("hangar2.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[5]);
	loadBMP("deathStar.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);



}


void drawSkyDome(){

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glPushMatrix();

	glMatrixMode(GL_TEXTURE);

	glLoadIdentity();
  glTranslatef(0.30, 0, 0);
  glMatrixMode(GL_MODELVIEW);
	  gluSphere ( q, 1500, 100, 100 );
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}


void drawPort()
{

  //hangar
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[3]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glPushMatrix();
	glColor3ub(128, 128, 0);
	glTranslatef(0, 10.1 , 200);
	// glTranslatef(0,0,zTranslateScene);
	glScalef(30, 10, 20);

	glRotatef(90.0, 1.0, 0.0, 0.0);
	//glutSolidCube(20);
	// draw a cube (6 quadrilaterals)
  glBegin(GL_QUADS);				// start drawing the cube.

  // back of cube.
  glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
  glTexCoord2f(4,4); glVertex3f( 1.0f,-1.0f,-1.0f);		// Top Right Of The Quad (Back)
  glTexCoord2f(0,4); glVertex3f(-1.0f,-1.0f,-1.0f);		// Top Left Of The Quad (Back)
  glTexCoord2f(0,0); glVertex3f(-1.0f, 1.0f,-1.0f);		// Bottom Left Of The Quad (Back)
  glTexCoord2f(4,0); glVertex3f( 1.0f, 1.0f,-1.0f);		// Bottom Right Of The Quad (Back)

  // bottom of cube
  glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
  glTexCoord2f(4,4); glVertex3f( 1.0f,-1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
  glTexCoord2f(0,4); glVertex3f(-1.0f,-1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
  glTexCoord2f(0,0); glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Bottom)
  glTexCoord2f(4,0); glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Bottom)

  // front of cube
  glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
  glTexCoord2f(4,4); glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
  glTexCoord2f(0,4); glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
  glTexCoord2f(0,0); glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
  glTexCoord2f(4,0); glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Front)

  // left of cube
  glColor3f(0.0f,0.0f,1.0f);			// Blue
  glTexCoord2f(4,4); glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
  glTexCoord2f(0,4); glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Left)
  glTexCoord2f(0,0); glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Left)
  glTexCoord2f(4,0); glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Left)

  // Right of cube
  glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
  glTexCoord2f(4,4); glVertex3f( 1.0f, 1.0f,-1.0f);	        // Top Right Of The Quad (Right)
  glTexCoord2f(0,4); glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
  glTexCoord2f(0,0); glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
  glTexCoord2f(4,0); glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Right)
  glEnd();
  			// Done Drawing The Cube
  glBindTexture(GL_TEXTURE_2D, txId[4]);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glMatrixMode(GL_TEXTURE);

	glLoadIdentity();
  glTranslatef(0.10, 0, 0);

	//glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  // top of cube
  glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
  glTexCoord2f(1,1); glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Of The Quad (Top)
  glTexCoord2f(0,1); glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Top)
  glTexCoord2f(0,0); glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
  glTexCoord2f(1,0); glVertex3f( 1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


}
void drawFloor()
{
	int terrainWidth = 1000;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[1]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-terrainWidth, 0, terrainWidth);
		glTexCoord2f(1, 0);
		glVertex3f(terrainWidth, 0, terrainWidth);
	  glTexCoord2f(1,1);
		glVertex3f(terrainWidth, 0, -terrainWidth);
		glTexCoord2f(0, 1);
		glVertex3f(-terrainWidth, 0, -terrainWidth);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawPlanet()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glPushMatrix();
	    glTranslatef(1000.0, 800.0, 5.0);
		  glColor3f(1.0, 1.0, 1.0);
	    glRotatef(planetAngle, 0, 1, 0);
	    gluSphere ( q, 200.0, 36, 17 );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);






}

//alien class functions
void Alien::drawAlien(){
	glColor3f(1, 0,0);
  glPushMatrix();
    //head
    glTranslatef(0+x, 6.8+y, 0+z);
		glScalef(1, 0.7, 1);
    glutSolidSphere(1.5, 20, 20);

  glPopMatrix();

	glPushMatrix();
		//torso
		glTranslatef(0 + x, 4.3+y, 0+z);
		glScalef(0.7, 1, 1);
		glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
		//leg1
		glTranslatef(0.65+x, 2+y, 0+z);
		glRotatef(rotateDeg, 1, 0, 0);
		glScalef(0.15, 0.7, 0.15);

		glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
		//leg2
		glTranslatef(-0.65+x, 2+y, 0+z);
		glScalef(0.15, 0.7, 0.15);
		glRotatef(-rotateDeg, 1, 0, 0);
		glutSolidCube(4);
	glPopMatrix();

}

void innerElevator(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
			glColor4f(1, 1, 1, 0.5);
			glTranslatef(40, upElevator, -100);
			glRotatef(-90,1,0,0);
			gluCylinder(c, 10, 10, 20, 30, 40);
		glPopMatrix();

}

void drawElevator(){
	glDisable(GL_LIGHTING);

	glColor3f(0,0,0);
	glPushMatrix();
		glTranslatef(40,0.2, -100);
		glRotatef(90,1,0,0);
		gluDisk(c, 0, 20,30, 20);
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		glColor4f(0.2, 0.2, 0.2, 0.4);
		glTranslatef(40,0, -100);
		glRotatef(-90,1,0,0);
		gluCylinder(c, 17, 17, 1000, 30, 40);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void drawSpaceShip()
{
  //torus
  glPushMatrix();
		glColor3ub(54, 100, 139);
		glTranslatef(xTranslate, yTranslate , zTranslate);
	  glScalef(3.0, 1.2, 3.0);
	  glRotatef(90.0, 1.0, 0.0, 0.0);
	  glutSolidTorus(1.5, 4, 20, 30 );
  glPopMatrix();
	//sphere
  glPushMatrix();
		glColor3ub(90,90, 90);
	  glTranslatef(xTranslate, yTranslate + 0.8, zTranslate);
	  glutSolidSphere(4.5, 30, 30);
	glPopMatrix();
	//blinking light
  glPushMatrix();

		glColor3f(red, green , blue);
		glTranslatef(lightx+xTranslate, lighty+yTranslate-3, lightz+zTranslate);
		glRotatef(130, 1, 0, 0);
		glRotatef(50, 0, 1, 0);
		gluDisk(s, 0, 0.3, 10, 10);
	glPopMatrix();

  if(dynamo == true) {
	  //dynamo drive
	  glPushMatrix();

		glColor3ub(128, 0, 0);
		glTranslatef(xTranslate, yTranslate , zTranslate);
		glRotatef(dynamoAngle, 0, 1, 0);
		glScalef(6, 6, 6);

		glRotatef(0.0, 1.0, 0.0, 0.0);
		glutSolidTorus(0.2, 3, 20, 30 );
	  glPopMatrix();

	  glPushMatrix();

		glColor3ub(128, 0, 0);
		glTranslatef(xTranslate, yTranslate , zTranslate);
		glRotatef(dynamoAngle, 1, 0, 0);
		glScalef(6.5, 6.5, 6.5);

		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidTorus(0.2, 3, 20, 30 );
	  glPopMatrix();
  }

}

void drawPeg(int x, int y, int z, int pegRadius, int height){
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(-90, 1, 0, 0);
		gluCylinder(c, pegRadius, pegRadius, height, 20, 40);
	glPopMatrix();

}


void drawLaunchPad(){

	glColor3f(0.6, 0.3 , 1);
	glPushMatrix();
		glTranslatef(60, 10, 0);
		glScalef(1, .15, 1);
		glutSolidCube(40);
	glPopMatrix();

	int pegRadius = 2;
	drawPeg(40 + pegRadius, 0, 20 - pegRadius, pegRadius, 7);
	drawPeg(40 + pegRadius, 0, -20 + pegRadius, pegRadius, 7);
	drawPeg(80 - pegRadius, 0, 20 - pegRadius, pegRadius, 7);
	drawPeg(80 - pegRadius, 0, -20 + pegRadius, pegRadius, 7);


}

void drawDeathStarPlatform()
{

		glColor3f(1,1,1);
		glPushMatrix();
			glTranslatef(-300,0, -150);
			glRotatef(-90,1,0,0);
			gluCylinder(plat, 30, 30, 10, 50, 40);
		glPopMatrix();


		glPushMatrix();
			glTranslatef(-300,10, -150);
			glRotatef(-90,1,0,0);
			gluDisk(c, 0, 30,30, 20);
		glPopMatrix();



}

void drawCone()
{
	glColor4f(0,0,1, 0.2);
	glPushMatrix();
		glTranslatef(-300,10, -150);
		glRotatef(-90,1,0,0);
		gluCylinder(plat, 1, 10, 30, 50, 40);
	glPopMatrix();
}

void drawDeathStar()
{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txId[5]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
				glTranslatef(-300, 60, -150);
				glColor4f(0.8, 0.8, 1, 0.6);
				glRotatef(planetAngle, 0, 1, 0);
				gluSphere ( q, 25.0, 36, 17 );
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);

}
//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
	float lpos[4] = {10, 10, 10, 1};  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(alienView == false) {
		gluLookAt(camForward, cam_hgt, 0, camForward + 30, cam_hgt, 0, 0, 1, 0);
		glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis
	}
	else {
		Alien aliens[] = {a,a3,a4,a5,a6};
		Alien i = aliens[alienIndex];
		gluLookAt(i.x, i.y+8, i.z-15, i.x, i.y, i.z, 0, 1, 0);
	}

	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

	float spotdir[3] = {0, 1,0};
	float spotpos[4]={-300, 8, -150, 1};
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	glLightfv(GL_LIGHT1,GL_POSITION, spotpos);   //Set spotlight position

	float spotdir3[3] = {0, -1,0};
	float spotpos3[4]={-300, 120, -150, 1};
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotdir3);
	glLightfv(GL_LIGHT3,GL_POSITION, spotpos3);   //Set spotlight position

	glEnable(GL_LIGHTING);

  drawFloor();
	drawPlanet();
	glPushMatrix();
	drawSpaceShip();
	glPopMatrix();
	drawLaunchPad();
	a.drawAlien();
	Alien a2;
	a2.x = -20;
	a2.y = 0;
	a2.z = 10;
	a2.rotateDeg = 0;
	a2.drawAlien();

	drawSkyDome();
	glPushMatrix();
	glTranslatef(0, 10.1 , 200);
	glRotatef(180,0,1,0);
	glTranslatef(0, -10.1 , -200);
	drawPort();
	glPopMatrix();

	glDisable(GL_LIGHT3);
	drawDeathStarPlatform();
	glEnable(GL_LIGHT3);
	a3.drawAlien();
	a4.drawAlien();
	a5.drawAlien();
	a6.drawAlien();

	drawDeathStar();
	drawCone();
	innerElevator();
	drawElevator();

	glutSwapBuffers();

}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	float grey[4] = {0.2, 0.2, 0.2, 1.0};
	float white[4]  = {1.0, 1.0, 1.0, 1.0};

	glClearColor(1, 1, 1, 1.0f);	//Background colour

	float lgt_amb[4] = {0.0, 0.0, 0.0, 1.0};
	float lgt_dif[4] = {1.0, 1.0, 1.0, 1.0};
	float lgt_dif2[4] = {0, 0, 1.0, 1.0};
	float lgt_spe[4] = {1.0, 1.0, 1.0, 1.0};
	float mat_amb[4] = {0.0, 0.0, 1.0, 1.0};
	float mat_dif[4] = {0.0, 0.0, 1.0, 1.0};
	float mat_spe[4] = {1.0, 1.0, 1.0, 1.0};
	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lgt_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lgt_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lgt_spe);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
//spotlight 1
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lgt_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lgt_dif2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lgt_spe);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,2);

	//glEnable(GL_LIGHT2);
	// glLightfv(GL_LIGHT2, GL_AMBIENT, lgt_amb);
	// glLightfv(GL_LIGHT2, GL_DIFFUSE, lgt_dif);
	// glLightfv(GL_LIGHT2, GL_SPECULAR, lgt_spe);
	// glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0);
	// glLightf(GL_LIGHT2, GL_SPOT_EXPONENT,0.01);
//spotlight 2
	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, lgt_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lgt_dif2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lgt_spe);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 80);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT,2);


 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 5000.0);   //Camera Frustum

	q =  gluNewQuadric ( );

	loadTexture();
	gluQuadricDrawStyle (q, GLU_FILL );
	gluQuadricNormals	(q, GLU_SMOOTH );

	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture (q, GL_TRUE);
		s = gluNewQuadric();
		gluQuadricDrawStyle (s, GLU_FILL );
		gluQuadricNormals	(s, GLU_SMOOTH );

		gluQuadricTexture (s, GL_TRUE);

		c = gluNewQuadric();
		gluQuadricDrawStyle (c, GLU_FILL );
		gluQuadricNormals	(c, GLU_SMOOTH );

		gluQuadricTexture (c, GL_TRUE);


		plat = gluNewQuadric();
		gluQuadricDrawStyle (plat, GLU_FILL );
		gluQuadricNormals	(plat, GLU_SMOOTH );

		gluQuadricTexture (plat, GL_TRUE);



}

//------------ Special key event callback ---------------------------------

void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle-=5;
    else if(key == GLUT_KEY_RIGHT) angle+=5;
		else if (key == GLUT_KEY_UP) camForward+=5;
    else if (key == GLUT_KEY_DOWN) camForward-=5;
		else if(key == GLUT_KEY_F11){
			moveSpaceship = true;
			elapsedTime = 0;
		}
		else if(key == GLUT_KEY_F7){
		 cam_hgt++;
		}
		else if(key == GLUT_KEY_F6){
			cam_hgt--;
		}
		else if(key == GLUT_KEY_F2){
			alienView = true;
			alienIndex+=1;
			if(alienIndex > 4)
				alienIndex = 0;
		}
		else if(key == GLUT_KEY_F1){
			alienView = false;
		}
    glutPostRedisplay();

}

void dynamoRotate(int value)
{
  if(value == 0) {
	  dynamoAngle += dynamoSpeed;

	  if(dynamoAngle >= 360)
			dynamoAngle = 0;
  }
   else {
	   dynamoAngle += dynamoSpeed;

	  if(dynamoAngle < 0)
		dynamoAngle = 360;

	  glutPostRedisplay();
	  if(dynamoSpeed > 0)
		dynamoSpeed -=1;

   }
   glutPostRedisplay();
}



//timer function for animations

void timer(int value)
{
		elapsedTime += value;
		//std::cout<<value;
     planetAngle += 0.2;


		if (changeLight == 1){

			red = 1;
			green = 0;
			blue = 1;
			changeLight = 0;
		}
		else{
			red = 1;
			green = 1;
			blue = 1;
			 changeLight = 1;
		}
		if (rotate == 4){
			a.rotateDeg = -a.rotateDeg;
			a4.rotateDeg = -a4.rotateDeg;
			rotate = 1;
		}
		else{
			rotate +=1;
		}


		if (forward){
			if (a.z < 20) {
				a.z += 0.2;
				a4.x -= 0.2;
			}

			else{
				forward = !forward;
			}

		}
		else{
			if (a.z > -20) {
				a.z -= 0.2;
				a4.x += 0.2;
			}
			else{
				forward = !forward;
			}
		}



		if (moveSpaceship && (yTranslate < 40 || dynamoSpeed >=50)){
			yTranslate += shipSpeed*(fmax(15, dynamoSpeed)/15);
			shipSpeed += 0.2;
		}

		if(moveSpaceship && elapsedTime > 30) {
			dynamo = true;
		}

		if(ElevatorMoveUpwards){
			if(upElevator < 980){
				upElevator+=5;
				a3.y +=5;
			}
			else{
				ElevatorMoveUpwards = false;
			}
		}
		else{
			if(upElevator> 0){
				upElevator -=5;
				a3.y -=5;
			}
			else{
				ElevatorMoveUpwards = true;
			}
		}


  dynamoRotate(0);
	if(dynamo && dynamoSpeed < 50)
		dynamoSpeed += 0.2;
	glutPostRedisplay();
	glutTimerFunc(50, timer, 1);
}


//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{

	a.x = 10;
	a.y = 0;
	a.z = 0;
	a.rotateDeg = 30;

	a3.x = 40;
	a3.y = upElevator;
	a3.z = -100;
	a3.rotateDeg = 0;

	a4.x = -40;
	a4.y = 0;
	a4.z = 30;
	a.rotateDeg = 30;

	a5.x = -100;
	a5.y = 0;
	a5.z = - 50;
		// glTranslatef(-200,0, -150);
	a6.x =  -300;
	a6.y = 0;
	a6.z = -100;
	a6.rotateDeg = 0;

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (10, 10);
   glutTimerFunc(50, timer, 0);

   glutCreateWindow ("Space Scene");
   initialize();

   glutDisplayFunc(display);
   glutSpecialFunc(special);

   glutMainLoop();
   return 0;
}
