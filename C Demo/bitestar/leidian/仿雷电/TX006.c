/*������ѵ2003    ����SZK8888     �������ڣ�03-10-28           */
/*����������ƶ�  ��Ҫ���ӵ����У���ֵ�ʱ��Խ�����ԽţB!     */

#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include "KEY.c"

#define PI 3.1415927

#define GAME_SPEED 200      /*��Ϸ�ٶ�*/

#define BULLET_SUM 50         /*�����ӵ�������*/

#define PLAYER_MOVE_SPEED 2   /*����ƶ��ٶ�*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void VGA_RESET();                            /*ͼ��ģʽ��ʼ��*/
void set_color(int color,int R,int G,int B); /*�ı��ɫ����ɫ*/

void TimeDelay(unsigned long microsec); /*��ʱ���� ����΢����*/

void MOVE_TO3(int oa,float *PX,float *PY,int D);  /*�ƶ���*/

void TRANSFORM(char filename[],int *NAME);        /*��TBFͼ���ļ���������*/

void GB_TBF(int x,int y,int *NAME);               /*��ʾTBFͼƬ����*/

int TimeDelayUnit(float t);  /*ʱ���ж��ж�*/

int Xrand(int A,int B);      /*�����������A��B*/

int ASK_a(int X1,int Y1,int X2,int Y2);   /*�õ����ĵ㵽Ŀ���ĽǶ�*/

double DZ(double X1,double Y1,double X2,double Y2);  /*�������*/

void DISPLAY_HP(int HP);             /*��ʾHP*/

void SOUND(int h,int t);             /* ��ʾ�� */

void GB_BULLET(int x,int y,int mode);   /*���ӵ�*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

main()
{

 int END=0; /*��Ϸ����*/

 int n,i,j; /*��ʱ�Ĳ���*/


 /*������ҽṹ*/
 struct player{
               int LIVE;

               int X1;
               int Y1;
               int X0;
               int Y0;

               int HP;

               int move;

               int LIFE;

              };

 struct player P; /*�������*/


 /*�����ӵ��ṹ*/
 struct BB{
           int RUN;               /*�Ƿ����� */
           float PX;              /*��ǰ����X*/
           float PY;              /*��ǰ����Y*/
           int oa;                /*Ŀ��Ƕ� */
           int LB;                /*�������� */
           int MAX_LB;
          };

 struct BB EB[BULLET_SUM];  /*��������ӵ�*/




 /*����TBFͼƬ����*/
 int PLANE[30][30];

 int BLAST[30][30];



 struct time t;   /*ϵͳʱ��*/
 int R;           /*�ɵ�ǰϵͳʱ��������������������*/


 int TimeM=0;     /*ʱ�� ��*/
 int TimeS=0;     /*ʱ�� ��*/
 char TM[3];
 char TS[3];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 VGA_RESET();             /*ͼ�γ�ʼ��*/

 InstallKeyboard();       /*�����жϳ�ʼ��*/

 gettime(&t);             /*ȡϵͳʱ��*/
 R=t.ti_hund;             /*R=����*/
 srand(R);                /*�������������������*/

 P.LIFE=3;                /*��ҵ���*/

 TRANSFORM("PLANE.TBF",&PLANE[0][0]);   /*����TBF��ʽͼƬ*/
 TRANSFORM("BZ2.TBF",&BLAST[0][0]);

/*+++++++++++++++++++++GAME ��ʼ+++++++++++++++++++++++++++++*/
 START:;
/*+++++++++++++++++++++��ʼ�����++++++++++++++++++++++++++++*/

P.X1=300;
P.Y1=240;
P.X0=P.X1;
P.Y0=P.Y1;
P.HP=100;
P.LIVE=1;
P.move=0;

 /*+++++++++++++++++++++��ʼ���ӵ�++++++++++++++++++++++++++++*/

 for(n=0;n<BULLET_SUM;n++)   /*�����ӵ���ʼ��*/
    {
     EB[n].RUN=0;
     EB[n].MAX_LB=4;
     EB[n].LB=EB[n].MAX_LB;
    }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 cleardevice();   /*����*/


 if(P.LIFE<=0)           /*���û���� GAME OVER ��Ϸ����*/
   {
    setcolor(4);
    settextstyle(0,0,4);
    outtextxy(164,190,"GAME OVER");


    setcolor(15);
    settextstyle(0,0,2);
    outtextxy(226,260,"TIME");


    setcolor(10);

    sprintf(TM,"%02d",TimeM);

    outtextxy(312,260,TM);

      outtextxy(342,260,":");

    sprintf(TS,"%02d",TimeS);

    outtextxy(357,260,TS);



    sleep(3); /*�ȴ�3��*/

    END=1;

    goto GAME_OVER;
   }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


