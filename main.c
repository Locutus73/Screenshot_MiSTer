/*
Copyright 2019 alanswx
with help from the MiSTer contributors including Grabulosaure 
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "memtool/fileaccess.h"
#include "lodepng.h"

#include "mister_scalar.h"

const char *version = "$VER:ScreenShot" VDATE;

#define BASEADDR 536870912 

unsigned char buffer[2048*3*1024];

void mister_scalar_free(mister_scalar *);


int main(int argc, char *argv[])
{
    char filename[4096];
    strcpy(filename,"MiSTer_screenshot.png");
    if (argc > 1) 
    {
        printf("output name: %s\n", argv[1]);
	strcpy(filename,argv[1]);
    }

    mister_scalar *ms=mister_scalar_init();
    if (ms==NULL)
    {
	    printf("some problem with the mister scalar, maybe this core doesn't support it\n");
	    exit(0);
    } 
    printf("\nScreenshot code by alanswx\n\n");
    printf("Version %s\n\n", version + 5);
   
    unsigned char *outputbuf = calloc(ms->width*ms->height*3,1);	
    mister_scalar_read(ms,outputbuf);
    unsigned error = lodepng_encode24_file(filename, outputbuf, ms->width, ms->height);
    if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
    free(outputbuf);
    mister_scalar_free(ms); 
    return 0;
}
