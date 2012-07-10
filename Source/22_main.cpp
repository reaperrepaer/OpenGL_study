/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/73.html
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
	GLfloat lightpos[] = { 200.0f, 150, -500.0f, 1.0f };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// カラーマテリアルを両面のディフェーズカラーに設定する。
	glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );
	// マテリアルカラーを有効に。
	glEnable( GL_COLOR_MATERIAL );
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
		0.0f, 0.0f, 0.0,
		0.0f, 1.0f, 0.0f
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	// 回転
	glRotatef( angleX, 1.0f, 0.0f, 0.0f );// X軸を回転
	glutSolidTorus( 20.0f, 40.0f, 16, 16 );

	glutSwapBuffers();
}

void timer( int value ) {
	// カラーを指定する
	glColor3f(
		(GLfloat)(rand()%100)/100,
		(GLfloat)(rand()%100)/100,
		(GLfloat)(rand()%100)/100
		);
	glutTimerFunc( 200, timer, 0 );// もう一回
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
	// 一定時間が経過でイベントを発生させるコールバック関数を設定
	glutTimerFunc( 200, timer, 0 );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

