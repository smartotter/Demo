/*��������Ϸ   ����SZK8888  �������ڣ�03-10-26            */
/*�����Ʒ��� �������Ϳո������ ���������ĵ������Ϸ��*/

#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include "KEY.c"
#include "mouse3.c"

#define PI 3.1415927


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void VGA_RESET();
void set_color(int color,int R,int G,int B);

void GB_PERSON(int X1,int Y1,int a,int COLOR);   /*���ƽ�ɫ*/

int Round(float x);  /*��������*/

void TimeDelay(unsigned long microsec); /*��ʱ���� ����΢����*/

void MOVE_TO3(int oa,float *PX,float *PY,int D);  /*�ƶ���*/

void TRANSFORM(char filename[],int *NAME);        /*��ͼ���ļ���������*/

void GB_TBF(int x,int y,int *NAME);                             /*��ʾ*/


int TimeDelayUnit(float t);

int Xrand(int A,int B);                                         /*�����������A��B*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

main()
{

 int END=0; /*��Ϸ����*/


 int E_FIRE_ATTACK=90;

 int n,i,j;

 /*�����ɫ�ṹ*/
 struct PERSON {
                int LIVE;

                float X1;           /*��Ļ����*/
                float Y1;
                float X0;
                float Y0;

                int a;            /*�Ƕ�*/
                int a0;

                int COLOR;

                int reload;

                int move;

                int fire;
 
               };


 struct PERSON MAN;    /*�������*/



  /*�����ӵ��ṹ*/
 struct BB{
           int RUN;               /*�Ƿ����� */
           float PX;              /*��ǰ����X*/
           float PY;              /*��ǰ����Y*/
           int oa;                /*Ŀ��Ƕ� */
           int LB;                /*�������� */
           int MAX_LB;
          };

 struct BB MB[30];      /*����ӵ�*/

 struct BB SB[30];



  struct  blast{
           int RUN;               /*�Ƿ����� */
           float PX;              /*��ǰ����X*/
           float PY;              /*��ǰ����Y*/

           int D_time;
                                  /*�������� */
           int MAX_D_time;
          };


  struct blast BBB[30];



 int STAR[30][30];

 int BLAST[30][30];







 int mx0;        /* ���ԭ����λ�� */


 struct time t;          /*ϵͳʱ��*/
 int R;





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 VGA_RESET();               /*ͼ�γ�ʼ��*/

 InstallKeyboard();         /*�����жϳ�ʼ��*/

 initmouse();                  /* ����ʼ�� */

 setmousexy(320,240);            /* �������λ�� */

 srand(Xrand(31,72456));

 gettime(&t);             /*ȡϵͳʱ��*/
 R=t.ti_hund;             /*R=����*/
 srand(R);                /*�������������������*/

/*+++++++++++++++++++++GAME ��ʼ+++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++��ʼ�����++++++++++++++++++++++++++++*/

 MAN.LIVE=1;

 MAN.X1=320;
 MAN.Y1=460;
 MAN.X0=MAN.X1;
 MAN.Y0=MAN.Y1;
 MAN.a=270;
 MAN.a0=MAN.a;
 MAN.COLOR=9;
 MAN.reload=0;
 MAN.move=0;
 MAN.fire=0;


 /*+++++++++++++++++++++��ʼ���ӵ�++++++++++++++++++++++++++++*/


 for(n=0;n<30;n++)   /*����ӵ���ʼ��*/
    {
     MB[n].RUN=0;
     MB[n].MAX_LB=2;
     MB[n].LB=MB[n].MAX_LB;
    }



 for(n=0;n<30;n++)   /*�ӵ���ʼ��*/
    {
     SB[n].RUN=0;
     SB[n].MAX_LB=10;
     SB[n].LB=SB[n].MAX_LB;
    }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


 for(n=0;n<30;n++)   /*��ʼ��*/
    {
     BBB[n].RUN=0;
     BBB[n].MAX_D_time=20;
     BBB[n].D_time=BBB[n].MAX_D_time;
    }
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

TRANSFORM("STAR.TBF",&STAR[0][0]);
TRANSFORM("BZ.TBF",&BLAST[0][0]);



