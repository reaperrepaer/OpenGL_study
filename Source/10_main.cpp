/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/29.html
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

	// 赤
	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	// ライトの位置
	GLfloat lightpos[] = { 200.0f, 150.0f, -500.0f, 1.0f };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	// ライティングを有効に
	glEnable( GL_LIGHTING );
	// ライト０を有効に
	glEnable( GL_LIGHT0 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );
	
	// ビューポート変換の設定
	// 3Dのレンダリング結果をスクリーン座標に変換する為の設定
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	// 射影変換の設定
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	// 視野角, アスペクト比(ウィンドウの幅/高さ), 描画する範囲(最も近い距離, 最も遠い距離)
	gluPerspective( 30.0f, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0f, 1000.0f );
	
	// モデルビュー変換の設定
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// 視点の設定
	gluLookAt(
		150.0f, 100.0f, -200.0f,	// カメラの座標
		0.0f, 0.0f, 0.0f,			// 注視点の座標
		0.0f, 1.0f, 0.0f			// 画面の上方向を指すベクトル
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, red );
	// キューブを描画
	glutSolidCube( 40.0f );

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

