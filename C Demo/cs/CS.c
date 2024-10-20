/* 
 *           本程序由 Turbo C 2.0 编写
 *
 *                  CS VER 0.16c
 *
 *           COPYRIGHT 2003 BY SZK8888 
 *
 */

/*2002.10.07*/
/*2003.03.31*/
/*2003.09.06*/
/*2003.09.15*/
/*WINTC 1.7.2 下编译通过*/

#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include "MAP.c"
#include "key.c"

#define PI 3.1415927

/*=========================================================================*/

void VGA_RESET();
void set_color(int color,int R,int G,int B);

int Round(float x);  /*四舍五入*/

void GB_PERSON(int X1,int Y1,int a,int COLOR);

void MOVE_TO2(int X1,int Y1,int X2,int Y2,int *PX,int *PY,int SPEED);

float K_B(int x1,int y1,int x2,int y2,int n);
float Z_X(float y,float k,float b);
float Z_Y(float x,float k,float b);

void DISPLAY_MAP(int MAP_X,int MAP_Y);

void PANE(int X1,int Y1,int B,int A,int L,int COLOR); /*方格*/
void ER(int COLOR);

int ASK_MAP_AB(int x,int y,int bx,int by,int L,int N);

void InstallKeyboard(void);
void ShutDownKeyboard(void);
void far interrupt NewInt9(void);
int GetKey(int ScanCode);

char key_state[128],key_pressed[128];
void interrupt far (*OldInt9Handler)();

void TimeDelay(unsigned long microsec); /*延时函数 传入微秒数*/

double DZ(double X1,double Y1,double X2,double Y2);  /*两点距离*/
int ASK_a(int X1,int Y1,int X2,int Y2);   /*得到中心点到目标点的角度*/

void Alert(int x,int y,int color);   /*惊叹号!*/

void DISPLAY_HP(int HP);

/*=========================================================================*/

