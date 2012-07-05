/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/21.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <cstdint>
#include <freegl/glut.h>

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;
}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	// ê¸ÇÃëæÇ≥Çê›íË
	glLineWidth( 1.0f );
	glBegin( GL_LINES );
	glVertex2i( 100, 100 );
	glVertex2i( 200, 200 );
	glEnd();

	glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
	glLineWidth( 10.0f );
	glBegin( GL_LINES );
	glVertex2i( DISPLAY_WIDTH, 0 );
	glVertex2i( 0, DISPLAY_HEIGHT );
	glEnd();

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

