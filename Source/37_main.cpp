/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/77.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <string>
#include <freegl/glut.h>

#include "TestLib.h"

using namespace std;

namespace {

	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	void drawLine2D( int x1, int y1, int x2, int y2, float size ) {
		glLineWidth( size );
		glBegin( GL_LINES );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y2 );
		glEnd();
	}

}// unnamed namespace

void initialize() {
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}
/*
void terminate() {
}
*/
void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
	drawLine2D( 120, 40, 300, 180, 1.0 );// アンチエイリアスなしの線

	// ラインのアンチエイリアス有効化
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
	drawLine2D( 20, 40, 200, 180, 1.0 );// アンチエイリアスの線
	glDisable( GL_LINE_SMOOTH );
	glDisable( GL_BLEND );

	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}

int main( int argc, char* argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

