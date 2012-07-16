/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/78.html
 *
 * イメージのアルファ値を参照して描画するかしないかを決める。
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <string>
#include <freegl/glut.h>
#include <lodepng.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	float alpha = 0.0f;
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
	fs::path image_path = fs::current_path() / "data/alphatest.png";
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
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );// 拡大されて表示されるときの設定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );// 縮小されて表示されるときの設定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); 

	glEnable( GL_TEXTURE_2D  );// 拡張機能を使う
	glBindTexture( GL_TEXTURE_2D , texture );
	glTexImage2D( GL_TEXTURE_2D , 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glDisable( GL_TEXTURE_2D  );
}
/*
void terminate() {
}
*/
void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glOrtho( 0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, -1.0, 1.0 );
	
	glEnable( GL_BLEND );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texture );

	// アルファテストの判定を指定
	// この場合だと、alpha値よりも透明度が大きいピクセルだけ描画する。
	glAlphaFunc( GL_GREATER, alpha );

	glEnable( GL_ALPHA_TEST );// アルファテスト開始
	glBegin( GL_POLYGON );
	glTexCoord2f( 0.0f, 1.0f ); glVertex2d( 10,  230 );// 左下
	glTexCoord2f( 0.0f, 0.0f ); glVertex2d( 10,   10 );// 左上
	glTexCoord2f( 1.0f, 0.0f ); glVertex2d( 310,  10 );// 右上
	glTexCoord2f( 1.0f, 1.0f ); glVertex2d( 310, 230 );// 右下
	glEnd();
	glDisable( GL_ALPHA_TEST );//アルファテスト終了
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );

	glutSwapBuffers();
}

void idle() {
	// 段々と値を上げていく･･･
	alpha += 0.0001f;
	if ( alpha > 1.0f ) {
		alpha = 0.0f;
	}
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