GB_TBF(P.X1,P.Y1,&PLANE[0][0]);




 setcolor(15);
 settextstyle(0,0,2);
 outtextxy(60,10,"LIFE");

  for(n=130,i=0;i<P.LIFE;n+=24,i++)  /*���ƹ��м�����*/
     {
      GB_TBF(n,1,&PLANE[0][0]);
     }



 outtextxy(245,10,"HP");
 DISPLAY_HP(P.HP);



  outtextxy(420,10,"TIME");


  setcolor(10);

     sprintf(TM,"%02d",TimeM);

     outtextxy(506,10,TM);

         outtextxy(536,10,":");

     sprintf(TS,"%02d",TimeS);

     outtextxy(551,10,TS);




if(P.LIFE==3)
  {
   while(1)
   {
    setcolor(9);
    outtextxy(160,200,"PRESS ENTER TO START");

   if(GetKey(KEY_ENTER))
     {
      setfillstyle(1,0);
      bar(156,196,478,218);
      break;
     }

   }

  }


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 /*��ѭ����ʼ*/

 while(END!=1)
{






/*++++++++++++++++++++++++�ӵ�����++++++++++++++++++++++++++++*/



/*���˵��ӵ�*/

       for(n=0;n<BULLET_SUM;n++)
          {
           if(EB[n].RUN==1)
             {
              if(EB[n].LB<=0)
                {

                 GB_BULLET(EB[n].PX,EB[n].PY,0);



                 MOVE_TO3(EB[n].oa,&EB[n].PX,&EB[n].PY,10);


                 GB_BULLET(EB[n].PX,EB[n].PY,1);


                 EB[n].LB=EB[n].MAX_LB;

                }




              if(EB[n].PX<=40||EB[n].PX>=600||EB[n].PY<=40||EB[n].PY>=440)  /*�ӵ���ǽ ��ʧ*/
                {

                 GB_BULLET(EB[n].PX,EB[n].PY,0);

                 EB[n].RUN=0;

                }



              EB[n].LB--; /*��ʱ*/


             }


          }











/*++++++++++++++++++++++++�жϽӴ�TOUCH++++++++++++++++++++++++++++*/

 for(n=0;n<BULLET_SUM;n++)
    {
     if(EB[n].RUN==1){



                  if(P.LIVE==1){

                                  if(P.X1+9<=EB[n].PX
                                            &&
                                     P.X1+24>=EB[n].PX
                                            &&
                                     P.Y1+7<=EB[n].PY
                                            &&
                                     P.Y1+25>=EB[n].PY
                                    )

                                      {

                                       P.HP=P.HP-5;    /*������ң�HP-5*/

                                       if(P.HP<=0)
                                              {
                                               P.LIVE=0;
                                              }


                                       DISPLAY_HP(P.HP);


                                       SOUND(450,1200); /*��ʾ��*/

                                       GB_BULLET(EB[n].PX,EB[n].PY,0);

                                       EB[n].RUN=0;



                                       }



                                  }



                    }

  }



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/






/*��ʼ��һ���ӵ�*/

for(n=0;n<BULLET_SUM;n++)
   {
    if(EB[n].RUN==0)
      {

        i=Xrand(1,5); /*ȷ�������ӵ�����ʼ�� 4�ֿ�����*/

             if(i==1)
               {
                EB[n].PX=Xrand(41,599);
                EB[n].PY=41;
               }
        else if(i==2)
               {
                EB[n].PX=Xrand(41,599);
                EB[n].PY=439;
               }
        else if(i==3)
               {
                EB[n].PX=41;
                EB[n].PY=Xrand(41,439);
               }
        else if(i==4)
               {
                EB[n].PX=599;
                EB[n].PY=Xrand(41,439);
               }

        else continue;

        EB[n].oa=ASK_a(EB[n].PX,EB[n].PY,P.X1+16,P.Y1+16);  /*ȷ�������ӵ���Ŀ���*/

        EB[n].RUN=1;

     }

  }





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*ʱ���жϴ���*/
if(TimeDelayUnit(1.0)){

                       setfillstyle(1,0);
                       bar(503,7,503+80,7+19);

                       setcolor(10);  /*����������ɫ ʱ��*/


                       TimeS++;
                       if(TimeS==60) { TimeS=0; TimeM++; }  /*IF��60��Ϊ1����*/

                            sprintf(TM,"%02d",TimeM);

                            outtextxy(506,10,TM);

                                outtextxy(536,10,":");

                            sprintf(TS,"%02d",TimeS);

                            outtextxy(551,10,TS);

                      }






/*++++++++++++++++++++++++�԰�������Ӧ+++++++++++++++++++++++++++++*/

   /*�˳�*/
   if(GetKey(KEY_ESC))  {

                         END=1;

                        } 
   /*����*/
   if(GetKey(KEY_UP))
                        {
                         P.Y1-=PLAYER_MOVE_SPEED;

                         if(P.Y1<=40) P.Y1=P.Y0;

                         P.move=1;
                        }
   /*����*/
   if(GetKey(KEY_DOWN))
                        {
                         P.Y1+=PLAYER_MOVE_SPEED;

                         if(P.Y1>=420) P.Y1=P.Y0;

                         P.move=1;
                        }
   /*��ƽ��*/
   if(GetKey(KEY_LEFT))
                        {
                         P.X1-=PLAYER_MOVE_SPEED;

                         if(P.X1<=40) P.X1=P.X0;

                         P.move=1;
                        }
   /*��ƽ��*/
   if(GetKey(KEY_RIGHT))
                        {
                         P.X1+=PLAYER_MOVE_SPEED;

                         if(P.X1>=580) P.X1=P.X0;

                         P.move=1;
                        }





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++����ҵ��¼�����+++++++++++++++++++++++++++*/
                        if(P.LIVE==1)
                        {
                         if(P.move==1)
                           {

                            setfillstyle(1,0);
                            bar(P.X0,P.Y0,P.X0+29,P.Y0+29);

                            GB_TBF(P.X1,P.Y1,&PLANE[0][0]);

                            P.X0=P.X1;
                            P.Y0=P.Y1;

                            P.move=0;

                           }

                         }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



     TimeDelay(GAME_SPEED); /*��Ϸ��ʱ*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

      if(P.LIVE==0)            /*���ʧ��*/
        {

         setfillstyle(1,0);
         bar(P.X0,P.Y0,P.X0+29,P.Y0+29);

         GB_TBF(P.X1,P.Y1,&BLAST[0][0]);

         sleep(1);


         setcolor(4);
         settextstyle(0,0,3);
         outtextxy(236,190,"YOU LOST");

         settextstyle(0,0,1);
         setcolor(15);
         outtextxy(210+72,200+30,"PLEASE WAIT...");


         P.LIFE--;

         sleep(2);
         goto START;

        }


 } /*while��ѭ��ĩβ*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 GAME_OVER:;

 closegraph();

 ShutDownKeyboard();   /*�ָ������ж�*/



}





