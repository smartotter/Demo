/*��꺯��*/

#define mbLeft 0
#define mbRight 1



int initmouse(void);       /*  ��ʼ�����   */
void getmousexy(void);	/* ȡ�����λ�� */
void setmmove(int x1,int y1,int x2,int y2);  /*��������ƶ���Χ */
void setmousexy(int x,int y);	/* �������λ�� */
int getmkeyin(int key);		/* ȡ����갴��������Ϣ 0�� 1�� */
int getmkeyout(int key);		/* ȡ����갴��̧����Ϣ 0�� 1�� */
void showmouse();
void hidemouse();
void SetGraphicCursor(int x,int y,unsigned int far *pattern);   /*�ı�����״*/
int MOUSE_IN_BOX(int x1,int y1,int x2,int y2);
void MouseSpeed(int vx,int vy);  /*��������ٶ�(ȱʡֵ:vx=8,vy=8)  ֵԽ���ٶ�Խ�� */








struct
{int x;
 int y;
 int getx;
 int gety;
}mouse;


/*-------------------------------------------------------------------------*/

unsigned int CURSOR[32]=
{
/*0011111111111111*/      0x3FFF,
/*0001111111111111*/      0x1FFF,
/*0000111111111111*/      0x0FFF,
/*0000011111111111*/      0x07FF,
/*0000001111111111*/      0x03FF,
/*0000000111111111*/      0x01FF,
/*0000000011111111*/      0x00FF,
/*0000000001111111*/      0x007F,
/*0000000000111111*/      0x003F,
/*0000000000011111*/      0x001F,
/*0000000111111111*/      0x01FF,
/*0001000011111111*/      0x10FF,
/*0011000011111111*/      0x30FF,
/*0111100001111111*/      0x787F,
/*1111100001111111*/      0xF87F,
/*1111110011111111*/      0xFCFF,


/*1100000000000000*/      0xC000,
/*1010000000000000*/      0xA000,
/*1001000000000000*/      0x9000,
/*1000100000000000*/      0x8800,
/*1000010000000000*/      0x8400,
/*1000001000000000*/      0x8200,
/*1000000100000000*/      0x8100,
/*1000000010000000*/      0x8080,
/*1000000001000000*/      0x8040,
/*1000001111100000*/      0x83E0,
/*1001001000000000*/      0x9200,
/*1010100100000000*/      0xA900,
/*1100100100000000*/      0xC900,
/*1000010010000000*/      0x8480,
/*0000010010000000*/      0x0480,
/*0000001100000000*/      0x0300,

};

/*-------------------------------------------------------------------------*/


int initmouse(void)       /*  ��ʼ�����   */
{int n;
 union REGS r;
 r.x.ax=0x0;
 int86(0x33,&r,&r);
 if (r.x.ax!=0)
 {
  getmousexy();                     /* ȡ�����λ�� */

  SetGraphicCursor(0,0,CURSOR);    /*�ı�����״*/

  setmmove(0,0,639,479);          /*��������ƶ���Χ */
  mouse.x=mouse.getx;
  mouse.y=mouse.gety;

  MouseSpeed(9,9);                /*��������ٶ�*/

  return 1;
 }
 else return 0;
}



void getmousexy(void)	/* ȡ�����λ�� */
{union REGS r;
 r.x.ax=0x3;
 int86(0x33,&r,&r);
 mouse.getx=r.x.cx;
 mouse.gety=r.x.dx;
}


void setmmove(int x1,int y1,int x2,int y2)  /*��������ƶ���Χ */
{union REGS r;
 r.x.ax=0x7;
 r.x.cx=x1;
 r.x.dx=x2;
 int86(0x33,&r,&r);
 r.x.ax=0x8;
 r.x.cx=y1;
 r.x.dx=y2;
 int86(0x33,&r,&r);
}


void setmousexy(int x,int y)	/* �������λ�� */
{union REGS r;
 r.x.ax=0x4;
 r.x.cx=x;
 r.x.dx=y;
 int86(0x33,&r,&r);
}

int getmkeyin(int key)		/* ȡ����갴��������Ϣ 0�� 1�� */
{union REGS r;
 r.x.ax=0x5;
 r.x.bx=key;
 int86(0x33,&r,&r);
 if(r.x.bx==1)return key;
 else return(key+1);
}

int getmkeyout(int key)		/* ȡ����갴��̧����Ϣ 0�� 1�� */
{union REGS r;
 r.x.ax=0x6;
 r.x.bx=key;
 int86(0x33,&r,&r);
 if(r.x.bx==1) return key;
 else return(key+1);
}


void showmouse()
{
 union REGS inregs,outregs;

 inregs.x.ax=1;               /*����1�Ź��� ��ʾ���*/
 int86(0x33,&inregs,&outregs);
}



void hidemouse()
{
 union REGS inregs,outregs;

 inregs.x.ax=2;               /*����2�Ź��� �������*/
 int86(0x33,&inregs,&outregs);
}



void SetGraphicCursor(int x,int y,unsigned int far *pattern)   /*�ı�����״*/
{
 union REGS ireg;
 struct SREGS isreg;

 ireg.x.ax=9;
 ireg.x.bx=x;
 ireg.x.cx=y;
 ireg.x.dx=FP_OFF(pattern);
 isreg.es=FP_SEG(pattern);

 int86x(0x33,&ireg,&ireg,&isreg);
}



void MouseSpeed(int vx,int vy)  /*��������ٶ�(ȱʡֵ:vx=8,vy=8)  ֵԽ���ٶ�Խ�� */
  {
   _CX=vx;
   _DX=vy;
   _AX=0x0f;
   geninterrupt(0x33);
  }



int MOUSE_IN_BOX(int x1,int y1,int x2,int y2)
{
 if(mouse.getx>=x1&&mouse.getx<=x2&&mouse.gety>=y1&&mouse.gety<=y2)
    return 1;
 else
    return 0;
}
