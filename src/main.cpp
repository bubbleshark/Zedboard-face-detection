#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "haar.h"
#include "image.h"

using namespace std;

void read_ppm(char *name,unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH])
{
	FILE *p;
	int ch;
	int version=0;
	int width=0;
	int height=0;
	int maxgrey=0;
	int i,k;
	int count=0;
	int header_enter=0;
	int header_space=0;
	int header_sharp=0;
	p=fopen(name,"rb");
	if(p==NULL)
	{
		printf("open file error\n");
		exit(1);
	}
	ch=fgetc(p);
	if(ch!='P')
	{
		printf("not ppm file\n");
		exit(1);
	}
	ch=fgetc(p);
	version=ch-'0';
	while(ch=fgetc(p))
	{
		if(ch=='#')
		{
			while(ch=fgetc(p))
			{
				if(ch=='#')
				{
					ch=fgetc(p);
					break;
				}
			}
			continue;
		}
		if(ch==' ')
		{
			header_space++;
			continue;
		}
		if(ch==10)
		{
			header_enter++;
			if(header_enter==3)
			{
				break;
			}
			continue;
		}
		if(header_space==0)
		{
			width*=10;
			width+=ch-'0';
		}
		else if(header_space==1 && header_enter==1)
		{
			height*=10;
			height+=ch-'0';
		}
		else if(header_space==1 && header_enter==2)
		{
			maxgrey*=10;
			maxgrey+=ch-'0';
		}
		else
		{
			printf("error parsing\n");
			exit(1);
		}
	}
	printf("width: %d height: %d maxgrey: %d\n",width,height,maxgrey);
	if(width!=IMAGE_WIDTH || height!=IMAGE_HEIGHT)
	{
		printf("not support current image size\n");
		exit(1);
	}
	i=0;
	k=0;
	while((ch=fgetc(p))!=EOF)
	{
		Data[i][k]=ch%256;//important with mod
		k++;
		if(k==width)
		{
			i++;
			k=0;
		}
	}
	printf("fclose\n");
	fclose(p);
}

int main ( int argc, char *argv[] ) 
{

	int flag;
	int in_flag , in_width , in_height , in_maxgrey;
	unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH];
	int ret_val=1;
	int k;
	double sec=0;
	char str[100];
	char str2[100];
	if(argc!=2)
	{
		printf("input error\n");
		printf("please input ppm file name\n");
		return 1;
	}
	/*
	read_ppm(argv[1],Data);*/
	//for(k=1;k<=576;k++)
	{
	//sprintf(str,"img%04d.png.pgm",k);
	//printf("read %s\n",str);
	read_ppm(argv[1],Data);
	//printf ("-- entering main function --\r\n");
	//printf ("-- loading image --\r\n");

	double duration=0;

	// Arguments to be passed to DUT
	MyRect result[RESULT_SIZE];
	int result_x[RESULT_SIZE];
	int result_y[RESULT_SIZE];
	int result_w[RESULT_SIZE];
	int result_h[RESULT_SIZE];

	int res_size=0;
	int *result_size = &res_size;
	int i;

	// As the SDSoC generated data motion network does not support sending 320 X 240 images at once
	// We needed to send all the 240 rows using 240 iterations. The last invokation of detectFaces() does the actual face detection

	for ( i = 0; i < IMAGE_HEIGHT-1; i+=1 )
	{
		detectFaces ( Data[i], result_x, result_y, result_w, result_h, result_size);
	}

	//printf ("-- detecting faces --\r\n");

	std::clock_t start = std::clock();
	detectFaces ( Data[IMAGE_HEIGHT-1], result_x, result_y, result_w, result_h, result_size);
	duration = ( std::clock() - start ) ;

	//printf("\nresult_size = %d", *result_size);

	for (int j = 0; j < RESULT_SIZE; j++)
	{
		result[j].x = result_x[j];
		result[j].y = result_y[j];
		result[j].width = result_w[j];
		result[j].height = result_h[j];
	}

	for( int i=0 ; i < *result_size ; i++ )
		printf("\n [Test Bench (main) ] detected rects: %d %d %d %d",result[i].x,result[i].y,result[i].width,result[i].height);
 
	if ( *result_size > 0 )
		ret_val = 0;

	//printf("\n-- saving output image [Start] --\r\n");

	// Draw the rectangles onto the images and save the outputs.
	for(i = 0; i < *result_size ; i++ )
	{
		MyRect r = result[i];
		drawRectangle(Data, r);
	}
	sprintf(str2,"out_%s",argv[1]);
	flag = writePgm(str2,Data);
	sec+=duration;
	}
	//printf("\n-- saving output image [Done] --\r\n");
	printf("DURATION: %2f", sec / (double) CLOCKS_PER_SEC);
	
	return ret_val;

}
