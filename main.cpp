#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>


//DEFINES--------------------------------------------

#define TAM_BLOCO 100
#define PASSO	10

#define NORTE  0
#define LESTE  1
#define SUL    2
#define OESTE  3

//GLOBALS--------------------------------------------
GLuint chao;
GLuint parede;
GLuint portal;
GLuint ceumanha;
GLuint menu;
GLuint ceunoite;
GLuint menu2;
GLuint win;

//----------------------Variáveis Teste--------


GLfloat luz_amarela[] = {0.8,0.8,0.1,1.0};
GLfloat posicao_fonte_de_luz[] = { 0.0, 500.0, 0.0, 1.0 };
GLfloat luz_branca[] = {1.0,1.0,1.0,1.0};
GLfloat luz_ambiente[] = {0.8, 0.8, 0.8, 0.8};
GLfloat matriz_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat matriz_intensidade_brilho[] = { 50.0 };
GLfloat lmodel_ambient[] = {0.6,0.6,0.6,1.0};
GLint valor_especular_material = 60; //brilho especular
GLfloat jog_x= 713, jog_z= 101 ;
GLfloat mov_x=PASSO, mov_z=0;
GLint angulo=0;
GLint wire = 0;
GLint inicia = 0;
GLint refTempo = 500;
GLint LookX = 0;
GLint LookZ = 0;


//---------------------------------------------------------------


GLint mapa[26][26] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1, 
                       1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,
                       1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
                       1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,
                       1,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,
                       1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,
                       1,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,
                       1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1, 
                       1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,0,0,1,0,1,0,1,0,5,0,1,0,0,0,1,0,0,0,1,0,1,0,1,
                       1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,
                       1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1, 
                       1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,
                       1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,
                       1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,
                       1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
                       1,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,2,
                       1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,
                       1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                     };


