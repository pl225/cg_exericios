#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"
#include <math.h>

// Globals
int width  = 1000, height = 500;
float rotationX = 0.0, rotationY = 0.0, sphereSize = 30.0, passoX = 6, passoY = -1;
float last_x = 20, last_y = 400, desiredFPS = 15, last_y_aux = 20, alturaMaxima = 400;

void atualizarPosicaoEsfera () {
   if (last_x >= 980 || last_x < 20) 
      passoX *= -1;
   last_x += passoX;

   if (passoY < 0) {
      if (last_y_aux > 4) {
         last_y_aux += passoY;
         last_y = pow(last_y_aux, 2);
      } else {
         passoY *= -1;
         alturaMaxima *= 0.75;
         //if (alturaMxima <= 20) passoX = 0;
      }
   } else if (passoY > 0) {
      last_y_aux += passoY;
      float aux = pow(last_y_aux, 2);
      if (aux <= alturaMaxima) {
         last_y = aux;
      } else {
         passoY *= -1;
      }
   } 
   /*if (last_y >= 480 || last_y <= 20)
      passoY *= -1;
   last_y += passoY;*/
}

void idle()
{
   float t, desiredFrameTime, frameTime;
   static float tLast = 0.0;

   // Get elapsed time
   t = glutGet(GLUT_ELAPSED_TIME);
   // convert milliseconds to seconds
   t /= 1000.0;

   // Calculate frame time
   frameTime = t - tLast;
   // Calculate desired frame time
   desiredFrameTime = 1.0 / (float) (desiredFPS);

   // Check if the desired frame time was achieved. If not, skip animation.
   if( frameTime <= desiredFrameTime)
     return;

   /*
   *UPDATE ANIMATION VARIABLES
   */
   atualizarPosicaoEsfera();

   /* Update tLast for next time, using static local variable */
   tLast = t;
   glutPostRedisplay();
}

void init(void)
{
   glClearColor (0.5, 0.5, 0.5, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
	 initLight(width, height);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   setMaterial();

   glPushMatrix();
      glTranslatef(last_x, last_y, 0.0); // Posicionamento inicial da esfera
      glutSolidSphere(20.0, 100, 100);
    glPopMatrix();

   glutSwapBuffers();
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
         if (passoX != 0) passoX += 1;
      break;
      case GLUT_KEY_LEFT:
         if (passoX != 0) passoX = passoX - 1 < 1 ? 1 : passoX - 1;
        break;
      default:
         printf("\nPressionou outra tecla especial não mapeada!");
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
   glutCreateWindow("Animation Base");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(specialKeysPress);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
