
#include "main.h"
#include "../global/debug.h"

/* The house map */
ObjectType map[HOUSE_HEIGHT][HOUSE_WIDTH];

/* Object for the house (track temperature, time, etc.) */
ObjectType houseObject;

/* Flags of which blocks have changed since the last display */
int update[HOUSE_HEIGHT][HOUSE_WIDTH];

int done = 0;	/* Flag to indicate when the program should exit */
Display *display;
GC gc;
Widget house;
Window win;
Pixmap pix;
pthread_mutex_t mapMutex;
pthread_mutex_t updateMutex;
pthread_mutex_t houseMutex;
pthread_mutex_t flagMutex;
int parseError;		/* Flag to indicate a parse error */
int serverShutdown;	/* Flag to indicate that the server is shutting down */
int connected = 0;	/* Flag to indicate if the client is connected */
int exposed = 0;
int modeMoveParent = 0;

