/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/28.html
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

	const float PAI = 3.1415926535897932384626433832795f;
	const float TO_RAD = PAI / 180.0f;
	const float TO_DEG = 180.0f / PAI;

	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// 3D描画設定
	void setup3D() {
		glMatrixMode( GL_PROJECTION );	// 射影変換行列設定
		glPopMatrix();					// 射影変換行列を復元
		glMatrixMode( GL_MODELVIEW );	// モデルビュー変換行列設定
		glPopMatrix();					// モデルビュー行列を復元
		glLoadIdentity();				// 単位行列を設定
	}

	// 2D描画設定
	void setup2D() {
		/*
			１階層下げて、そこに2D設定をする。
			イメージでは「下げて」というよりも、押し込む感じ。
			ちょっと一旦別のマトリクスを突っ込みますよ･･･として
			再度3D描画するときはpopして元に戻す。
		*/
		glMatrixMode( GL_PROJECTION );	// 射影変換行列設定
		glPushMatrix();					// 現在の射影変換行列を保存
		glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );// 正射影変換設定
		glMatrixMode( GL_MODELVIEW );	// モデルビュー変換行列設定
		glPushMatrix();					// 現在のモデルビュー行列を保存
		glLoadIdentity();				// 単位行列を設定
	}

	void drawCircle2DFill( float radius, int x, int y ) {
		for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {
			float th2 = th1 + 10.0f;
			float th1_rad = th1 * TO_RAD; 
			float th2_rad = th2 * TO_RAD;

			float x1 = radius * cos( th1_rad );
			float y1 = radius * sin( th1_rad );
			float x2 = radius * cos( th2_rad );
			float y2 = radius * sin( th2_rad );

			glBegin( GL_TRIANGLES );
			glVertex2f( static_cast<float>(x), static_cast<float>(y) );
			glVertex2f( x1+x, y1+y );     
			glVertex2f( x2+x, y2+y );
			glEnd();
		} 
	}

}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	// 3D描画用に設定
	// マトリクスをpopして3D用(先頭のマトリクス)に戻す。
	setup3D();
	glRotated( angleY, 0.0f, 1.0f, 0.0f );
	glRotated( angleX, 1.0f, 0.0f, 0.0f );
	glRotated( angleZ, 0.0f, 0.0f, 1.0f );

	// たぶんこれは透視投影でもいいはず。
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );

	glBegin( GL_TRIANGLES );
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50 , 30, 0 );
	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	glVertex3f( 10 , 100, 0 );
	glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
	glVertex3f( 90 , 100, 0 );
	glEnd();

	glBegin( GL_QUADS );
	glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	glVertex3f( 100 , 180, 0 );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glVertex3f( 200 , 180, 0 );
	glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
	glVertex3f( 200 , 220, 0 );
	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 100 , 220, 0 );
	glEnd();

	// 2D描画用に切り替え
	// マトリクスを１つ押し込んで、
	// 新しく突っ込まれたマトリクスに2D設定をする。
	setup2D();

	// 四角形ポリゴン
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

	glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
	drawCircle2DFill( 50.0f, 250, 100 );

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

