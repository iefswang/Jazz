/*****************************************************
 *@File:	test.c
 *@Created:	Wed 06 Jul 2011 02:11:47 PM CST
 *@Author:	muryo
 *@Description:
 *@
*******************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <linux/input.h>
#include    <linux/uinput.h>
#include    <sys/time.h>
#include    <unistd.h>
#include    <stdlib.h>

int main(int argc, char *argv[])
{

    int fd_kbd;
    if(argc != 2)
    {
//	printf("usage: ./test_event  /dev/eventx (x:0-2)");
	printf("usage: ./test_event  /dev/eventx (x:0-2)");
	return -1;
    }
    fd_kbd = open(argv[1], O_RDWR);
    if(fd_kbd < 0)
    {
	perror("open error");
	return -2;
    }

    struct input_event event;
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    while(1)
    {
    read(fd_kbd,  &event, sizeof(event));
    if(event.code == KEY_LEFT && event.value == 0)
    {
	printf("KEY_LEFT\n");
    }
    else if(event.code == KEY_RIGHT && event.value ==0)
    {
	printf("KEY_RIGHT\n");
    }
    else if(event.code == KEY_UP && event.value == 0)
    {
	printf("KEY_UP\n");
    }
    else if(event.code == KEY_DOWN && event.value == 0)
    {
	printf("KEY_DOWN\n");
	printf("you have pressed KEY_DOWN,exit\n");
	return 0;
	
    }
    else if(event.code == KEY_SELECT && event.value == 0)
    {
	printf("KEY_SELECT\n");
    }

    }
}
