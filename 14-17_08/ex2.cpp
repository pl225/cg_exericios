#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);

int partes = 0;

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (450, 390);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercício 2");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc( specialKeysPress );

	printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT);

   // Desenhar um polígono branco (retângulo)
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_LINES);
      glVertex3f (0.0, -2.0, 0.0);
      glVertex3f (0.0, 2.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f (-10.0, 0.0, 0.0);
      glVertex3f (390.0, 0.0, 0.0);
   glEnd();

   glColor3f (0.0, 255.0, 0.0);

   const float volta = 360.0;
   float discretizacao;

   glBegin(GL_LINE_STRIP);

   if (partes == 0) discretizacao = volta / 6.0;   
   else if (partes == 1) discretizacao = volta / 12.0;
   else discretizacao = volta / 180.0;

   float fatorConversao = M_PI / 180.0;

   for (float i = 0.0; i <= volta; i += discretizacao) {
      glVertex3f(i, sin(i * fatorConversao), 0.0);
   }

   glEnd();

   glutSwapBuffers ();
}


void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27:
         exit(0);
         break;
   }
}

void specialKeysPress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			partes = partes + 1 > 2 ? 0 : partes + 1;
		break;
		case GLUT_KEY_LEFT:
			partes = partes - 1 < 0 ? 2 : partes - 1;
        break;
		default:
			printf("\nPressionou outra tecla especial não mapeada!");
	break;
	}
	glutPostRedisplay();
}
