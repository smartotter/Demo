/*�����жϺ���*/

/*128������ɨ����*/

#define KEY_A 0x1E

#define KEY_B 0x30

#define KEY_C 0x2e

#define KEY_D 0x20

#define KEY_E 0x12

#define KEY_F 0x21

#define KEY_G 0x22

#define KEY_H 0x23

#define KEY_I 0x17

#define KEY_J 0x24

#define KEY_K 0x25

#define KEY_L 0x26

#define KEY_M 0x32

#define KEY_N 0x31

#define KEY_O 0x18

#define KEY_P 0x19

#define KEY_Q 0x10

#define KEY_R 0x13

#define KEY_S 0x1f

#define KEY_T 0x14

#define KEY_U 0x16

#define KEY_V 0x2f

#define KEY_W 0x11

#define KEY_X 0x2d

#define KEY_Y 0x15

#define KEY_Z 0x2c

#define KEY_1 0x02

#define KEY_2 0x03

#define KEY_3 0x04

#define KEY_4 0x05

#define KEY_5 0x06

#define KEY_6 0x07

#define KEY_7 0x08

#define KEY_8 0x09

#define KEY_9 0x0a

#define KEY_0 0x0b

#define KEY_DASH 0x0c /* _- */

#define KEY_EQUAL 0x0d /* += */

#define KEY_LBRACKET 0x1a /* {[ */

#define KEY_RBRACKET 0x1b /* }] */

#define KEY_SEMICOLON 0x27 /* :; */

#define KEY_RQUOTE 0x28 /* "' */

#define KEY_LQUOTE 0x29 /* ~` */

#define KEY_PERIOD 0x33 /* >. */

#define KEY_COMMA 0x34 /* <, */

#define KEY_SLASH 0x35 /* ?/ */

#define KEY_BACKSLASH 0x2b /* |\ */

#define KEY_F1 0x3b

#define KEY_F2 0x3c

#define KEY_F3 0x3d

#define KEY_F4 0x3e

#define KEY_F5 0x3f

#define KEY_F6 0x40

#define KEY_F7 0x41

#define KEY_F8 0x42

#define KEY_F9 0x43

#define KEY_F10 0x44

#define KEY_ESC 0x01

#define KEY_BACKSPACE 0x0e

#define KEY_TAB 0x0f

#define KEY_ENTER 0x1c

#define KEY_CONTROL 0x1d

#define KEY_LSHIFT 0x2a

#define KEY_RSHIFT 0x36

#define KEY_PRTSC 0x37

#define KEY_ALT 0x38

#define KEY_SPACE 0x39

#define KEY_CAPSLOCK 0x3a

#define KEY_NUMLOCK 0x45

#define KEY_SCROLLLOCK 0x46

#define KEY_HOME 0x47

#define KEY_UP 0x48

#define KEY_PGUP 0x49

#define KEY_MINUS 0x4a

#define KEY_LEFT 0x4b

#define KEY_CENTER 0x4c

#define KEY_RIGHT 0x4d

#define KEY_PLUS 0x4e

#define KEY_END 0x4f

#define KEY_DOWN 0x50

#define KEY_PGDOWN 0x51

#define KEY_INS 0x52

#define KEY_DEL 0x53



void InstallKeyboard(void);
void ShutDownKeyboard(void);
void far interrupt NewInt9(void);
int GetKey(int ScanCode);

char key_state[128],key_pressed[128];
void interrupt far (*OldInt9Handler)();





void InstallKeyboard(void)          /*�����жϳ���*/
{
 int i;
 for(i=0;i<128;i++)
 key_state[i]=key_pressed[i]=0;
 OldInt9Handler=getvect(9);         /*�ж�����ֵ*/
 setvect(9,NewInt9);                /*�жϳ���NewInt9��ַ����ָ�����ж���������INT 09H*/
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

