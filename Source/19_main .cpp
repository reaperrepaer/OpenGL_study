/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/35.html
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

	GLfloat aqua[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	// ライトを付けたままワイヤーフレームにすることもできる。
//	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// ワイヤーフレーム表示
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 30.0f, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0f, 1000.0f );

	gluLookAt(
		150.0f, 150.0f, -150.0f,
		0.0f, 0.0f, 0.0,
		0.0f, 1.0f, 0.0f
		);

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	glMaterialfv( GL_FRONT, GL_DIFFUSE, aqua );
	glutSolidSphere( 40.0f, 16, 16 );

	glutSwapBuffers();
}

void idle() {
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

