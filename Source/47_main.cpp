
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <freegl/glut.h>
#include <lodepng.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "TestLib.h"

using namespace std;

// サイズ用の矩形
struct Rect {
	Rect( int a, int b, int w, int h )
	: x(a), y(b), width(w), height(h) {}
	int x;
	int y;
	int width;
	int height;
};

// テクスチャクラス
class Texture {
protected:
	LodePNG_Decoder decoder;
	unsigned char* buffer;
	size_t buffersize;
	size_t imagesize;

public:
	Texture() {}
	Texture( const char* fileName ) {
		loadPNG( fileName );
	}

	void loadPNG( const char* FileName ) {// PNG読み込み
		LodePNG_Decoder_init( &decoder );
		LodePNG_loadFile( &buffer, &buffersize, FileName );
		LodePNG_decode( &decoder, &image, &imagesize, buffer, buffersize );
		Width = decoder.infoPng.width;Height = decoder.infoPng.height;
	}

	unsigned char* image;	// イメージポインタ
	unsigned int Width;		// 画像サイズ
	unsigned int Height;
};

namespace {

	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	// ライトの位置
	GLfloat lightPos[] = { 200.0f, 150.0f, -500.0f, 1.0f };
	// 赤
	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	float angleX = 0.0f;

	GLuint texID;
	Texture* texture;

	// ストレッチ描画
	void drawStretch( Rect dst, Rect src ) {
		glEnable( GL_TEXTURE_RECTANGLE_EXT );// 拡張機能を使う
		glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texID );

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
	glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );

	namespace fs = boost::filesystem;  
	fs::path image_path = fs::current_path() / "data/hituzi.png";
	std::string str = image_path.string();

	// テクスチャを作成
	texture = new Texture( str.c_str() );
	glGenTextures( 1, (GLuint*)&texID );
	glBindTexture( GL_TEXTURE_2D, texID );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glEnable( GL_TEXTURE_RECTANGLE_EXT );
	glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texID );
	glTexImage2D( GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA, texture->Width, texture->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image );
	glDisable( GL_TEXTURE_RECTANGLE_EXT );
}

void finalize() {
}

void setup3D() {
	// 2D用に押し込んでいたマトリクスを戻す(親階層)
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();					

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

void setup2D() {
	// 押し込んで正射影を設定(子階層)
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );
	glDisable( GL_LIGHT0 );
}

void update() {
}

void draw() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );

	setup3D();
	// ----------- ここに3D描画 -----------
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 1000.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		150.0, 100.0, -200.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );

	// マテリアルの設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, red );

	glRotatef( angleX, 1.0f, 0.0f, 0.0f );

	// キューブを描画
	glutSolidCube( 40.0f );
	// ------------------------------------

	setup2D();
	// ----------- ここに2D描画 -----------
	/*
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
	*/

	glEnable( GL_TEXTURE_2D );

	Rect dst( 0, 0, 128, 128 );// 貼り付ける元になる矩形
	Rect src( 0, 0, 64, 64 );	// テクスチャのどの部分を貼り付けるか
	drawStretch( dst, src );

	glDisable( GL_TEXTURE_2D );

	// ------------------------------------

	glutSwapBuffers();
}

void display() {
	update();
	draw();
}

void idle() {
	angleX += 0.02f;
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
	glewInit();

	initialize();
	glutMainLoop();
	finalize();
	return 0;
}