GB_PERSON(MAN.X1,MAN.Y1,MAN.a,9);




  /*��ѭ����ʼ*/

 while(END!=1)
{



/*++++++++++++++++++++++++�ӵ�����++++++++++++++++++++++++++++*/

/*��ҵ��ӵ�*/

       for(n=0;n<30;n++)
          {
           if(MB[n].RUN==1)
             {
              if(MB[n].LB<=0)
                {


                 setfillstyle(1,0);
                 bar(MB[n].PX,MB[n].PY,MB[n].PX+1,MB[n].PY+1);

                 MOVE_TO3(MB[n].oa,&MB[n].PX,&MB[n].PY,10);

                 setfillstyle(1,14);
                 bar(MB[n].PX,MB[n].PY,MB[n].PX+1,MB[n].PY+1);

                 MB[n].LB=MB[n].MAX_LB;
                }


              if(MB[n].PX<=40||MB[n].PX>=600||MB[n].PY<=40)

                         {   /*�ӵ���ǽ ��ʧ*/

                          setfillstyle(1,0);
                          bar(MB[n].PX,MB[n].PY,MB[n].PX+1,MB[n].PY+1);

                           MB[n].RUN=0;

                         }

              MB[n].LB--; /*��ʱ*/


             }


          }





/*�ӵ�*/

       for(n=0;n<30;n++)
          {
           if(SB[n].RUN==1)
             {
              if(SB[n].LB<=0)
                {


                 setfillstyle(1,0);
                 bar(SB[n].PX,SB[n].PY,SB[n].PX+29,SB[n].PY+29);

                 MOVE_TO3(SB[n].oa,&SB[n].PX,&SB[n].PY,10);

                 GB_TBF(SB[n].PX,SB[n].PY,&STAR[0][0]);

                 SB[n].LB=SB[n].MAX_LB;
                }


              if(SB[n].PY>=400)

                         {   /*�ӵ���ǽ ��ʧ*/

                 setfillstyle(1,0);
                 bar(SB[n].PX,SB[n].PY,SB[n].PX+29,SB[n].PY+29);

                           SB[n].RUN=0;

                         }

              SB[n].LB--; /*��ʱ*/


             }


          }

















/*++++++++++++++++++++++++�Ӵ�TOUCH++++++++++++++++++++++++++++*/

/*��ҵ��ӵ�����˽Ӵ�*/

 for(n=0;n<30;n++)
    {
     if(MB[n].RUN==1){



             for(i=0;i<30;i++)
                {
                 if(SB[i].RUN==1){

                                  if(SB[i].PX<=MB[n].PX   /*�Ӵ��ķ�Χ*/
                                            &&
                                     SB[i].PX+29>=MB[n].PX
                                            &&
                                     SB[i].PY<=MB[n].PY
                                            &&
                                     SB[i].PY+29>=MB[n].PY
                                    )

                                      {



                                       MB[n].RUN=0;
                                       setfillstyle(1,0);
                                       bar(MB[n].PX,MB[n].PY,MB[n].PX+1,MB[n].PY+1);

                                       SB[i].RUN=0;
                                       setfillstyle(1,0);
                                       bar(SB[i].PX,SB[i].PY,SB[i].PX+29,SB[i].PY+29);

                                           for(j=0;j<30;j++)
                                              {
                                                if(BBB[j].RUN==0)
                                                  {
                                                   BBB[j].D_time=BBB[j].MAX_D_time;

                                                   BBB[j].PX=SB[i].PX;
                                                   BBB[j].PY=SB[i].PY;


                                                   BBB[j].RUN=1;

                                                   break;
                                                  }
                                             }



                                         i=30;
                                       }



                                  }

                 }/*for i*/

                    }

  }


/*++++++++++++++*/


















/*��ը*/

       for(n=0;n<30;n++)
          {
           if(BBB[n].RUN==1)
             {

              GB_TBF(BBB[n].PX,BBB[n].PY,&BLAST[0][0]);

              BBB[n].D_time--;


              if(BBB[n].D_time<=0)

                         {   /*��ʧ*/

                           setfillstyle(1,0);
                           bar(BBB[n].PX,BBB[n].PY,BBB[n].PX+29,BBB[n].PY+29);

                           BBB[n].RUN=0;

                         }




             }


          }










if(TimeDelayUnit(0.5))
  {
                              /*���Կ���*/
  E_FIRE_ATTACK=random(100);




  if(E_FIRE_ATTACK<=90)
                        {

                         for(n=0;n<30;n++)
                            {
                             if(SB[n].RUN==0)
                               {
                                /*��ʼ��һ������*/
                                SB[n].oa=90;

                                SB[n].PX=Xrand(50,560);
                                SB[n].PY=20;

                                SB[n].RUN=1;

                                break;
                               }

                            }

                        }




  }










  mx0=mouse.getx;



  getmousexy();


  if(mouse.getx!=mx0)   /* ��궯�� x */
    {

      MAN.a+=mouse.getx-mx0;
      if(MAN.a>360) MAN.a=360;
      else if(MAN.a<180)   MAN.a=180;


            if(mouse.getx>=620){  setmousexy(320,240);  getmousexy(); }

     else   if(mouse.getx<=20) {  setmousexy(320,240);  getmousexy(); }

     MAN.move=1;

   }



 if(getmkeyin(mbLeft)==mbLeft) /*�������*/
   {
    MAN.fire=1;
   }

if(getmkeyout(mbLeft)==mbLeft)  /*������̧��*/
  {
    MAN.fire=0;
  }




/*++++++++++++++++++++++++�԰�������Ӧ+++++++++++++++++++++++++++++*/

   /*�˳�*/
   if(GetKey(KEY_ESC))  {

                         END=1;

                        } 


   /*��ת*/
   if(GetKey(KEY_LEFT))  {

                          MAN.a=MAN.a-3;
                          if(MAN.a>360) MAN.a=360;
                          else if(MAN.a<180)   MAN.a=180;

                          MAN.move=1;

                         }


    /*��ת*/
    if(GetKey(KEY_RIGHT)){

                          MAN.a=MAN.a+3;
                          if(MAN.a>360) MAN.a=360;
                          else if(MAN.a<180)   MAN.a=180;

                          MAN.move=1;

                         }


    /*�������*/
   if(GetKey(KEY_SPACE)){
                         if(MAN.reload<=0){  /*װ��ʱ��*/
                                           for(n=0;n<30;n++)
                                              {
                                               if(MB[n].RUN==0)
                                                 {
                                                  /*��ʼ��һ���ӵ�*/
                                                  MB[n].oa=MAN.a;

                                                  MB[n].PX=Round(22*cos(MAN.a*PI/180))+MAN.X1;
                                                  MB[n].PY=Round(22*sin(MAN.a*PI/180))+MAN.Y1;


                                                  MB[n].RUN=1;



                                                  break;
                                                 }

                                               }

                                             MAN.reload=6;
                                           }
                        }











/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++����ҵ��¼�����+++++++++++++++++++++++++++*/

                        if(MAN.LIVE==1)
                        {
                         if(MAN.move==1)
                           {     

                            GB_PERSON(MAN.X0,MAN.Y0,MAN.a0,0);

                            GB_PERSON(MAN.X1,MAN.Y1,MAN.a,9);


                            MAN.X0=MAN.X1;
                            MAN.Y0=MAN.Y1;


                            MAN.a0=MAN.a;

                            MAN.move=0;

                         }





 if(MAN.fire==1) /*����*/
  {
                         if(MAN.reload<=0){  /*װ��ʱ��*/
                                           for(n=0;n<30;n++)
                                              {
                                               if(MB[n].RUN==0)
                                                 {
                                                  /*��ʼ��һ���ӵ�*/
                                                  MB[n].oa=MAN.a;

                                                  MB[n].PX=Round(22*cos(MAN.a*PI/180))+MAN.X1;
                                                  MB[n].PY=Round(22*sin(MAN.a*PI/180))+MAN.Y1;


                                                  MB[n].RUN=1;



                                                  break;
                                                 }

                                               }

                                             MAN.reload=6;
                                           }


  }





                        }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

     MAN.reload--;    /*װ��ʱ��仯*/
     if(MAN.reload<=0)   MAN.reload=0;

     TimeDelay(10000L); /*��Ϸ��ʱ*/


 } /*while��ѭ��ĩβ*/



 GAME_OVER:;

 closegraph();

 ShutDownKeyboard();   /*�ָ������ж�*/





}









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








void GB_PERSON(int X1,int Y1,int a,int COLOR)   /*����*/
{
 int X2,Y2;

 setcolor(COLOR);
 setfillstyle(1,COLOR);

 circle(X1,Y1,12);

 bar(X1-1,Y1-1,X1+1,Y1+1);


 X2=Round(18*cos(a*PI/180))+X1;   /*r=10   ����=�Ƕ�*PI/180*/
 Y2=Round(18*sin(a*PI/180))+Y1;


 line(X1,Y1,X2,Y2);
 bar(X2-1,Y2-1,X2+1,Y2+1);

}



int Round(float x)  /*��������*/
{
 return((int)(x+0.5));
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

void TRANSFORM(char filename[],int *NAME)        /*��ͼ���ļ���������*/
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

void GB_TBF(int x,int y,int *NAME)                             /*��ʾ*/
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
