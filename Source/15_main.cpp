/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/69.html
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

	float angleX = 0.0f;
	GLfloat aqua[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };

	// 円柱
	// 自力といってもコピペ
	// 頭に３角ポリゴンで作った円を置いて、
	// 側面は４角形ポリゴンで塞ぐだけ。
	void renderCylinder( float radius, float height, int sides ) {
		double pi = 3.1415;
		// 上面
		glNormal3d( 0.0, 1.0, 0.0 );// 法線を上向きに設定
		glBegin( GL_POLYGON );
		for(double i = 0; i < sides; i++) {
			double t = pi*2/sides * (double)i;
			glVertex3d(radius * cos(t), height, radius * sin(t));
		}
		glEnd();

		// 側面
		glBegin( GL_QUAD_STRIP );
		for ( double i=0; i<=sides; i=i+1 ) {
			double t = i*2*pi/sides;
			// 法線は面に対しての外向きに
			glNormal3f((GLfloat)cos(t), 0.0, (GLfloat)sin(t));
			glVertex3f((GLfloat)(radius * cos(t)), -height, (GLfloat)(radius * sin(t)));
			glVertex3f((GLfloat)(radius * cos(t)), height, (GLfloat)(radius * sin(t)));
		}
		glEnd();

		// 下面
		glNormal3d( 0.0f, -1.0f, 0.0f );// 法線を下向きに設定
		glBegin( GL_POLYGON );
		for ( double i = sides; i >= 0; --i ) {
			double t = pi*2/sides * (double)i;
			glVertex3d(radius * cos(t), -height, radius * sin(t));
		}
		glEnd();
	}

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
	
	// 回転
	glRotatef( angleX, 1.0f, 0.0f, 0.0f );
	renderCylinder( 30.0f, 50.0f, 10 );

	glutSwapBuffers();
}

void idle() {
	angleX += 0.02f;
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

