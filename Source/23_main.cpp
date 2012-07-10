/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/57.html
 * テクスチャ座標について
 * http://www.c3.club.kyutech.ac.jp/gamewiki/index.php?%A5%C6%A5%AF%A5%B9%A5%C1%A5%E3%BA%C2%C9%B8
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <freegl/glut.h>
// glpngを使う
#include <gl/glpng.h>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };

	pngInfo info;
	GLuint texture;

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
	
	// テクスチャを作る
	texture = pngBind (
				"sample.png",
				PNG_NOMIPMAP,
				PNG_ALPHA,
				&info,
				GL_CLAMP,
				GL_NEAREST,
				GL_NEAREST
				);
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// 久しぶりに正射影
	glOrtho( 0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, -1.0, 1.0 );

	glEnable( GL_TEXTURE_2D );// テクスチャ有効
	glEnable( GL_ALPHA_TEST );// アルファテスト開始

	glBegin( GL_POLYGON );

	// 頂点の設定
	glVertex2d(  10, 230 );// 左下
	glVertex2d(  10,  10 );// 左上
	glVertex2d( 310,  10 );// 右上
	glVertex2d( 310, 230 );// 右下

	// テクスチャ座標を設定
	glTexCoord2f( 0.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f );
	glTexCoord2f( 1.0f, 0.0f );
	glTexCoord2f( 1.0f, 1.0f );

	glEnd();

	glDisable( GL_ALPHA_TEST );// アルファテスト終了
	glDisable( GL_TEXTURE_2D );// テクスチャ無効

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

