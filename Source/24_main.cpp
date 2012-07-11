/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/46.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <freegl/glut.h>
#include <gl/glpng.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "TestLib.h"

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	float angleZ = 0.0f;

	pngInfo info;
	GLuint texture;

}// unnamed namespace

void initialize() {
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
	
	namespace fs = boost::filesystem;  
	fs::path image_path = fs::current_path() / "data/mapchip.png";
	std::string str = image_path.string();

	texture = pngBind (
				str.c_str(),
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
	glOrtho( 0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, -1.0, 1.0 );

	// 行列をテクスチャモードに変更
	// テクスチャも射影行列とかのように移動拡大回転などができる。
	glMatrixMode( GL_TEXTURE );
	// 単位行列を設定
	glLoadIdentity();
	// Z軸回転
	glRotatef( angleZ, 0.0f, 0.0f, 1.0f );// Z軸を回転

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_ALPHA_TEST );

	glBegin( GL_POLYGON );

	// 頂点座標とテクスチャ座標の設定
	// 左下
	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d(  10, 230 );
	// 左上
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d(  10,  10 );
	// 右上
	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( 310,  10 );
	// 右下
	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( 310, 230 );

	glEnd();

	glDisable( GL_ALPHA_TEST );
	glDisable( GL_TEXTURE_2D );

	glutSwapBuffers();
}

void idle() {
	angleZ += 0.02f;
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