//---------------------------------------------------------------
void desenhaCubo(){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, parede);

    // Desenha um cubo

    glBegin(GL_QUADS);			// Face posterior

    glNormal3f(0.0, 0.0, 1.0);	// Normal da face
    glTexCoord2d(0.0,0.0);
    glVertex3f(50.0, 50.0, 50.0);
    glTexCoord2d(1.0,0.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glTexCoord2d(1.0,1.0);
    glVertex3f(-50.0, -50.0, 50.0);
    glTexCoord2d(0.0,1.0);
    glVertex3f(50.0, -50.0, 50.0);

    glEnd();
    glPushMatrix();
    glRotatef(90.0f, 0.0f,0.0f,1.0f);
    
    glBegin(GL_QUADS);			// Face frontal
    glRotatef(90.0f, 0.0f,0.0f,1.0f);
    glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
    glTexCoord2d(0.0,0.0);
    glVertex3f(50.0, 50.0, -50.0);
    glTexCoord2d(1.0,0.0);
    glVertex3f(50.0, -50.0, -50.0);
    glTexCoord2d(1.0,1.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glTexCoord2d(0.0,1.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glEnd();
    glPopMatrix();


    glBegin(GL_QUADS);			// Face lateral esquerda

    glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
    glTexCoord2d(0.0,0.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glTexCoord2d(1.0,0.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glTexCoord2d(1.0,1.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glTexCoord2d(0.0,1.0);
    glVertex3f(-50.0, -50.0, 50.0);
    glEnd();

    glPushMatrix();
    glRotatef(90.0f, 1.0f,0.0f,0.0f);
    glBegin(GL_QUADS);			// Face lateral direita

    glNormal3f(1.0, 0.0, 0.0);	// Normal da face
    glTexCoord2d(0.0,0.0);
    glVertex3f(50.0, 50.0, 50.0);
    glTexCoord2d(1.0,0.0);
    glVertex3f(50.0, -50.0, 50.0);
    glTexCoord2d(1.0,1.0);
    glVertex3f(50.0, -50.0, -50.0);
    glTexCoord2d(0.0,1.0);
    glVertex3f(50.0, 50.0, -50.0);
    glEnd();
    glPopMatrix();


    
}



//Desenha uma esfera
void DesenhaEsfera(float raio, double lat, double longe)
{
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // tentando evitar "marcas" na esfera.
    //glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // tentando evitar "marcas" na esfera.
    glEnable(GL_TEXTURE_2D);
    if(refTempo >= 250){
        glBindTexture( GL_TEXTURE_2D, ceumanha);
    }else{
        glBindTexture( GL_TEXTURE_2D, ceunoite);
    }
    

    GLUquadricObj *sphere=NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    gluSphere(sphere, raio, lat, longe);
    glEndList();
    //glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // tentando evitar "marcas" na esfera.

}



void display(void)
{
    switch(inicia)
    {
    case 0:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela
        glLoadIdentity();// Carrega a identidade

        glEnable(GL_TEXTURE_2D); // Ativa a aplica��o de textura.
        glBindTexture( GL_TEXTURE_2D, menu);// Define qual textura queremos aplicar.

        glPushMatrix(); //
        gluLookAt(-60,0,750,-60,0,0,0,1,0); // (vis�o do personagem)
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);// Carrega nossa textura 1000 x 1600.
        glTexCoord2d(0.0,0.0);
        glVertex3f(-800.0,-800.0,0.0);
        glTexCoord2d(1.0,0.0);
        glVertex3f(-800.0,800.0,0.0);
        glTexCoord2d(1.0,1.0);
        glVertex3f(800.0,800.0,0.0);
        glTexCoord2d(0.0,1.0);
        glVertex3f(800.0,-800.0,0.0);

        glEnd();
        glutSwapBuffers();
        glFlush();
        break;

    case 1:
        
        if(refTempo == 0){
        exit(0);
        }else
        refTempo = refTempo - 1;
        printf("%d\n", refTempo);
        int x, z;
        int x_mun, z_mun;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela

        glLoadIdentity();// Carrega a identidade

        gluLookAt(jog_x,25,jog_z, jog_x+mov_x,25,jog_z+mov_z, 0,1,0); // (vis�o do personagem)
        // Coordenadas X e Y que a camera t� ap�s se mover.
        LookX = (int) (jog_x+mov_x);
        LookZ = (int) (jog_z+mov_z);
        //printf's permitem ver tais coordenadas, para posteriormente aplicar textura:
        printf("X = %d\n", LookX);
        printf("Z = %d\n", LookZ);


        //DesenhaEsfera(10000.0);
        glPushMatrix(); //
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, chao);
        //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_verde);


        //glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin ( GL_QUADS);

        glTexCoord2d(0.0,0.0);
        glVertex3f(-10000, -50, -10000);

        glTexCoord2d(50.0,0.0);
        glVertex3f(-10000, -50, 10000);

        glTexCoord2d(50.0,50.0);
        glVertex3f(10000, -50, 10000);

        glTexCoord2d(0.0,50.0);
        glVertex3f(10000, -50, -10000);

        glEnd();

        glPopMatrix();

        // Textura - WIN:
        if(((LookX>=2100) && (LookX<=2130)) && ((LookZ >= 2450)&&(LookZ<=2480)))
        {


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela
            glLoadIdentity();// Carrega a identidade

            glEnable(GL_TEXTURE_2D); // Ativa a aplica��o de textura.
            glBindTexture( GL_TEXTURE_2D, win);// Define qual textura queremos aplicar.

            glPushMatrix(); //
            gluLookAt(-60,0,750,-60,0,0,0,1,0); // (vis�o do personagem)
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);// Carrega nossa textura 1000 x 1600.
            glTexCoord2d(0.0,0.0);
            glVertex3f(-800.0,-800.0,0.0);
            glTexCoord2d(1.0,0.0);
            glVertex3f(-800.0,800.0,0.0);
            glTexCoord2d(1.0,1.0);
            glVertex3f(800.0,800.0,0.0);
            glTexCoord2d(0.0,1.0);
            glVertex3f(800.0,-800.0,0.0);

            glEnd();

            glutSwapBuffers();
            glFlush();
            break;
        }
        



        glDisable( GL_TEXTURE_2D );

        for(x=0; x < 26; x++)
        {
            for(z=0; z < 26; z++)
            {
                if(mapa[x][z]) //Verifica se h� bloco:
                {
                    x_mun = x * TAM_BLOCO;
                    z_mun = z * TAM_BLOCO;

                    //cubo grande
                    glPushMatrix();

                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, luz_branca);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, matriz_especular);
                    glMaterialfv(GL_FRONT, GL_SHININESS, matriz_intensidade_brilho);

                    glTranslatef(x_mun, 5,z_mun);


                    int casa = mapa[x][z];

                    
                    if(casa==5) // Desenha o "ceu" no meio da matriz.
                    {
                       DesenhaEsfera(2850.0,3,3);

                    }

                    else
                    {
                        if(wire) glutWireCube(TAM_BLOCO);
                        else desenhaCubo(); // Desenha as "paredes" do labirinto.
                    }

                    glPopMatrix();


                }
            }//for
        }//for

    

        glutSwapBuffers();
        break;
    case 2:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela
        glLoadIdentity();// Carrega a identidade

        glEnable(GL_TEXTURE_2D); // Ativa a aplica��o de textura.
        glBindTexture( GL_TEXTURE_2D, menu2);// Define qual textura queremos aplicar.

        glPushMatrix(); //
        gluLookAt(-60,0,750,-60,0,0,0,1,0); // (vis�o do personagem)
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);// Carrega nossa textura 1000 x 1600.
        glTexCoord2d(0.0,0.0);
        glVertex3f(-797.0,-797.0,0.0);
        glTexCoord2d(1.0,0.0);
        glVertex3f(-797.0,797.0,0.0);
        glTexCoord2d(1.0,1.0);
        glVertex3f(797.0,797.0,0.0);
        glTexCoord2d(0.0,1.0);
        glVertex3f(797.0,-797.0,0.0);

        glEnd();
        glutSwapBuffers();
        glFlush();
        break;


    }
}



void Inicializa(void){

    

glShadeModel(GL_SMOOTH); //especifica a técnica de colorização

glClearColor(0.9, 0.6, 0.2, 1.0);

// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, matriz_especular);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,valor_especular_material);

glLightfv(GL_LIGHT0, GL_POSITION, posicao_fonte_de_luz);
glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_branca);
glLightfv(GL_LIGHT0, GL_SPECULAR, luz_branca);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


