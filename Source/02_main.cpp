/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/20.html
 * http://exlight.net/devel/cpp/unnamed_namespace.html
 * http://www.komoto.org/opengl/sample01.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <cstdint>
#include <freegl/glut.h>

// C++ではファイルスコープの変数はstaticを付けるのではなく無名名前空間に突っ込む。
// staticが使う場所によって意味が変わって分かりにくいかららしい。
namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;
}// unnamed namespace

void initialize() {
	// クリアカラーの設定は毎フレ変える必要はない
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	// 射影変換を正射影に設定
	// 引数の順番に注意。left, top, right, bottomではない。
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	// 描画色RGBAをfloatで設定
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	// 点のサイズを設定
	glPointSize( 1.0f );
	// 図形の描画を開始する
	glBegin( GL_POINTS );
	// 頂点XYを整数型で設定
	glVertex2i( 100, 100 );
	// 図形描画の終了
	glEnd();

	glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
	glPointSize( 50.0f );
	glBegin( GL_POINTS );
	glVertex2i( 150, 150 );
	glEnd();

	glFlush();
}

int main( int argc, char *argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	initialize();// 初期化処理
	glutMainLoop();
	terminate();// 終了処理
	return 0;
}

