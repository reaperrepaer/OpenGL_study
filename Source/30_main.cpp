/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/84.html
 * 
 * 異方性フィルタリングを使うと、
 * ミップマップの境目をぼやかして目立たなくすることができる。
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
	const int DISPLAY_WIDTH = 640;
	const int DISPLAY_HEIGHT = 480;

	GLuint texture;

	bool flag = false;
	string windowTitle = "";

}// unnamed namespace

void keyEvent( unsigned char key, int x, int y );

void initialize() {
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
	
	LodePNG_Decoder decoder;
	LodePNG_Decoder_init( &decoder );
	unsigned char* buffer;
	unsigned char* image;
	size_t buffersize;
	size_t imagesize;

	namespace fs = boost::filesystem;  
	fs::path image_path = fs::current_path() / "data/mapchip.png";
	std::string str = image_path.string();

	// ロード
	LodePNG_loadFile( &buffer, &buffersize, str.c_str() );
	// デコード
	LodePNG_decode( &decoder, &image, &imagesize, buffer, buffersize );
	// 幅、高さ
	int width = decoder.infoPng.width;
	int height = decoder.infoPng.height;

	// テクスチャを作る
	glGenTextures( 1, (GLuint*)&texture );
	glEnable( GL_TEXTURE_2D );

	// 最近傍法
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
	glBindTexture( GL_TEXTURE_2D, texture );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image );

	glDisable( GL_TEXTURE_2D );
	keyEvent( ' ', 0, 0 );
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
	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 200.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// 視点の設定
	gluLookAt(
		0.0, 0.0, -5.0,	// カメラの座標
		0.0, 0.0, 0.0,	// 注視点の座標
		0.0, -1.0, 0.0	// 画面の上方向を指すベクトル
		);

	glBindTexture( GL_TEXTURE_2D, texture );
	glEnable( GL_TEXTURE_2D );// テクスチャ有効
	glEnable( GL_ALPHA_TEST );// アルファテスト開始

	glBegin( GL_POLYGON );
	glTexCoord2f( 0.f, 0.f ); glVertex3f( -0.5f, -0.5f,  5.0f );
	glTexCoord2f( 1.f, 0.f ); glVertex3f(  0.5f, -0.5f,  5.0f );
	glTexCoord2f( 1.f, 1.f ); glVertex3f(  0.5f,  0.5f, -5.0f );
	glTexCoord2f( 0.f, 1.f ); glVertex3f( -0.5f,  0.5f, -5.0f );
	glEnd();

	glDisable( GL_ALPHA_TEST );// アルファテスト終了
	glDisable( GL_TEXTURE_2D );

	glutSwapBuffers();
}

void keyEvent( unsigned char key, int x, int y ) {
	if ( key == ' ' ) {// スペースキーで切り替え
		if ( flag ) {
			flag = false;
			windowTitle = "異方性フィルタリング OFF";
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f );
		}
		else {
			flag = true;
			windowTitle = "異方性フィルタリング ON";
			float x;
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &x );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, x );
		}
		glutSetWindowTitle( windowTitle.c_str() );
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

	glewInit();

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

