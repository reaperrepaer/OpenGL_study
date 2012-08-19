/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/80.html
 * wglについて
 * http://sky.geocities.jp/freakish_osprey/opengl/opengl_vsync.htm
 *
 * 垂直同期
 *
 * 
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <freegl/glut.h>
#include "TestLib.h"

using namespace std;

namespace {

	const int DISPLAY_WIDTH = 640;
	const int DISPLAY_HEIGHT = 480;

	float anglex = 0.0f;

	// 灰色
	GLfloat gray[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	
	// ライトの位置
	GLfloat lightpos[] = { 200.0f, 150.0f, -500.0f, 1.0f };
	
	// 描画フレーム数
	int count = 0;
	int Max = 0;

	// 垂直同期フラグ
	int vsync = 1;
	string str = "";

	char buf[255];
	char buf2[255];

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
	anglex += 0.2f;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 1000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt(
		150.0, 100.0, -200.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, gray );

	// 回転
	glRotatef( anglex, 0.8f, 0.5f, 0.3f );// X軸を回転

	// トーラスの描画
	glutSolidTorus( 20.0, 40.0, 16, 16 );

	glutSwapBuffers();
	++count;
	_itoa_s( count, buf, 255, 10 );
	_itoa_s( Max, buf2, 255, 10 );

	str = "スペースキーで垂直同期On/Off切り替え FPS[";
	str += buf2;
	str += "] FRAME[";
	str += buf;
	str += "]";
	glutSetWindowTitle( str.c_str() );
}

// タイマーコールバック
void timer( int value ) {
	Max = count;
	count = 0;
	glutTimerFunc( 1000, timer, 0 );// もう一回
}

void keyEvent( unsigned char key, int x, int y ) {
	if ( key == ' ' ) {
		// WGL_EXT_swap_controlがサポートされているかの確認。
		if ( glewGetExtension( "WGL_EXT_swap_control" ) ) {
			vsync = 1 - vsync;
			if ( vsync == 0 ) {
				// 垂直同期オフ
				// 0は同期なし
				wglSwapIntervalEXT(0);
			}
			else {
				// 垂直同期オン
				// １だとバッファスワップが次のフレームまで待たされるようになる。
				wglSwapIntervalEXT(1);
			}
		}
		count = 0;
	}
}

void idle() {
	glutPostRedisplay();
}

int main( int argc, char* argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutTimerFunc( 1000 , timer, 0 );
	glutKeyboardFunc( keyEvent );
	glutIdleFunc( idle );

	glewInit();

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

