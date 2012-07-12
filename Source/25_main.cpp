/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/58.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <gl/glew.h>// GL_TEXTURE_RECTANGLE_EXTを使う
#include <freegl/glut.h>
//#include <gl/glpng.h>// glpngは使わない
#include <lodepng.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	GLuint texture;

	// サイズ用の矩形
	struct Rect {
		Rect( int a, int b, int w, int h )
		: x(a), y(b), width(w), height(h) {}
		int x;
		int y;
		int width;
		int height;
	};

	// ストレッチ描画
	void drawStretch( Rect dst, Rect src ) {
		glEnable( GL_TEXTURE_RECTANGLE_EXT );// 拡張機能を使う
		glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texture );

		glEnable( GL_ALPHA_TEST );// アルファテスト開始
		glBegin( GL_POLYGON );
		// 左下
		glTexCoord2i( src.x, src.y+src.height );
		glVertex2d( dst.x, dst.y+dst.height );
		// 左上
		glTexCoord2i( src.x, src.y );
		glVertex2d( dst.x, dst.y );
		// 右上
		glTexCoord2i( src.x+src.width, src.y );
		glVertex2d( dst.x+dst.width, dst.y );
		// 右下
		glTexCoord2i( src.x+src.width, src.y+src.height );
		glVertex2d( dst.x+dst.width, dst.y+dst.height );

		glEnd();
		glDisable( GL_ALPHA_TEST );// アルファテスト終了
		glDisable( GL_TEXTURE_RECTANGLE_EXT );
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
	glGenTextures( 1, (GLuint*)&texture );

	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); 

	glEnable( GL_TEXTURE_RECTANGLE_EXT );// 拡張機能を使う
	glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texture );
	glTexImage2D( GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glDisable( GL_TEXTURE_RECTANGLE_EXT );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glOrtho( 0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, -1.0, 1.0 );

	glEnable( GL_TEXTURE_2D );

	// 城
	{
		Rect dst( 50, 50, 128, 128 );// 貼り付ける元になる矩形
		Rect src( 80, 160, 48, 48 );// テクスチャのどの部分を貼り付けるか

		// dstのサイズになるように拡縮されて描画される。
		drawStretch( dst, src );
	}

	// 林
	{
		Rect dst( 10, 10, 32, 32);
		Rect src ( 0, 80, 16, 16 );
		drawStretch( dst, src );
	}

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

