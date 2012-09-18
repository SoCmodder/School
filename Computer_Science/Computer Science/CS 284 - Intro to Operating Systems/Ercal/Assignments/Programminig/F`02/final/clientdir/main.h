
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <Xm/DrawingA.h>
#include <Xm/MainW.h>
#include <Xm/ScrolledW.h>
#include <Xm/DrawingA.h>
#include <Xm/PushB.h>
#include <Xm/PanedW.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <X11/xpm.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>  
#include <pthread.h>

#include "../global/proto.h"

#define HOUSE_WIDTH		30
#define HOUSE_HEIGHT		30
#define SPRITE_WIDTH		16
#define SPRITE_HEIGHT	16

#define LEVEL_COUNT		2

typedef void (*CallBackType)(Widget, XtPointer, XtPointer);

extern ObjectType map[HOUSE_HEIGHT][HOUSE_WIDTH];
extern int update[HOUSE_HEIGHT][HOUSE_WIDTH];

extern int done;
extern Display *display;
extern GC gc;
extern Widget house;
extern Window win;
extern Pixmap pix;
extern pthread_mutex_t mapMutex;
extern pthread_mutex_t updateMutex;
extern pthread_mutex_t houseMutex;
extern pthread_mutex_t flagMutex;
extern int parseError;
extern int serverShutdown; 
extern int connected;
extern int exposed;
extern int modeMoveParent;

#endif

