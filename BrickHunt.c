#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<GL/glut.h>
#include<windows.h>

using namespace std;

const int brickcount = 10;

float brickx[brickcount], bricky[brickcount], brickxdir[brickcount], brickydir[brickcount];
bool brickalive[brickcount];

float cursorx, cursory;
int score;
char buffer[10];

void initgame()
{
	srand(time(NULL));
	score = 0;
	for (int i = 0; i <= brickcount - 1; i++)
	{
		brickalive[i] = true;
		brickx[i] = rand() % 640;
		bricky[i] = rand() % 350;

		if (rand() % 2 == 0)
			brickxdir[i] = 1;
		else
			brickxdir[i] = -1;


		if (rand() % 2 == 0)
			brickydir[i] = 1;
		else
			brickydir[i] = -1;
	}
}




void shoot(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i <= brickcount - 1; i++)
		{
			if (brickalive[i])
			{
				if (x > brickx[i] - 15 && x < brickx[i] + 15 && y < bricky[i] + 10 && y > bricky[i] - 10)
				{
					score = score + 5;
					brickalive[i] = false;
				}
			}
		}
	}
}

void setcursor(int x, int y)
{
	cursorx = x;
	cursory = y;
}

void drawcursor()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex2f(cursorx - 5, cursory - 5);
	glVertex2f(cursorx - 5, cursory + 5);
	glVertex2f(cursorx + 5, cursory + 5);
	glVertex2f(cursorx + 5, cursory - 5);
	glVertex2f(cursorx - 5, cursory - 5);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(cursorx - 10, cursory);
	glVertex2f(cursorx + 10, cursory);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(cursorx, cursory - 10);
	glVertex2f(cursorx, cursory + 10);
	glEnd();

	//glutSwapBuffers();
}


void drawbrick()
{
	for (int i = 0; i <= brickcount - 1; i++)
	{
		if (brickalive[i] == true)
		{
			if (brickx[i] - 10 < 0 || brickx[i] + 10 > 640)
			{
				brickxdir[i] = -brickxdir[i];
			}

			if (bricky[i] - 5 < 0 || bricky[i] + 5 > 360)
			{
				brickydir[i] = -brickydir[i];
			}

			brickx[i] = brickx[i] + brickxdir[i];
			bricky[i] = bricky[i] + brickydir[i];

			glBegin(GL_QUADS);
			glColor3f(0.5, 0, 0.05);//color for moving bricks
			glVertex2f(brickx[i] - 15, bricky[i] - 10);
			glVertex2f(brickx[i] - 15, bricky[i] + 10);
			glVertex2f(brickx[i] + 15, bricky[i] + 10);
			glVertex2f(brickx[i] + 15, bricky[i] - 10);
			glEnd();
		}
		else
		{
			if (bricky[i] < 360)
			{
				bricky[i] = bricky[i] + 0.5;
			}

			glBegin(GL_QUADS);
			glColor3f(1, 0, 0);//color for dead bricks
			glVertex2f(brickx[i] - 15, bricky[i] - 10);
			glVertex2f(brickx[i] - 15, bricky[i] + 10);
			glVertex2f(brickx[i] + 15, bricky[i] + 10);
			glVertex2f(brickx[i] + 15, bricky[i] - 10);
			glEnd();
		}
	}
}

void drawground()
{
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glVertex2f(0, 360);
	glVertex2f(0, 480);
	glVertex2f(640, 480);
	glVertex2f(640, 360);
	glEnd();
}


char str2[10];
char str[] = { "points:" };
void point_table()
{

	glColor3f(0, 0, 1);
	glRasterPos2i(50, 450);

	for (int i = 0; i < strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);//or use GLUT_BITMAP_TIMES_ROMAN_24 
	}

	_itoa_s(score, str2, 10);
	glColor3f(1, 0, 0);
	glRasterPos2i(120, 450);

	for (int i = 0; i < strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
	}


}

void display1()
{
	char str1[] = { "* The objective of this game is to shoot moving bricks on screen." };
	char str2[] = { "* The position of the target can be changed by moving the mouse accordingly." };
	char str3[] = { "* Each time a brick is shot the score increases by 5 points." };
	char str4[] = {"* The game is played until all the bricks are dead." };

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0, 1);

	glColor3f(0, 0, 1);
	glRasterPos2i(10, 100);

	for (int i = 0; i < strlen(str1); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str1[i]);//or use GLUT_BITMAP_TIMES_ROMAN_24 
	}
	glRasterPos2i(10, 80);
	for (int i = 0; i < strlen(str2); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
	}
	glRasterPos2i(10, 60);
	for (int i = 0; i < strlen(str3); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str3[i]); 
	}
	glRasterPos2i(10, 40);
	for (int i = 0; i < strlen(str4); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str4[i]); 
	}

	glutSwapBuffers();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.43, 0.77, 0.86, 1);

	drawground();

	drawbrick();

	drawcursor();

	point_table();



	glutSwapBuffers();
	Sleep(10);//for reducing the brick speed
}


void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


void main(int argc, char **argv)
{
	int choice;
	initgame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("brick Hunt");
	glutReshapeFunc(reshape);
	printf("enter your choice\n");
	printf("1.descreption 2.play game 3.exit\n");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:glutDisplayFunc(display1);
		break;
	case 2:glutDisplayFunc(display);
		glutIdleFunc(display);
		break;
	case 3:exit(0);
	default:exit(0);
	}
	glutMouseFunc(shoot);
	glutPassiveMotionFunc(setcursor);
	glutMotionFunc(setcursor);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
}