main()
{

 int END=0;      /*游戏结束*/

 int MAP_X0=94;  /*地图坐标*/
 int MAP_Y0=20;

 int cc=0;       /*显示格子 DEL*/
 int EYE=0;      /*显示敌人的视觉线 F2*/

 int n,i,j;      /*临时的 无意义*/

 int e;          /*判断出错*/

 int LIFE=2;     /*玩家的命*/
 char LL[3];

 int KILL=0;     /*玩家杀敌的人数*/
 char KK[3];
 int  LK;

 int move;       /*响应玩家动作*/


 /*定义PERSON*/
 struct PERSON {
                int LIVE;

                int X1;           /*绝对坐标*/
                int Y1;
                int X0;
                int Y0;

                int X2;           /*目标点*/
                int Y2;

                int MAP_A;        /*MAP坐标*/
                int MAP_B;
                int MAP_A0;
                int MAP_B0;

                int a;            /*角度*/
                int a0;

                int COLOR;

                int LB;           /*生命钟*/
                int MAX_LB;
 

                int PB[5];        /*路径*/
                int PA[5];
                int PP;  

                int HP;          /*生命值*/   

                reload;          /*装填时间*/
   
                int Alert;       /*警报*/
                int Alert_MAP_A;
                int Alert_MAP_B;

                int EX;          /*视觉点*/
                int EY;
                int EX2;
                int EY2;
                int Ea;

                fire;

                int move;
                int round;
                int ra;
                int oa;

               }MAN;



 struct PERSON T[5];   /*敌人*/


 /*定义子弹*/
 struct BB{
                int RUN;               /**/
                int PX;                /**/
                int PY;                /**/
                int X1,Y1;             /*起点*/
                int X2,Y2;             /*终点*/
                int LB;                /*生命钟*/
                int MAX_LB;
          }MB[30];


 struct BB EB[30];




/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


 VGA_RESET();               /*图形初始化*/

 InstallKeyboard();         /*键盘中断初始化*/


 START:;


/*+++++++++++++++++++++初始化玩家++++++++++++++++++++++++++++*/


 MAN.LIVE=1;
 MAN.MAP_A=28;
 MAN.MAP_B=15;
 MAN.MAP_A0=MAN.MAP_A;
 MAN.MAP_B0=MAN.MAP_B;
 MAN.X1=MAP_X0+MAN.MAP_B*15+7;
 MAN.Y1=MAP_Y0+MAN.MAP_A*15+7;
 MAN.X0=MAN.X1;
 MAN.Y0=MAN.Y1;
 MAN.a=270;
 MAN.a0=MAN.a;
 MAN.COLOR=9;
 MAN.X2=Round(10*cos(MAN.a*PI/180))+MAN.X1;
 MAN.Y2=Round(10*sin(MAN.a*PI/180))+MAN.Y1;
 MAN.reload=0;
 MAN.HP=100;


/*+++++++++++++++++++++初始化敌人++++++++++++++++++++++++++++*/


T[0].LIVE=1;
T[0].MAP_A=16;
T[0].MAP_B=7;
T[0].MAP_A0=T[0].MAP_A;
T[0].MAP_B0=T[0].MAP_B;
T[0].X1=MAP_X0+T[0].MAP_B*15+7;
T[0].Y1=MAP_Y0+T[0].MAP_A*15+7;
T[0].X0=T[0].X1;
T[0].Y0=T[0].Y1;
T[0].a=45;
T[0].a0=T[0].a;
T[0].COLOR=4;
T[0].MAX_LB=2;
T[0].LB=T[0].MAX_LB;
T[0].HP=100;
T[0].reload=0;
T[0].Alert=0;
T[0].Alert_MAP_A=-1;
T[0].Alert_MAP_B=-1;
T[0].fire=0;
T[0].move=1;
T[0].round=0;
T[0].ra=0;
T[0].oa=0;



T[1].LIVE=1;
T[1].MAP_A=12;
T[1].MAP_B=12;
T[1].MAP_A0=T[1].MAP_A;
T[1].MAP_B0=T[1].MAP_B;
T[1].X1=MAP_X0+T[1].MAP_B*15+7;
T[1].Y1=MAP_Y0+T[1].MAP_A*15+7;
T[1].X0=T[1].X1;
T[1].Y0=T[1].Y1;
T[1].a=270;
T[1].a0=T[1].a;
T[1].COLOR=4;
T[1].MAX_LB=2;
T[1].LB=T[1].MAX_LB;
T[1].HP=100;
T[1].reload=0;
T[1].Alert=0;
T[1].Alert_MAP_A=-1;
T[1].Alert_MAP_B=-1;
T[1].fire=0;
T[1].move=1;
T[1].round=0;
T[1].ra=0;
T[1].oa=0;


T[2].LIVE=1;
T[2].MAP_A=6;
T[2].MAP_B=16;
T[2].MAP_A0=T[2].MAP_A;
T[2].MAP_B0=T[2].MAP_B;
T[2].X1=MAP_X0+T[2].MAP_B*15+7;
T[2].Y1=MAP_Y0+T[2].MAP_A*15+7;
T[2].X0=T[2].X1;
T[2].Y0=T[2].Y1;
T[2].a=90;
T[2].a0=T[2].a;
T[2].COLOR=4;
T[2].MAX_LB=2;
T[2].LB=T[2].MAX_LB;
T[2].HP=100;
T[2].reload=0;
T[2].Alert=0;
T[2].Alert_MAP_A=-1;
T[2].Alert_MAP_B=-1;
T[2].fire=0;
T[2].move=1;
T[2].round=0;
T[2].ra=0;
T[2].oa=0;


T[3].LIVE=1;
T[3].MAP_A=20;
T[3].MAP_B=17;
T[3].MAP_A0=T[3].MAP_A;
T[3].MAP_B0=T[3].MAP_B;
T[3].X1=MAP_X0+T[3].MAP_B*15+7;
T[3].Y1=MAP_Y0+T[3].MAP_A*15+7;
T[3].X0=T[3].X1;
T[3].Y0=T[3].Y1;
T[3].a=270;
T[3].a0=T[3].a;
T[3].COLOR=4;
T[3].MAX_LB=2;
T[3].LB=T[3].MAX_LB;
T[3].Alert=0;
T[3].HP=100;
T[3].reload=0;
T[3].Alert=0;
T[3].Alert_MAP_A=-1;
T[3].Alert_MAP_B=-1;
T[3].fire=0;
T[3].move=1;
T[3].round=0;
T[3].ra=0;
T[3].oa=0;


T[4].LIVE=1;
T[4].MAP_A=14;
T[4].MAP_B=25;
T[4].MAP_A0=T[4].MAP_A;
T[4].MAP_B0=T[4].MAP_B;
T[4].X1=MAP_X0+T[4].MAP_B*15+7;
T[4].Y1=MAP_Y0+T[4].MAP_A*15+7;
T[4].X0=T[4].X1;
T[4].Y0=T[4].Y1;
T[4].a=180;
T[4].a0=T[4].a;
T[4].COLOR=4;
T[4].MAX_LB=2;
T[4].LB=T[4].MAX_LB;
T[4].HP=100;
T[4].reload=0;
T[4].Alert=0;
T[4].Alert_MAP_A=-1;
T[4].Alert_MAP_B=-1;
T[4].fire=0;
T[4].move=1;
T[4].round=0;
T[4].ra=0;
T[4].oa=0;


/*------------------------*/
/*定义行走路径*/
T[0].PP=0;

T[0].PA[0]=18;
T[0].PB[0]=10;

T[0].PA[1]=16;
T[0].PB[1]=12;

T[0].PA[2]=14;
T[0].PB[2]=10;

T[0].PA[3]=14;
T[0].PB[3]=6;

T[0].PA[4]=17;
T[0].PB[4]=5;

T[0].X2=MAP_X0+T[0].PB[T[0].PP]*15+7;       /*定义新目标点*/
T[0].Y2=MAP_Y0+T[0].PA[T[0].PP]*15+7;
T[0].a=ASK_a(T[0].X1,T[0].Y1,T[0].X2,T[0].Y2);   /*得到目标点的角度*/
T[0].oa=T[0].a;
T[0].a0=T[0].a;

T[1].PP=0;

T[1].PA[0]=7;
T[1].PB[0]=12;

T[1].PA[1]=7;
T[1].PB[1]=13;

T[1].PA[2]=6;
T[1].PB[2]=13;

T[1].PA[3]=6;
T[1].PB[3]=6;

T[1].PA[4]=11;
T[1].PB[4]=8;

T[1].X2=MAP_X0+T[1].PB[T[1].PP]*15+7;       /*定义新目标点*/
T[1].Y2=MAP_Y0+T[1].PA[T[1].PP]*15+7;
T[1].a=ASK_a(T[1].X1,T[1].Y1,T[1].X2,T[1].Y2);   /*得到目标点的角度*/
T[1].oa=T[1].a;
T[1].a0=T[1].a;

T[2].PP=0;

T[2].PA[0]=14;
T[2].PB[0]=16;

T[2].PA[1]=2;
T[2].PB[1]=16;

T[2].PA[2]=2;
T[2].PB[2]=20;

T[2].PA[3]=1;
T[2].PB[3]=20;

T[2].PA[4]=1;
T[2].PB[4]=16;

T[2].X2=MAP_X0+T[2].PB[T[2].PP]*15+7;       /*定义新目标点*/
T[2].Y2=MAP_Y0+T[2].PA[T[2].PP]*15+7;
T[2].a=ASK_a(T[2].X1,T[2].Y1,T[2].X2,T[2].Y2);   /*得到目标点的角度*/
T[2].oa=T[2].a;
T[2].a0=T[2].a;


T[3].PP=0;

T[3].PA[0]=24;
T[3].PB[0]=14;

T[3].PA[1]=21;
T[3].PB[1]=5;

T[3].PA[2]=22;
T[3].PB[2]=16;

T[3].PA[3]=17;
T[3].PB[3]=15;

T[3].PA[4]=17;
T[3].PB[4]=18;

T[3].X2=MAP_X0+T[3].PB[T[3].PP]*15+7;       /*定义新目标点*/
T[3].Y2=MAP_Y0+T[3].PA[T[3].PP]*15+7;
T[3].a=ASK_a(T[3].X1,T[3].Y1,T[3].X2,T[3].Y2);   /*得到目标点的角度*/
T[3].oa=T[3].a;
T[3].a0=T[3].a;



T[4].PP=0;

T[4].PA[0]=12;
T[4].PB[0]=25;

T[4].PA[1]=10;
T[4].PB[1]=24;

T[4].PA[2]=7;
T[4].PB[2]=24;

T[4].PA[3]=7;
T[4].PB[3]=20;

T[4].PA[4]=11;
T[4].PB[4]=19;

T[4].X2=MAP_X0+T[4].PB[T[4].PP]*15+7;       /*定义新目标点*/
T[4].Y2=MAP_Y0+T[4].PA[T[4].PP]*15+7;
T[4].a=ASK_a(T[4].X1,T[4].Y1,T[4].X2,T[4].Y2);   /*得到目标点的角度*/
T[4].oa=T[4].a;
T[4].a0=T[4].a;





/*+++++++++++++++++++++初始化子弹++++++++++++++++++++++++++++*/


 for(n=0;n<30;n++)   /*玩家子弹初始化*/
    {
     MB[n].PX=0;
     MB[n].PY=0;
     MB[n].X1=1;
     MB[n].Y1=2;
     MB[n].X2=3;
     MB[n].Y2=4;

     MB[n].RUN=0;
     MB[n].MAX_LB=0;
     MB[n].LB=MB[n].MAX_LB;

    }

/*------------------------*/



 for(n=0;n<30;n++)   /*敌人子弹初始化*/
    {
     EB[n].PX=0;
     EB[n].PY=0;
     EB[n].X1=1;
     EB[n].Y1=2;
     EB[n].X2=3;
     EB[n].Y2=4;

     EB[n].RUN=0;
     EB[n].MAX_LB=0;
     EB[n].LB=EB[n].MAX_LB;

    }


/*+++++++++++++++++++++++++++开始++++++++++++++++++++++++++++++++++*/

 cleardevice();


 if(LIFE<0)           /*玩家没命了 GAME OVER 游戏结束*/
   {

    setcolor(4);
    settextstyle(0,0,4);
    outtextxy(162,200,"GAME OVER");

    sleep(3);

    END=1;

    goto GAME_OVER;
   }



 setcolor(15);
 settextstyle(0,0,2);
 outtextxy(110,7,"LIFE");
 outtextxy(245,7,"HP");
 outtextxy(418,7,"KILL");

 sprintf(LL,"%d",LIFE);
 outtextxy(200,7,LL);
 sprintf(KK,"%02d",KILL);
 outtextxy(500,7,KK);

 DISPLAY_HP(MAN.HP);





 DISPLAY_MAP(MAP_X0,MAP_Y0);  /*显示地图*/

 settextstyle(0,0,1);         /*显示版本*/
 setcolor(10);
 outtextxy(560,470,"VER 0.16c");

 /*绘制各个角色*/
 GB_PERSON(MAN.X1,MAN.Y1,MAN.a,MAN.COLOR);
 MAP2[MAN.MAP_A][MAN.MAP_B]=1;

 for(n=0;n<5;n++)
    {
     GB_PERSON(T[n].X1,T[n].Y1,T[n].a,T[n].COLOR);
    }


 GB_PERSON(431,237,270,10);

 move=0;

 LK=0;




 /*大循环开始*/

 while(END!=1)
{



/*++++++++++++++++++++++++对敌人T的处理++++++++++++++++++++++++++++*/

  for(n=0;n<5;n++)
     {
      if(T[n].LIVE==1) /*IF存在*/
        {
         if(T[n].LB<=0)
          {

          /*警报状态*/
          if(T[n].Alert==1)
            {
              T[n].X2=MAP_X0+T[n].Alert_MAP_B*15+7;   /*前往出事地点*/
              T[n].Y2=MAP_Y0+T[n].Alert_MAP_A*15+7;



             if(T[n].MAP_A==T[n].Alert_MAP_A&&T[n].MAP_B==T[n].Alert_MAP_B)  /*IF到达出事地点*/
               {
                T[n].Alert=0;

                T[n].PP--;                               /*得到警报前的节点号*/
                if(T[n].PP<0) T[n].PP=0;

                T[n].X2=MAP_X0+T[n].PB[T[n].PP]*15+7;       /*定义T的新目标点*/   /*返回巡逻路线*/
                T[n].Y2=MAP_Y0+T[n].PA[T[n].PP]*15+7;

                T[n].oa=ASK_a(T[n].X1,T[n].Y1,T[n].X2,T[n].Y2);   /*得到目标点的角度*/

               if(T[n].oa!=T[n].a)  /*目标角!=当前角*/
               {
                /* 确定旋转角度值 */
                if( T[n].oa-T[n].a <= 180 )
                  {
                   if( T[n].oa-T[n].a >0 )  T[n].ra=18;
                   else T[n].ra=-18;
                  }

                 else if( T[n].oa-T[n].a > 180 )
                  {
                   if( T[n].oa-T[n].a >0 )  T[n].ra=-18;
                   else T[n].ra=18;
                  }

                 /*----------------*/


                T[n].move=0;
                T[n].round=1;
               }


               }
             }


           /*一般状态  巡逻*/
           else{

                if(T[n].MAP_A==T[n].PA[T[n].PP]&&T[n].MAP_B==T[n].PB[T[n].PP]) /*到达目标点*/
                  {
                   T[n].PP++;                                  /*下一个节点*/
                   if(T[n].PP>4) T[n].PP=0;

                   T[n].X2=MAP_X0+T[n].PB[T[n].PP]*15+7;       /*定义T的新目标点*/
                   T[n].Y2=MAP_Y0+T[n].PA[T[n].PP]*15+7;

                   T[n].oa=ASK_a(T[n].X1,T[n].Y1,T[n].X2,T[n].Y2);   /*得到目标点的角度*/

               if(T[n].oa!=T[n].a)  /*目标角!=当前角*/
               {
                /* 确定旋转角度值 */
                if( T[n].oa-T[n].a <= 180 )
                  {
                   if( T[n].oa-T[n].a >0 )  T[n].ra=18;
                   else T[n].ra=-18;
                  }

                 else if( T[n].oa-T[n].a > 180 )
                  {
                   if( T[n].oa-T[n].a >0 )  T[n].ra=-18;
                   else T[n].ra=18;
                  }

                 /*----------------*/


                T[n].move=0;
                T[n].round=1;
               }

                  }
                }










          /*------------------------*/

          if(T[n].round==1)  /*旋转*/
            {

             GB_PERSON(T[n].X0,T[n].Y0,T[n].a0,0); /*擦去原来的*/

             T[n].a=T[n].a+T[n].ra;

              if(T[n].a<0)   { T[n].a=360+T[n].a; }

        else if(T[n].a>360) { T[n].a=T[n].a-360; }

        else if(T[n].a==360)  { T[n].a=0; }

             GB_PERSON(T[n].X1,T[n].Y1,T[n].a,T[n].COLOR);

             T[n].a0=T[n].a;



             if( abs(T[n].oa-T[n].a) <= 24)
               {
                T[n].a=T[n].oa;   T[n]. round=0;  T[n].move=1;
               }

             else T[n].move=0;

            }

          /*------------------------*/



          /*------------------------*/

          if(T[n].move==1)   /*移动*/
            {

                MOVE_TO2(T[n].X1,T[n].Y1,T[n].X2,T[n].Y2,&T[n].X1,&T[n].Y1,3); /*向目标点移动*/

                GB_PERSON(T[n].X0,T[n].Y0,T[n].a0,0); /*擦去原来的*/

                T[n].MAP_A=ASK_MAP_AB(T[n].X1,T[n].Y1,MAP_X0,MAP_Y0,15,2);   /*得到新的MAP的位置*/
                T[n].MAP_B=ASK_MAP_AB(T[n].X1,T[n].Y1,MAP_X0,MAP_Y0,15,1);


                           if(MAP[T[n].MAP_A][T[n].MAP_B]==0)    /*0没有障碍*/
                             {
                              ;
                             }


                           else                                   /*有障碍*/
                             {

                              if(MAP[T[n].MAP_A0][T[n].MAP_B0+(T[n].MAP_B-T[n].MAP_B0)]!=0)     /*特殊算法*/
                                {
                                 T[n].X1=T[n].X0;
                                }


                              if(MAP[T[n].MAP_A0+(T[n].MAP_A-T[n].MAP_A0)][T[n].MAP_B0]!=0)
                                {
                                 T[n].Y1=T[n].Y0;
                                } 


                              if(MAP[T[n].MAP_A0+(T[n].MAP_A-T[n].MAP_A0)][T[n].MAP_B0+(T[n].MAP_B-T[n].MAP_B0)]!=0 /*45度进入*/
                                                            &&
                                 MAP[T[n].MAP_A0][T[n].MAP_B0+(T[n].MAP_B-T[n].MAP_B0)]==0
                                                            &&
                                 MAP[T[n].MAP_A0+(T[n].MAP_A-T[n].MAP_A0)][T[n].MAP_B0]==0

                                )
                                {
                                 T[n].X1=T[n].X0;
                                 T[n].Y1=T[n].Y0;
                                } 

                               T[n].MAP_A=T[n].MAP_A0;     /*停止移动还原*/
                               T[n].MAP_B=T[n].MAP_B0;
                               
                              }

                            T[n].a=ASK_a(T[n].X1,T[n].Y1,T[n].X2,T[n].Y2);   /*得到面向的角度*/

                            GB_PERSON(T[n].X1,T[n].Y1,T[n].a,T[n].COLOR);

                            T[n].X0=T[n].X1;
                            T[n].Y0=T[n].Y1;

                            T[n].MAP_A0=T[n].MAP_A;
                            T[n].MAP_B0=T[n].MAP_B;

                            T[n].a0=T[n].a;






            }

          /*------------------------*/



         T[n].LB=T[n].MAX_LB;

         }       /*if(T[n].LB<=0)*/





           if(T[n].fire==1)   /*开火*/
            {
             if(T[n].reload<=0){  /*装填时间*/

               for(i=0;i<30;i++)
                  {
                   if(EB[i].RUN==0)
                     {
                      EB[i].X2=T[n].X2;
                      EB[i].Y2=T[n].Y2;
                      EB[i].X1=T[n].X1;
                      EB[i].Y1=T[n].Y1;

                      EB[i].PX=EB[i].X1;
                      EB[i].PY=EB[i].Y1;

                      EB[i].RUN=1;

                      break;
                     }

                  }
                  T[n].reload=5;
                               }


              if(MAP2[T[n].Alert_MAP_A][T[n].Alert_MAP_B]==0)
                {
                 T[n].fire=0;

                 Alert(T[n].X0-1,T[n].Y0-21,0);  /*擦去!*/
                 T[n].move=1;
                }

             else T[n].move=0;
            }

                  /*++++++++敌人视觉判断++++++++++++++*/

        T[n].Ea=T[n].a-20;   /*视角40度*/

        for(j=0;j<40;j++)
           {
            T[n].EX=T[n].X1; T[n].EY=T[n].Y1;
            T[n].EX2=Round(50*cos(T[n].Ea*PI/180))+T[n].X1;      /*生成新的目标点*/
            T[n].EY2=Round(50*sin(T[n].Ea*PI/180))+T[n].Y1;

          for(e=0;e>=0;)
           {
            MOVE_TO2(T[n].X1,T[n].Y1,T[n].EX2,T[n].EY2,&T[n].EX,&T[n].EY,5);  /* EX EY 视觉点*/

            if(MAP[ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,2)][ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,1)]!=0)
              {
               if(EYE==1) /*显示敌人的视觉线*/
                 {
                  setcolor(1);
                  line(T[n].X1,T[n].Y1,T[n].EX,T[n].EY);
                 }

               e=-1;
              }

            if(MAP2[ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,2)][ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,1)]==-1)
              {
               e=-1;
              }

            if(MAP2[ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,2)][ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,1)]==1)
              {
               if(T[n].fire==0)
                 {
                  T[n].Alert=1;

                  Alert(T[n].X1-1,T[n].Y1-21,10);
                  T[n].Alert_MAP_A=ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,2);
                  T[n].Alert_MAP_B=ASK_MAP_AB(T[n].EX,T[n].EY,MAP_X0,MAP_Y0,15,1);
                  T[n].X2=MAN.X1;       /*定义T的新目标点*/
                  T[n].Y2=MAN.Y1;

                  T[n].a=ASK_a(T[n].X1,T[n].Y1,T[n].X2,T[n].Y2); /*改变角度*/

                  GB_PERSON(T[n].X0,T[n].Y0,T[n].a0,0);
                  GB_PERSON(T[n].X1,T[n].Y1,T[n].a,T[n].COLOR);
                  T[n].a0=T[n].a;

                  T[n].fire=1;
                  T[n].move=0;
                  T[n].round=0;
                  e=-1;
                 }


               }


            }/*e*/

           T[n].Ea=T[n].Ea+1;

          }/*j*/





          T[n].reload--;    /*装填时间变化*/
          if(T[n].reload<=0)   T[n].reload=0;

          T[n].LB--; /*延时*/

        }


     } 


