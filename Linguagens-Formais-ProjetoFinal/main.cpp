#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>


//DEFINIÇÕES--------------------------------------------

#define TAM_BLOCO 100
#define PASSO	10

//GLOBAIS--------------------------------------------

// TEXTURAS----------------------------------
GLuint chao;
GLuint parede;
GLuint porta;
GLuint ceutarde;
GLuint ceumanha;
GLuint menu;
GLuint ceunoite;
GLuint ganhou;
GLuint perdeu;
//VARIAVEIS----------------------------------
GLfloat luz_amarela[] = {0.8,0.8,0.1,1.0};
GLfloat posicao_fonte_de_luz[] = { 0.0, 500.0, 0.0, 1.0 };
GLfloat luz_branca[] = {1.0,1.0,1.0,1.0};
GLfloat luz_ambiente[] = {0.8, 0.8, 0.8, 0.8};
GLfloat matriz_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat matriz_intensidade_brilho[] = { 50.0 };
GLfloat lmodel_ambient[] = {0.6,0.6,0.6,1.0};
GLint valor_especular_material = 60;
GLfloat jog_x= 713, jog_z= 101 ;
GLfloat mov_x=PASSO, mov_z=0;
GLint angulo=0;
GLint inicia = 0;
GLint refTempo = 8000;
GLint LookX = 0;
GLint LookZ = 0;


//MATRIZ UTILIZADA COMO MAPA(1 = PAREDE, 9 = ESFERA CEU, 0 = NADA)---------------------------------------------------------------
// UTILIZADA PARA MODELAÇÃO DE PRIMITIVAS E TESTE DE COLISÃO POR RELAÇÃO DE PROPORÇÃO


GLint mapa[26][26] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1, 
                       1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,
                       1,0,1,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
                       1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,
                       1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,
                       1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,
                       1,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,
                       1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1, 
                       1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,0,0,1,0,1,0,1,0,9,0,1,0,0,0,1,0,0,0,1,0,1,0,1,
                       1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,
                       1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1, 
                       1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,
                       1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,
                       1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,
                       1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
                       1,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,2,
                       1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,
                       1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                     };


//PRIMITIVA CUBO-----------------------------------------------------------
void desenhaCubo(){
    //TEXTURA
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, parede);

    //DESENHA O CUBO (SEM NECESSIDADE DE FACES EM CIMA E EMBAIXO)

    glBegin(GL_QUADS);			

    glNormal3f(0.0, 0.0, 1.0);	// NORMAL DA FACE POSTERIOR
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
    
    glBegin(GL_QUADS);			
    glRotatef(90.0f, 0.0f,0.0f,1.0f);
    glNormal3f(0.0, 0.0, -1.0); 	// NORMAL DA FACE FRONTAL
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


    glBegin(GL_QUADS);			

    glNormal3f(-1.0, 0.0, 0.0); 	// NORMAL DA FACE ESQUERDA
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
    glBegin(GL_QUADS);			

    glNormal3f(1.0, 0.0, 0.0);	// NORMAL DA FACE DIREITA
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

void desenhaPorta(){
    // TEXTURA DA PORTA
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, porta);

    //DESENHA UMA PORTA (MESMA COISA DO CUBO)
    //INTERCECSIONA O CHÃO EM Y = -50

    glBegin(GL_QUADS);			

    glNormal3f(0.0, 0.0, 1.0);	
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
    
    glBegin(GL_QUADS);			
    glRotatef(90.0f, 0.0f,0.0f,1.0f);
    glNormal3f(0.0, 0.0, -1.0); 	
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


    glBegin(GL_QUADS);			

    glNormal3f(-1.0, 0.0, 0.0); 	
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
    glBegin(GL_QUADS);			

    glNormal3f(1.0, 0.0, 0.0);	
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




void DesenhaEsfera(float raio, double lat, double longe)
{
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // MASCARANDO AS MARCAS NA ESFERA
    
    
    if(refTempo >= 6000){
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, ceumanha);
    }
    else if(refTempo >= 3000){
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, ceutarde);
    }else{
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, ceunoite);
    }
    

    GLUquadricObj *sphere=NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    gluSphere(sphere, raio, lat, longe);
    glEndList();


}

void MouseClick (int button, int state, int x, int y)
{

        switch (button)
    {
        case GLUT_LEFT_BUTTON: exit(0);
                               break;
    }
      
    
}



