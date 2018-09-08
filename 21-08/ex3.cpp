#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define INICIO -3
#define FIM 3
#define SIZE 80

int desiredFPS = 15;

float xtrans = -2.5, ytrans = -2.5, xtransParcial = xtrans, ytransParcial = ytrans;

void display(void);
void init (void);
void idle();
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (480, 480);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   glutIdleFunc( idle);
   glutMouseFunc( mouse );
   init ();
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

void desenharTabuleiro () {
  for (int linha = INICIO; linha < FIM; linha++) {
      for (int coluna = INICIO; coluna < FIM; coluna ++) {
        
        if (linha % 2 == 0) {
          if (coluna % 2 == 0) glColor3f (255.0, 255.0, 255.0);
          else glColor3f (0.0, 0.0, 0.0);
        } else {
          if (coluna % 2 == 0) glColor3f (0.0, 0.0, 0.0);
          else glColor3f (255.0, 255.0, 255.0);
        }

        glBegin(GL_POLYGON);
          glVertex3f(linha, coluna, 0);
          glVertex3f(linha + 1, coluna, 0);
          glVertex3f(linha + 1, coluna + 1, 0);
          glVertex3f(linha, coluna + 1, 0);
        glEnd();
      }
   }
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenharTabuleiro();

   glPushMatrix();
      glColor3f(255.0, 0.0, 0.0);
      glTranslatef(xtransParcial, ytransParcial, 0.0);
      glutSolidSphere(0.5, 20, 20);
   glPopMatrix();

   glutSwapBuffers ();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(INICIO, FIM, INICIO, FIM, INICIO, FIM);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void atualizarPosicaoCirculo () {
    if (xtransParcial < xtrans)
      xtransParcial += 0.25;
    else if (xtransParcial > xtrans)
      xtransParcial -= 0.25;

    if (ytransParcial < ytrans)
      ytransParcial += 0.25;
    else if (ytransParcial > ytrans)
      ytransParcial -= 0.25;
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
     atualizarPosicaoCirculo();

    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

float definirCoordenada (int p) {
  if (p == 0) return - 2.5;
  else if (p == 1) return - 1.5;
  else if (p == 2) return - 0.5;
  else if (p == 3) return 0.5;
  else if (p == 4) return 1.5;
  else return 2.5;
}

void mouse(int button, int state, int x, int y)
{
  // Inverte mouse para que origem fique no canto inferior esquerdo da janela
  // (por default, a origem é no canto superior esquerdo)
  if (xtrans == xtransParcial && ytrans == ytransParcial) {
    int posX = x / SIZE, posY = (480 - y) / SIZE;
    xtrans = definirCoordenada(posX);
    ytrans = definirCoordenada(posY);
  }

}