/*++++++++++++++++++++++++设置事件++++++++++++++++++++++++++++*/

     if(MAN.MAP_A==26&&MAN.MAP_B==7)  /*触发警报*/
       {
         T[3].Alert=1;    T[3].Alert_MAP_A=MAN.MAP_A;   T[3].Alert_MAP_B=MAN.MAP_B;

       }

     if(MAN.MAP_A==26&&MAN.MAP_B==8)  /*触发警报*/
       {
         T[3].Alert=1;    T[3].Alert_MAP_A=MAN.MAP_A;   T[3].Alert_MAP_B=MAN.MAP_B;
       }

     if(MAN.MAP_A==7&&MAN.MAP_B==14)  /*触发警报*/
       {
         T[1].Alert=1;    T[1].Alert_MAP_A=MAN.MAP_A;   T[1].Alert_MAP_B=MAN.MAP_B;
       }

     if(MAN.MAP_A==6&&MAN.MAP_B==14)  /*触发警报*/
       {
         T[1].Alert=1;    T[1].Alert_MAP_A=MAN.MAP_A;   T[1].Alert_MAP_B=MAN.MAP_B;
       }

     if(MAN.MAP_A==13&&MAN.MAP_B==18)  /*触发警报*/
       {
         T[4].Alert=1;    T[4].Alert_MAP_A=MAN.MAP_A;   T[4].Alert_MAP_B=MAN.MAP_B;
       }








