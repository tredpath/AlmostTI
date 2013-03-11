/** AlmostTI: portable TI calcs emulator *********************/
/**                                                         **/
/**                         Unix.c                          **/
/**                                                         **/
/** This file contains Unix-dependent subroutines and       **/
/** drivers. It includes screen drivers via Display.h.      **/
/**                                                         **/
/** Copyright (C) Marat Fayzullin 2009                      **/
/**     You are not allowed to distribute this software     **/
/**     commercially. Please, notify me, if you make any    **/
/**     changes to this file.                               **/
/*************************************************************/
#include "config.h"
#include "../TI85.h"
#include "../../EMULib/Console.h"
#include "../../EMULib/EMULib.h"
#include "../../EMULib/Sound.h"

#include <sys/keycodes.h>
#include <bps/dialog.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <bps/screen.h>
#include <bps/deviceinfo.h>

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define WIDTH       600                   						/* Buffer width      */
#define HEIGHT      (isPhysicalKeyboardDevice ? 600 : 1024)		/* Buffer height     */
#define TIWIDTH		(TI83_FAMILY?96:128)						/* TI display width  */
#define TIHEIGHT	64					  						/* TI display height */
#define XOFFSET     (WIDTH-(TIWIDTH)*(TI83_FAMILY?5:4))/2		/* Display offset    */
#define YOFFSET     63                    						/* Display offset    */
#define PORTRAIT

/* Combination of EFF_* bits */
int UseEffects  = 0;//EFF_SCALE|EFF_SAVECPU|EFF_MITSHM|EFF_VARBPP|EFF_SYNC;

int InMenu;                /* 1: In MenuTI85(), ignore keys  */
int UseStatic   = 1;       /* 1: Use static palette          */
int UseZoom     = 1;       /* Zoom factor (1=no zoom)        */
int UseSound    = 0;//22050;   /* Audio sampling frequency (Hz)  */
int SyncFreq    = 0;//60;      /* Sync frequency (0=sync off)    */
int FastForward;           /* Fast-forwarded UPeriod backup  */
int SndSwitch;             /* Mask of enabled sound channels */
int SndVolume;             /* Master volume for audio        */
byte KeyReady;             /* 1: Key has been pressed        */
Image OutImage;            /* Unix display image buffer      */
Image ScrImage;            /* TI85 display image buffer      */
unsigned int XPal[2];      /* Referenced from Common.h       */
unsigned int Black,White;
byte lastKeyTouch;

const char *Title = "AlmostTI-QNX 2.0"; /* Program version  */

void HandleKeys(unsigned int Key, int pressed);
void HandleMouse(int X, int Y, int State);
int LoadPNG(Image *Img,const char *FileName);

/** TouchMap[] ***********************************************/
/** This map translates on-screen rectangles into keys.     **/
/*************************************************************/
struct
{
	byte KeyCode;
	int X,Y,W,H;
} TouchMap[] =
{
	{ KBD_RIGHT,  501,480,41,69 },
	{ KBD_LEFT,   363,479,38,68 },
	{ KBD_UP,     405,448,96,35 },
	{ KBD_DOWN,   405,544,96,36 },

	{ KBD_F5,     459,369,105,40 },
	{ KBD_F4,     355,369,105,40 },
	{ KBD_F3,     251,369,105,40 },
	{ KBD_F2,     147,369,105,40 },
	{ KBD_F1,     44,369,105,40 },

	{ KBD_CLEAR,  455,590,101,53 },
	{ KBD_POWER,  455,647,101,53 },
	{ KBD_DIV,    455,704,101,53 },
	{ KBD_MUL,    455,760,101,53 },
	{ KBD_MINUS,  455,816,101,53 },
	{ KBD_PLUS,   455,872,101,53 },
	{ KBD_ENTER,  455,928,101,66 },

	{ KBD_CUSTOM, 352,590,101,53 },
	{ KBD_TAN,    352,647,101,53 },
	{ KBD_RPARENT,352,704,101,53 },
	{ KBD_9,      352,760,101,56 },
	{ KBD_6,      352,816,101,56 },
	{ KBD_3,      352,872,101,56 },
	{ KBD_SIGN,   352,928,101,56 },

	{ KBD_MORE,   249,477,101,53 },
	{ KBD_DEL,    249,533,101,53 },
	{ KBD_PRGM,   249,590,101,53 },
	{ KBD_COS,    249,647,101,53 },
	{ KBD_LPARENT,249,704,101,53 },
	{ KBD_8,      249,760,101,56 },
	{ KBD_5,      249,816,101,56 },
	{ KBD_2,      249,872,101,56 },
	{ KBD_DOT,    249,928,101,56 },

	{ KBD_EXIT,   146,477,101,53 },
	{ KBD_XVAR,   146,533,101,53 },
	{ KBD_STAT,   146,590,101,53 },
	{ KBD_SIN,    146,647,101,53 },
	{ KBD_EE,     146,704,101,53 },
	{ KBD_7,      146,760,101,56 },
	{ KBD_4,      146,816,101,56 },
	{ KBD_1,      146,872,101,56 },
	{ KBD_0,      146,928,101,56 },

	{ KBD_2ND,    44,477,101,53 },
	{ KBD_ALPHA,  44,533,101,53 },
	{ KBD_GRAPH,  44,590,101,53 },
	{ KBD_LOG,    44,647,101,53 },
	{ KBD_LN,     44,704,101,53 },
	{ KBD_SQR,    44,760,101,53 },
	{ KBD_COMMA,  44,816,101,53 },
	{ KBD_STO,    44,872,101,53 },
	{ KBD_ON,     44,928,101,53 },

	{ KBD_LAST,0,0,0,0 }
};

