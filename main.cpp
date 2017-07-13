#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

GLfloat angle = 60, fAspect;
int rodar = 0.0;
int rodarApa = 0.0;
float rodarHaste = 0.0;
float soma = 0.2;

int rodarHori = 0;
int rodarVert = 0;

typedef struct
{
    float x;
    float y;
    float z;
    bool vis;
    float forcax;
    float forcay;
    float forcaz;

} Bola;

Bola tiro;

void Inicializa(void)
{
    tiro.vis = false;

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65, 1.0, 0.5, 500);
    glClearColor (1.0, 1.0, 1.0, 0.0);


    glColor3f(0.0, 0.0,0.0);
    angle = 60;
}

void Canon()
{

    glColor3f(0.5, 0.0,0.0);
    glPushMatrix();

    glutWireSphere(0.5, 10, 10);
    glRotated(180.0,1,0,0);

    GLUquadricObj* q = gluNewQuadric();
    gluQuadricDrawStyle(q,GLU_LINE);
    gluCylinder(q, 0.2, 0.2, 2.0, 5,5);
    gluDeleteQuadric(q);
    glPopMatrix();

}

void TerrenoBase()
{
    glPushMatrix();
    glColor3f(0.5, 0.5,0.5);
        glBegin(GL_QUADS);
        glVertex3f(50.0,0.0,50.0);
        glVertex3f(50.0,0.0,-50.0);
        glVertex3f(-50.0,0.0,-50.0);
        glVertex3f(-50.0,0.0,50.0);
    glEnd();

    glColor3f(1.0, 0.0,0.0);
    glScaled(1.0, 4.0, 1.0);
    glutWireCube(1);

    //for(int i=0; i<50; i+5)
    //{

    //}
    //glColor3f(0.0, 1.0,0.0);
    //    glBegin(GL_QUADS);
    //    glVertex3f(50.0,0.0,50.0);
    //    glVertex3f(50.0,0.0,-50.0);
    //    glVertex3f(-50.0,0.0,-50.0);
    //    glVertex3f(-50.0,0.0,50.0);
   // glEnd();

    glPopMatrix();
}


void Desenha(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,4,6, 0,3,0, 0,1,0);
    glColor3f(0.0, 0.0,0.0);

    glPushMatrix();
    TerrenoBase();

    glTranslated(0.0,2.0,0.0);
    glRotated(rodarHori, 0.0, 1.0, 0.0);
    glRotated(rodarVert, 1.0, 0.0, 0.0);
    Canon();
    glPopMatrix();


    glColor3f(0.0, 0.0,0.0);
    if(tiro.vis)
    {
        glPushMatrix();
        glTranslated(tiro.x, tiro.y, tiro.z);
        //glRotated(90.0, 1.0, 0.0, 0.0);
        glutSolidSphere(0.2, 10, 10);
        glPopMatrix();
    }


    glutSwapBuffers();
}




void AlteraTamanhoJanela (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    if(h == 0) h = 1;

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65, (GLfloat) w/(GLfloat) h, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,1,13, 0,4,0, 0,1,0); // Especifica posi��o do observador e do alvo
}

void Teclado(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        rodarHori = rodarHori + 5;
        rodarHori = rodarHori%360;
    }
    if (key == 'd')
    {
        rodarHori = rodarHori - 5;
        rodarHori = rodarHori%360;
    }
    if (key == 'w')
    {
        rodarVert = rodarVert + 5;
        rodarVert = rodarVert%360;
    }
    if (key == 's')
    {
        rodarVert = rodarVert - 5;
        rodarVert = rodarVert%360;
    }
    if (key == 'e')
    {
        tiro.vis = true;
        tiro.y = 2.0*sin((rodarVert*M_PI)/180.0);
        float raio = 2.0*cos((rodarVert*M_PI)/180.0);
        tiro.x = -1.0*raio*sin((rodarHori*M_PI)/180.0);
        tiro.z = -1.0*raio*cos((rodarHori*M_PI)/180.0);
        float norma = sqrt(tiro.x*tiro.x + tiro.y*tiro.y + tiro.z*tiro.z);
        tiro.forcax = tiro.x/norma;
        tiro.forcay = tiro.y/norma;
        tiro.forcaz = tiro.z/norma;
        tiro.y = tiro.y + 2.0;
    }
    glutPostRedisplay();

}

void Timer(int value)
{
    if(tiro.vis){
         tiro.x = tiro.x + tiro.forcax;
         tiro.y = tiro.y + tiro.forcay;
         tiro.z = tiro.z + tiro.forcaz;

    }
    glutTimerFunc(10,Timer,0);
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    Inicializa();

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize (800, 800);

    glutInitWindowPosition ((1280 - 800)/2, (800 - 800)/2);

    glutCreateWindow ("Trabalho 1");

    glutTimerFunc(10,Timer,0);

    glutDisplayFunc(Desenha);

    glutReshapeFunc(AlteraTamanhoJanela);

    glutKeyboardFunc(Teclado);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
