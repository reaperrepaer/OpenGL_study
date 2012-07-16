/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/51.html
 *
 * 法線ベクトルは２次元ではある線に垂直なベクトル。
 * ３次元では面に垂直なベクトル。
 * 光の計算や面の裏表を判断するのに使われる。
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

	//黄色
	GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };

	// ライトの位置
	GLfloat lightPos[] = { 0.0f, 0.0f, 50.0f, 1.0f };

	float normal = -5.0f;
	bool flag = false;

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}
/*
void terminate() {
}
*/
void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH,  DISPLAY_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// 視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
	gluPerspective( 30.0, (double) DISPLAY_WIDTH / (double) DISPLAY_HEIGHT, 1.0, 1000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// 視点の設定
	gluLookAt(
		0.0,0.0,-100.0,	// カメラの座標
		0.0,0.0,0.0,	// 注視点の座標
		0.0,1.0,0.0		// 画面の上方向を指すベクトル
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, orange );
	glBegin( GL_POLYGON );
	// 法線を設定
	glNormal3f( -normal, -normal, -normal );
	glVertex3f( 0 , -15 , 0 );
	glVertex3f( -30 ,15 , 0 );
	glVertex3f( 0 , 15 , 0 );
	glEnd();

	glutSwapBuffers();
}

void idle() {
	// 法線をフレーム毎に加減算して動かしてみる
	if ( flag ) {
		normal -= 0.001f;
	}
	else {
		normal += 0.001f;
	}
	if ( normal > 0.0f ) {
		flag = true;
	}
	if ( normal < -5.0f ) {
		flag = false;
	}
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

