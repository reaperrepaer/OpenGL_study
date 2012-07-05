/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/19.html
 * http://wisdom.sakura.ne.jp/system/opengl/gl2.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
	glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	glFlush();
}

int main( int argc, char *argv[] ) {
	// ウィンドウの初期位置を指定
	glutInitWindowPosition( 100, 100 );
	// ウィンドウのサイズを指定
	glutInitWindowSize( 320, 240 );

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}