/*++++++++++++++++++++++++子弹飞行++++++++++++++++++++++++++++*/

       for(n=0;n<30;n++)
          {
           if(MB[n].RUN==1)
             {
              if(MB[n].LB<=0)
                {
                 putpixel(MB[n].PX,MB[n].PY,0);

                 MOVE_TO2(MB[n].X1,MB[n].Y1,MB[n].X2,MB[n].Y2,&MB[n].PX,&MB[n].PY,10);

                 putpixel(MB[n].PX,MB[n].PY,14);

                 MB[n].LB=MB[n].MAX_LB;
                }


              if(MAP[ASK_MAP_AB(MB[n].PX,MB[n].PY,MAP_X0,MAP_Y0,15,2)][ASK_MAP_AB(MB[n].PX,MB[n].PY,MAP_X0,MAP_Y0,15,1)]!=0)

                         {   /*子弹碰墙 消失*/

                           putpixel(MB[n].PX,MB[n].PY,0);

                           MB[n].RUN=0;

                         }

              MB[n].LB--; /*延时*/


             }


          }










       for(n=0;n<30;n++)
          {
           if(EB[n].RUN==1)
             {
              if(EB[n].LB<=0)
                {
                 putpixel(EB[n].PX,EB[n].PY,0);

                 MOVE_TO2(EB[n].X1,EB[n].Y1,EB[n].X2,EB[n].Y2,&EB[n].PX,&EB[n].PY,10);

                 putpixel(EB[n].PX,EB[n].PY,14);

                 EB[n].LB=EB[n].MAX_LB;
                }


              if(MAP[ASK_MAP_AB(EB[n].PX,EB[n].PY,MAP_X0,MAP_Y0,15,2)][ASK_MAP_AB(EB[n].PX,EB[n].PY,MAP_X0,MAP_Y0,15,1)]!=0)

                         {   /*子弹碰墙 消失*/

                           putpixel(EB[n].PX,EB[n].PY,0);

                           EB[n].RUN=0;

                         }

              EB[n].LB--; /*延时*/


             }


          }










