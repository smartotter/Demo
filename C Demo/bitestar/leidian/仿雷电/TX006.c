/*飞行特训2003    作者SZK8888     制作日期：03-10-28           */
/*方向键控制移动  不要被子弹打中，坚持的时间越久你就越牛B!     */

#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include "KEY.c"

#define PI 3.1415927

#define GAME_SPEED 200      /*游戏速度*/

#define BULLET_SUM 50         /*敌人子弹的数量*/

#define PLAYER_MOVE_SPEED 2   /*玩家移动速度*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void VGA_RESET();                            /*图形模式初始化*/
void set_color(int color,int R,int G,int B); /*改变调色板颜色*/

void TimeDelay(unsigned long microsec); /*延时函数 传入微秒数*/

void MOVE_TO3(int oa,float *PX,float *PY,int D);  /*移动到*/

void TRANSFORM(char filename[],int *NAME);        /*把TBF图象文件置入数组*/

void GB_TBF(int x,int y,int *NAME);               /*显示TBF图片数组*/

int TimeDelayUnit(float t);  /*时间中断判断*/

int Xrand(int A,int B);      /*随机数发生器A—B*/

int ASK_a(int X1,int Y1,int X2,int Y2);   /*得到中心点到目标点的角度*/

double DZ(double X1,double Y1,double X2,double Y2);  /*两点距离*/

void DISPLAY_HP(int HP);             /*显示HP*/

void SOUND(int h,int t);             /* 提示音 */

void GB_BULLET(int x,int y,int mode);   /*画子弹*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

main()
{

 int END=0; /*游戏结束*/

 int n,i,j; /*临时的参数*/


 /*定义玩家结构*/
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

 struct player P; /*定义玩家*/


 /*定义子弹结构*/
 struct BB{
           int RUN;               /*是否运行 */
           float PX;              /*当前坐标X*/
           float PY;              /*当前坐标Y*/
           int oa;                /*目标角度 */
           int LB;                /*运行周期 */
           int MAX_LB;
          };

 struct BB EB[BULLET_SUM];  /*定义敌人子弹*/




 /*定义TBF图片数组*/
 int PLANE[30][30];

 int BLAST[30][30];



 struct time t;   /*系统时间*/
 int R;           /*由当前系统时间产生真正的随机数种子*/


 int TimeM=0;     /*时间 分*/
 int TimeS=0;     /*时间 秒*/
 char TM[3];
 char TS[3];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 VGA_RESET();             /*图形初始化*/

 InstallKeyboard();       /*键盘中断初始化*/

 gettime(&t);             /*取系统时间*/
 R=t.ti_hund;             /*R=毫秒*/
 srand(R);                /*产生真正的随机数种子*/

 P.LIFE=3;                /*玩家的命*/

 TRANSFORM("PLANE.TBF",&PLANE[0][0]);   /*加载TBF格式图片*/
 TRANSFORM("BZ2.TBF",&BLAST[0][0]);

/*+++++++++++++++++++++GAME 开始+++++++++++++++++++++++++++++*/
 START:;
/*+++++++++++++++++++++初始化玩家++++++++++++++++++++++++++++*/

P.X1=300;
P.Y1=240;
P.X0=P.X1;
P.Y0=P.Y1;
P.HP=100;
P.LIVE=1;
P.move=0;

 /*+++++++++++++++++++++初始化子弹++++++++++++++++++++++++++++*/

 for(n=0;n<BULLET_SUM;n++)   /*敌人子弹初始化*/
    {
     EB[n].RUN=0;
     EB[n].MAX_LB=4;
     EB[n].LB=EB[n].MAX_LB;
    }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 cleardevice();   /*清屏*/


 if(P.LIFE<=0)           /*玩家没命了 GAME OVER 游戏结束*/
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



    sleep(3); /*等待3秒*/

    END=1;

    goto GAME_OVER;
   }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


GB_TBF(P.X1,P.Y1,&PLANE[0][0]);




 setcolor(15);
 settextstyle(0,0,2);
 outtextxy(60,10,"LIFE");

  for(n=130,i=0;i<P.LIFE;n+=24,i++)  /*绘制共有几条命*/
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

 /*大循环开始*/

 while(END!=1)
{






/*++++++++++++++++++++++++子弹飞行++++++++++++++++++++++++++++*/



/*敌人的子弹*/

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




              if(EB[n].PX<=40||EB[n].PX>=600||EB[n].PY<=40||EB[n].PY>=440)  /*子弹碰墙 消失*/
                {

                 GB_BULLET(EB[n].PX,EB[n].PY,0);

                 EB[n].RUN=0;

                }



              EB[n].LB--; /*延时*/


             }


          }











