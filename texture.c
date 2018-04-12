#include "texture.h"




/////////////////////////////////////////////////////////////////////////////////////////////////
//										TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////
int rglLoadTextures(char *filename,GLuint *texti)
{   
	rgl_Image_t *image;
	int tex_format=GL_RGBA;

	image=(rgl_Image_t *) malloc(sizeof(rgl_Image_t));
	
	if(!filename)  return 1;
	if (rglLoadImage(filename,image)!=0) return 2;

	if (image->imgType==RGL_RGB) tex_format=GL_RGB; 
	if (image->imgType==RGL_BGR) tex_format=GL_RGB; 
	if (image->imgType==RGL_BGRA) tex_format=GL_RGBA;
	
	glGenTextures(1, texti);  
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, *texti);   
	//printf("Test01\n"); 	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	//printf("Test02\n"); 	
	glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP, GL_TRUE);
	//printf("Test03 %i \t %i\n", image->width, image->height); 
	//printf("Test04 %i \t %i\n", tex_format, image->imgType); 
	glTexImage2D(GL_TEXTURE_2D, 0, tex_format,  image->width, image->height, 0,  image->imgType, GL_UNSIGNED_BYTE, image->data);
	//printf("Test04\n"); 
	free(image->data); 
	free(image); 
	printf("Load texture  from %s \t - OK \n", filename);
  	return 0;
}
/*
int rglLoadTextureEx(char *filename, GLuint *texti, GLuint txFilter, GLuint txMode, GLuint txPlace, GLuint txCompress, GLboolean txMip_map)
{   
    rgl_Image_t *image;
	int tex_format=GL_RGBA;
	
	GLfloat anis_level;
    GLint filter_tx;
    GLfloat compress_size;
    filter_tx= txFilter;

	image=(rgl_Image_t *) malloc(sizeof(rgl_Image_t));
	
	if(!filename)  return 1;
	if (rglLoadImage(filename,image)!=0) return 2;

	if (image->imgType==RGL_RGB) tex_format=GL_RGB; 
	if (image->imgType==RGL_BGR) tex_format=GL_BGR; 
	if (image->imgType==RGL_BGRA) tex_format=GL_BGRA;
	


	if (txCompress>0)
	{
		  switch (txCompress  )
		{	
			case  txS3TC_DXT1:
				if (image->imgBpp <= 24) tex_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
				if (image->imgBpp == 32) tex_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
			case txS3TC_DXT3:
				if (image->imgBpp <= 24) tex_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				if (image->imgBpp == 32) tex_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
			case txS3TC_DXT5:
				if (image->imgBpp <= 24) tex_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				if (image->imgBpp == 32) tex_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
			case txGL_COMPRESS:
				if (image->imgBpp <= 24) tex_format = GL_COMPRESSED_RGB;
				if (image->imgBpp == 32) tex_format = GL_COMPRESSED_RGBA;
			break;
			default:
				if (image->imgBpp <= 24) tex_format = GL_COMPRESSED_RGB;
				if (image->imgBpp == 32) tex_format = GL_COMPRESSED_RGBA;
			break;
		}
	}
      
	 glGenTextures(1, texti);  
   	 glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	 glBindTexture(GL_TEXTURE_2D, *texti);  
	  
	  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anis_level);	
	
	  if (anis_level < 2.0)
	  { 
	  	filter_tx = txTrilinear;
  		}
	  if  (( filter_tx == txAnisotropic_02) || ( filter_tx == txAnisotropic_04) || ( filter_tx == txAnisotropic_08) || ( filter_tx == txAnisotropic_16)) 
	  		if ( filter_tx >  anis_level )
	  			 filter_tx=  anis_level;
	  if (txMip_map == GL_FALSE) 
		   switch (   filter_tx )
				{	
				case txTrilinear:
					  filter_tx=txBilinear;
				break;
				case txAnisotropic_02:
					  filter_tx=txBilinear;
				break;
				case txAnisotropic_04:
					  filter_tx=txBilinear;
				break;
				case txAnisotropic_08:
					  filter_tx=txBilinear;
				break;
				case txAnisotropic_16:
					 filter_tx=txBilinear;
				break;
				}
			
	  switch (   filter_tx  )
		{	
		case  txNoFilter:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
		case txBilinear:
				if  (txMip_map == GL_TRUE) 
					{
						glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
					}
				else
					{
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					}				
		break;
		case txTrilinear:
		  	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
		case txAnisotropic_02:
		 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0);
		break;
		case txAnisotropic_04:
		 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
		break;
		case txAnisotropic_08:
		 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0);
		break;
		case txAnisotropic_16:
		 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0);
		break;		
		default:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
		}
	
	    switch ( txMode  )
		{	
			case  GL_REPLACE:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			break;
			case GL_BLEND:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
			break;
			case GL_DECAL:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			break;
			case GL_MODULATE:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
			break;
			default:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			break;
		}
	  
	   switch ( txPlace  )
		{	
			case   GL_REPEAT:
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;	
			break;
			case GL_CLAMP_TO_EDGE:
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) ;	
			break;
			case GL_CLAMP:
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	    		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP) ;
			break;			
			default:
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;
			break;
		}
	
	     if (txMip_map == GL_TRUE) 
	     {
	     	glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP, GL_TRUE);
	    // 		gluBuild2DMipmaps ( GL_TEXTURE_2D, tex_format,  image->width, image->height,  color_type_pixels, GL_UNSIGNED_BYTE,   image->data );
			glTexImage2D(GL_TEXTURE_2D, 0, tex_format,  image->width, image->height, 0,  image->imgType, GL_UNSIGNED_BYTE, image->data);
		}
		else
			glTexImage2D(GL_TEXTURE_2D, 0, tex_format,  image->width, image->height, 0,  image->imgType, GL_UNSIGNED_BYTE, image->data);
		
		glGetTexLevelParameterfv(GL_TEXTURE_2D, 0,GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);
		
		if (compress_size <=1024 )
		{
			printf("Texture compressed size %8.2f  byte \n", compress_size );
			printf("Image size %d  byte \n", image->width*image->height*image->imgBpp/8 );
		}
		else
		{
			printf("Texture compressed size %8.2f  Kb \n", compress_size/1024 );
			printf("Image size %d  Kb \n", image->width*image->height*image->imgBpp/8192 );
		}
		printf("Texture load OK!!! \n" );
		free(image->data); 
		free(image); 
  	return 0;
}
*/