/*++++++++++++++++++++++++接触++++++++++++++++++++++++++++*/

 for(n=0;n<30;n++)
    {
     if(MB[n].RUN==1){



             for(i=0;i<5;i++)            /*接触*/
                {
                 if(T[i].LIVE==1){

                                  if(T[i].X1-7<=MB[n].PX
                                            &&
                                     T[i].X1+7>=MB[n].PX
                                            &&
                                     T[i].Y1-7<=MB[n].PY
                                            &&
                                     T[i].Y1+7>=MB[n].PY
                                    )

                                      {
                                       T[i].HP=T[i].HP-25;
                                       if(T[i].HP<=0)
                                              {
                                               T[i].LIVE=0;
                                               T[i].COLOR=12;
                                               GB_PERSON(T[i].X1,T[i].Y1,T[i].a,T[i].COLOR);
                                               Alert(T[i].X1-1,T[i].Y1-21,0);  /*擦去!*/

                                               KILL++;    LK++;
                                               setfillstyle(1,0);
                                               bar(485,5,533,22);
                                               setcolor(15);
                                               settextstyle(0,0,2);
                                               sprintf(KK,"%02d",KILL);
                                               outtextxy(500,7,KK);
                                               settextstyle(0,0,1);

                                              }


                                       MB[n].RUN=0;

                                       putpixel(MB[n].PX,MB[n].PY,0);




                                       }



                                  }

                 }/*for i*/

                    }

  }


