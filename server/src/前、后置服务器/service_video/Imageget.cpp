#include "Imageget.h"

CImageGet::CImageGet(CShmFIFO &fifo)
    :m_fifo(fifo)
{
	m_fifo.open(ftok(".", 3),sizeof(Image_t),300);
}
CImageGet::~CImageGet()
{
}
int CImageGet::run(void) 
{
	int outfd;
    char  name[20]="\n";
	Image_t * img=new Image_t;
  	 while(this->m_bRun)
    {
    m_fifo.read((char *)img);
    
    if(strcmp(img->img_name,name)!=0 && strcmp(img->img_name,"end")!=0)
    {
         printf("img:%s\n",img->img_name);
         if (outfd!=0)
         {
             close(outfd);
         }
         strcpy(name,img->img_name);
         outfd = open(img->img_name,O_RDWR | O_CREAT ,0644);
    }
    else if (strcmp(img->img_name,"end")==0)
    {
        delete this;
        return 0;
    }
    if(-1 == outfd){ perror("open");exit(1);}
    write(outfd,img->image,MAX_LEN);
    }
    return 0;
}
