#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
	#define M_PI 3.141592653589793238463
#endif

#define NUMBER_OF_SPIRALS 3
#define NUMBER_OF_SCALES 20

using namespace std;

GLint counter = 0;
GLfloat scale = 1;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	switch (key) {
	case 27: //Escape key
		exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawBox(){
	glTranslatef(0.0f, 10.0f, -30.0f);
	glBegin(GL_QUADS);									// Draw A Quad
	glColor3f(0.0f, 1.0f, 0.0f);						// Set The Color To Blue
	glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
	glVertex3f(1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)

	glColor3f(1.0f, 0.5f, 0.0f);						// Set The Color To Orange
	glVertex3f(1.0f, -1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom Left Of The Quad (Bottom)
	glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom Right Of The Quad (Bottom)

	glColor3f(1.0f, 0.0f, 0.0f);						// Set The Color To Red
	glVertex3f(1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
	glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom Right Of The Quad (Front)

	glColor3f(1.0f, 1.0f, 0.0f);						// Set The Color To Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);					// Top Right Of The Quad (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Top Left Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Bottom Left Of The Quad (Back)
	glVertex3f(1.0f, 1.0f, -1.0f);					// Bottom Right Of The Quad (Back)

	glColor3f(0.0f, 0.0f, 1.0f);						// Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom Right Of The Quad (Left)

	glColor3f(1.0f, 0.0f, 1.0f);						// Set The Color To Violet
	glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right Of The Quad (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();
	glTranslatef(0.0f, -10.0f, 30.0f);

}

void drawSphere(GLdouble x_translate, GLdouble y_translate, GLdouble z_translate, GLdouble radius)
{
	glPushMatrix();
		glTranslated(x_translate, y_translate, z_translate);
		glutSolidSphere(radius, 50, 50);
	glPopMatrix();
}
void drawSpring(){
	GLfloat t, t_max = 2 * NUMBER_OF_SPIRALS * M_PI, x, y, z;
	GLfloat x_ball = t_max + M_PI / 2, y_ball, z_ball = sin(t_max + M_PI / 2) / 2;
	glTranslatef(0.0f, 0.0f, -10.0f);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	
		for (t = M_PI / 2; t <= t_max + M_PI / 2; t += 0.1f)
		{
			x = cos(t) / 2;
			y = -t / 10 * scale;
			z = sin(t) / 2;
			y_ball = -(t_max + M_PI / 2) / 10 * scale;
			//glVertex3f(x, y, z);
			glPushMatrix();
				//glTranslatef(0.0, 11.5, -29.0);
				drawSphere(x, y, z, 0.1);
				drawSphere(0, y_ball - 0.4, 0, 0.4);
			glPopMatrix();
			//cout << x_ball << " " << y_ball << " " << z_ball << endl;
		}
	glEnd();




}
void drawScene() {

	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	drawBox();
	drawSpring();

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void update(int value)
{
	if (counter <= NUMBER_OF_SCALES)
	{
		scale += 0.01;
	}
	if (counter > NUMBER_OF_SCALES)
	{
		scale -= 0.01;
	}
	if (counter == 2 * NUMBER_OF_SCALES)
	{
		counter = 0;
	}
	counter++;
	//cout << scale << endl;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800); //Set the window size

	//Create the window
	glutCreateWindow("String");
	initRendering(); //Initialize rendering

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}