/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/76.html
 *
 * アルファブレンディングは既に描画済みの色に対してブレンドされるので
 * 陰面消去と同時に使う場合は注意が必要になる。
 *
 * つまり、透明のものを先に描画してしまうと
 * 透明色が反映されなかったりする。
 *
 * [解決方法]
 * 1.不透明なオブジェクトを描画
 * 2.半透明オブジェクトをZソート(視点からの奥行き順)
 * 3.半透明オブジェクトの、奥にあるものから描画
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <string>
#include <gl/glew.h>
#include <freegl/glut.h>

#include "TestLib.h"

using namespace std;

void keyEvent( unsigned char key, int x, int y );

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	int Current = -1;
	string str = "";

}// unnamed namespace

void initialize() {
	glewInit();
	glClearColor( 0.5f, 0.5f, 0.5f, 1.f );
	glEnable( GL_DEPTH_TEST );
	keyEvent( ' ', 0, 0 );
}
/*
void terminate() {
}
*/
void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );
	gluPerspective( 30.0, double(DISPLAY_WIDTH)/DISPLAY_HEIGHT, 0.1, 200 );
	gluLookAt( 0.0, 1.5, 3.0, 0.0 ,0.0 ,0.0, 0.0,1.0, 0.0 );

	glDisable( GL_DEPTH_TEST );	// デプステストの無効化
	glEnable( GL_BLEND );		//ブレンドの有効化

	// 奥の物から描画
	glTranslatef( 0.0f,0.0f,-1.0f );
	glColor4f( 0.0f, 0.0f, 1.0f, 0.5f );// 青
	glRectf( -0.5, 0.5, 0.5, -0.5 );
 
	glTranslatef( 0.0f, 0.0f, 1.0f );
	glColor4f (1.f, 0.f, 0.f, 0.7f );// 赤
	glRectf( -0.5, 0.5, 0.5, -0.5 );

	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );

	glutSwapBuffers();
}

void keyEvent( unsigned char key, int x, int y ) {
	if ( key == ' ' ) {// スペースキーで切り替え
		++Current;
		if ( Current == 6 ) {
			Current=0;
		}
		str = "アルファブレンディング";

		if ( Current == 0 ) {
			str += ":0　透明度無し描画";
			glBlendFunc( GL_ONE, GL_ZERO );
		}
		if ( Current == 1 ) {
			str += ":1　半透明合成";
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		}
		if ( Current == 2 ) {
			str += ":2　加算合成";
			glBlendFunc( GL_SRC_ALPHA, GL_ONE );
		}
		if ( Current == 3 ) {
			str += ":3　減算合成";
			glBlendEquationEXT( GL_FUNC_REVERSE_SUBTRACT_EXT );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE );
		}
		if ( Current == 4 ) {
			str += ":4　乗算合成";
			glBlendEquationEXT( GL_FUNC_ADD_EXT );// glBlendEquationEXTを戻す
			glBlendFunc( GL_ZERO, GL_SRC_COLOR );
		}
		if ( Current == 5 ) {
			str += ":5　反転合成";
			glBlendFunc( GL_ONE_MINUS_DST_COLOR, GL_ZERO );
		}
		glutSetWindowTitle( str.c_str() );
		glutPostRedisplay();
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
	glutKeyboardFunc( keyEvent );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

