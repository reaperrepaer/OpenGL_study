#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
	// カラーバッファのクリア色を指定
	glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
	// カラーバッファをクリアする
	glClear( GL_COLOR_BUFFER_BIT );
	// ここまでの描画コマンドを実行
	glFlush();
}

int main( int argc, char *argv[] ) {
	// GLUTを初期化
	glutInit( &argc, argv );
	// ディスプレイモードの設定。指定しなくてもいいが、GLUT_RGBAがデフォルトになる。
	glutInitDisplayMode( GLUT_RGBA );
	// ウィンドウを生成
	glutCreateWindow( "Hello OpenGL!!" );
	// ディスプレイコールバック関数の登録
	glutDisplayFunc( display );
	// イベント処理を開始
	glutMainLoop();
	return 0;
}

