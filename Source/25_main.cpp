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

#if 1

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	GLfloat lightpos[] = { 200.0f, 1000.0f, -500.0f, 1.0f };
	GLuint texture;

	// サイズ用構造体
	struct Rect {
		int x;
		int y;
		int width;
		int height;
	};

	//ストレッチ描画
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
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
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
	glGenTextures( 1, (GLuint *)&texture );

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

#else

#define WIDTH 320
#define HEIGHT 240

//サイズ用構造体
struct SizeRECT{
 int x;
 int y;
 int width;
 int height;
};

GLuint texture;
//サイズセット
void SetSizeRECT(SizeRECT* rect, int a,int b,int c,int d)
{
 rect->x=a;rect->y=b;rect->width=c;rect->height=d;
}
//ストレッチ描画
void DrawStretch(SizeRECT Dst,SizeRECT Src)
{
 glEnable( GL_TEXTURE_RECTANGLE_EXT );//拡張機能を使う
 glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texture );

    glEnable(GL_ALPHA_TEST);//アルファテスト開始
    glBegin(GL_POLYGON);
  glTexCoord2i(Src.x, Src.y+Src.height);   glVertex2d(Dst.x , Dst.y+Dst.height);//左下
  glTexCoord2i(Src.x, Src.y);      glVertex2d(Dst.x ,  Dst.y);//左上
  glTexCoord2i(Src.x+Src.width, Src.y);    glVertex2d( Dst.x+Dst.width ,  Dst.y);//右上
  glTexCoord2i(Src.x+Src.width, Src.y+Src.height);glVertex2d( Dst.x+Dst.width , Dst.y+Dst.height);//右下
    glEnd();
    glDisable(GL_ALPHA_TEST);//アルファテスト終了
 glDisable( GL_TEXTURE_RECTANGLE_EXT );
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);

 glEnable(GL_TEXTURE_2D);//テクスチャ有効

 SizeRECT Dst,Src;
 //城
 SetSizeRECT(&Dst,50,50,128,128);
 SetSizeRECT(&Src,80,160,48,48);
 DrawStretch(Dst,Src);
 //林
 SetSizeRECT(&Dst,10,10,32,32);
 SetSizeRECT(&Src,0,80,16,16);
 DrawStretch(Dst,Src);

 glDisable(GL_TEXTURE_2D);//テクスチャ無効

 glutSwapBuffers();
}
void idle(void)
{
 glutPostRedisplay();
}
void Init(){
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

 LodePNG_Decoder decoder;
 LodePNG_Decoder_init(&decoder);
 unsigned char* buffer;
 unsigned char* image;
 size_t buffersize, imagesize;

 namespace fs = boost::filesystem;  
fs::path image_path = fs::current_path() / "data/mapchip.png";
std::string str = image_path.string();

 //ロード
 LodePNG_loadFile(&buffer, &buffersize, str.c_str());
 //デコード
 LodePNG_decode(&decoder, &image, &imagesize, buffer, buffersize);
 //幅,高さ
 int width = decoder.infoPng.width; int height = decoder.infoPng.height;

 glGenTextures(1, (GLuint *)&texture);
 
 glBindTexture(GL_TEXTURE_2D, texture);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

 glEnable( GL_TEXTURE_RECTANGLE_EXT );//拡張機能を使う
 glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texture );
 glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA,width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image);
 glDisable( GL_TEXTURE_RECTANGLE_EXT );

}
int main(int argc, char *argv[])
{
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(WIDTH, HEIGHT);
 glutInit(&argc, argv);
 glutCreateWindow("画像の切り抜きとストレッチ");
 glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
 glutDisplayFunc(display);
 glutIdleFunc(idle);
 Init();
 glutMainLoop();
 return 0;
}

#endif

