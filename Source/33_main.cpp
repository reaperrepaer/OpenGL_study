/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/52.html
 *
 * デプスバッファを使って奥行きを判定する。
 * これを使うと後から描画したものが手前にくるのではなく、
 * Z値によって判断される。
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

	// 黄色
	GLfloat yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// 紫
	GLfloat purple[] = { 0.5f, 0.0f, 1.0f, 1.0f };

	// ライトの位置
	GLfloat lightPos[] = { 0.0f, 0.0f, 50.0f, 1.0f };

	float depth = -3.0f;
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
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	// 視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 1000.0 );
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
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow );
	glBegin( GL_POLYGON );
	glVertex3f( 0 , -15 , 0 ); // こっちはZ0の位置に
	glVertex3f( -30 ,15 , 0 );
	glVertex3f( 0 , 15 , 0 );
	glEnd();

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, purple );
	glBegin( GL_POLYGON );
	glVertex3f( 15 , -15 , 10 ); // こっちはZ10
	glVertex3f( -15 ,15 , 10 );
	glVertex3f( 15 , 15 , 10 );
	glEnd();

	glutSwapBuffers();
}

void idle() {
	if ( flag ) {
		depth -= 0.001f;
	}
	else {
		depth += 0.001f;
	}
	// デプステストの切り替え
	if ( depth > 0.0f ) {
		flag = true;
		glEnable( GL_DEPTH_TEST );
	}
	if ( depth < -3.0f ) {
		flag = false;
		glDisable( GL_DEPTH_TEST );
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

