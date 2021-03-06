#include "sinwave.h"

global g = {false, 0.2f, false, false};

float light_pos[] = {1, 1, 1, 0};
float light_colour[] = {1, 1, 1, 1};
float object_colour[] = {0, 1, 0, 1};
float poly = 16;
vec3f origin = {0,0,0};


void drawLight()
{
//	glColor3f()

	glLightfv(GL_FRONT, GL_SPECULAR, light_colour);
	glLightfv(GL_FRONT, GL_DIFFUSE, light_colour);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, object_colour);
	//glMaterialfv(GL_)
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, object_colour);
}

void keyboardCB (unsigned char key, int x, int y)
{
	switch(key) {
	case 'd':
		g.debug = !g.debug;
		sg.normals = !sg.normals;
		c.debug = !c.debug;
		break;
	case '=':
		g.teapot_scale += 0.01;
		if(g.debug)
			printf("increasing scale: %f\n", g.teapot_scale);
		break;
	case '-':
		g.teapot_scale -= 0.01;
		if(g.debug)
			printf("reducing scale: %f\n", g.teapot_scale);
		break;
	case 'q':
		if(g.debug)
			printf("EXITING VIA KEY\n");
		exit(0);
		break;
	case 'l':
		if(!g.lit)
		{
			glShadeModel(GL_SMOOTH);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}
		g.lit = !g.lit;
		sg.lit = !sg.lit;
		if(g.debug)
			printf("TOGGLING LIGHTING\n");
		break;
	case 'w':
		g.wire = !g.wire;
		sg.wireframe = !sg.wireframe;
		if(g.debug)
			printf("TOGGLING WIREFRAME\n");
		break;
	case ']':
		poly *= 2;
		break;
	case '[':
		poly /= 2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void display()
{
	vec3f coords = {-10, 0, 0};
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glPushMatrix();
	
	cameraTransform();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(c.x_angle, c.y_angle, 0);

	drawLight();
	
	if(g.lit)
		glDisable(GL_LIGHTING);
	drawAxes(50);
	if(g.lit)
		glEnable(GL_LIGHTING);

	drawGrid(16, 1, true);
	

	
	glPopMatrix();
	
	glutSwapBuffers();

}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("s3718372 - Assignment 1");
	glutKeyboardFunc(keyboardCB);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseCB);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
//	glutIdleFunc(update);

	glutMainLoop();
}