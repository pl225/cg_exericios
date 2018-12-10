#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


float x_minimo = -24,x_maximo = 24, z_minimo = 12,z_maximo = 60;
float desiredFPS = 30;
float X = x_maximo, XL = x_maximo;
float Z = z_minimo, ZL = z_maximo;
float rotationX = 25.0, rotationY = 0.0;
int last_x, last_y;
int width = 1200, height = 480;
float var = 0.0f;
float dir = 1.0f;
int count=0;
int distancia = 45;
char direction = 'x';
int gridSize = 12;

void init(void);
void display(void) ;
void idle(void);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void mouse(int button, int state, int x, int y);
void drawGrid(float x_maximo, float xStep, float x_minimo, float z_maximo, float zStep, float z_minimo);
void drawCube(float x, float z);
void reshape(int w, int h);

float max(float a, float b) {
  return a > b ? a : b;
}

float min(float a, float b) {
  return a < b ? a : b;
}


void keyboard (unsigned char key, int x, int y) {
  if(isMoving) {
    return;
  }
  isMoving = true;
  direction=tolower(key);
  ZL = Z; XL = X;
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (width, height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  printf("W,A,S,D para mover o cubo \n");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

void init(void) {
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  glEnable(GL_LIGHT0);                   // habilita luz 0
  glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
  glColorMaterial(GL_FRONT, GL_DIFFUSE);

  glEnable(GL_LIGHTING);                 // Habilita luz
  glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
  glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

  glutSetWindowTitle("3D Board");
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(70.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt (0.0, 30.0, 0, 0.0, 0.0, 25.0, 0.0, 1.0, 0.0);

  drawGrid(-30, gridSize, 30, 6, gridSize, 66);

  drawCube(X, Z);

  glutSwapBuffers();
  //fpsViewer->drawFPS();
}


void drawCube(float x, float z) {

  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(x , gridSize/2, z);
    glutSolidCube(gridSize);
  glPopMatrix();
}

void drawGrid(float x_maximo, float xStep, float x_minimo, float z_maximo, float zStep, float z_minimo) {

  glPushMatrix();
    glColor3f (1.0, 1.0, 1.0);
    for(float i = x_maximo; i < x_minimo; i = i + xStep) {
      for(float j = z_maximo; j < z_minimo; j = j + zStep) {
        glBegin(GL_LINE_LOOP);
          glVertex3f(i, 0, j);
          glVertex3f(i + xStep, 0, j);
          glVertex3f(i + xStep, 0, j + zStep);
          glVertex3f(i, 0, j + zStep);
        glEnd();
      }
    }
  glPopMatrix();
}

bool isMoving = false;

void updateMovement(float dt) {
  float qtdMov = gridSize/10.0;
   switch (tolower(direction))
    {
    case 'w':
       Z = Z + qtdMov > z_maximo ? z_maximo : Z + qtdMov;
       isMoving = Z != z_maximo;
    break;
    case 's':
    	Z = Z - qtdMov < z_minimo ? z_minimo : Z - qtdMov;
    	isMoving = Z != z_minimo;
    break;
    case 'a':
        X = X + qtdMov > x_maximo ? x_maximo : X + qtdMov;
       isMoving = X != x_maximo;
    break;
    case 'd':
        X = X - qtdMov < x_minimo ? x_minimo : X - qtdMov;
       isMoving = X != x_minimo;
    break;
    }
  	if(abs(ZL - Z) >= gridSize - 0.01 || abs(XL - X) >= gridSize - 0.01) {
    	isMoving = false;
    }
}


void idle () {  
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
   if(isMoving) {
    updateMovement(frameTime);
  }

    /* Update tLast for next time, using static local variable */
  tLast = t;
  glutPostRedisplay();
}

void reshape (int w, int h) {
  width = w;
  height = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

// Motion callback
void motion(int x, int y ) {
  rotationX += (float) (y - last_y);
  rotationY += (float) (x - last_x);

  last_x = x;
  last_y = y;
}


}