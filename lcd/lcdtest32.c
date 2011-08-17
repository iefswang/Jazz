#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
int main()
{
        FILE *fp;
        /*char *cmd1="echo 0 > /sys/class/backlight/stmp3xxx-bl/brightness";
        char *cmd2="echo 100 > /sys/class/backlight/stmp3xxx-bl/brightness";
	char *cmd3="echo 50 > /sys/class/backlight/stmp3xxx-bl/brightness";*/
	char *cmd1="echo 0 > /sys/class/backlight/mxs-bl/brightness";
        char *cmd2="echo 100 > /sys/class/backlight/mxs-bl/brightness";
	char *cmd3="echo 50 > /sys/class/backlight/mxs-bl/brightness";

        int fb;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
        long int screensize=0;
        long int location=0;
        //unsigned int x=0,y=0;
        __u32 x=0,y=0;
	char *fb_mem=0;
	unsigned int R=0,G=0,B=0;
	unsigned long t=0;
	printf("1.backlight test\n");
        if((fp=popen(cmd1,"r"))==NULL)
                perror("popen");
        sleep(2);
        if((fp=popen(cmd2,"r"))==NULL)
                perror("popen");
	sleep(2);
	if((fp=popen(cmd3,"r"))==NULL)
                perror("popen");
	sleep(2);

        fb=open("/dev/fb0",O_RDWR);
        if(fb<0)
        {
                printf("ERROR:can't open fb!\n");
        }
        //printf("The fb was opened!\n");

        if(ioctl(fb,FBIOGET_FSCREENINFO,&finfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }

        if(ioctl(fb,FBIOGET_VSCREENINFO,&vinfo))
        {
                printf("Error:reading var infp!\n");
                return -1;
        }


        //printf("xoffset:%d,yoffset:%d,line_length:%d\n",vinfo.xoffset,vinfo.yoffset,finfo.line_length );
        //printf("Bites_per_pixel=%d\n",vinfo.bits_per_pixel);
        //printf("xres:%d, yres:%d, line_length: %d\n",vinfo.xres,vinfo.yres, finfo.line_length );

        screensize=vinfo.xres*vinfo.yres*vinfo.bits_per_pixel/8;
	char *fbbuf=malloc(screensize*sizeof(unsigned char));
        //printf("screensize:%d\n",screensize);

        fb_mem=mmap(NULL,screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fb,0);

        if(fb_mem==(void*)-1)
        {
                printf("Can't mmap!\n");
                printf("Errno=%d!\n",errno);
                return -1;
        }
	memcpy(fbbuf,fb_mem,screensize);
        
	printf("2.dead pixel test\n");
	memset(fb_mem,0x00000000,screensize);
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }	
        sleep(2);
        memset(fb_mem,0xffffffff,screensize);
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);
	
	printf("3.color test\n");
	
	printf("black\n");
        for(x=0;x<vinfo.xres;x++)
        {
                for(y=0;y<vinfo.yres;y++)
                {
                        location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length;
                        *(fb_mem+location)=0x00;
			*(fb_mem+location+1)=0x00;
			*(fb_mem+location+2)=0x00;
			*(fb_mem+location+3)=0x00;
                }
        }
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);

	printf("white\n");
        for(x=0;x<vinfo.xres;x++)
        {
                for(y=0;y<vinfo.yres;y++)
                {
                        location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length;
                        *(fb_mem+location)=0xff;
			*(fb_mem+location+1)=0xff;
			*(fb_mem+location+2)=0xff;
			*(fb_mem+location+3)=0xff;
                }
        }
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);

	printf("red\n");	
        for(y=0;y<vinfo.yres;y++)
        {
                for(x=0;x<vinfo.xres;x++)
                {
                        location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length;
                        *(fb_mem+location)=0x00;
			*(fb_mem+location+1)=0x00;
			*(fb_mem+location+2)=0xff;
			*(fb_mem+location+3)=0x00;
                }
        }
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);
	
	printf("green\n");
        for(x=0;x<vinfo.xres;x++)
        {
                for(y=0;y<vinfo.yres;y++)
                {
                        location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length;
                       	*(fb_mem+location)=0x00;
			*(fb_mem+location+1)=0xff;
			*(fb_mem+location+2)=0x00;
			*(fb_mem+location+3)=0x00;			
                }
        }
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);

	printf("blue\n");
        for(y=0;y<vinfo.yres;y++)
        {
                for(x=0;x<vinfo.xres;x++)
                {
                        location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length;
                       
                        *(fb_mem+location)=0xff;
			*(fb_mem+location+1)=0x00;
			*(fb_mem+location+2)=0x00;
			*(fb_mem+location+3)=0x00;			
                }
        }
        if(ioctl(fb,FBIOPAN_DISPLAY,&vinfo))
        {
                printf("Error:reading fixed infp!\n");
                return -1;
        }
        sleep(2);
	memcpy(fb_mem,fbbuf,screensize);
        munmap(fb_mem,screensize);
        close(fb);
        //printf("framebuffer closed!\n");
	printf("LCDtest over!\n");
	free(fbbuf);
        pclose(fp);
        return 0;
}

