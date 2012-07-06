/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/99.html
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

	// 回転用
	float angleX = 0.0f;
	// ズームイン、ズームアウトを表現する視野角
	float zoom = 50.0f;
	// インかアウトか
	bool flag = false;

	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	// オレンジ
	GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 150.0f, -500.0f, 1.0f };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	// デプステストを有効化
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
	gluPerspective( zoom, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0f, 1000.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		150.0f, 100.0f, -200.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
		);

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	// 地面
	glMaterialfv( GL_FRONT, GL_DIFFUSE, orange );
	glBegin( GL_QUADS );
	glVertex3i(  100, -30,  100 );
	glVertex3i( -100, -30,  100 );
	glVertex3i( -100, -30, -100 );
	glVertex3i(  100, -30, -100 );
	glEnd();

	// キューブ5
	glRotatef( angleX, 1.0f, 0.0f, 0.0f );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, red );
	glutSolidCube( 40.0f );

	glutSwapBuffers();
}

void idle() {

	angleX += 0.02f;
	if ( flag ) {
		zoom += 0.02f;
	}
	else {
		zoom -= 0.02f;
	}

	if ( zoom < 15.0f ) flag = true;
	if ( zoom > 50.0f ) flag = false;

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

