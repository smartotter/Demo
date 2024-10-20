/*打星星游戏   作者SZK8888  制作日期：03-10-26            */
/*鼠标控制方向 鼠标左键和空格键开火 （纯属无聊的射击游戏）*/

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

void GB_PERSON(int X1,int Y1,int a,int COLOR);   /*绘制角色*/

int Round(float x);  /*四舍五入*/

void TimeDelay(unsigned long microsec); /*延时函数 传入微秒数*/

void MOVE_TO3(int oa,float *PX,float *PY,int D);  /*移动到*/

void TRANSFORM(char filename[],int *NAME);        /*把图象文件置入数组*/

void GB_TBF(int x,int y,int *NAME);                             /*显示*/


int TimeDelayUnit(float t);

int Xrand(int A,int B);                                         /*随机数发生器A—B*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

main()
{

 int END=0; /*游戏结束*/


 int E_FIRE_ATTACK=90;

 int n,i,j;

 /*定义角色结构*/
 struct PERSON {
                int LIVE;

                float X1;           /*屏幕坐标*/
                float Y1;
                float X0;
                float Y0;

                int a;            /*角度*/
                int a0;

                int COLOR;

                int reload;

                int move;

                int fire;
 
               };


 struct PERSON MAN;    /*定义玩家*/



  /*定义子弹结构*/
 struct BB{
           int RUN;               /*是否运行 */
           float PX;              /*当前坐标X*/
           float PY;              /*当前坐标Y*/
           int oa;                /*目标角度 */
           int LB;                /*运行周期 */
           int MAX_LB;
          };

 struct BB MB[30];      /*玩家子弹*/

 struct BB SB[30];



  struct  blast{
           int RUN;               /*是否运行 */
           float PX;              /*当前坐标X*/
           float PY;              /*当前坐标Y*/

           int D_time;
                                  /*运行周期 */
           int MAX_D_time;
          };


  struct blast BBB[30];



 int STAR[30][30];

 int BLAST[30][30];







 int mx0;        /* 鼠标原来的位置 */


 struct time t;          /*系统时间*/
 int R;





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 VGA_RESET();               /*图形初始化*/

 InstallKeyboard();         /*键盘中断初始化*/

 initmouse();                  /* 鼠标初始化 */

 setmousexy(320,240);            /* 设置鼠标位置 */

 srand(Xrand(31,72456));

 gettime(&t);             /*取系统时间*/
 R=t.ti_hund;             /*R=毫秒*/
 srand(R);                /*产生真正的随机数种子*/

/*+++++++++++++++++++++GAME 开始+++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++初始化玩家++++++++++++++++++++++++++++*/

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


 /*+++++++++++++++++++++初始化子弹++++++++++++++++++++++++++++*/


 for(n=0;n<30;n++)   /*玩家子弹初始化*/
    {
     MB[n].RUN=0;
     MB[n].MAX_LB=2;
     MB[n].LB=MB[n].MAX_LB;
    }



 for(n=0;n<30;n++)   /*子弹初始化*/
    {
     SB[n].RUN=0;
     SB[n].MAX_LB=10;
     SB[n].LB=SB[n].MAX_LB;
    }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


 for(n=0;n<30;n++)   /*初始化*/
    {
     BBB[n].RUN=0;
     BBB[n].MAX_D_time=20;
     BBB[n].D_time=BBB[n].MAX_D_time;
    }
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

TRANSFORM("STAR.TBF",&STAR[0][0]);
TRANSFORM("BZ.TBF",&BLAST[0][0]);



GB_PERSON(MAN.X1,MAN.Y1,MAN.a,9);




  /*大循环开始*/

 while(END!=1)
{



/*++++++++++++++++++++++++子弹飞行++++++++++++++++++++++++++++*/

/*玩家的子弹*/

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

                         {   /*子弹碰墙 消失*/

                          setfillstyle(1,0);
                          bar(MB[n].PX,MB[n].PY,MB[n].PX+1,MB[n].PY+1);

                           MB[n].RUN=0;

                         }

              MB[n].LB--; /*延时*/


             }


          }





/*子弹*/

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

                         {   /*子弹碰墙 消失*/

                 setfillstyle(1,0);
                 bar(SB[n].PX,SB[n].PY,SB[n].PX+29,SB[n].PY+29);

                           SB[n].RUN=0;

                         }

              SB[n].LB--; /*延时*/


             }


          }

















/*++++++++++++++++++++++++接触TOUCH++++++++++++++++++++++++++++*/

