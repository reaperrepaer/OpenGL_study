
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

// conf ------------------------------------
const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 480;

// common ----------------------------------
const float PAI = 3.1415926535897932384626433832795f;
const float TO_RAD = PAI / 180.0f;
const float TO_DEG = 180.0f / PAI;

// rectangle -------------------------------
struct Rect {
	Rect( int a, int b, int w, int h )
	: x(a), y(b), width(w), height(h) {}
	int x;
	int y;
	int width;
	int height;
};

// graphics --------------------------------
// 3D描画用の設定
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

// 2D描画用の設定
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

void setColor( float r, float g, float b, float a ) {
	glColor4f( r, g, b, a );
}

void setTexture( int texID ) {
	if ( texID ) {
		glEnable( GL_TEXTURE_RECTANGLE_EXT );// 拡張機能を使う
		glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texID );
	}
	else {
		glBindTexture( GL_TEXTURE_RECTANGLE_EXT, 0 );
		glDisable( GL_TEXTURE_RECTANGLE_EXT );
	}
}

void drawImage( int texID, int x, int y, int w, int h, int u, int v, int uw, int vh ) {
	Rect dst( x, y, w, h );		// 貼り付ける元になる矩形
	Rect src( u, v, uw, vh );	// テクスチャのどの部分を貼り付けるか

	//////
	glEnable( GL_TEXTURE_RECTANGLE_EXT );// 拡張機能を使う
	glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texID );

	glEnable( GL_ALPHA_TEST );// アルファテスト開始
	glBegin( GL_POLYGON );
	// 左下
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2i( src.x, src.y+src.height );
	glVertex2d( dst.x, dst.y+dst.height );
	// 左上
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2i( src.x, src.y );
	glVertex2d( dst.x, dst.y );
	// 右上
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2i( src.x+src.width, src.y );
	glVertex2d( dst.x+dst.width, dst.y );
	// 右下
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2i( src.x+src.width, src.y+src.height );
	glVertex2d( dst.x+dst.width, dst.y+dst.height );

	glEnd();
	glDisable( GL_ALPHA_TEST );// アルファテスト終了
	glDisable( GL_TEXTURE_RECTANGLE_EXT );
}

void drawImage( int texID, int x, int y, int w, int h ) {
	drawImage( texID, x, y, w, h, 0, 0, w, h );
}

void drawImage( int texID, int x, int y, int u, int v, int uw, int vh ) {
	drawImage( texID, x, y, uw, vh, u, v, uw, vh );
}

void drawPoint( int x, int y, float size ) {
	glPointSize( size );
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();
}

void drawLine( int x, int y, int x2, int y2, float lineWidth ) {
	glLineWidth( lineWidth );
	glBegin( GL_LINES );
	glVertex2i( x, y );
	glVertex2i( x2, y2 );
	glEnd();
}

void drawRect( int x, int y, int w, int h, float lineWidth ) {
	glLineWidth( lineWidth );
	glBegin( GL_LINE_LOOP );
	glVertex2i( x, y );
	glVertex2i( x+w, y );
	glVertex2i( x+w, y+h );
	glVertex2i( x, y+h );
	glEnd();
}

void drawFillRect( int x, int y, int w, int h ) {
	glBegin( GL_QUADS );
	glVertex2i( x, y );
	glVertex2i( x+w, y );
	glVertex2i( x+w, y+h );
	glVertex2i( x, y+h );
	glEnd();
}