/*++++++++++++++*/

 for(n=0;n<30;n++)
    {
     if(EB[n].RUN==1){



                  if(MAN.LIVE==1){

                                  if(MAN.X1-7<=EB[n].PX
                                            &&
                                     MAN.X1+7>=EB[n].PX
                                            &&
                                     MAN.Y1-7<=EB[n].PY
                                            &&
                                     MAN.Y1+7>=EB[n].PY
                                    )

                                      {
                                       MAN.HP=MAN.HP-5;
                                       if(MAN.HP<=0)
                                              {
                                               MAN.LIVE=0;
                                               MAN.COLOR=15;
                                               GB_PERSON(MAN.X1,MAN.Y1,MAN.a,MAN.COLOR);

                                              }

                                      DISPLAY_HP(MAN.HP);
                                       EB[n].RUN=0;

                                       putpixel(EB[n].PX,EB[n].PY,0);




                                       }



                                  }



                    }

  }



/*++++++++++++++++++++++++对按键的响应+++++++++++++++++++++++++++++*/


   if(GetKey(KEY_ESC))  {
                          END=1;
                        } 


   if(GetKey(KEY_UP))   {

                         MOVE_TO2(MAN.X1,MAN.Y1,MAN.X2,MAN.Y2,&MAN.X1,&MAN.Y1,3);

                         move=1;

                        }


   if(GetKey(KEY_LEFT))  {

                          MAN.a=MAN.a-9;
                          if(MAN.a>360) MAN.a=9;
                          else if(MAN.a<0)   MAN.a=351;

                          move=1;

                         }




    if(GetKey(KEY_RIGHT)){

                          MAN.a=MAN.a+9;
                          if(MAN.a>360) MAN.a=9;
                          else if(MAN.a<0)   MAN.a=351;

                          move=1;

                         }



   if(GetKey(KEY_DEL))   {
                          /*显示辅助线  不推荐 会花屏    */
                          if(cc==0) { ER(10);  cc=1; }

                          else      { ER(0);   cc=0; }
                         }


   if(GetKey(KEY_F2))    {
                          /*显示敌人的视觉线 不推荐 会花屏*/
                          if(EYE==1) { EYE=0; }

                          else       { EYE=1; }
                         }



   if(GetKey(KEY_SPACE)){

                         if(MAN.reload<=0){  /*装填时间*/

                                           for(n=0;n<30;n++)
                                              {
                                               if(MB[n].RUN==0){

                                                        MB[n].X2=MAN.X2;
                                                        MB[n].Y2=MAN.Y2;
                                                        MB[n].X1=MAN.X1;
                                                        MB[n].Y1=MAN.Y1;

                                                        MB[n].PX=MB[n].X1;
                                                        MB[n].PY=MB[n].Y1;

                                                        MB[n].RUN=1;

                                                        break;
                                                                }

                                               }
                                             MAN.reload=5;
                                           }

                         }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++对玩家的事件处理+++++++++++++++++++++++++++*/

                        if(MAN.LIVE==1)
                        {
                         if(move==1)
                           {     

                            GB_PERSON(MAN.X0,MAN.Y0,MAN.a0,0);


                           /*+++++++++++++++++++++++++++++++++++*/

                           MAN.MAP_A=ASK_MAP_AB(MAN.X1,MAN.Y1,MAP_X0,MAP_Y0,15,2);   /*得到新的MAP的位置*/
                           MAN.MAP_B=ASK_MAP_AB(MAN.X1,MAN.Y1,MAP_X0,MAP_Y0,15,1);

                           /*+++++++++++++++++++++++++++++++++++*/

                           if(MAP[MAN.MAP_A][MAN.MAP_B]==0)    /*0没有障碍*/
                             {
                              ;
                             }


                           else                                   /*有障碍*/
                             {
                              /*+++++++++++++++++++++++++++++++++++*/
                              if(MAP[MAN.MAP_A0][MAN.MAP_B0+(MAN.MAP_B-MAN.MAP_B0)]!=0)     /*特殊算法*/
                                {
                                 MAN.X1=MAN.X0;    MAN.MAP_B=MAN.MAP_B0;
                                }


                              if(MAP[MAN.MAP_A0+(MAN.MAP_A-MAN.MAP_A0)][MAN.MAP_B0]!=0)
                                {
                                 MAN.Y1=MAN.Y0;    MAN.MAP_A=MAN.MAP_A0;
                                } 


                              if(MAP[MAN.MAP_A0+(MAN.MAP_A-MAN.MAP_A0)][MAN.MAP_B0+(MAN.MAP_B-MAN.MAP_B0)]!=0 /*45度进入*/
                                                            &&
                                 MAP[MAN.MAP_A0][MAN.MAP_B0+(MAN.MAP_B-MAN.MAP_B0)]==0
                                                            &&
                                 MAP[MAN.MAP_A0+(MAN.MAP_A-MAN.MAP_A0)][MAN.MAP_B0]==0

                                )
                                {
                                 MAN.X1=MAN.X0;     MAN.MAP_B=MAN.MAP_B0;
                                 MAN.Y1=MAN.Y0;     MAN.MAP_A=MAN.MAP_A0;
                                } 

                                /*停止移动还原*/

                               /*+++++++++++++++++++++++++++++++++++*/
                              }

                                 MAP2[MAN.MAP_A0][MAN.MAP_B0]=0;
                                 MAP2[MAN.MAP_A][MAN.MAP_B]=1;

                              MAN.X2=Round(10*cos(MAN.a*PI/180))+MAN.X1;      /*生成新的目标点*/
                              MAN.Y2=Round(10*sin(MAN.a*PI/180))+MAN.Y1;


                            GB_PERSON(MAN.X1,MAN.Y1,MAN.a,MAN.COLOR);


                            MAN.X0=MAN.X1;
                            MAN.Y0=MAN.Y1;

                            MAN.MAP_A0=MAN.MAP_A;
                            MAN.MAP_B0=MAN.MAP_B;
                            MAN.a0=MAN.a;

                            move=0;

                         }
                        }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


     MAN.reload--;    /*装填时间变化*/
     if(MAN.reload<=0)   MAN.reload=0;

     DISPLAY_MAP(MAP_X0,MAP_Y0);   /*重画地图*/


     TimeDelay(30000L); /*游戏延时*/





      if(MAN.LIVE==0)            /*玩家失败*/
        {
         setfillstyle(1,1);
         bar(210-4,200-4,210+240,200+18);
         setcolor(15);
         settextstyle(0,0,2);
         outtextxy(210,200,"Terrorists Win!");
         settextstyle(0,0,1);
         outtextxy(210+40,200+30,"Please the waiting...");

         MAP2[MAN.MAP_A0][MAN.MAP_B0]=0;
         MAP2[MAN.MAP_A][MAN.MAP_B]=0;

         LIFE--;

         sleep(3);
         goto START;

        }


       if(LK>=5)                /*玩家胜利*/
         {
          setfillstyle(1,1);
          bar(140-4,200-4,140+366,200+18);
          setcolor(15);
          settextstyle(0,0,2);
          outtextxy(140,200,"Counter-Terrorists Win!");
          settextstyle(0,0,1);
          outtextxy(210+40,200+30,"Please the waiting...");

          MAP2[MAN.MAP_A0][MAN.MAP_B0]=0;
          MAP2[MAN.MAP_A][MAN.MAP_B]=0;

          sleep(3);
          goto START;
         }







 } /*while大循环末尾*/



 GAME_OVER:;

 closegraph();

 ShutDownKeyboard();   /*恢复键盘中断*/

}