void display(void)
{
    

    switch(inicia)
    {
        
    case 0:// ESTÁ NO MENU
           
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//LIMPA TELA E BUFFERS
            glLoadIdentity();//IDENTIDADE
            
            //APLICA TEXTURA
            glEnable(GL_TEXTURE_2D); 
            glBindTexture( GL_TEXTURE_2D, menu);
            //TELA DE MENU
            glPushMatrix(); 
            gluLookAt(-60,0,750,-60,0,0,0,1,0); //VISÃO PERSONAGEM DA TELA DE MENU
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
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

    case 1: //JOGO COMEÇOU
    if(refTempo >= 6000){
        glClearColor(0.3, 0.6, 0.8, 0.0);
    }
    else if(refTempo >= 3000){
        
        glClearColor(1.0, 0.9, 0.8, 0.0);

    }else{
        glClearColor(0.0, 0.0, 0.0, 0.0);
    }
        
        if(refTempo == 0){
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//LIMPA TELA
            glLoadIdentity();// IDENTIDADE
            //APLICAÇÃO DA TEXTURA
            glEnable(GL_TEXTURE_2D); 
            glBindTexture( GL_TEXTURE_2D, perdeu);

            //GAME OVER TELA
            glPushMatrix(); 
            gluLookAt(-60,0,750,-60,0,0,0,1,0);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
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

        }else
        refTempo = refTempo - 1;
        printf("%d\n", refTempo);
        int x, z;
        int x_mun, z_mun;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//LIMPA TELA

        glLoadIdentity();//IDENTIDADE

        gluLookAt(jog_x,25,jog_z, jog_x+mov_x,25,jog_z+mov_z, 0,1,0); //VISÃO DO PERSONAGEM
        // CORDENADAS X E Z PÓS MOVIMENTAÇÃO
        LookX = (int) (jog_x+mov_x);
        LookZ = (int) (jog_z+mov_z);

        //PRINTS DE TELA PARA TESTES
        printf("X = %d\n", LookX);
        printf("Z = %d\n", LookZ);


        
        glPushMatrix(); 
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, chao);
        


        
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

        // GANHOU
        if(((LookX>=2100) && (LookX<=2130)) && ((LookZ >= 2450)&&(LookZ<=2480)))
        {


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// LIMPA TELA
            glLoadIdentity();

            glEnable(GL_TEXTURE_2D); //ATIVA A APLICAÇÃO DE TEXTURA
            glBindTexture( GL_TEXTURE_2D, ganhou);//APLICA A TEXTURA

            glPushMatrix(); 
            gluLookAt(-60,0,750,-60,0,0,0,1,0); //VISAO DO PERSONAGEM
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
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
        //CRIA O MUNDO
        for(x=0; x < 26; x++)
        {
            for(z=0; z < 26; z++)
            {
                if(mapa[x][z]) //VERIFICA SE HÁ BLOCO
                {
                    x_mun = x * TAM_BLOCO;
                    z_mun = z * TAM_BLOCO;

                    
                    glPushMatrix();

                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, luz_branca);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, matriz_especular);
                    glMaterialfv(GL_FRONT, GL_SHININESS, matriz_intensidade_brilho);

                    glTranslatef(x_mun, 5,z_mun);


                    int casa = mapa[x][z];

                    
                    if(casa==9) // CEU
                    {
                       DesenhaEsfera(2850.0,3,3);

                    }else if(casa==2){
                        desenhaPorta();
                    }else
                    {
                        desenhaCubo(); //PAREDES
                    }

                    glPopMatrix();

                }
            }
        }

    

        glutSwapBuffers();
        break;

    }
}




void Inicializa(void){

    

glShadeModel(GL_SMOOTH); //HABILITA O MODELO DE COLORIZAÇÃO DO GOURAUD, A COR RESULTANTE É INTERPOLADA NA FACE




    // DEFINE A REFLETÂNCIA DO MATERIAL
	glMaterialfv(GL_FRONT,GL_SPECULAR, matriz_especular);
	
    // DEFINE A CONCENTRAÇÃO DO BRILHO DO MATERIAL
	glMateriali(GL_FRONT,GL_SHININESS,valor_especular_material);
    
    //ATIVA A ILUMINAÇÃO AMBIENTE
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    //POSICIONA A FONTE DE LUZ
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_fonte_de_luz);
    
    //DEFINE OS PARAMETROS DA LUZ DE NÚMERO ZERO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_branca);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_branca);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lmodel_ambient);

    //HABILITA O USO DA ILUMINAÇÃO
    glEnable(GL_LIGHTING);
    //LIGA A LUZ DE NÚMERO ZERO
    glEnable(GL_LIGHT0);

