/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/62.html
 * http://wisdom.sakura.ne.jp/system/opengl/gl20.html
 *
 * OpenGLのコマンドを、ハードウェアが理解できる形で保存しておく。
 * これを実行すると、毎回生成するよりも高速に描画することができる。
 *
 * 但しディスプレイリストに出来ない関数もあるので注意。
 * 何回も描画するもので、パラメータの変化しないものに有効。
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

	float angle = 0.0f;

	GLuint ListID = 0;

}// unnamed namespace

void initialize() {
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHTING );

	// ディスプレイリスト作成
	ListID = glGenLists( 5 );
	
	//　1、スフィア
	glNewList( ListID, GL_COMPILE );// コマンドの保存を開始する
	glColor4f( 1.0, 1.0, 1.0, 1.0f );
	glutSolidSphere( 1.0, 16, 16 );
	glEndList();// ここまでのコマンドを保存する

	//　2、キューブ
	glNewList( ListID+1, GL_COMPILE );
	glutSolidCube( 1.0 );
	glEndList();
	
	//　3、トーラス
	glNewList( ListID+2, GL_COMPILE );
	glColor4f( 1.0, 0.0, 1.0, 1.0f );
	glutSolidTorus( 0.2, 0.4, 30, 30 );
	glEndList();

	//　4、スフィア（色違い）
	glNewList( ListID+3, GL_COMPILE );
	glColor4f( 0.0, 0.0, 1.0, 1.0f );
	glutSolidSphere( 1.0, 16, 16 );
	glEndList();

	//　5、キューブ（大きさ違い）
	glNewList( ListID+4, GL_COMPILE );
	glColor4f( 0.0, 1.0, 0.0, 1.0f );
	glutSolidCube( 2.0 );
	glEndList();
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
	gluPerspective( 30.0, DISPLAY_WIDTH / DISPLAY_HEIGHT, 0.1, 200.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt(
		0.0, 0.0, 8.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	glRotatef( angle, 1.0f, 0.0f, 0.0f );// 回転
	glRotatef( angle, 0.0f, 1.0f, 0.0f );// 回転

	glCallList( ListID );

	glutSwapBuffers();
}

void timer( int value ) {
	++ListID;
	if ( ListID > 5 ) {
		ListID = 1;
	}
	glutTimerFunc( 300, timer, 0 );
}

void idle() {
	angle += 0.02f;
	glutPostRedisplay();
}

int main( int argc, char* argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutTimerFunc( 300, timer, 0 );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

