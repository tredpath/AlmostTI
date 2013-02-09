/** AlmostTI: portable TI calcs emulator *********************/
/**                                                         **/
/**                          ATI85.c                        **/
/**                                                         **/
/** This file contains generic main() procedure statrting   **/
/** the emulation.                                          **/
/**                                                         **/
/** Copyright (C) Marat Fayzullin 1994-2009                 **/
/**     You are not allowed to distribute this software     **/
/**     commercially. Please, notify me, if you make any    **/
/**     changes to this file.                               **/
/*************************************************************/

#include "config.h"
#include "../EMULib/EMULib.h"
#include "TI85.h"
#include "Help.h"
#include "QNX/QNXMenu.h"

#include <bps/bps.h>
#include <bps/navigator.h>
#include <bps/dialog.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char *Options[]=
{ 
  (char*)"ti82",(char*)"ti83",(char*)"ti83+",(char*)"ti83se",(char*)"ti84",(char*)"ti84+",(char*)"ti84se",(char*)"ti85",(char*)"ti86",
  (char*)"verbose",(char*)"uperiod",(char*)"help",(char*)"home",(char*)"link",(char*)"trap",
  (char*)"shm",(char*)"noshm",(char*)"saver",(char*)"nosaver",
  (char*)0
};

extern int   UseEffects; /* Platform-dependent effects          */
extern int   SyncScreen; /* Sync screen updates (#ifdef MSDOS)  */
extern int   FullScreen; /* Use 320x240 VGA (#ifdef MSDOS)      */
static Image OutImg;
extern Image OutImage;
extern Image ScrImage;

#ifdef __BBTEN__
int almostti_main(char* romname)
#else
int main(int argc,char *argv[])
#endif
{
	bps_initialize();

	dialog_request_events(0);
	//if (!UpdateRomList())
	//	exit(-1);

    int M, T;

    int N,J,I;

#ifdef DEBUG
    CPU.Trap  = 0xFFFF;
    CPU.Trace = 0;
#endif

#if defined(UNIX) || defined(MAEMO) || (defined(__QNXNTO__) && !defined(__BBTEN__))
    ARGC = argc;
    ARGV = argv;
#endif

#if defined(MSDOS) || defined(WINDOWS)
	/* No separate console, so no messages */
	Verbose=0;
	/* Figure out program directory name */
	ProgDir=GetFilePath(argv[0]);
//TODO asdf
#elif defined(__QNXNTO__) && !defined(__BBTEN__)
	Verbose=5;
	ProgDir = "shared/misc/TI/ROM";
#endif

#ifndef __BBTEN__
	if (navigator_request_events(0) != BPS_SUCCESS)
	{
		bps_shutdown();
		return 0;
	}
#endif

	//if ((M = AutoLoadRom(T, true)) < 0)
	//{
	//	bps_shutdown();
	//	return 0;
	//}
	strcpy(TIFilename, romname);
	T = WhichTI(TIFilename, M);
	Mode=(Mode&~ATI_MODEL)|T;
	Mode=(Mode&~ATI_MODEL)|T;

	if(!InitMachine()) return(1);

	RAMFile = (char*)malloc(sizeof(char)*strlen(Config[M].RAMFile));
	strcpy(RAMFile, Config[M].RAMFile);

#ifdef __BBTEN__
	StartTI85();
#else
	while (!StartTI85())
	{
		if ((M = AutoLoadRom(T, true)) < 0)
		{
			bps_shutdown();
			return 0;
		}
		free(RAMFile);
		RAMFile = (char*)malloc(sizeof(char)*strlen(Config[T].RAMFile));
		strcpy(RAMFile, Config[T].RAMFile);
		FreeImage(&OutImg);
		NewImage(&OutImage,600,1024);
		ClearImage(&OutImage,PIXEL(0,0,0));
		CropImage(&ScrImage,&OutImage,(600-((TI83_FAMILY?96:128))*(TI83_FAMILY?5:4))/2,63,4*(TI83_FAMILY?96:128),4*64);
		SetVideo(&OutImage,0,0,600,1024);
	}
#endif
	TrashTI85();
	TrashMachine();

	free(RAMFile);

	bps_shutdown();

	return(0);
}
