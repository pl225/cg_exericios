#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;

float desiredFPS = 5;

float xTrianguloVerde = 0.3, yTrianguloVerde = 0.5,
    dirXTrianguloVerde = 0.1, dirYTrianguloVerde = 0.1;

const float maiorXTrianguloVerde = 0.7, maiorYTrianguloVerde = 0.5,
    menorXTrianguloVerde = 0.2, menorYTrianguloVerde = 0.2;

float xTrianguloVermelho = 0.2, yTrianguloVermelho = 0.2,
    dirXTrianguloVermelho = 0.1, dirYTrianguloVermelho = 0.1;

const float maiorXTrianguloVermelho = 0.8, maiorYTrianguloVermelho = 0.8,
    menorXTrianguloVermelho = 0.4, menorYTrianguloVermelho = 0.5;

void display(void);
void init (void);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

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
    
    if(maiorXTrianguloVerde + xTrianguloVerde >= 1 || menorXTrianguloVerde + xTrianguloVerde <= 0.1) 
        dirXTrianguloVerde *= -1;
    if(maiorYTrianguloVerde + yTrianguloVerde >= 1 || menorYTrianguloVerde + yTrianguloVerde <= 0.1) 
        dirYTrianguloVerde *= -1;
    //else if ()
    xTrianguloVerde += dirXTrianguloVerde;
    yTrianguloVerde += dirYTrianguloVerde;

    if(maiorXTrianguloVermelho + xTrianguloVermelho >= 1 || menorXTrianguloVermelho + xTrianguloVermelho <= 0) 
        dirXTrianguloVermelho *= -1;
    if(maiorYTrianguloVermelho + yTrianguloVermelho >= 1 || menorYTrianguloVermelho + yTrianguloVermelho <= 0) 
        dirYTrianguloVermelho *= -1;
    //else if ()
    xTrianguloVermelho += dirXTrianguloVermelho;
    yTrianguloVermelho += dirYTrianguloVermelho;

    
    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

void plotTriangle (float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f (x1, y1);
        glVertex2f (x2, y2);
        glVertex2f (x3, y3);
    glEnd();
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    glColor3f (0.0, 1.0, 0.0);

    glPushMatrix();
        glTranslatef(xTrianguloVerde, yTrianguloVerde, 0);
        glBegin(GL_TRIANGLES);
            plotTriangle(0.5, menorYTrianguloVerde, maiorXTrianguloVerde, 0.4, menorXTrianguloVerde, maiorYTrianguloVerde);
        glEnd();
    glPopMatrix();

    glColor3f (1.0, 0.0, 0.0);

    glPushMatrix();
        glTranslatef(xTrianguloVermelho, yTrianguloVermelho, 0);
        plotTriangle(0.6, maiorYTrianguloVermelho, maiorXTrianguloVermelho, menorYTrianguloVermelho, menorXTrianguloVermelho, 0.6);
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
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Screensaver");
    glutFullScreen();
    glutIdleFunc( idle);
    init ();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
