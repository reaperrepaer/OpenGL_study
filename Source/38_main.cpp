/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/97.html
 *
 * ステンシルバッファの値をみて、描画するかしないかを決めることができる。
 * 画面の切り抜き(クリッピング)とかができるようになる。
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

	// 平行移動用
	float x = 0.0f;
	bool flag = false;
	//緑
	GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
	//ライトの位置
	GLfloat lightPos[] = { 200.0, 150.0, -500.0, 1.0 };

	void drawSquareFill2D( int x1,int y1,int x2, int y2 ) {
		glBegin( GL_QUADS );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y1 );
		glVertex2i( x2, y2 );
		glVertex2i( x1, y2 );
		glEnd();
	}

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClearStencil( 0 );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

/*
void terminate() {
}
*/

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	// 2D切り替え
	glMatrixMode( GL_PROJECTION );			// 射影変換行列設定
	glPushMatrix();							// 現在の射影変換行列を保存
	glLoadIdentity();						// 単位行列を設定
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );	// 正射影変換設定
	glMatrixMode( GL_MODELVIEW );			// モデルビュー変換行列設定
	glPushMatrix();							// 現在のモデルビュー行列を保存
	glLoadIdentity();						// 単位行列を設定

	glDisable( GL_LIGHTING );
	glEnable( GL_STENCIL_TEST );
	glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
	glStencilFunc( GL_ALWAYS, 1, ~0 );
	glStencilOp( GL_KEEP,GL_REPLACE,GL_REPLACE );
	// ステンシルバッファに書き込む
	drawSquareFill2D( 70, 80, 250, 150 );
	glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );

	glStencilFunc( GL_EQUAL, 1, ~0 );// ステンシルが1の所を描画

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();// 射影変換行列を復元
	glLoadIdentity();

	// 視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 1000.0 );
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();// モデルビュー行列を復元
	glLoadIdentity();

	// 視点の設定
	gluLookAt(
		150.0, 100.0, -200.0,	// カメラの座標
		0.0, 0.0, 0.0,			// 注視点の座標
		0.0, 1.0, 0.0			// 画面の上方向を指すベクトル
		);

	glEnable( GL_LIGHTING );
	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, green );
	// 平行移動
	glTranslatef( x, 0.0f, 0.0f );
	// 球を描画
	glutSolidSphere( 40.0, 16, 16 );

	glDisable( GL_STENCIL_TEST );

	glutSwapBuffers();
}

void idle() {
	if ( flag ) {
		x -= 0.05f;
	}
	else {
		x += 0.05f;
	}
	if ( x >  50.0f) flag = true;
	if ( x < -50.0f) flag = false;

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

