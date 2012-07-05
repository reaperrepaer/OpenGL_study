/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/22.html
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

	// 四角枠描画
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glLineWidth( 1.0f );
	glBegin( GL_LINE_LOOP );
	glVertex2i( 100, 100 );
	glVertex2i( 200, 100 );
	glVertex2i( 200, 200 );
	glVertex2i( 100, 200 );
	glEnd();

	// 四角形(塗りつぶし)描画
	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	glBegin( GL_QUADS );
	glVertex2i( 0, 0 );
	glVertex2i( 100, 0 );
	glVertex2i( 100, 100 );
	glVertex2i( 0, 100 );
	glEnd();

	// 矩形である必要はない。
	glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
	glBegin( GL_QUADS );
	glVertex2i( 200, 0 );
	glVertex2i( 250, 50 );
	glVertex2i( 280, 120 );
	glVertex2i( 180, 60 );
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

