/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/23.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <cstdint>
#include <cmath>
#include <freegl/glut.h>

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	const float PAI = 3.1415926535897932384626433832795f;
	const float TO_RAD = PAI / 180.0f;
	const float TO_DEG = 180.0f / PAI;
}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	glFlush();
}

int main( int argc, char *argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

