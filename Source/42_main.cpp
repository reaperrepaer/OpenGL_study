/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/112.html
 * http://wiki.livedoor.jp/mikk_ni3_92/d/%B4%F0%CB%DC%CA%D413
 *
 * テッセレーションはポリゴンの再分割をすること。
 * ローポリで作っておいたカクカクの3Dオブジェクトをなめらかにしたりできる。
 * 
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include <freegl/glut.h>

#include "TestLib.h"

using namespace std;

namespace {

	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	// 頂点情報用
	struct vector3d {
		double x;
		double y;
		double z;
	} vec3d;

	vector <vector3d> vertex;
	// テッセレータオブジェクト
	GLUtesselator* tess;
	// 回転用
	float anglex = 0.0f;
	// 白
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

	void setdata( double x, double y, double z ) {
		vec3d.x = x;
		vec3d.y = y;
		vec3d.z = z;
		vertex.push_back( vec3d );
	}

	// キーボード
	BYTE KeyTbl[256];

}// unnamed namespace

void initialize() {
	// 頂点情報セット
	setdata( 50, 50, 0 );
	setdata( 200, 50, 0 );
	setdata( 150, -50, 0 );
	setdata( 50, -20, 0 );
	setdata( 0, 0, 0 );

	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	// ワイヤーフレーム表示
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// テッセレータオブジェクトを生成
	tess = gluNewTess();
	if ( tess == NULL ) {
		printf( "テッセレータオブジェクトがありません。" );
		exit( 1 );
	}
	// テッセレーションを行った際に呼ばれるコールバックを設定する。
	gluTessCallback( tess, GLU_TESS_BEGIN,  (void (__stdcall*)(void))glBegin );
	gluTessCallback( tess, GLU_TESS_END,    (void (__stdcall*)(void))glEnd );
	gluTessCallback( tess, GLU_TESS_VERTEX, (void (__stdcall*)(void))glVertex3dv );
}

/*
void terminate() {
}
*/

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport( 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 30.0, (double)DISPLAY_WIDTH / (double)DISPLAY_HEIGHT, 1.0, 1000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt(
		0.0,0.0,800.0,
		0.0,0.0,0.0,
		0.0,1.0,0.0
		);

	glMaterialfv( GL_FRONT, GL_DIFFUSE, white );
	glColor3f( 1, 1, 1 );

	// WindowsAPIでのキーボード入力チェック
	GetKeyboardState( KeyTbl );
	if ( KeyTbl[ VK_SPACE ] & 0x80 ) {
		// テッセレータに座標を渡すと勝手にテッセレーションしてくれる。
		gluTessBeginPolygon( tess, 0 );// テッセレーションの範囲を指定（開始）
		gluTessBeginContour( tess );
		for ( int i=0; i<(signed)vertex.size(); ++i ) {
			gluTessVertex( tess, &vertex[i].x, &vertex[i] );// テッセレーション対象となる頂点
		}
		gluTessEndContour( tess );
		gluTessEndPolygon( tess );// テッセレーションの範囲を指定（終了）
	}
	else {
		// 何も押されて無いときは普通に描画
		glBegin( GL_LINE_LOOP );
		for ( int i=0; i<(signed)vertex.size(); ++i ) {
			glVertex3dv( &vertex[i].x );
		}
		glEnd();
	}
	glutSwapBuffers();
}

void idle() {
	anglex += 0.02f;
	glutPostRedisplay();
}

int main( int argc, char* argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );
	glutIdleFunc( idle );

	initialize();
	glutMainLoop();
//	terminate();
	return 0;
}