/*=========================================================================*/



void set_color(int color,int R,int G,int B)      /*�ı��ɫ��*/
{

 static union REGS regs;
  switch(color){
    case 6:color=20;break;
    case 8:color=56;break;
    case 9:color=57;break;
    case 10:color=58;break;
    case 11:color=59;break;
    case 12:color=60;break;
    case 13:color=61;break;
    case 14:color=62;break;
    case 15:color=63;break;
    default:break;
              }
   regs.h.ah=0x10;
   regs.h.al=0x10;
   regs.x.bx=color;
   regs.h.ch=G;
   regs.h.cl=B;
   regs.h.dh=R;
   int86(0x10,&regs,&regs);
   return;
}

void VGA_RESET()                        /*ͼ��ģʽ��ʼ��*/
{
 int driver=VGA;
 int mode=VGAHI;

 registerbgidriver(EGAVGA_driver);      /*ͼ��ģʽ��������*/
 initgraph(&driver,&mode,"");
 cleardevice();

 setpalette(4,36);                      /*�ı��ɫ����ɫ*/
 setpalette(10,18);
 setpalette(13,45);
 setpalette(9,11);
 setpalette(1,9);

  setpalette(12,32);

set_color(7,112,112,112);
set_color(8,95,95,95);

}





void TimeDelay(unsigned long microsec) /*��ʱ���� ����΢����*/
{
 union REGS r;
 r.h.ah=0x86;
 r.x.cx=microsec>>16;
 r.x.dx=microsec;
 int86(0x15,&r,&r);
}




