#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MIN -100
#define SIZE 10

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

void display(void);
void init (void);
void desenhaEixos();
void showMenu();
void specialKeysPress(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeysPress);
   glutMainLoop();

   return 0;
}

void showMenu()
{
   printf("\n=== MENU ===");
   printf("\n1 - Use as setas direcionais para Translacao");
   printf("\n2 - Use as teclas R e r para Rotacao");
   printf("\n3 - Use as teclas + e - para Escala");
   printf("\n4 - Pressione ESC para Sair");
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtrans, ytrans, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glScalef(scale, scale, scale);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();

   if(enableMenu) showMenu();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void specialKeysPress(int key, int x, int y)
{
   float metadeLado = (SIZE * scale) / 2;
   switch(key)
   {
      case GLUT_KEY_RIGHT:
         xtrans = xtrans + metadeLado + 1 > MAX ? xtrans : xtrans + 1;
         break;
      case GLUT_KEY_LEFT:
         xtrans = xtrans - metadeLado - 1 < MIN ? xtrans : xtrans - 1;
         break;
      case GLUT_KEY_UP:
         ytrans = ytrans + metadeLado + 1 > MAX ? ytrans : ytrans + 1;
         break;
      case GLUT_KEY_DOWN:
         ytrans = ytrans - metadeLado - 1 < MIN ? ytrans : ytrans - 1;
         break;
   }
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27: // ESC
         exit(0);
         break;
      case 43: // +
         scale += 1;
         break;
      case 45: // -
         scale =  scale - 1 <= 0 ? scale : scale - 1;
         break;
      case 114: // r
         angle += 1;
         break;
      case 82: // R
         angle -= 1;
         break;
   }
   glutPostRedisplay();
}