//SISTEMA DE CORDENADAS DE PROJEÇÃO
    glMatrixMode(GL_PROJECTION);

// CARREGA A IDENTIDADE
    glLoadIdentity();

//PROJEÇÃO PERSPECTIVA
    gluPerspective(90,1,0.1,3000); //primeiro parâmetro = angulo de visao em graus em y
                                   //segundo parametro = a proporção que determina o campo de visão na direção x
                                   //terceiro parametro = distancia do visualizador até o proximo clipping plane
                                   //quarto parametro =  distancia do visualizador até o clipping plane distante

//SISTEMAS DE CORDENADAS DO MODELO
    glMatrixMode(GL_MODELVIEW);

// CARREGA A IDENTIDADE
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST); //TESTE DE PROFUNDIDADE



}
GLuint CarregarTextura( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //O CDG ABAIXO LE O ARQUIVO
    file = fopen( filename, "rb" );  //ABRE O ARQUIVO
    if ( file == NULL ) return 0;  //RETORNA 0 CASO VAZIO


    data = (unsigned char *)malloc( width * height * 3 ); //ALOCA A MEMÓRIA NECESSÁRIA PARA A TEXTURA


    fread( data, width * height * 3, 1, file );  //LÊ O ARQUIVO
    fclose( file ); //FECHA O ARQUIVO

    glGenTextures( 1, &texture ); //INFORMA AO OPENGL QUE ESTAMOS GENERANDO UMA TEXTURA
    glBindTexture( GL_TEXTURE_2D, texture ); //now we bind the texture that we are working with
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data ); //LIBERA A TEXTURA(DESALOCA)
    return texture; //RETORNA A TEXTURA
}

void Teclado (unsigned char chave, int x, int y){

    switch (chave){
    
    case 'c':
    case 'C':

    inicia = 1;
    glutPostRedisplay();
    break;

    case  27:

    exit(0);
    break; //SAI DO JOGO

    }

    }
        //COLISÃO
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
   

    void Special_Function(int chave, int x, int y) //CAPTURA DA INTERAÇÃO POR SETAS
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

    }// FIM SWITCH

}


void Move(void) // MOVE A CAMERA
{
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    // INICIAÇÃO DA TELA
	std::clog << "Begin...\n";

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Labirinto Projeto");
    glutFullScreen();

    //CARREGA TEXTURAS

    chao = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/areia.bmp", 1600, 1600);
    parede = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/papel_parede.bmp", 1000, 708);
    porta = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/porta.bmp", 900, 600); 
    ceutarde = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/ceu.bmp", 8000, 2000); 
    menu = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/menulabirinto.bmp", 615, 300); 
    ceunoite = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/ceunoite3.bmp", 3888, 2592);
    ganhou = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/ganhou.bmp", 4000, 2200);
    perdeu = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/perdeu.bmp", 480, 360);
    ceumanha = CarregarTextura( "/home/augusto/Downloads/ProjetoLabirinto/obj/ceumanha2.bmp", 300, 300);
    
    //NÃO CARREGOU/CARREGOU
    if(chao==0 || parede == 0 || porta == 0 || ceutarde == 0 || menu == 0 || ceunoite == 0 || ganhou == 0)
    {
        printf("Erro ao carregar Imagem\n");
    }
    else
    {
        printf("Carregaram todas as imagens! \n");
    }

    //ILUMINAÇÃO E TRANSFORMAÇÕES
	
    Inicializa();
    
    //CALLBACKS
    //DESENHO DAS PRIMITIVAS

    glutDisplayFunc(display);

    //INTERAÇÃO TECLADO
    glutKeyboardFunc(Teclado);

    //TRATAMENTO DAS SETAS
    glutSpecialFunc(Special_Function);

    //MOVE/NAO MOVE A CAMERA
    glutIdleFunc(Move);

    //INTERAÇÃO MOUSE
    glutMouseFunc(MouseClick);
    
   


	glutMainLoop();

	return 0;
}
