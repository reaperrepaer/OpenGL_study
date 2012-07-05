/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/20.html
 * http://exlight.net/devel/cpp/unnamed_namespace.html
 * http://www.komoto.org/opengl/sample01.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <cstdint>
#include <freegl/glut.h>

// C++�ł̓t�@�C���X�R�[�v�̕ϐ���static��t����̂ł͂Ȃ��������O��Ԃɓ˂����ށB
// static���g���ꏊ�ɂ���ĈӖ����ς���ĕ�����ɂ�������炵���B
namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;
}// unnamed namespace

void initialize() {
	// �N���A�J���[�̐ݒ�͖��t���ς���K�v�͂Ȃ�
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	// �ˉe�ϊ��𐳎ˉe�ɐݒ�
	// �����̏��Ԃɒ��ӁBleft, top, right, bottom�ł͂Ȃ��B
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	// �`��FRGBA��float�Őݒ�
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	// �_�̃T�C�Y��ݒ�
	glPointSize( 1.0f );
	// �}�`�̕`����J�n����
	glBegin( GL_POINTS );
	// ���_XY�𐮐��^�Őݒ�
	glVertex2i( 100, 100 );
	// �}�`�`��̏I��
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
	initialize();// ����������
	glutMainLoop();
	terminate();// �I������
	return 0;
}

