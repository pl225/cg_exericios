#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float altura = 400, largura = 400;

void  DesenhaEixos();
void  DesenhaObjetos1();
void  DesenhaObjetos2();
void  display(void);
void  keyboard(unsigned char key, int x, int y);
void  init(void);
void desenhaTudo();

//////////////////////////////////////////////////
// Main Function
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (20,20);
   glutCreateWindow ("Execício 3");
   init ();
   glutDisplayFunc(display);  // Eh quem ira chamar todo o restante das funçoes
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}

//////////////////////////////////////////////////
// Functions

// Inicializa opengl
void init(void)
{
   glClearColor(0.0,0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
}

// Eixos coordenados
void DesenhaEixos()
{
   glBegin(GL_LINES);
      glColor3f (  0.0,   1.0, 0.0);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f( 10.0, 0.0, 0.0);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f(0.0, -10.0, 0.0);
      glVertex3f(0.0,  10.0, 0.0);
   glEnd();
}

void DesenhaObjetos()
{
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f(2.0, 2.0, 0.0);
      glVertex3f(8.0, 2.0, 0.0);
      glVertex3f(2.0, 8.0, 0.0);
   glEnd();

  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glColor3f(135.0, 206.0, 250.0);
  glBegin(GL_POLYGON);
      glVertex3f(2.0, -2.0, 0.0);
      glVertex3f(8.0, -2.0, 0.0);
      glVertex3f(2.0, -8.0, 0.0);
  glEnd();

  glColor3f(135.0, 206.0, 250.0);
  glBegin(GL_LINE_STRIP);
      glVertex3f(-2.0, -2.0, 0.0);
      glVertex3f(-8.0, -2.0, 0.0);
      glVertex3f(-2.0, -8.0, 0.0);
      glVertex3f(-8.0, -8.0, 0.0);
  glEnd();
}

void desenhaTudo () {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    DesenhaEixos();
    DesenhaObjetos();
}

///////////////////////////////////////////////////////////
// Glut and image functions
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Define viewport do canto superior esquerdo
   glViewport ((int) 0, (int) 200, (int) 200, (int) 200);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-10.0, 10.0, -10.0, 10.0, -1, 1);

   desenhaTudo();

   // canto superior direito
   glViewport ((int) 200, (int) 200, (int) 200, (int) 200);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-1.0, 9.0, -1.0, 9.0, -1, 1);

   desenhaTudo();

   // canto inferior direito
   glViewport ((int) 200, (int) 0, (int) 190, (int) 190);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-1.0, 9.0, -9.0, 1.0, -1, 1);

   desenhaTudo();

   // canto inferior esquerdo
   glViewport ((int) 0, (int) 0, (int) 190, (int) 190);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-9.0, 1.0, -9.0, 1.0, -1, 1);

   desenhaTudo();

   glutSwapBuffers();
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit(0);
      break;
   }
   glutPostRedisplay();
}

