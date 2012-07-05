/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/24.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <freegl/glut.h>

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	class FontDrawer {
	public:
		FontDrawer( wchar_t *fontname, int size ) {
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

		void DrawStringW( int x, int y, wchar_t* format, ... ) {
			wchar_t buf[256];
			va_list ap;
			int Length=0;
			int list=0;
 
			// ポインタがNULLの場合は終了
			if ( format == NULL ) {
				return;
			}

			// 文字列変換
			va_start( ap, format );
			vswprintf_s( buf, format, ap );
			va_end( ap );

			Length = wcslen( buf );
			list = glGenLists( Length );
			for( int i=0; i<Length; ++i ) {
				wglUseFontBitmapsW( deviceContext_, buf[i], 1, list + (DWORD)i );
			}

			glDisable(GL_LIGHTING);
			glRasterPos2i(x, y);
			//ディスプレイリストで描画
			for ( int i=0; i<Length; ++i ) {
				glCallList( list + i );
			}
			glEnable( GL_LIGHTING );
			//ディスプレイリスト破棄
			glDeleteLists( list, Length );
			list = 0;
			Length = 0;
		}

	private:
		HDC		deviceContext_;
		HFONT	fontHandle_;
	};

}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );


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

