#include<conio.h>
#include<dos.h>
#define SPEED 10
void sound1(int freq,int time);
void pause(int time);
main()
{
      int i,freq;
      int time=4*SPEED;
      char *qm="iddgwwwqqgfffddddfghhhggg ddgwwwqqgfff\
		ddgghjqqqqqwpggjhgddgqqq hhqwwqjjjggg\
		ddgwwwqqgfff ddgghjqqqqqq";
	while(*qm++!='\0')
	{
	  i=1;
	  switch(*qm)
	  {case 'k':
		 time=1*SPEED;
		 i=0;
		 break;
	   case 'l':
		 time=2*SPEED;
		 i=0;
		 break;
	   case 'i':
		 time=4*SPEED;
		 i=0;
		 break;
	   case 'o':
		 time=6*SPEED;
		 i=0;
		 break;
	   case 'p':
		 pause(time);
		 i=0;
		 break;
	   case 'a':
		 freq=523;
		 break;
	   case 'd':
		 freq=587;
		 break;
	    case 'f':
		   freq=698;
		  break;
	     case 'h':
		    freq=880;
		  break;
	      case 'j':
		     freq=998;
			    break;
		case 'z':
		       freq=262;
			      break;
	       case 'x':
		      freq=294;
			     break;
		case 'c':
		       freq=330;
			      break;
	      case 'v':
		     freq=349;
			    break;
	       case 'b':
		       freq=392;
			break;
	       case 'n':
		       freq=440;
		       break;
		case 'm':
			 freq=494;
				  break;
		case 'q':
			 freq=1047;
				  break;
		case 'w':
			 freq=1175;
				  break;
		case 'e':
			 freq=1319;
				  break;
		case 'r':
			 freq=1397;
			  break;
		case 't':
			 freq=2568;
				  break;
		case 'y':
			 freq=1760;
				  break;
		case 'u':
			 freq=1976;
				  break;
	       default:
			i=0;
			break;
		}
		if(i)
		sound1(freq,time);
	      }
  }
  void sound1(int freq,int time)
  {
       union{
	  long divisor;
	  unsigned char c[2];
	  }count;
       unsigned char ch;
       count.divisor=1193280/freq;
       outp(67,182);
       outp(66,count.c[0]);
       outp(66,count.c[1]);
       ch=inp(97);
       outp(97,ch|3);
       pause(time);
       outp(97,ch);
    }
  void pause(int time)
  {
    int t1,t2;
    union REGS in,out;
    in.h.ah=0x2c;
    int86(0x21,&in,&out);
    t1=t2=100*out.h.dh+out.h.dl;
    while(t2-t1<time)
    {
       int86(0x21,&in,&out);
       t2=100*out.h.dh+out.h.dl;
       if(t2<t1)t2+=6000;
    }
  }