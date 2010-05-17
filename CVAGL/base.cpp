// Date Mon May 17 12:06:59 MSD 2010
// peko@gasubasu.com

// Configuration for TextMate: 
// TM_CXX_FLAGS=-arch i386 -framework GLUT -framework OpenGL -framework OpenCV

// Description:
// Just simple integration of OpenGL & OpenCV libraries

// Dependencies:
// OpenGL.framework, GLUT.framework, OpenCV.framework

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <OpenCV/cv.h>
#include <OpenCV/highgui.h>


/// CONSTANTS ///

const int VIEWPORT_W = 720;
const int VIEWPORT_H = 480;

const int count = 8;
const float K = 1000;


/// VARS ///

//OpenCV
CvCapture *videoCapture;
IplImage *captureImg;

// id of GL window for destroy
GLint w_id;

// Misc
int lastFrameTime = 0;
int currentFrame = 0;
int frameLength = 10;


/// FUNC DECLARATION ///

void init ();
void display ();
void reshape (int w, int h);
void passiveMouseMotion (int x, int y);
void mouseMotion (int x, int y);
void mouseClick (int button, int state, int x, int y);
void keyboard (unsigned char key, int x, int y);
void idle(void);
void captureFrame(void);

float rnd () { return float(rand())/RAND_MAX; }
int grand( int i ) { return (i) ? rand() %i - rand() %i : 0; }


/// MAIN ///

int main (int argc, char *argv[]) {
	
	//	OPENCV INIT
	videoCapture = cvCreateCameraCapture(0);
	assert(videoCapture);
		
	// OPENGL INIT
	glutInit(&argc, argv);          /* setup GLUT */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(VIEWPORT_W, VIEWPORT_H);
	glutInitWindowPosition(128, 128);
    w_id = glutCreateWindow(argv[0]);      /* open a window */
	init();

	// GLUT HANDLERS
	glutIdleFunc(idle);
	glutDisplayFunc(display);       /* tell GLUT how to fill window */
    glutReshapeFunc(reshape);       /* update shape of window */
	glutMouseFunc(mouseClick);
	glutKeyboardFunc (keyboard);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	
    glutMainLoop();                 /* let glut manage i/o processing */

	return 0;
	
}

void init (void) {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	
}

void captureFrame(void) {
	// Capture next frame
	captureImg = cvQueryFrame(videoCapture);
	
	// just some opencv conversions 
	// processedVideo = cvCreateImage( cvGetSize(captureImg), 8, 1 );
	// cvSmooth(captureImg, captureImg, CV_GAUSSIAN, 21, 21);
	// cvCvtColor(captureImg, processedVideo, CV_BGR2GRAY);
	// cvThreshold( processedVideo, processedVideo, rand()%128, 128+rand()%128, CV_THRESH_BINARY );
	// cvThreshold( processedVideo, processedVideo, 50, 250, CV_THRESH_BINARY_INV );
	// int Nc = cvFindContours(processedVideo, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);
	// first_contour = cvApproxPoly(first_contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 1, 1);

	// KEY OF ITEGRATION
	// CONVERTING OPENCV IMAGE TO OPENGL RGB TEXTURE
	cvCvtColor(captureImg, captureImg, CV_BGR2RGB);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, captureImg->width, captureImg->height, GL_RGB, GL_UNSIGNED_BYTE, captureImg->imageData);
}

/// GLUT HANDLERS ///

void display (void) {

	if (lastFrameTime == 0) {
        lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    }
	
	int now = glutGet(GLUT_ELAPSED_TIME);
    int elapsedMilliseconds = now - lastFrameTime;
    float elapsedTime = elapsedMilliseconds / 1000.0f;
    lastFrameTime = now;

	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    	
	// Set Projection Matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VIEWPORT_W, VIEWPORT_H, 0);
			
	glClear(GL_COLOR_BUFFER_BIT);
	
	// CAMERA
	glEnable(GL_TEXTURE_2D);
	
	// Switch to Model View Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(VIEWPORT_W, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(VIEWPORT_W, VIEWPORT_H);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, VIEWPORT_H);
	glEnd();
		
}

void idle(void) {
	
	int now = glutGet(GLUT_ELAPSED_TIME);
	
	if (currentFrame < now/frameLength) {
		
		currentFrame = now/frameLength + 1;
		captureFrame();
		
		// Update View port
		glutSwapBuffers();
	    glutPostRedisplay();
		
	}
	
}

void mouseClick (int button, int state, int x, int y) {
	
	// switch(button) {
	// 	
	// 	case GLUT_LEFT_BUTTON:
	// 		if(state == GLUT_DOWN) {
	// 			boom();
	// 			// glutIdleFunc(spinDisplay)
	// 		};
	// 		break;
	// 		
	// 	// case GLUT_RIGHT_BUTTON:
	// 	// 	if(state == GLUT_DOWN) glutIdleFunc(NULL);
	// 	// 	break;
	// 
	// 	default:
	// 		break;
	// }
	// 
}

void mouseMotion (int x, int y) {
	
	// std::cout << "mm:" << x << ":" << y << " "; 

	// User must press the SHIFT key to change the 
	// rotation in the X axis
	// if (specialKey != GLUT_ACTIVE_SHIFT) {
	// 
	// 	// setting the angle to be relative to the mouse 
	// 	// position inside the window
	// 	if (x < 0)
	// 		angleX = 0.0;
	// 	else if (x > width)
	// 		angleX = 180.0;
	// 	else
	// 		angleX = 180.0 * ((float) x)/height;
	// }
}

void passiveMouseMotion(int x, int y) {
	
	// std::cout << "pm:" << x << ":" << y << " "; 
	
	// mp.x = x;
	// mp.y = 480 - y;
	// 
	// the ALT key was used in the previous function
	// if (specialKey != GLUT_ACTIVE_ALT) {
	// 	// setting red to be relative to the mouse 
	// 	// position inside the window
	// 	if (x < 0)
	// 		red = 0.0;
	// 	else if (x > width)
	// 		red = 1.0;
	// 	else
	// 		red = ((float) x)/height;
	// 	// setting green to be relative to the mouse 
	// 	// position inside the window
	// 	if (y < 0)
	// 		green = 0.0;
	// 	else if (y > width)
	// 		green = 1.0;
	// 	else
	// 		green = ((float) y)/height;
	// 	// removing the blue component.
	// 	blue = 0.0;
	// }
}

void reshape (int w, int h) {
    glViewport(0, 0, w, h);         /* Establish viewing area to cover entire window. */
}

void keyboard (unsigned char key, int x, int y) {
	
	switch (key) {
		
		//	ESC – quit
		case 27:
			std::cout << videoCapture << "\n";
			if (videoCapture) cvReleaseCapture(&videoCapture);
			std::cout << videoCapture << "\n";
			// if (captureImg) cvReleaseImage(&captureImg);
			// glutDestroyWindow(w_id);
			
			exit(0);
			break;

		case 's':
			break;
			
			
		default:
			break;
	}
}