/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/32.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <freegl/glut.h>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	bool flag = false;
	float size = 1.0f;
	GLfloat aqua[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 30.0f, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0f, 1000.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		150.0f, 500.0f, -150.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
		);

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	glMaterialfv( GL_FRONT, GL_DIFFUSE, aqua );
	// 拡大縮小
	glScalef( size, size, size );
	// 回転
	glRotatef( 280, 1.0f, 0.0f, 0.0f );
	glutSolidCone( 40.0f, 100.0f, 8, 8 );

	glutSwapBuffers();
}

void idle() {
	if ( flag ) {
		size -= 0.001f;
	}
	else {
		size += 0.001f;
	}

	if ( size > 3.0f ) flag = true;
	if ( size < 1.0f ) flag = false;
	glutPostRedisplay();
}

int main( int argc, char *argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

