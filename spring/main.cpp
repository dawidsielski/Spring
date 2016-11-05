#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;


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

void drawBox(GLfloat w, GLfloat h, GLfloat d)
{
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
}

void drawScene() {

	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	drawBox(1, 1, 1);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void update(int value)
{

	glutPostRedisplay();
	glutTimerFunc(35, update, 0);
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