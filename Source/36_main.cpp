/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/54.html
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
	float z = 0.0f;
	bool flag = false;

	// 緑
	GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
	// 白
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

	// ライトの位置
	GLfloat lightPos[] = { 200.0, 150.0, -500.0, 1.0 };

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// フォグを有効化
	glEnable( GL_FOG );
	// フォグの色を設定
	glFogfv( GL_FOG_COLOR, white );
	// フォグの計算式を設定
	glFogi( GL_FOG_MODE, GL_LINEAR );
	// フォグの計算を頂点単位でやるかピクセル単位でやるか
	glFogi( GL_FOG_HINT, GL_FASTEST );
	// フォグの開始位置を設定
	glFogi( GL_FOG_START, 10 );
	// フォグの終了位置を設定
	glFogi( GL_FOG_END, 2000 );
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
	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 2000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// 視点の設定
	gluLookAt(
		0.0, 100.0, -1000.0,	// カメラの座標
		0.0, 0.0, 0.0,			// 注視点の座標
		0.0, 1.0, 0.0			// 画面の上方向を指すベクトル
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, green );
	// 平行移動
	glTranslatef( 0.0f, 0.0f, z );
	glutSolidSphere( 40.0, 16, 16 );

	glutSwapBuffers();
}

void idle() {
	if ( flag ) {
		z -= 0.5f;
	}
	else {
		z += 0.5f;
	}
	if ( z >  500.0f ) flag = true;
	if ( z < -500.0f ) flag = false;

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

