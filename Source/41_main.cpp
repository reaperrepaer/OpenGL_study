/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/98.html
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
	float anglex = 0.0f;

	// オレンジ
	GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };

	// ライトの位置
	GLfloat lightpos[] = { 0.0, 100.0, 0.0, 1.0 };

	// ディスプレイリスト
	GLuint ListID = 0;

	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat dir[] = { 0.0f, -1.0f, 0.0f };

	void Square( int x1, int y1, int x2, int y2 ) {
		glVertex3i( x1, 0, y1 );
		glVertex3i( x2, 0, y1 );
		glVertex3i( x2, 0, y2 );
		glVertex3i( x1, 0, y2 );
	}

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	ListID = glGenLists( 1 );
	glNewList( ListID, GL_COMPILE );// ディスプレイリストに保存開始
	glBegin( GL_QUADS );
	// １ｘ１の矩形（ピクセル）で四角を作る
	for ( int i=0; i<100; i++ ) {
		for ( int j=0; j<100; j++ ) {
			Square( i-50, j-50, i+1-50, j+1-50 );
		}
	}
	glEnd();
	glEndList();// 保存終了
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
		150.0, 100.0, -200.0,	// カメラの座標
		0.0, 0.0, 0.0,			// 注視点の座標
		0.0, 1.0, 0.0			// 画面の上方向を指すベクトル
		);

	// ライトの位置を設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );

	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.001f );
	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001f );
	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0001f );
	// ライトの向きを設定
	glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, dir );
	glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f );
	glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f );

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange );

	// 回転
	glRotatef( anglex, 1.0f, 0.0f, 0.0f );// X軸を回転
	glCallList( ListID );

	glutSwapBuffers();
}

void idle() {
	anglex += 0.02f;
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

