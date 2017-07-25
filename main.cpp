#include <GL/gl.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>

#define G 9.8


#define randomico() ((float) rand()/ RAND_MAX) //Numero aleatório entre 0 e1

GLfloat angle = 60, fAspect;
int rodar = 0.0;
int rodarApa = 0.0;
float rodarHaste = 0.0;
float soma = 0.2;


int rodarHori = 0;
int rodarVert = 0;


double d_x, d_z;

float forca = 1.0;

int n = 1;

double rotacaoVento;
double intensidadeVento = 0.025;
double intensidadeVentoz;
double intensidadeVentox;


typedef struct
{
    float x;
    float y;
    float z;
    float x0;
    float y0;
    float z0;
    bool vis;
    float forcax;
    float forcay;
    float forcaz;
    float tempo;
    float vel;
    float anguloy;
    float anguloxz;
    double ventox;
    double ventoz;
    int pulo;

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

    srand(time(0));
    d_z = (25.0 * randomico()) + 25.0;
    d_x = (40.0 - (-40.0)) * randomico() + (-40.0);
    rotacaoVento = 180.0 * randomico();

}


void ativaIluminacao (void)
{
    GLfloat luzAmbiente[4]= {0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0};	  // "cor"
    GLfloat luzEspecular[4]= {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4]= {0.0, 50.0, 50.0, 1.0};
    // Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;
    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);
}


void desativaIluminacao(void)
{
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
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


void DivisaoCampo()
{
    glPushMatrix();
    glTranslated(0.0, 0.0, -50.0); //-50

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-45

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-40

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-35

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-30

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-35

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-30

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-25

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-20

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-15

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //-10

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.5, 0.5, 5.0); //-5

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //0

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //5

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //10

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //15

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //20

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //25

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //30

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //35

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //40

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 10.0); //45

    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glTranslated(0.0, 0.0, 5.0); //50

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,5.0);
    glVertex3f(50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(-50.0,0.0,5.0);
    glEnd();

    glPopMatrix();
}


void Alvo()
{
    glPushMatrix();

    glTranslated(d_x, 0.0, -d_z);

    glColor3f(0.0, 1.0, 1.0);

    glScaled(2.0, 4.0, 2.0);

    glutSolidCube(1);

    glPopMatrix();

}


void MarcadorForca()
{
    glPushMatrix();
    desativaIluminacao();
    glTranslated(5.0, 5.0, 0.0);

    glColor3f(1.0, 1.5, 0.0);
    for(int i = 0; i<n ; i++)
    {
        glBegin(GL_QUADS);
        glVertex3f(0.5,0.1*n,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.1*n,0.0);

        glEnd();
    }
    ativaIluminacao();
    glPopMatrix();
}


void GeraVento()
{
    glPushMatrix();

    desativaIluminacao();

    glTranslated(-5.0, 5.0, 0.0);
    glRotated(rotacaoVento, 0.0, 1.0, 0.0);
    glRotated(290.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.5);

    glBegin(GL_QUADS);
    glVertex3f(0.1,0.5,0.0);
    glVertex3f(0.1,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0.2,0.5,0);
    glVertex3f(0.05,0.7,0);
    glVertex3f(-0.1,0.5,0);
    glEnd();

    std::cout << rotacaoVento << std::endl;

    intensidadeVentoz = intensidadeVento*sin(rotacaoVento);
    intensidadeVentox = intensidadeVento*cos(rotacaoVento);

    ativaIluminacao();
    glPopMatrix();

}


void TerrenoBase()
{
    glPushMatrix();

    DivisaoCampo();

    Alvo();

    glColor3f(1.0, 0.0,0.0);

    glColor3f(0.5, 0.0,0.0);

    glScaled(1.0, 4.0, 1.0);
    glutWireCube(1);

    glPopMatrix();
}


void DestroiAlvo()
{
    std::cout << "Destruiu!!" << std::endl;
}


