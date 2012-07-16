/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/81.html
 *
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

	// ライトの位置
	GLfloat lightpos[] = { 20.0f, 80.0f, -50.0f, 1.0f };

	float Ambient[] = { 0.8f, 0.0f, 0.2f, 1.0f };
	float Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[]= { 0.4f, 0.4f, 0.4f, 1.0f };// 鏡面反射
	float AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float DiffuseLight[] = { 0.2f, 0.7f, 0.7f, 1.0f };
	float SpecularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};// 鏡面光

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

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	glLightfv( GL_LIGHT0, GL_SPECULAR, SpecularLight );	// スペキュラライトを設定
	glLightfv( GL_LIGHT0, GL_DIFFUSE, DiffuseLight );
	glLightfv( GL_LIGHT0, GL_AMBIENT, AmbientLight );

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, Diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );	// 反射の設定
	glMaterialfv( GL_FRONT, GL_AMBIENT, Ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 8 );			// スペキュラの指数を設定

	// 回転
	glRotatef( anglex, 1.0f, 0.0f, 0.0f );// X軸を回転
	// 球描画
	glutSolidSphere( 40.0, 16, 16 );

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

