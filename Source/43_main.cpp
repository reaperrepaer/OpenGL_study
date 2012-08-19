/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/61.html
 *
 * glVertex3dやglTexCoord2fを使って頂点データを直接設定することもできるが
 * 何度も関数を呼び出したり、機能の切り替えが必要になるので、
 * 大量に表示しようと思うと速度に影響する。
 * 
 * 頂点は頂点、法泉は法線、マテリアルはマテリアルというように
 * データがまとまっていた方が機能切り替えが最小限になり効率がよくなる。
 * 
 * 頂点配列はCPUがすべて処理する。
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <freegl/glut.h>

#include "TestLib.h"

using namespace std;

namespace {

	const int DISPLAY_WIDTH = 640;
	const int DISPLAY_HEIGHT = 480;

	GLuint VBO_ID[3];// ３つ分
	float angle = 0.0f;

	// 頂点データ。3面を4頂点で作成する
	// 1頂点は x, y, z の3要素
	GLfloat Vertex[3][4][3] = {
		{{  1.0f, 0.0f, 0.0f }, {  1.0f, 0.0f, 0.5f }, {  0.0f, 1.0f, 0.5f }, {  0.0f, 1.0f, 0.0f } },// 1枚目
		{{  1.0f, 0.0f, 0.0f }, {  1.0f, 0.0f, 0.5f }, { -1.0f, 0.0f, 0.5f }, { -1.0f, 0.0f, 0.0f } },// 2枚目
		{{ -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.5f }, {  0.0f, 1.0f, 0.5f }, {  0.0f, 1.0f, 0.0f } },// 3枚目
	};
	GLfloat Normal[6][4][3] = {
		{{  1.0f,  0.5f, 0.0f }, {  1.0f,  0.5f, 0.0f }, {  1.0f,  0.5f, 0.0f }, {  1.0f,  0.5f, 0.0f } },// 右上
		{{  0.0f, -1.0f, 0.0f }, {  0.0f, -1.0f, 0.0f }, {  0.0f, -1.0f, 0.0f }, {  0.0f, -1.0f, 0.0f } },// 下
		{{ -1.0f,  0.5f, 0.0f }, { -1.0f,  0.5f, 0.0f }, { -1.0f,  0.5f, 0.0f }, { -1.0f,  0.5f, 0.0f } },// 左上
	};
	GLfloat Color[6][4][3] = {
		{{  1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f,0.0f,0.0f }, { 1.0f, 0.0f, 0.0f } },// 赤
		{{  0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f,0.0f,1.0f }, { 0.0f, 0.0f, 1.0f } },// 青
		{{  0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f,1.0f,0.0f }, { 0.0f, 1.0f, 0.0f } },// 緑
	};

	void drawArray() {
		// 有効化
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		// データの関連付け
		// ここでデータを突っ込む。
		glVertexPointer( 3, GL_FLOAT, 0, Vertex );	// 座標
		glNormalPointer( GL_FLOAT, 0, Normal );		// 法線
		glColorPointer( 3,GL_FLOAT, 0, Color );		// 色

		glDrawArrays( GL_QUADS, 0, 4*3 );			// 描画(4頂点*3面)

		// 無効化
		glDisableClientState( GL_COLOR_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
	}

}// unnamed namespace

void initialize() {
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glEnable( GL_DEPTH_TEST );
	glColorMaterial( GL_FRONT,GL_AMBIENT_AND_DIFFUSE );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHTING );
	glEnable( GL_NORMALIZE );// 法線の正規化
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

	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 200.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	glRotatef( angle, 1.0f, 0.0f, 0.0f );// 回転
	glRotatef( angle, 0.0f, 1.0f, 0.0f );// 回転

	drawArray();

	glutSwapBuffers();
}

void idle() {
	angle += 0.2f;
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