void Trajetoria(void)
{
    float tempo = 0.0;

    float raio = 2.0*cos((rodarVert*M_PI)/180.0);

    float y = 2.0*sin((rodarVert*M_PI)/180.0);
    float x = -1.0*raio*sin((rodarHori*M_PI)/180.0);
    float z = -1.0*raio*cos((rodarHori*M_PI)/180.0);

    float norma = sqrt(x*x + y*y + z*z);

    float  forcax = x/norma;
    float  forcay = y/norma;
    float  forcaz = z/norma;

    y = y + 2.0;


    float x0 = x;
    float y0 = y;
    float z0 = z;

    glColor3f(0.5, 1.0,0.5);
    glBegin(GL_LINE_STRIP);
    do
    {
        x =    x0  + forca*forcax*tempo;
        y =    y0  + forca*forcay*tempo - 0.5*G*tempo*tempo;
        z =    z0  + forca*forcaz*tempo;
        glVertex3f(x,y,z);
        tempo += 0.01;

        if((x == d_x && z == d_z))
        {
            DestroiAlvo();
        }

    }
    while(y > 0);
    glEnd();
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

    MarcadorForca();

    GeraVento();

    glTranslated(0.0,2.0,0.0);
    glRotated(rodarHori, 0.0, 1.0, 0.0);
    glRotated(rodarVert, 1.0, 0.0, 0.0);
    Canon();
    glPopMatrix();
    if(!tiro.vis)
    {
        Trajetoria();
    }

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
    gluLookAt(0,1,13, 0,4,0, 0,1,0); // Especifica posição do observador e do alvo
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
        tiro.tempo = 0.0;

        float raio = 2.0*cos((rodarVert*M_PI)/180.0);

        tiro.y = 2.0*sin((rodarVert*M_PI)/180.0);
        tiro.x = (-1.0*raio*sin((rodarHori*M_PI)/180.0));
        tiro.z = (-1.0*raio*cos((rodarHori*M_PI)/180.0));

        float norma = sqrt(tiro.x*tiro.x + tiro.y*tiro.y + tiro.z*tiro.z);

        tiro.forcax = tiro.x/norma;
        tiro.forcay = tiro.y/norma;
        tiro.forcaz = tiro.z/norma;

        tiro.y = tiro.y + 2.0;

        tiro.vel = forca;

        tiro.x0 = tiro.x;
        tiro.y0 = tiro.y;
        tiro.z0 = tiro.z;

        tiro.ventox = 0.0;
        tiro.ventoz = 0.0;

        tiro.pulo = 0;
        tiro.anguloy = (rodarVert*M_PI)/180.0;
        tiro.anguloxz = (rodarHori*M_PI)/180.0;
    }
    if (key == '+')
    {
        forca += 2.0;
        n++;
    }
    if (key == '-')
    {
        forca -= 2.0;
        n--;

    }
    glutPostRedisplay();

}


void Timer(int value)
{
    if(tiro.vis)
    {
        if(tiro.vel > 0.1)
        {
            tiro.x =    tiro.x0  + tiro.vel*tiro.forcax*tiro.tempo /*+ tiro.ventox*/;
            tiro.y =    tiro.y0  + tiro.vel*tiro.forcay*tiro.tempo - 0.5*G*tiro.tempo*tiro.tempo;
            tiro.z =    tiro.z0  + tiro.vel*tiro.forcaz*tiro.tempo /*+ tiro.ventoz*/;
            tiro.ventox += intensidadeVentox;
            tiro.ventoz += intensidadeVentoz;
            if(tiro.y <0.2)
            {
                printf("ANGULO: %f VELOCIDADE: %f\n",tiro.anguloy,tiro.vel);
                if(tiro.pulo == 0)
                {
                    tiro.anguloy = tiro.anguloy + M_PI_2;
                }
                tiro.x0 = tiro.x;
                tiro.y0 = tiro.y;
                tiro.z0 = tiro.z;
                tiro.ventox = 0.0;
                tiro.ventoz = 0.0;
                tiro.vel = tiro.vel*0.9;
                tiro.pulo ++; //Numero de Pulos
                tiro.tempo = 0.0;
            }

            if (tiro.vel < 0.1)
            {
                tiro.vis = false;
            }
        }
        tiro.tempo += 0.01;
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

    ativaIluminacao();

    glutReshapeFunc(AlteraTamanhoJanela);

    glutKeyboardFunc(Teclado);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