/*玩家的子弹与敌人接触*/

 for(n=0;n<30;n++)
    {
     if(MB[n].RUN==1){



             for(i=0;i<30;i++)
                {
                 if(SB[i].RUN==1){

                                  if(SB[i].PX<=MB[n].PX   /*接触的范围*/
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


















/*爆炸*/

       for(n=0;n<30;n++)
          {
           if(BBB[n].RUN==1)
             {

              GB_TBF(BBB[n].PX,BBB[n].PY,&BLAST[0][0]);

              BBB[n].D_time--;


              if(BBB[n].D_time<=0)

                         {   /*消失*/

                           setfillstyle(1,0);
                           bar(BBB[n].PX,BBB[n].PY,BBB[n].PX+29,BBB[n].PY+29);

                           BBB[n].RUN=0;

                         }




             }


          }










if(TimeDelayUnit(0.5))
  {
                              /*电脑开火*/
  E_FIRE_ATTACK=random(100);




  if(E_FIRE_ATTACK<=90)
                        {

                         for(n=0;n<30;n++)
                            {
                             if(SB[n].RUN==0)
                               {
                                /*初始化一颗星星*/
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


  if(mouse.getx!=mx0)   /* 鼠标动了 x */
    {

      MAN.a+=mouse.getx-mx0;
      if(MAN.a>360) MAN.a=360;
      else if(MAN.a<180)   MAN.a=180;


            if(mouse.getx>=620){  setmousexy(320,240);  getmousexy(); }

     else   if(mouse.getx<=20) {  setmousexy(320,240);  getmousexy(); }

     MAN.move=1;

   }



 if(getmkeyin(mbLeft)==mbLeft) /*左键按下*/
   {
    MAN.fire=1;
   }

if(getmkeyout(mbLeft)==mbLeft)  /*左键鼠标抬起*/
  {
    MAN.fire=0;
  }




/*++++++++++++++++++++++++对按键的响应+++++++++++++++++++++++++++++*/

   /*退出*/
   if(GetKey(KEY_ESC))  {

                         END=1;

                        } 


   /*左转*/
   if(GetKey(KEY_LEFT))  {

                          MAN.a=MAN.a-3;
                          if(MAN.a>360) MAN.a=360;
                          else if(MAN.a<180)   MAN.a=180;

                          MAN.move=1;

                         }


    /*右转*/
    if(GetKey(KEY_RIGHT)){

                          MAN.a=MAN.a+3;
                          if(MAN.a>360) MAN.a=360;
                          else if(MAN.a<180)   MAN.a=180;

                          MAN.move=1;

                         }


    /*开火射击*/
   if(GetKey(KEY_SPACE)){
                         if(MAN.reload<=0){  /*装填时间*/
                                           for(n=0;n<30;n++)
                                              {
                                               if(MB[n].RUN==0)
                                                 {
                                                  /*初始化一颗子弹*/
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

/*++++++++++++++++++++++对玩家的事件处理+++++++++++++++++++++++++++*/

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





 if(MAN.fire==1) /*开火*/
  {
                         if(MAN.reload<=0){  /*装填时间*/
                                           for(n=0;n<30;n++)
                                              {
                                               if(MB[n].RUN==0)
                                                 {
                                                  /*初始化一颗子弹*/
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

     MAN.reload--;    /*装填时间变化*/
     if(MAN.reload<=0)   MAN.reload=0;

     TimeDelay(10000L); /*游戏延时*/


 } /*while大循环末尾*/



 GAME_OVER:;

 closegraph();

 ShutDownKeyboard();   /*恢复键盘中断*/





}









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








void GB_PERSON(int X1,int Y1,int a,int COLOR)   /*绘制*/
{
 int X2,Y2;

 setcolor(COLOR);
 setfillstyle(1,COLOR);

 circle(X1,Y1,12);

 bar(X1-1,Y1-1,X1+1,Y1+1);


 X2=Round(18*cos(a*PI/180))+X1;   /*r=10   弧度=角度*PI/180*/
 Y2=Round(18*sin(a*PI/180))+Y1;


 line(X1,Y1,X2,Y2);
 bar(X2-1,Y2-1,X2+1,Y2+1);

}



int Round(float x)  /*四舍五入*/
{
 return((int)(x+0.5));
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

void TRANSFORM(char filename[],int *NAME)        /*把图象文件置入数组*/
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

void GB_TBF(int x,int y,int *NAME)                             /*显示*/
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
