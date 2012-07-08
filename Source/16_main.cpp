/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/70.html
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

	float angle = 0.0f;
	GLfloat pink[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };

	// 直方体
	void drawCuboid( float width, float height, float depth ) {
		glBegin( GL_QUADS );
		// 前
		glNormal3f( 0.0f, 0.0f, -1.0f );
		glVertex3f(  width/2,  height/2, depth/2 );
		glVertex3f( -width/2,  height/2, depth/2 );
		glVertex3f( -width/2, -height/2, depth/2 );
		glVertex3f(  width/2, -height/2, depth/2 );

		// 左
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( width/2,  height/2,  depth/2 );
		glVertex3f( width/2,  height/2, -depth/2 );
		glVertex3f( width/2, -height/2, -depth/2 );
		glVertex3f( width/2, -height/2,  depth/2 );

		// 右
		glNormal3f( -1.0f, 0.0f, 0.0f );
		glVertex3f( -width/2,  height/2, -depth/2 );
		glVertex3f( -width/2,  height/2,  depth/2 );
		glVertex3f( -width/2, -height/2,  depth/2 );
		glVertex3f( -width/2, -height/2, -depth/2 );

		// 後
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glVertex3f(  width/2,  height/2, -depth/2 );
		glVertex3f( -width/2,  height/2, -depth/2 );
		glVertex3f( -width/2, -height/2, -depth/2 );
		glVertex3f(  width/2, -height/2, -depth/2 );

		// 上
		glNormal3f( 0.0f, 1.0f, 0.0f );
		glVertex3f(  width/2, height/2,  depth/2 );
		glVertex3f( -width/2, height/2,  depth/2 );
		glVertex3f( -width/2, height/2, -depth/2 );
		glVertex3f(  width/2, height/2, -depth/2 );

		// 下
		glNormal3f( 0.0f, -1.0f, 0.0 );
		glVertex3f(  width/2, -height/2,  depth/2 );
		glVertex3f( -width/2, -height/2,  depth/2 );
		glVertex3f( -width/2, -height/2, -depth/2 );
		glVertex3f(  width/2, -height/2, -depth/2 );
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
		150.0f, 100.0f, -200.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
		);

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, pink );
	
	// 回転
	glRotatef( angle, 1.0f, 0.5f, 0.0f );
	drawCuboid( 50.0f, 100.0f, 30 );

	glutSwapBuffers();
}

void idle() {
	angle += 0.02f;
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

