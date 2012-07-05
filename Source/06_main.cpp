/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/23.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdint>
#include <freegl/glut.h>

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	float x = 0.0f;
	float y = 0.0f;
	float vx = 0.05f;
	float vy = 0.05f;
	const int w = 10;
	const int h = 10;

}// unnamed namespace

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glPointSize( 20.0f );// �T�C�Y�ݒ��Begin�̑O�ɂ��Ȃ��ƃ_�����ۂ�
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();

	x += vx;
	y += vy;
	if ( x < 0 || x > DISPLAY_WIDTH-w ) vx *= -1.0f;
	if ( y < 0 || y > DISPLAY_HEIGHT-h ) vy *= -1.0f;

	// glFlush()�ł͂Ȃ��A�o�b�t�@���X���b�v����
	glutSwapBuffers();
}

void idle() {
	// �����C�x���g���Ȃ��Ă���ɍĕ`�悳����
	glutPostRedisplay();
}

int main( int argc, char *argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	// �_�u���o�b�t�@�����O�̐ݒ��ǉ�5
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	// �E�B���h�E�ɃC�x���g���������Ă��Ȃ��Ƃ��ɌĂ΂��R�[���o�b�N�֐���ݒ�
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

