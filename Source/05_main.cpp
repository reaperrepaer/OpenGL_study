/**
 * Referenced :
 * http://www21.atwiki.jp/opengl/pages/23.html
 */
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <cstdint>
#include <cmath>
#include <freegl/glut.h>

using namespace std;

namespace {
	const int DISPLAY_WIDTH = 320;
	const int DISPLAY_HEIGHT = 240;

	const float PAI = 3.1415926535897932384626433832795f;
	const float TO_RAD = PAI / 180.0f;
	const float TO_DEG = 180.0f / PAI;
}// unnamed namespace

void drawCircle2D( float radius, int x,int y ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {             
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad );
		float y1 = radius * sin( th1_rad );
		float x2 = radius * cos( th2_rad );
		float y2 = radius * sin( th2_rad );

		glBegin( GL_LINES );
		glVertex2f( x1+x, y1+y );     
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

void drawCircle2DFill( float radius, int x, int y ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad );
		float y1 = radius * sin( th1_rad );
		float x2 = radius * cos( th2_rad );
		float y2 = radius * sin( th2_rad );

		glBegin( GL_TRIANGLES );
		glVertex2f( static_cast<float>(x), static_cast<float>(y) );
		glVertex2f( x1+x, y1+y );     
		glVertex2f( x2+x, y2+y );
		glEnd();
	} 
}

void drawOval2D( float radius,int x, int y, float ovalx, float ovaly ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f;  th1 = th1 + 1.0f ) {
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad ) * (ovalx / 100.0f);
		float y1 = radius * sin( th1_rad ) * (ovaly / 100.0f);
		float x2 = radius * cos( th2_rad ) * (ovalx / 100.0f);
		float y2 = radius * sin( th2_rad ) * (ovaly / 100.0f);

		glBegin( GL_LINES );
		glVertex2f( x1+x, y1+y );     
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

void drawOval2DFill( float radius, int x, int y, float ovalx, float ovaly ) {
	for ( float th1 = 0.0f;  th1 <= 360.0f; th1 = th1 + 1.0f ) {
		float th2 = th1 + 10.0f;
		float th1_rad = th1 * TO_RAD; 
		float th2_rad = th2 * TO_RAD;

		float x1 = radius * cos( th1_rad ) * (ovalx / 100.0f);
		float y1 = radius * sin( th1_rad ) * (ovaly / 100.0f);
		float x2 = radius * cos( th2_rad ) * (ovalx / 100.0f);
		float y2 = radius * sin( th2_rad ) * (ovaly / 100.0f);

		glBegin( GL_TRIANGLES );
		glVertex2f( static_cast<float>(x), static_cast<float>(y) );
		glVertex2f( x1+x, y1+y );
		glVertex2f( x2+x, y2+y );
		glEnd();
	}
}

void initialize() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glOrtho( 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1 );
}

void terminate() {
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT );

	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f);
	drawCircle2D( 40.0f, 50, 50 );
	glColor4f( 0.0f, 0.0f, 1.0f, 1.0f);
	drawCircle2DFill( 50.0f, 150, 180 );
	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	drawOval2D( 50.0f, 150, 80, 100.0f, 80.0f );
	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
	drawOval2DFill( 80.0f, 260, 120, 50.0f, 100.0f );

	glFlush();
}

int main( int argc, char *argv[] ) {
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( DISPLAY_WIDTH, DISPLAY_HEIGHT );
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutCreateWindow( "Hello OpenGL!!" );
	glutDisplayFunc( display );

	initialize();
	glutMainLoop();
	terminate();
	return 0;
}