void MOVE_TO3(int oa,float *PX,float *PY,int D)  /*�ƶ���*/
{
 *PX+=D*cos(oa*PI/180);
 *PY+=D*sin(oa*PI/180);
}






void TRANSFORM(char filename[],int *NAME)    /*��TBFͼ���ļ���������*/
{
 int i,j;
 char C;
 FILE *fp;

 if((fp=fopen(filename,"r"))==NULL)  /*��һ���ļ�ֻ��*/
  {

 sound(450);
 delay(1200);
 nosound();
         /*ʧ�ܻ��׷���*/
   return;
  }


 for(i=0;i<=29;i++)
    {
     for(j=0;j<=29;j++)
        {
          C=fgetc(fp);
          *(NAME+(i*30+j))=(int)(C-65);  /*��ԭ����-65*/
        }
    }


 fclose(fp);

}




void GB_TBF(int x,int y,int *NAME)        /*��ʾTBFͼƬ����*/
{ int i,j,X,Y;


  X=x;
  Y=y;
 for(i=0,y=Y;i<=29;i++,y++)
    {
     for(j=0,x=X;j<=29;j++,x++)
     if(*(NAME+(i*30+j))==3){;}
     else{putpixel(x,y,*(NAME+(i*30+j)));}
    }


}







int TimeDelayUnit(float t)                         /*��ʱ  t��*/
{
 static clock_t start_time=0,end_time;

 if(start_time==0){
                   start_time=clock();
                  }

 end_time=clock();


 if((end_time-start_time)/CLK_TCK>=t){
                                      start_time=0;
                                      return(1);
                                     }

 else 
     return(0);


}



int Xrand(int A,int B)    /*�����������A��B*/
{
 int i,x;

 while(1)
    {
     x=random(B);

     if(x>=A) break;

    }

 return(x);

}




double DZ(double X1,double Y1,double X2,double Y2)  /*�������*/
{
 double D;
 D=sqrt(fabs((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1)));

 return (D);
}




int ASK_a(int X1,int Y1,int X2,int Y2)   /*�õ����ĵ㵽Ŀ���ĽǶ�*/
{
   double duibian,xiebian;
   double k;
   double m=0;

   if(X1==X2&&Y1==Y2){return(-1);}

   if(Y2>Y1)
   duibian=Y2-Y1;
   else
   duibian=Y1-Y2;

   xiebian=DZ(X1,Y1,X2,Y2);

   k=duibian/xiebian;


   if(k>=-1&&k<=1){      /*��ֹasin()����*/

   m=asin(k)/PI*180;

        if(X1>X2&&Y1>Y2) {m=180+m;}

   else if(X1<X2&&Y1>Y2) {m=360-m;}

   else if(X1>X2&&Y1<Y2) {m=180-m;}

   else if(X1>X2&&Y1<Y2) {;}

   else if(X1<X2&&Y1==Y2) {m=0;}

   else if(X1==X2&&Y1<Y2) {m=90;}

   else if(X1>X2&&Y1==Y2) {m=180;}

   else if(X1==X2&&Y1>Y2) {m=270;}

   return(m);
                  }

   else return(-1);


}




void DISPLAY_HP(int HP)    /*��ʾ��ҵ�HPֵ*/
{
 int x;
 int HP_X=384;

 x=HP_X-(100-HP);

 setcolor(15);
 rectangle(282,9,386,23);

 setfillstyle(1,0);
 bar(282+1,9+1,386-1,23-1);

 setfillstyle(1,4);
 bar(282+2,9+2,386-2,23-2);

 if(HP!=100){
 setfillstyle(1,0);
 bar(x,11,384,21);
            }

}





void SOUND(int h,int t)
{
 sound(h);
 delay(t);
 nosound();
}



void GB_BULLET(int x,int y,int mode)   /*���ӵ�*/
{
 int COLOR1,COLOR2;

       if(mode==1)
         {
          COLOR1=14;
          COLOR2=4;
         }

 else  if(mode==0)
         {
          COLOR1=0;
          COLOR2=0;
         }

 setfillstyle(1,COLOR1);
 bar(x,y,x+1,y+1);

 setcolor(COLOR2);
 line(x,y-1,x+1,y-1);
 line(x-1,y,x-1,y+1);
 line(x,y+2,x+1,y+2);
 line(x+2,y,x+2,y+1);



}
