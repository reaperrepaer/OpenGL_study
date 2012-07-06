/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/27.html
 * http://wisdom.sakura.ne.jp/system/opengl/gl11.html
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

	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;

}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );
	// 行列演算のターゲットを設定
	glMatrixMode( GL_MODELVIEW );
	// 現在の行列を単位行列に。
	glLoadIdentity();
	glRotated( angleY, 0.0, 1.0, 0.0 );
	glRotated( angleX, 1.0, 0.0, 0.0 );
	glRotated( angleZ, 0.0, 0.0, 1.0 );
	
	// ビューマトリクスを更新するので
	// ここで射影変換の設定をしなければならない。
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );

	// 三角形ポリゴン
	glBegin( GL_TRIANGLES );
	glColor4f( 1.0, 0.0, 0.0, 1.0f );
	glVertex3f( 50 , 30, 0 );
	glColor4f( 0.0, 1.0, 0.0, 1.0f );
	glVertex3f( 10 , 100, 0);
	glColor4f( 0.0, 0.0, 1.0, 1.0f );
	glVertex3f( 90 , 100, 0 );
	glEnd();

	// 四角形ポリゴン
	// OpenGLでは四角形ポリゴンが使える。
	glBegin( GL_QUADS );
	glColor4f( 1.0, 1.0, 0.0, 1.0f );
	glVertex3f( 100 , 180, 0 );
	glColor4f( 1.0, 1.0, 1.0, 1.0f );
	glVertex3f( 200 , 180, 0 );
	glColor4f( 0.0, 1.0, 1.0, 1.0f );
	glVertex3f( 200 , 220, 0 );
	glColor4f( 0.0, 0.0, 0.0, 1.0f );
	glVertex3f( 100 , 220, 0 );
	glEnd();

	glutSwapBuffers();
}

void idle() {
	// 移動させてみる。
	// 但しこの状態では原点は画面中心となる。
	angleX += 0.05f;
	angleY += 0.0025f;
	angleZ += 0.03f;

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

