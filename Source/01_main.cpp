#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
	glClearColor( 0.0, 0.0, 1.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glFlush();
}

int main( int argc, char *argv[] ) {
	// �E�B���h�E�̏����ʒu���w��
	glutInitWindowPosition( 100, 100 );
	// �E�B���h�E�̃T�C�Y���w��
	glutInitWindowSize( 320, 240 );

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}

