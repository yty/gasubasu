#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <time.h>


GLfloat year = 0;
GLfloat day = 0;
float rnd() { return float(rand())/RAND_MAX; }

void Reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Display (void) {
	day += 0.2; year += 1.0;
	glClear(GL_COLOR_BUFFER_BIT); glColor3f(1.0, 1.0, 1.0);
	
	glPushMatrix();
	glutWireSphere(1.0, 20.0, 20.0); /* draw sun */
	glRotatef( (GLfloat) year, 0.0, 1.0, 0.0); /* planet rotate around sun */ 
	glTranslatef(1.0, 0.0, 0.0); /* orbit of 2 units from sun */
	glRotatef( (GLfloat) day, 0.0, 1.0, 0.0); /* planet rotate around himself */
	glutWireSphere(0.2, 10.0, 10.0); /* draw smaller planet */
	glPopMatrix();
	
	
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	/* creating window ... */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("jack");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}