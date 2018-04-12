#ifndef _LAB_TEXTURE_H
#define _LAB_TEXTURE_H

#include "common.h"
#include <rglImage/rglImagelib.h>

// texture filter type
#define txNoFilter 0
#define txBilinear 1
#define txTrilinear 3
#define txAnisotropic_02 2
#define txAnisotropic_04 4
#define txAnisotropic_08 8
#define txAnisotropic_16 16
// texture compressed type
#define txNoCompressed 0
#define txS3TC_DXT1 1
#define txS3TC_DXT3 2
#define txS3TC_DXT5 3
#define txGL_COMPRESS 4

int rglLoadTextures(char *filename,GLuint *texti);

//GLboolean rglLoad_Texture_SDL(char *filename, GLuint *texti, GLuint txFilter, GLuint txMode, GLuint txPlace, GLuint txCompress, GLboolean txMip_map);
//Filename - имя файла
//texti - opengl текстура
//txFilter - фильтрация (txNoFilter, txBilinear, txTrilinear, txAnisotropic_02, txAnisotropic_04, txAnisotropic_08, txAnisotropic_16)
//txMode режим наложения (GL_REPLACE, GL_BLEND,  GL_DECAL,  GL_MODULATE)
//txPlace способ наложения (GL_REPEAT,GL_CLAMP_TO_EDGE, GL_CLAMP)
//txCompress - способ сжатия текстур (txNoCompressed, txS3TC_DXT1, txS3TC_DXT3, txS3TC_DXT5, txGL_COMPRESS )
//txMip_map - мипмапинг включение и выключение (GL_TRUE, GL_FALSE)

//GLboolean rglCreateTexture(GLint tx_iner_format, GLint tx_width, GLint tx_heght, GLuint *texti, GLuint txFilter, GLuint txMode, GLuint txPlace, GLuint txCompress, GLboolean txMip_map);
//tx_iner_format - GL_RGB, GL_RGBA
//tx_width, tx_heght - размеры текстуры


//int rglLoadTextureEx(char *filename, GLuint *texti, GLuint txFilter, GLuint txMode, GLuint txPlace, GLuint txCompress, GLboolean txMip_map);


#endif
