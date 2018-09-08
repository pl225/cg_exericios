#include <stdio.h>
#include <GL/glut.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);

int triangulo = 3;

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercício 1");
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
   glColor3f (0.0, 255.0, 0.0);
   glBegin(GL_LINES);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.5, 1.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f (0.0, 0.5, 0.0);
      glVertex3f (1.0, 0.5, 0.0);
   glEnd();

   if (triangulo != 3)
        glColor3f(255.0, 0.0, 0.0);
   else
        glColor3f(0.0, 0.0, 0.0);


   if (triangulo == 1 || triangulo == 2) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

   if (triangulo < 3) {
        glBegin(GL_TRIANGLES);
            glVertex3f(0.5, 0.5, 0.0);
            glVertex3f(1.0, 0.5, 0.0);
            glVertex3f(0.75, 0.85, 0.0);
        glEnd();

        if (triangulo == 2) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.0, 0.5, 0.0);
                glVertex3f(0.5, 0.5, 0.0);
                glVertex3f(0.25, 0.15, 0.0);
            glEnd();
        }

   } else if (triangulo == 3) {
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.35, 0.85, 0.0);
            glVertex3f(0.15, 0.5, 0.0);
            glVertex3f(0.35, 0.15, 0.0);
            glVertex3f(0.65, 0.15, 0.0);
            glVertex3f(0.85, 0.5, 0.0);
            glVertex3f(0.65, 0.85, 0.0);
        glEnd();
   }

   glutSwapBuffers ();
}


void init (void)
{
   glClearColor (1.0, 1.0, 1.0, 1.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

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
			triangulo = triangulo + 1 > 3 ? 0 : triangulo + 1;
		break;
		case GLUT_KEY_LEFT:
			triangulo = triangulo - 1 < 0 ? 3 : triangulo - 1;
        break;
		default:
			printf("\nPressionou outra tecla especial não mapeada!");
	break;
	}
	glutPostRedisplay();
}