glEnable(GL_LIGHTING); //liga a iluminação
glEnable(GL_LIGHT0);

//Especifica sistema de coordenadas de projecao
    glMatrixMode(GL_PROJECTION);

// Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

//Especifica a projecao perspectiva
    gluPerspective(90,1,0.1,3000); //primeiro parâmetro = angulo de visao em graus em y
                                   //segundo parametro = a proporção que determina o campo de visão na direção x
                                   //terceiro parametro = distancia do visualizador até o proximo clipping plane
                                   //quarto parametro =  distancia do visualizador até o clipping plane distante

//Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

// Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST); // teste de profundidade



}
GLuint CarregarTextura( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

//The following code will read in our RAW file
    file = fopen( filename, "rb" );  //We need to open our file
    if ( file == NULL ) return 0;  //If our file is empty, set our texture to empty


    data = (unsigned char *)malloc( width * height * 3 ); //assign the necessary memory for the texture


    fread( data, width * height * 3, 1, file );  //read in our file
    fclose( file ); //close our file, no point leaving it open

    glGenTextures( 1, &texture ); //then we need to tell OpenGL that we are generating a texture
    glBindTexture( GL_TEXTURE_2D, texture ); //now we bind the texture that we are working with
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data ); //free the texture
    return texture; //return the texture data
}

void Teclado (unsigned char chave, int x, int y){

    switch (chave){

        case  27:
        exit(0);
        break; //ESC -> encerra aplicativo...

    case 'w':
    case 'W':
        wire =!wire;
        glutPostRedisplay();
        break;

    case 'h':
    case 'H':
        inicia=2;
        glutPostRedisplay();
        break;

    case 32:
        inicia=1;
        glutPostRedisplay();
        break;

    }

    }

    int pode_mover(float pos_x, float pos_z, float vet_x, float vet_z)
{
    float mundo_x = pos_x + vet_x ;
    float mundo_z = pos_z + vet_z ;

    int ind_x = (int) ((mundo_x + TAM_BLOCO/2) / TAM_BLOCO);
    int ind_z = (int) ((mundo_z + TAM_BLOCO/2) / TAM_BLOCO);

    int casa = mapa[ind_x][ind_z];

    if(casa == 3 || casa==2|| casa==5|| casa==4)
    {
        return 1;
    }
    else if(casa)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
   

    void Special_Function(int chave, int x, int y)
{
    float rad;

    switch (chave)
    {
    case GLUT_KEY_DOWN:

        if(pode_mover(jog_x, jog_z, - mov_x, -mov_z))
        {
            jog_x -= mov_x;
            jog_z -= mov_z;
        }
        break;


    case GLUT_KEY_UP:

        if(pode_mover(jog_x, jog_z,  mov_x, mov_z))
        {
            jog_x += mov_x;
            jog_z += mov_z;
        }
        break;

    case GLUT_KEY_LEFT:

        angulo -= 10;

        if(angulo < 0) angulo +=360;


        rad =  (float) (3.14159 * angulo / 180.0f);

        mov_x =  cos(rad) * PASSO;
        mov_z =  sin(rad) * PASSO;
        break;


    case GLUT_KEY_RIGHT:

        angulo += 10;

        if(angulo >= 360) angulo -=360;

        rad =  (float) (3.14159 * angulo / 180.0f);

        mov_x = cos(rad) * PASSO;
        mov_z = sin(rad) * PASSO;

        break;

    }//fim do switch

}

// Clean up
void FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );  //Delete our texture, simple enough.
}
//---------------------------------------------------------------
void free_mem(void)
{
    std::clog << "Exiting...\n";
}

void Move(void)
{
    glutPostRedisplay();
}

//---------------------------------------------------------------
int main(int argc, char **argv)
{
	std::clog << "Begin...\n";

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Labirinto Projeto");
    glutFullScreen();
    chao = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/areia.bmp", 1600, 1600); // Carrega primeira textura (Ch�o).
    parede = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/papel_parede.bmp", 1000, 708);// Carrrega segunda textura (Parede).
    portal = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/portal.bmp", 2560, 1920); // Carrega terceira textura (Porta)
    ceumanha = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/ceu.bmp", 8000, 2000); // Carrega terceira textura (Porta)
    menu = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/menu1espelhado.bmp", 1280, 799); // Carrega terceira textura (Porta)
    ceunoite = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/ceu3.bmp", 6000, 5000);
    menu2 = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/menu2.bmp", 1278, 797); // Carrega terceira textura (Porta)
    win = CarregarTextura( "/home/augusto/Downloads/opengl_hello_world/obj/winCerto.bmp", 1278, 797);
    
    if(chao==0 || parede == 0)
    {
        printf("Erro ao carregar Imagem\n");
    }
    else
    {
        printf("Carregaram todas as imagens! \n");
    }

	
    Inicializa();
    glutDisplayFunc(display);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(Special_Function);
    glutIdleFunc(Move);
   


	glutMainLoop();

	return 0;
}
