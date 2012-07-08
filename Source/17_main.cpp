/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/114.html
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
	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	
	float Radius = 80.0f;
	float posX = 120.0f;
	float posY = 0.0f;
	float posZ = 80.0f;

	// 3D空間にラインを描画
	void drawLine3D( float x1, float y1, float z1, float x2, float y2, float z2 ) {
		// 線幅
		glLineWidth( 1.0f );
		// 線
		glBegin( GL_LINES );
		glVertex3f( x1, y1, z1 );
		glVertex3f( x2, y2, z2 );
		glEnd();
	}
	
	// 3D空間にラインで升目を描画
	void drawMeasure( int measure, float size ) {
		glDisable( GL_LIGHTING );
		glColor4f( 0.5f, 0.5f, 0.5f, 0.5f );
		for ( int x=0; x<=measure; ++x ) {
			drawLine3D( 
				x*size-(size*measure/2),
				0,
				-(size*measure/2),
				x*size-(size*measure/2),
				0,
				measure*size-(size*measure/2)
				);
		}
		for ( int y=0; y<=measure; ++y ) {
			drawLine3D(
				-(size*measure/2),
				0,
				y*size-(size*measure/2),
				measure*size-(size*measure/2),
				0,
				y*size-(size*measure/2)
				);
		}
		glDisable( GL_DEPTH_TEST );
		// 軸を示すラインを描画
		glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		drawLine3D( 0, 0, 0, (measure/2+2)*size, 0, 0 );
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
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 30.0f, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0f, 5000.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		300.0f, 800.0f, 800.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
		);

	glColor3f( 1.0f, 1.0f, 1.0f );
	// 升目を描画
	drawMeasure( 16, 40.0f );

	// 回転基準の目印
	glMaterialfv( GL_FRONT, GL_DIFFUSE, yellow );
	glTranslatef( posX, 50.0f, posZ );
	glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( angle, 0.0f, 0.0f, 1.0f );
	glutSolidCone( 10.0f, 50.0f, 4, 3 );

	// 円運動
	// 視点座標へ移動
	glLoadIdentity();
	gluLookAt(
		300.0f, 800.0f, 800.0f,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0
		);

	// 回転基準位置に移動
	glTranslatef( posX, posY, posZ );
	glRotatef( angle, 0.0f, 1.0f, 0.0f );// Y軸を回転
	// 回転半径を足す(ちょっと大回りするように。)
	glTranslatef( Radius, 0.0f, 0.0f );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, white );
	// 運動する球を描画
	glutSolidSphere( 10.0,16,16 );

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