struct
{
	byte KeyCode;
	int nativeKeyCode;
} KeyboardMap[] =
{
	{ KBD_CLEAR,  KEYCODE_Y },
	{ KBD_POWER,  KEYCODE_H },
	{ KBD_DIV,    KEYCODE_B },
	{ KBD_MUL,    KEYCODE_O },
	{ KBD_MINUS,  KEYCODE_L },
	{ KBD_PLUS,   KEYCODE_DOLLAR },
	{ KBD_ENTER,  KEYCODE_RETURN },

	{ KBD_CUSTOM, KEYCODE_T },
	{ KBD_TAN,    KEYCODE_G },
	{ KBD_RPARENT,KEYCODE_V },
	{ KBD_9,      KEYCODE_NINE },
	{ KBD_6,      KEYCODE_SIX },
	{ KBD_3,      KEYCODE_THREE },
	{ KBD_SIGN,   KEYCODE_MINUS },

	{ KBD_PRGM,   KEYCODE_R },
	{ KBD_COS,    KEYCODE_F },
	{ KBD_LPARENT,KEYCODE_C },
	{ KBD_8,      KEYCODE_EIGHT },
	{ KBD_5,      KEYCODE_FIVE },
	{ KBD_2,      KEYCODE_TWO },
	{ KBD_DOT,    KEYCODE_PERIOD },

	{ KBD_STAT,   KEYCODE_E },
	{ KBD_SIN,    KEYCODE_D },
	{ KBD_EE,     KEYCODE_X },
	{ KBD_7,      KEYCODE_SEVEN },
	{ KBD_4,      KEYCODE_FOUR },
	{ KBD_1,      KEYCODE_ONE },
	{ KBD_0,      KEYCODE_ZERO },

	{ KBD_GRAPH,  KEYCODE_W },
	{ KBD_LOG,    KEYCODE_S },
	{ KBD_LN,     KEYCODE_Z },
	{ KBD_SQR,    KEYCODE_I },
	{ KBD_COMMA,  KEYCODE_K },
	{ KBD_STO,    KEYCODE_M },
	{ KBD_ON,     KEYCODE_SPACE },

	{ KBD_LAST,   0 }
};

/** InitMachine() ********************************************/
/** Allocate resources needed by machine-dependent code.    **/
/*************************************************************/
int InitMachine(void)
{
  int J;

  /* Initialize variables */
  UseZoom       = UseZoom<1? 1:UseZoom>5? 5:UseZoom;
  InMenu        = 0;
  FastForward   = 0;
  OutImage.Data = 0;
  KeyReady      = 0;

  /* Initialize system resources */
  if (!InitQNX(Title,UseZoom*WIDTH,UseZoom*HEIGHT))
	  return 0;

  /* Set visual effects */
  BPSSetEffects(UseEffects);

  /* Create main image buffer */
  if(!NewImage(&OutImage,WIDTH,HEIGHT)) { TrashQNX(); return(0); }
  ClearImage(&OutImage,PIXEL(0,0,0));
  CropImage(&ScrImage,&OutImage,(WIDTH-(((TI83_FAMILY?96:128))*(TI83_FAMILY?5:4)))/2,YOFFSET,(TI83_FAMILY?5:4)*TIWIDTH,4*TIHEIGHT);

  /* Initialize video to main image */
  SetVideo(&OutImage,0,0,WIDTH,HEIGHT);

  /* Set colors */
  XPal[0] = White = PIXEL(255,255,255);
  XPal[1] = Black = PIXEL(0,0,0);

  /* Attach keyboard handler */
  SetKeyHandler(HandleKeys);

  /* Attach mouse handler */
  SetMouseHandler(HandleMouse);

  /* Initialize sound */
  InitSound(UseSound,150);
  SndSwitch=(1<<4)-1;
  SndVolume=255/4;
  SetChannels(SndVolume,SndSwitch);

  /* Initialize sync timer if needed */
  if((SyncFreq>0)&&!SetSyncTimer(SyncFreq*UPeriod/100)) SyncFreq=0;

  /* Done */
  return(1);
}

