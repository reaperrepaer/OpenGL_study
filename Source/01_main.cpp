#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
	glClearColor( 0.0, 0.0, 1.0, 1.0 );
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

