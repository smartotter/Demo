#include "graphics.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#define POINTNUMBER 428
#define COLOR LIGHTBLUE
#define DELTA 0.008
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
 char s[10],tmp;
 int i=0,j=0,k=0,tag,color;
/****************************************************************/
initgraph(&drive,&mode,"");

if((p=fopen("data.txt","r"))==NULL)
 {
  printf("ERROR");
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
{  setcolor(COLOR);
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
 setcolor(COLOR);
 for(i=0;i<POINTNUMBER;i++)
           {
       if(sin(a[i].theta)>0)
	moveto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
       else{
	if(a[i].nextvisible==0)/*||sin(a[i].theta)<0)*/
                    moveto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
                else
		    {  if(i<77) setcolor(RED);
		       else setcolor(COLOR);
		       lineto(R*cos(a[i].alpha)*cos(a[i].theta)+320,R*sin(a[i].alpha)+240);
		    }
		}      a[i].theta+=DELTA;

       }



moveto(R*cos(a[0].alpha)*cos(a[0].theta-3*DELTA)+320,R*sin(a[0].alpha)+240);
      setcolor(BLACK);
      for(i=0;i<POINTNUMBER;i++)
           {
		   if(a[i].nextvisible==0)/*||sin(a[i].theta)<0)*/
		       moveto(R*cos(a[i].alpha)*cos(a[i].theta-3*DELTA)+320,R*sin(a[i].alpha)+240);
	else

                  {
			 lineto(R*cos(a[i].alpha)*cos(a[i].theta-3*DELTA)+320,R*sin(a[i].alpha)+240);
		  }
}





}
 closegraph();

}









