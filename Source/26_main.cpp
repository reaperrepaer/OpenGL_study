/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/74.html
 * ミップマップについて
 * http://wiki.livedoor.jp/mikk_ni3_92/d/%C8%AF%C5%B8%CA%D401%3A%3A%A5%DF%A5%C3%A5%D7%A5%DE%A5%C3%A5%D7
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
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

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	GLuint texture;

}// unnamed namespace

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

	// ミップマップを作る
	glBindTexture( GL_TEXTURE_2D, texture );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image );
	// 拡大・縮小フィルタ
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );

	glDisable( GL_TEXTURE_2D );
}

void terminate() {
}

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
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