/*=========================================================================*/


void set_color(int color,int R,int G,int B)      /*改变调色板*/
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

void VGA_RESET()                        /*图形模式初始化*/
{
 int driver=VGA;
 int mode=VGAHI;

 registerbgidriver(EGAVGA_driver);      /*图形模式独立运行*/
 initgraph(&driver,&mode,"");
 cleardevice();

 setpalette(4,36);                      /*改变调色板颜色*/
 setpalette(10,18);
 setpalette(13,45);
 setpalette(9,11);
 setpalette(1,9);

  setpalette(12,32);

set_color(7,112,112,112);
set_color(8,95,95,95);

}




void GB_PERSON(int X1,int Y1,int a,int COLOR)   /*绘制人物*/
{
 int X2,Y2;

 setcolor(COLOR);

 circle(X1,Y1,1);
 circle(X1,Y1,8);

 X2=Round(10*cos(a*PI/180))+X1;   /*r=10   弧度=角度*PI/180*/
 Y2=Round(10*sin(a*PI/180))+Y1;

 line(X1,Y1,X2,Y2);

}


void Alert(int x,int y,int color)   /*惊叹号!*/
{
 setfillstyle(1,color);
 bar(x,y,x+2,y+5);
 bar(x,y+7,x+2,y+8);
}



void MOVE_TO2(int X1,int Y1,int X2,int Y2,int *PX,int *PY,int SPEED)  /*移动到*/
{
 float k,b;
 float kz;   /*k的绝对值*/

 int m=0;      /*更靠近的轴*/
 int mx,my;  /*x y轴上增值*/

 int end=0;

 int SS=0;

  
/*斜线*/
     if(X1<X2&&Y1<Y2){mx=1;my=1;}

else if(X1>X2&&Y1>Y2){mx=-1;my=-1;}

else if(X1>X2&&Y1<Y2){mx=-1;my=1;}

else if(X1<X2&&Y1>Y2){mx=1;my=-1;}

/*直线*/
else if(X1<X2&&Y1==Y2){mx=1; m=2;}    /*左右*/

else if(X1>X2&&Y1==Y2){mx=-1; m=2;}   /*右左*/

else if(X1==X2&&Y1<Y2){my=1; m=3;}    /*上下*/

else if(X1==X2&&Y1>Y2){my=-1; m=3;}   /*下上*/

else if(X1==X2&&Y1==Y2)  { m=10;} 


if(m<2)
  {
 k=K_B(X1,Y1,X2,Y2,1);
 b=K_B(X1,Y1,X2,Y2,2);

 kz=k;                /*k的绝对值*/
 if(kz<0) kz=-kz;

     if(kz<1) m=1;    /*更靠近的轴*/
else if(kz>1) m=-1;
else if(kz==1) m=0;



  while(end!=1)
        {


         if(m==-1) /*更靠近y轴*/
           {


            *PY=*PY+my; /*y轴上增值*/

        *PX=Round(Z_X(*PY,k,b));

           }

    else if(m==1) /*更靠近x轴*/
           {

            *PX=*PX+mx; /*x轴上增值*/


        *PY=Round(Z_Y(*PX,k,b));

           }

    else if(m==0) /*45度*/
           {

            *PX=*PX+mx; /*x轴上增值*/

            *PY=*PY+my; /*y轴上增值*/


           }

       SS++;

       if(SS>=SPEED) end=1;
       


      }



 }


else if(m==2){

  while(end!=1)
        {

              *PX=*PX+mx; /*x轴上增值*/

       SS++;
 
       if(SS>=SPEED) end=1;

        }


             }


else if(m==3){

  while(end!=1)
        {
              *PY=*PY+my; /*y轴上增值*/

       SS++;
 
       if(SS>=SPEED) end=1;

         }
         }







}







