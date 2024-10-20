#include "graphics.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#define POINTNUMBER 383
#define COLOR GREEN
#define DELTA 0.012
#define R 150
main()
{
 struct point
  {
   int nextvisible;
   float alpha;
   float theta;
  };

 struct point a[500];
 int drive=DETECT,mode;
 FILE *p;
 char s[10],tmp,input[3];
 int x,y,i=0,j=0,k=0,tag,color;
/****************************************************************/
printf("This program demostrate a circling earth.\nPress any key...\n");

getch();
printf("  SELECT A COLOR:\n");
printf("\n\n1 : BLUE\n2 : GREEN\n3 : CYAN\n4 : RED\n5 : MAGENTA\n6 : LIGHTGRAY\n7 : BROWN\n");
printf("8 : DARKGRAY\n9 : LIGHTBLUE\n10: LIGHTGREEN\n11: LIGHTCYAN\n12: LIGHTRED\n13: LIGHTMAGENTA\n14: YELLOW\n15: WHITE\n");


do
{
  gets(input);
  color=atoi(input);

}
while(!(color>0&&color<16));




initgraph(&drive,&mode,"");


if((p=fopen("data.txt","r"))==NULL)
 {
  printf("ERROSFR");
  exit(1);
 }
while(!feof(p))
{
 tmp=fgetc(p);
 if(tmp=='\n')
 tmp=fgetc(p);

 if(tmp=='*')
  {
    for(;tmp!='*';tmp=fgetc(p));
    tmp=fgetc(p);
  }

 if(tmp==' ')
 {
  k++;



  switch(k)
   {
   case 1: a[j].nextvisible=atoi(s);break;
   case 2: a[j].alpha=-2*atof(s)*0.0087266464;break;
   case 3: a[j].theta=2*atof(s)*0.0087266464;break;
   }
  i=0;
  if(k==3)
  {
   j++;
   k=0;
  }
for(tag=0;tag<10;tag++)
s[tag]='\0';
}

 s[i]=tmp;
 i++;
}
fclose(p);
/*****************************************************************
	  DATA READY!
*****************************************************************/

/*for(i=0;i<5;i++)
 printf("%f ,%f ,%f\n",a[i].r,a[i].alpha,a[i].theta);*/

/******************************************************************************************/
{
   setcolor(color);
   randomize();
   for(i=0;i<1000;i++)
   {
     x=rand()/40;
     y=rand()/30;

     putpixel(x,y,i/100);
   }
   circle(320,240,R+2);
   setfillstyle(1,BLACK);
   floodfill(320,240,color);
   setcolor(YELLOW);
   arc(500,20,-90,90,20);
   arc(454,20,-24,25,50);
   setfillstyle(1,YELLOW);
   floodfill(515,20,YELLOW);




   setcolor(color);
   circle(320,240,R+2);
  moveto(R*cos(a[0].alpha)*cos(a[0].theta)+320,R*sin(a[0].alpha)+240);
      for(i=0;i<POINTNUMBER;i++)
	{
	 if(a[i].nextvisible==0)
                    moveto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
                 else
                 {
                  setcolor(COLOR);
	  lineto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
	}
     }
}
while(!kbhit())
{

 moveto(R*cos(a[0].alpha)*cos(a[0].theta)+320,R*sin(a[0].alpha)+240);
 setcolor(color);
 for(i=0;i<POINTNUMBER;i++)
           {
       if(sin(a[i].theta)>0)
	moveto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
       else{
	if(a[i].nextvisible==0)/*||sin(a[i].theta)<0)*/
                    moveto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
                else
                    {
		       lineto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
	    }
		}      a[i].theta+=DELTA;

       }


   delay(10);
moveto(R*cos(a[0].alpha)*cos(a[0].theta-2*DELTA)+320,R*sin(a[0].alpha)+240);
      setcolor(BLACK);
      for(i=0;i<POINTNUMBER;i++)
           {
		   if(a[i].nextvisible==0)/*||sin(a[i].theta)<0)*/
		       moveto(R*cos(a[i].alpha)*cos(a[i].theta-2*DELTA)+320,R*sin(a[i].alpha)+240);
	else

                  {
			 lineto(R*cos(a[i].alpha)*cos(a[i].theta-2*DELTA)+320,R*sin(a[i].alpha)+240);
                  }
}





}

 printf("Press R to restart, Else to Quit.\n");
 getch();
 tmp=getch();
 if(tmp=='r'||tmp=='R')
 {
  closegraph();
  main();
 }
 closegraph();

}