void scaleTouchMap(double scaleX, double scaleY)
{
	int i = 0;
	while (TouchMap[i].KeyCode != KBD_LAST)
	{
		TouchMap[i].X = TouchMap[i].X * scaleX;
		TouchMap[i].W = TouchMap[i].W * scaleX;
		TouchMap[i].Y = TouchMap[i].Y * scaleY;
		TouchMap[i].H = TouchMap[i].H * scaleY;
		i++;
	}
}

/** TrashMachine() *******************************************/
/** Deallocate all resources taken by InitMachine().        **/
/*************************************************************/
void TrashMachine(void)
{
  FreeImage(&OutImage);
  TrashAudio();
  TrashQNX();
}

/** SetColor() ***********************************************/
/** Allocate new color.                                     **/
/*************************************************************/
void SetColor(byte N,byte R,byte G,byte B)
{
  /* Set requested color */
  XPal[N&1]=PIXEL(R,G,B);
}

/** PutImage() ***********************************************/
/** Put an image on the screen.                             **/
/*************************************************************/
void PutImage(void)
{
  /* Show rendered screen buffer */
  ShowVideo();
}

/** Keypad() *************************************************/
/** Poll the keyboard.                                      **/ 
/*************************************************************/
byte Keypad(void)
{
  BPSProcessEvents();
  return(IS_KBD(KBD_ON));
}

/** ShowBackdrop() *******************************************/
/** Show backdrop image with calculator faceplate.          **/
/*************************************************************/
int ShowBackdrop(const char *FileName)
{
	char *P;
	int J;
	const char* imgDir;
	if (isPhysicalKeyboardDevice)
		imgDir = "app/native/Backdropsq";
	else
		imgDir = "app/native/Backdrops";

	/* Load background image */
	if(!(P = (char*)malloc((imgDir ? strlen(imgDir) : 8) + 16)))
		J=0;
	else
	{
		strcpy(P,imgDir? imgDir:".");
		strcat(P,"/");
		strcat(P,FileName);
		J=LoadPNG(&OutImage,P);
		free(P);
	}

	return(J);
}

/** HandleKeys() *********************************************/
/** Key handler.                                            **/
/*************************************************************/
void HandleKeys(unsigned int Key, int pressed)
{
  if(InMenu||CPU.Trace) return;

  int i = 0;
  while (KeyboardMap[i].KeyCode != KBD_LAST)
  {
	  if (KeyboardMap[i].nativeKeyCode == Key)
	  {
		  if (pressed)
		  {
			  KBD_SET(KeyboardMap[i].KeyCode);
			  KeyReady = 1;
		  }
		  else
		  {
			  KBD_RES(KeyboardMap[i].KeyCode);
			  KeyReady = 1;
		  }
		  break;
	  }
  }
}

/** HandleMouse() *********************************************/
/** Mouse click/unclick handler.                             **/
/*************************************************************/
void HandleMouse(int X, int Y, int State)
{
	if (lastKeyTouch)
	{
		KBD_RES(lastKeyTouch);
		return;
	}
    int J;
    int Flags = State ? 0:CON_RELEASE;
    for(J=0;TouchMap[J].W;++J)
      if((X>=TouchMap[J].X)&&(Y>=TouchMap[J].Y))
        if((X<TouchMap[J].X+TouchMap[J].W)&&(Y<TouchMap[J].Y+TouchMap[J].H))
        {
          if (State)
          {
            KBD_SET(TouchMap[J].KeyCode);
          }
          else
          {
            KBD_RES(TouchMap[J].KeyCode);
          }
          break;
        }
}

/** Common.h *************************************************/
/** Common display drivers.                                 **/
/*************************************************************/
#include "../Common.h"


