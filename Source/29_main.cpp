/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/75.html
 * http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20040914
 *
 * バイリニアフィルタリングは、画像を拡大した場合に荒くなる部分を
 * 付近の色をいい感じに混ぜ合わせることでぼやかした感じにし、なめらかに見せる方法。
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

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	
	// テクスチャ。比較用に２つ。
	GLuint textures[ 2 ] = { 0 };

	void draw( float x, float y, float w, float h ) {
		glEnable( GL_ALPHA_TEST );// アルファテスト開始
		glBegin( GL_POLYGON );
		glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x,  y );
		glTexCoord2f( 0.2f, 0.0f ); glVertex2f( x+w,y );
		glTexCoord2f( 0.2f, 0.2f ); glVertex2f( x+w,y+h );
		glTexCoord2f( 0.0f, 0.2f ); glVertex2f( x,  y+h );
		glEnd();
		glDisable( GL_ALPHA_TEST );// アルファテスト終了
	}

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
	glGenTextures( 2, textures );
	glEnable( GL_TEXTURE_2D );

	// 最近傍法
	glBindTexture( GL_TEXTURE_2D, textures[ 0 ] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glBindTexture( GL_TEXTURE_2D, textures[ 0 ] );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );

	// 双線形補間
	glBindTexture( GL_TEXTURE_2D, textures[ 1 ] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glBindTexture( GL_TEXTURE_2D, textures[ 1 ] );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );

	glDisable( GL_TEXTURE_2D );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glOrtho( 0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, -1.0, 1.0 );

	glEnable( GL_TEXTURE_2D );// テクスチャ有効

	// 元画像
	glBindTexture( GL_TEXTURE_2D, textures[ 0 ] );
	draw( 10, 10, 128, 128 );

	// バイリニアフィルタリング
	glBindTexture( GL_TEXTURE_2D, textures[ 1 ] );
	draw( 160, 10, 128, 128 );

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