/*++++++++++++++++++++++++判断接触TOUCH++++++++++++++++++++++++++++*/

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

                                       P.HP=P.HP-5;    /*击中玩家，HP-5*/

                                       if(P.HP<=0)
                                              {
                                               P.LIVE=0;
                                              }


                                       DISPLAY_HP(P.HP);


                                       SOUND(450,1200); /*提示音*/

                                       GB_BULLET(EB[n].PX,EB[n].PY,0);

                                       EB[n].RUN=0;



                                       }



                                  }



                    }

  }



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/






/*初始化一颗子弹*/

for(n=0;n<BULLET_SUM;n++)
   {
    if(EB[n].RUN==0)
      {

        i=Xrand(1,5); /*确定敌人子弹的启始点 4种可能性*/

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

        EB[n].oa=ASK_a(EB[n].PX,EB[n].PY,P.X1+16,P.Y1+16);  /*确定敌人子弹的目标点*/

        EB[n].RUN=1;

     }

  }





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*时间中断处理*/
if(TimeDelayUnit(1.0)){

                       setfillstyle(1,0);
                       bar(503,7,503+80,7+19);

                       setcolor(10);  /*设置字体颜色 时间*/


                       TimeS++;
                       if(TimeS==60) { TimeS=0; TimeM++; }  /*IF满60秒为1分钟*/

                            sprintf(TM,"%02d",TimeM);

                            outtextxy(506,10,TM);

                                outtextxy(536,10,":");

                            sprintf(TS,"%02d",TimeS);

                            outtextxy(551,10,TS);

                      }






/*++++++++++++++++++++++++对按键的响应+++++++++++++++++++++++++++++*/

   /*退出*/
   if(GetKey(KEY_ESC))  {

                         END=1;

                        } 
   /*向上*/
   if(GetKey(KEY_UP))
                        {
                         P.Y1-=PLAYER_MOVE_SPEED;

                         if(P.Y1<=40) P.Y1=P.Y0;

                         P.move=1;
                        }
   /*向下*/
   if(GetKey(KEY_DOWN))
                        {
                         P.Y1+=PLAYER_MOVE_SPEED;

                         if(P.Y1>=420) P.Y1=P.Y0;

                         P.move=1;
                        }
   /*左平移*/
   if(GetKey(KEY_LEFT))
                        {
                         P.X1-=PLAYER_MOVE_SPEED;

                         if(P.X1<=40) P.X1=P.X0;

                         P.move=1;
                        }
   /*右平移*/
   if(GetKey(KEY_RIGHT))
                        {
                         P.X1+=PLAYER_MOVE_SPEED;

                         if(P.X1>=580) P.X1=P.X0;

                         P.move=1;
                        }





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++对玩家的事件处理+++++++++++++++++++++++++++*/
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



     TimeDelay(GAME_SPEED); /*游戏延时*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

      if(P.LIVE==0)            /*玩家失败*/
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


 } /*while大循环末尾*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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





void TimeDelay(unsigned long microsec) /*延时函数 传入微秒数*/
{
 union REGS r;
 r.h.ah=0x86;
 r.x.cx=microsec>>16;
 r.x.dx=microsec;
 int86(0x15,&r,&r);
}




void MOVE_TO3(int oa,float *PX,float *PY,int D)  /*移动到*/
{
 *PX+=D*cos(oa*PI/180);
 *PY+=D*sin(oa*PI/180);
}






void TRANSFORM(char filename[],int *NAME)    /*把TBF图象文件置入数组*/
{
 int i,j;
 char C;
 FILE *fp;

 if((fp=fopen(filename,"r"))==NULL)  /*打开一个文件只读*/
  {

 sound(450);
 delay(1200);
 nosound();
         /*失败画白方块*/
   return;
  }


 for(i=0;i<=29;i++)
    {
     for(j=0;j<=29;j++)
        {
          C=fgetc(fp);
          *(NAME+(i*30+j))=(int)(C-65);  /*还原数字-65*/
        }
    }


 fclose(fp);

}




void GB_TBF(int x,int y,int *NAME)        /*显示TBF图片数组*/
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







int TimeDelayUnit(float t)                         /*计时  t秒*/
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



int Xrand(int A,int B)    /*随机数发生器A—B*/
{
 int i,x;

 while(1)
    {
     x=random(B);

     if(x>=A) break;

    }

 return(x);

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




void DISPLAY_HP(int HP)    /*显示玩家的HP值*/
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



void GB_BULLET(int x,int y,int mode)   /*画子弹*/
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
