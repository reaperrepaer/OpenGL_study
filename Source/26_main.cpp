/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/83.html
 * http://wisdom.sakura.ne.jp/system/opengl/gl10.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <string>
#include <gl/glew.h>
#include <freegl/glut.h>
#include <lodepng.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

}// unnamed namespace

void initialize() {
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glutSwapBuffers();
}

// keyには押されたキーのアスキーコード、
// xとyにはキーが押されたときのマウスカーソルの位置が渡されてくる。
//
// 但し矢印キーやファンクションキーは特殊キー扱いとなるので、このコールバックでは検出できない。
// また、５キー以上の同時検出もできないらしい。
void keyEvent( unsigned char key, int x, int y ) {
	// スペースキー
	if ( key == ' ' ) {
		glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
	}
	// Zキー
	if ( key == 'z' ) {
		glClearColor( 0.0f, 1.0f, 0.0f, 1.0f );
	}
	// Xキー
	if ( key == 'x' ) {
		glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
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
	// キーボード入力のコールバックを登録する
	glutKeyboardFunc( keyEvent );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

