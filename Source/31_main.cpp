/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/144.html
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

	// 回転用
	float angle = 0.0f;

	//黄色
	GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
	float Radius = 80.0f;

	//3つのベクトル
	struct Vector3f {
		float x;
		float y;
		float z;
	} vec3d;

	void drawLine3D( float x1, float y1, float z1, float x2, float y2, float z2 ) {
		// 線幅
		glLineWidth( 1.0 );
		// 線
		glBegin( GL_LINES );
		glVertex3f( x1, y1, z1 );
		glVertex3f( x2, y2, z2 );
		glEnd();
	}

	void drawMeasure( int measure, float size ) {
		glDisable( GL_LIGHTING );
		glColor4f( 0.5f, 0.5f, 0.5f, 0.5f );
		for( int x=0; x<=measure; x++ ) {
			drawLine3D(x*size-(size*measure/2),0,-(size*measure/2),x*size-(size*measure/2),0,measure*size-(size*measure/2));}

		for( int y=0; y<=measure; y++ ) {
			drawLine3D(-(size*measure/2),0,y*size-(size*measure/2),measure*size-(size*measure/2),0,y*size-(size*measure/2));}

		glDisable( GL_DEPTH_TEST );
		glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		drawLine3D( 0,0,0,(measure/2+2)*size, 0, 0 );
		glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
		drawLine3D( 0, 0, 0, 0, (measure/2+2)*size, 0 );
		glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
		drawLine3D( 0, 0, 0, 0, 0, (measure/2+2)*size );
		glEnable( GL_LIGHTING );
		glEnable( GL_DEPTH_TEST );
	}

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	// 任意軸のベクトルを設定
	vec3d.x = 45.0f;
	vec3d.y = 90.0f;
	vec3d.z = 0.0f;
}
/*
void terminate() {
}
*/
void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 5000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt(
		0.0, 800.0, 800.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	glColor3f( 1, 1, 1 );
	drawMeasure( 16, 40 );

	glMaterialfv( GL_FRONT, GL_DIFFUSE, yellow );
	glRotatef( angle, vec3d.x, vec3d.y, vec3d.z );

	glutSolidCube( 80.0 );

	glutSwapBuffers();
}

void idle() {
	angle += 0.2f;
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

