#ifndef _LAB_COMMON_H
#define _LAB_COMMON_H
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#define GLEW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <rglImage/rglImagelib.h>
#include <rglMath/rglMath3D.h>
#include <bass/bass.h>


typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void			GLvoid;
typedef signed char		GLbyte;		/* 1-byte signed */
typedef short			GLshort;	/* 2-byte signed */
typedef int				GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int				GLsizei;	/* 4-byte signed */
typedef float			GLfloat;	/* single precision float */
typedef float			GLclampf;	/* single precision float in [0,1] */
typedef double			GLdouble;	/* double precision float */
typedef double			GLclampd;	/* double precision float in [0,1] */

#endif
