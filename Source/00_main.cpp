#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <freegl/glut.h>

void display() {
	// �J���[�o�b�t�@�̃N���A�F���w��
	glClearColor( 0.0, 0.0, 1.0, 1.0 );
	// �J���[�o�b�t�@���N���A����
	glClear( GL_COLOR_BUFFER_BIT );
	// �����܂ł̕`��R�}���h�����s
	glFlush();
}

int main( int argc, char *argv[] ) {
	// GLUT��������
	glutInit( &argc, argv );
	// �f�B�X�v���C���[�h�̐ݒ�B�w�肵�Ȃ��Ă��������AGLUT_RGBA���f�t�H���g�ɂȂ�B
	glutInitDisplayMode( GLUT_RGBA );
	// �E�B���h�E�𐶐�
	glutCreateWindow( "Hello OpenGL!!" );
	// �f�B�X�v���C�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc( display );
	// �C�x���g�������J�n
	glutMainLoop();
	return 0;
}