float K_B(int x1,int y1,int x2,int y2,int n)
{float kz1,kz2;
 float k,b;
 kz1=x1-x2;
 kz2=y1-y2;
 k=kz2/kz1;
 b=y1-x1*k;
 if(n==1){return(k);}
 else if(n==2){return(b);}
 }

float Z_X(float y,float k,float b)
{float x;
 x=(y-b)/k;
 return(x);
}

float Z_Y(float x,float k,float b)
{float y;
 y=k*x+b;
 return(y);
}



int Round(float x)  /*四舍五入*/
{
 return((int)(x+0.5));
}



void PANE(int X1,int Y1,int B,int A,int L,int COLOR)
{

int x=X1;
int y=Y1;

int a=0;
int b=0;


   while(1)
   {

    putpixel(x,y,COLOR);

    x=x+L;

    b++;

    if(b>B){y=y+L;x=X1;b=0;a++;}

    if(a>A) break;

   }



}




void ER(int COLOR)
{
 char aa[2];
 char bb[2];
 int A=0;
 int B=0;

 int TX=0;
 int TY=0;

 int n;


 PANE(94,20,30,30,15,COLOR);

 setcolor(COLOR);

TX=94;
TY=1;

while(B<30)
{
n=B;
 sprintf(bb,"%02d",B);
 outtextxy(TX,TY,bb);

B=n;
 B++;
 TX=TX+15;

}


TX=64;
TY=24;

outtextxy(72,12,"A");
outtextxy(83,1,"B");

while(A<30)
{
n=A;
 sprintf(aa,"%02d",A);
 outtextxy(TX,TY,aa);

 TY=TY+15;
A=n;
 A++;

}



}



void DISPLAY_MAP(int MAP_X,int MAP_Y)         /*绘制地图*/
{

 int i,j,PX,PY;


 for(i=0;i<=29;i++)
    {
      for(j=0;j<=29;j++)
         {
               if(MAP[i][j]==0) {UNITNAME=&UNIT_00[0][0];}
          else if(MAP[i][j]==1) {UNITNAME=&UNIT_01[0][0];}
          else if(MAP[i][j]==2) {UNITNAME=&UNIT_02[0][0];}
          else if(MAP[i][j]==3) {UNITNAME=&UNIT_03[0][0];}
          else if(MAP[i][j]==4) {UNITNAME=&UNIT_04[0][0];}
          else if(MAP[i][j]==5) {UNITNAME=&UNIT_05[0][0];}
          else if(MAP[i][j]==6) {UNITNAME=&UNIT_06[0][0];}
          else if(MAP[i][j]==7) {UNITNAME=&UNIT_07[0][0];}
          else if(MAP[i][j]==8) {UNITNAME=&UNIT_08[0][0];}
          else if(MAP[i][j]==9) {UNITNAME=&UNIT_09[0][0];}
          else if(MAP[i][j]==10){UNITNAME=&UNIT_10[0][0];}


          PX=MAP_X+15*j;
          PY=MAP_Y+15*i;

      GB15(PX,PY,UNITNAME);
         }
    }






}




int ASK_MAP_AB(int x,int y,int bx,int by,int L,int N)
{

 int Z;

if(N==1)
  {
  Z=(x-bx)/L;
  }

else
  {
  Z=(y-by)/L;
  }

 return(Z);

}



void InstallKeyboard(void)          /*键盘中断程序*/
{
 int i;
 for(i=0;i<128;i++)
 key_state[i]=key_pressed[i]=0;
 OldInt9Handler=getvect(9);         /*中断向量值*/
 setvect(9,NewInt9);                /*中断程序NewInt9地址存入指定的中断向量表中INT 09H*/
}


void ShutDownKeyboard(void)
{
 setvect(9,OldInt9Handler);
}


void far interrupt NewInt9(void)
{
 unsigned char ScanCode,temp;
 ScanCode=inportb(0x60);
 temp=inportb(0x61);
 outportb(0x61,temp | 0x80);
 outportb(0x61,temp & 0x7f);
 if(ScanCode&0x80)
   {
    ScanCode&=0x7f;
    key_state[ScanCode]=0;
   }
else
   {
    key_state[ScanCode]=1;
    key_pressed[ScanCode]=1;
   }
 outportb(0x20,0x20);
}


int GetKey(int ScanCode)
{
 int res;
 res=key_state[ScanCode]|key_pressed[ScanCode];
 key_pressed[ScanCode]=0;
 return res;
}






void TimeDelay(unsigned long microsec) /*延时函数 传入微秒数*/
{
 union REGS r;
 r.h.ah=0x86;
 r.x.cx=microsec>>16;
 r.x.dx=microsec;
 int86(0x15,&r,&r);
}







double DZ(double X1,double Y1,double X2,double Y2)  /*两点距离*/
{
 double D;
 D=sqrt(fabs((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1)));

 return (D);

}



int ASK_a(int X1,int Y1,int X2,int Y2)   /*得到中心点到目标点的角度*/
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


   if(k>=-1&&k<=1){      /*防止asin()出错*/

   m=asin(k)/3.1415*180;

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







void DISPLAY_HP(int HP)
{
 int x;
 int HP_X=382;

 x=HP_X-(100-HP);

 setfillstyle(1,4);
 bar(282,6,382,20);

 if(HP!=100){
 setfillstyle(1,7);
 bar(x,6,382,20);
            }

}




