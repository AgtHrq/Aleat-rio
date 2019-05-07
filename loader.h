#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>


GLuint loader( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

//The following code will read in our RAW file
    file = fopen( filename, "rb" );  //We need to open our file
    if ( file == NULL ) return 0;  //If our file is empty, set our texture to empty


    data = (unsigned char *)malloc( width * height * 3 ); //assign the nessecary memory for the texture


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

