#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define INICIO -15
#define FIM 35
#define PASSO 10

float rotationX = 45.0, rotationY = 0.0;
float last_x = -20, last_y = 6;
int width = 640, height = 300;

int distOrigem = 45;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}

void desenharGrid () {
  for (int linha = INICIO; linha < FIM; linha += PASSO) {
      for (int coluna = INICIO; coluna < FIM; coluna += PASSO) {

         glPushMatrix();
            glRotatef(45, 1, 0, 0);
            glTranslatef(-10, -20, 0);
            glBegin(GL_POLYGON);
               glVertex3f(linha, coluna, 0);
               glVertex3f(linha + PASSO, coluna, 0);
               glVertex3f(linha + PASSO, coluna + PASSO, 0);
               glVertex3f(linha, coluna + PASSO, 0);
            glEnd();
         glPopMatrix();
      }
   }
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1, 1, 1);
   desenharGrid();
   glColor3f (1, 0, 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   
   glPushMatrix();
      glScalef(1.11, 1.1, 1.1);
		glRotatef(rotationX, 1.0, 0.0, 0.0 );
      glTranslatef(last_x, last_y, 0);
      glutSolidCube(10);
   glPopMatrix();

   glutSwapBuffers();
}

void idle ()
{
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void specialKeysPress(int key, int x, int y)
{
   printf("%d\n", key);
   switch(key)
   {
      case GLUT_KEY_RIGHT:
         //if (passoX != 0) passoX += 1;
      break;
      case GLUT_KEY_LEFT:
         //if (passoX != 0) passoX = passoX - 1 < 1 ? 1 : passoX - 1;
        break;
   break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(specialKeysPress);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