void drawCircle( float radius, int x, int y ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {             
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad );
		float y1 = radius * sin( th1_rad );
		float x2 = radius * cos( th2_rad );
		float y2 = radius * sin( th2_rad );

		glBegin( GL_LINES );
		glVertex2f( x1+x, y1+y );     
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

void drawCircleFill( float radius, int x, int y ) {
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

void drawOval( float radius,int x, int y, float ovalx, float ovaly ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad ) * (ovalx / 100.0f);
		float y1 = radius * sin( th1_rad ) * (ovaly / 100.0f);
		float x2 = radius * cos( th2_rad ) * (ovalx / 100.0f);
		float y2 = radius * sin( th2_rad ) * (ovaly / 100.0f);

		glBegin( GL_LINES );
		glVertex2f( x1+x, y1+y );     
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

void drawOvalFill( float radius, int x, int y, float ovalx, float ovaly ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f; th1 = th1 + 1.0f ) {
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad ) * (ovalx / 100.0f);
		float y1 = radius * sin( th1_rad ) * (ovaly / 100.0f);
		float x2 = radius * cos( th2_rad ) * (ovalx / 100.0f);
		float y2 = radius * sin( th2_rad ) * (ovaly / 100.0f);

		glBegin( GL_TRIANGLES );
		glVertex2f( static_cast<float>(x), static_cast<float>(y) );
		glVertex2f( x1+x, y1+y );
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

// texture ------------------------------
class Texture {
public:
	Texture() {}
	Texture( const char* FileName ) {
		loadPNG( FileName );
	}

	void loadPNG( const char* FileName ) {// PNG読み込み
		LodePNG_Decoder_init( &decoder_ );
		LodePNG_loadFile( &buffer_, &buffersize_, FileName );
		LodePNG_decode( &decoder_, &image, &imagesize_, buffer_, buffersize_ );
		Width = decoder_.infoPng.width;
		Height = decoder_.infoPng.height;
	}

	unsigned char* image;	// イメージポインタ
	unsigned int Width;		// 画像サイズ
	unsigned int Height;

protected:
	LodePNG_Decoder decoder_;
	unsigned char* buffer_;
	size_t buffersize_;
	size_t imagesize_;
};

// font ----------------------------
class FontDrawer {
public:
	FontDrawer( wchar_t* fontname, int size ) {
		fontHandle_ = CreateFontW(
			size,						// フォント高さ
			0,							// 文字幅
			0,							// テキストの角度
			0,							// ベースラインとｘ軸との角度
			FW_REGULAR,					// フォントの太さ
			FALSE,						// イタリック体
			FALSE,						// アンダーライン
			FALSE,						// 打ち消し線
			SHIFTJIS_CHARSET,			// 文字セット
			OUT_DEFAULT_PRECIS,			// 出力精度
			CLIP_DEFAULT_PRECIS,		// クリッピング精度
			ANTIALIASED_QUALITY,		// 出力品質
			FIXED_PITCH | FF_MODERN,	// ピッチとファミリー
			fontname					// 書体名
			);				

		deviceContext_ = wglGetCurrentDC();
		SelectObject( deviceContext_, fontHandle_ );
	}

	~FontDrawer() {
	}

	void drawStringW( int x, int y, wchar_t* format, ... ) {
		// １フレーム目に１番目のフォントが表示されない件の回避
		// ---
		const int list_ = glGenLists( 1 );
		wglUseFontBitmapsW( deviceContext_, L'a', 1, list_ );
		glDeleteLists( list_, 1 );
		// ---

		if ( format == NULL ) {
			return;
		}

		// 文字列変換
		wchar_t buf[ 256 ];
		va_list ap;
		va_start( ap, format );
		vswprintf_s( buf, format, ap );
		va_end( ap );
		
		const int length = wcslen( buf );
		const int list = glGenLists( length );
		for ( int i=0; i<length; ++i ) {
			wglUseFontBitmapsW( deviceContext_, buf[i], 1, list + (DWORD)i );
		}

		glRasterPos2i( x, y );
		//ディスプレイリストで描画
		for ( int i=0; i<length; ++i ) {
			glCallList( list + i );
		}
		//ディスプレイリスト破棄
		glDeleteLists( list, length );
	}

private:
	HDC		deviceContext_;
	HFONT	fontHandle_;
};

// main ------------------------------
namespace {

	// ライトの位置
	GLfloat lightPos[] = { 200.0f, 150.0f, -500.0f, 1.0f };
	// 赤
	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	float angleX = 0.0f;

	GLuint texID;
	Texture* texture;

	shared_ptr<FontDrawer> fontDrawer;

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

	// フォント
	fontDrawer = shared_ptr<FontDrawer>( new FontDrawer( L"ＭＳ明朝", 24 ) );
}

void finalize() {
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

	// キューブを描画
	glRotatef( angleX, 1.0f, 0.0f, 0.0f );
	glutSolidCube( 40.0f );
	// ------------------------------------

	setup2D();
	// ----------- ここに2D描画 -----------
	
	int x = 0;
	int y = 0;
	int w = 128;
	int h = 128;
	int u = 0;
	int v = 0;
	int uw = 64;
	int vh = 64;

	glEnable( GL_TEXTURE_2D );
	setColor( 1.0f, 1.0f, 1.0f, 1.0f );
	drawImage( texID, x, y, w, h, u, v, uw, vh );
	drawImage( texID, 10, 200, 32, 32, 32, 32, 32, 32 );
	drawImage( texID, 320, 200, 10, 10, 40, 40 );
	drawImage( texID, 320, 300, 64, 64 );
	glDisable( GL_TEXTURE_2D );

	setColor( 1.0f, 0.0f, 0.0f, 1.0f );
	drawPoint( 150, 150, 5.0f );

	setColor( 0.0f, 1.0f, 0.0f, 1.0f );
	drawLine( 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, 0, 3.0f );

	setColor( 0.0f, 0.0f, 1.0f, 1.0f );
	drawRect( 220, 10, 30, 30, 2.0f );

	setColor( 1.0f, 1.0f, 0.0f, 1.0f );
	drawFillRect( 220, 100, 30, 30 );

	setColor( 1.0f, 0.0f, 1.0f, 1.0f );
	drawCircle( 40.0f, 50, 50 );

	setColor( 0.0f, 1.0f, 1.0f, 1.0f );
	drawCircleFill( 50.0f, 150, 180 );

	setColor( 0.5f, 0.5f, 1.0f, 1.0f );
	drawOval( 50.0f, 150, 80, 100.0f, 80.0f );


	setColor( 1.0f, 1.0f, 0.0f, 1.0f );
	fontDrawer->drawStringW( 80, 150, L"あいうえお" );
	fontDrawer->drawStringW( 80, 180, L"あいうえお" );

	setColor( 1.0f, 1.0f, 1.0f, 1.0f );
	drawOvalFill( 80.0f, 260, 120, 50.0f, 100.0f );

	// ------------------------------------

	glutSwapBuffers();
}

void display() {
	update();
	draw();
}

void idle() {
	angleX += 0.2f;
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

