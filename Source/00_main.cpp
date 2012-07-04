#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
}

int main( int argc, char *argv[] ) {
	glutInit( &argc, argv );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}

