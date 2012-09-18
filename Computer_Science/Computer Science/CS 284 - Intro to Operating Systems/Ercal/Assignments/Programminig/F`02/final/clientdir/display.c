/***************************************************************************
 * Functions to handle drawing the house.
 ***************************************************************************/

#include "main.h"
#include "display.h"
#include "client.h"
#include "event.h"
#include "../global/debug.h"

/* Path to the XPM images */
#define XPM_PATH		"xpm/"

/* Number of animation states */
#define STATE_COUNT	3

/* Maximum number of images for the house */
#define IMAGE_COUNT	50

/* Struct for the block type to image file name mapping */
typedef struct {
	BlockType block;
	const char *file;
} ImageLoadMapType;

/* Struct for the block type to animated types mapping */
typedef struct {
	BlockType block;
	BlockType states[STATE_COUNT];
} AnimatedObjectType;

/* Enumeration to image file mapping */
static const ImageLoadMapType imageLoadMap[] = {
	{ TYPE_GRASS,			"grass.xpm"			},
	{ TYPE_FLOOR,			"floor.xpm"			},
	{ TYPE_WALL,			"wall.xpm"			},
	{ TYPE_DOOR,			"door.xpm"			},
	{ TYPE_WINDOW,			"window.xpm"		},
	{ TYPE_BED,				"bed.xpm"			},
	{ TYPE_DRESSER,		"dresser.xpm"		},
	{ TYPE_LAMP,			"lamp.xpm"			},
	{ TYPE_TV,				"tv.xpm"				},
	{ TYPE_SOFA,			"sofa.xpm"			},
	{ TYPE_TABLE,			"table.xpm"			},
	{ TYPE_CHAIR,			"chair.xpm"			},
	{ TYPE_SINK,			"sink.xpm"			},
	{ TYPE_TOILET,			"toilet.xpm"		},
	{ TYPE_FRIDGE,			"fridge.xpm"		},
	{ TYPE_STOVE,			"stove.xpm"			},
	{ TYPE_SHOWER,			"shower.xpm"		},

	{ TYPE_DOOR_OPEN,		"door-open.xpm"	},
	{ TYPE_WINDOW_OPEN,	"window-open.xpm"	},
	{ TYPE_LAMP_ON,		"lamp-on.xpm"		},
	{ TYPE_TOILET_DIRTY,	"toilet-dirty.xpm"},
	{ TYPE_STOVE_ON,		"stove-on.xpm"		},

	{ TYPE_KID,				"kid1.xpm"			},

	{ TYPE_TV_ON1,			"tv-on1.xpm"		},
	{ TYPE_TV_ON2,			"tv-on2.xpm"		},
	{ TYPE_TV_ON3,			"tv-on3.xpm"		},

	{ TYPE_SHOWER_ON1,	"shower-on1.xpm"	},
	{ TYPE_SHOWER_ON2,	"shower-on2.xpm"	},
	{ TYPE_SHOWER_ON3,	"shower-on3.xpm"	},

	{ TYPE_KID1,			"kid1.xpm"			},
	{ TYPE_KID2,			"kid2.xpm"			},
	{ TYPE_KID3,			"kid3.xpm"			},

	{ TYPE_SINK_ON1,		"sink-on1.xpm"		},
	{ TYPE_SINK_ON2,		"sink-on2.xpm"		},
	{ TYPE_SINK_ON3,		"sink-on3.xpm"		},

	{ TYPE_FRIDGE_ON1,	"fridge-on1.xpm"	},
	{ TYPE_FRIDGE_ON2,	"fridge-on2.xpm"	},
	{ TYPE_FRIDGE_ON3,	"fridge-on3.xpm"	},

	{ TYPE_BIGBED,			"bigbed.xpm"		},

	{ TYPE_PERSON,			"person1.xpm"		},
	{ TYPE_PERSON1,		"person1.xpm"		},
	{ TYPE_PERSON2,		"person2.xpm"		},
	{ TYPE_PERSON3,		"person3.xpm"		},

	{ TYPE_HOUSE,		NULL					}
};

/* Map block types to animated types */
static const AnimatedObjectType animatedObjects[] = {

	{ TYPE_HOUSE,
		{ TYPE_HOUSE, TYPE_HOUSE, TYPE_HOUSE }
	},

	{ TYPE_GRASS,
		{ TYPE_GRASS, TYPE_GRASS, TYPE_GRASS }
	},

	{ TYPE_FLOOR,
		{ TYPE_FLOOR, TYPE_FLOOR, TYPE_FLOOR }
	},

	{ TYPE_WALL,
		{ TYPE_WALL, TYPE_WALL, TYPE_WALL }
	},

	{ TYPE_BED,
		{ TYPE_BED, TYPE_BED, TYPE_BED }
	},

	{ TYPE_BIGBED,
		{ TYPE_BIGBED,TYPE_BIGBED, TYPE_BIGBED }
	},

	{ TYPE_DRESSER,
		{ TYPE_DRESSER, TYPE_DRESSER, TYPE_DRESSER }
	},

	{ TYPE_SOFA,
		{ TYPE_SOFA, TYPE_SOFA, TYPE_SOFA }
	},

	{ TYPE_TABLE,
		{ TYPE_TABLE, TYPE_TABLE, TYPE_TABLE }
	},

	{ TYPE_CHAIR,
		{ TYPE_CHAIR, TYPE_CHAIR, TYPE_CHAIR }
	},

	{ TYPE_DOOR,
		{ TYPE_DOOR_OPEN, TYPE_DOOR_OPEN, TYPE_DOOR_OPEN }
	},

	{ TYPE_WINDOW,
		{ TYPE_WINDOW_OPEN, TYPE_WINDOW_OPEN, TYPE_WINDOW_OPEN }
	},

	{ TYPE_SINK,
		{ TYPE_SINK_ON1, TYPE_SINK_ON2, TYPE_SINK_ON3 }
	},

	{ TYPE_TOILET,
		{ TYPE_TOILET_DIRTY, TYPE_TOILET_DIRTY, TYPE_TOILET_DIRTY }
	},

	{ TYPE_FRIDGE,
		{ TYPE_FRIDGE_ON1, TYPE_FRIDGE_ON2, TYPE_FRIDGE_ON3 }
	},

	{ TYPE_STOVE,
		{ TYPE_STOVE_ON, TYPE_STOVE_ON, TYPE_STOVE_ON }
	},

	{ TYPE_SHOWER,
		{ TYPE_SHOWER_ON1, TYPE_SHOWER_ON2, TYPE_SHOWER_ON3 }
	},

	{ TYPE_LAMP,
		{ TYPE_LAMP_ON, TYPE_LAMP_ON, TYPE_LAMP_ON }
	},

	{ TYPE_TV,
		{ TYPE_TV_ON1, TYPE_TV_ON2, TYPE_TV_ON3 }
	},

	{ TYPE_KID,
		{ TYPE_KID1, TYPE_KID2, TYPE_KID3 }
	},

	{ TYPE_PERSON,
		{ TYPE_PERSON1, TYPE_PERSON2, TYPE_PERSON3 }
	}

};

static XImage *images[IMAGE_COUNT];

/* Coordinates of the highlighted block in the house */
static int hx = 0, hy = 0;

/* Current animation state */
static int state = 0;

static void UpdateHouseData();
static void LoadImages();

/***************************************************************************
 * Create a button.
 ***************************************************************************/
Widget CreateButton(char *label, Widget parent, CallBackType callback) {
	Widget button;
	XmString labelString;
	labelString = XmStringCreateLocalized(label);
	button = XtVaCreateManagedWidget("button",
		xmPushButtonWidgetClass, parent,
		XmNlabelString, labelString, NULL);
	XmStringFree(labelString);
	XtAddCallback(button, XmNactivateCallback, callback, NULL);
	return button;
}

/***************************************************************************
 * Set the coordinates of the highlighted block in the house.
 * (x, y) are 0 based and indicated indices in the house matrix.
 ***************************************************************************/
void SetHighlight(int x, int y) {
	int tx, ty;
	int a, b;
	char str[32];
	int temp;

	pthread_mutex_lock(&flagMutex);
	temp = connected;
	pthread_mutex_unlock(&flagMutex);

	if(temp) {

		pthread_mutex_lock(&updateMutex);
		update[hy][hx] = 1;
		pthread_mutex_unlock(&updateMutex);

		hx = x;
		hy = y;
		if(hx < 0 || hx >= HOUSE_WIDTH) {
			hx = 0;
		}
		if(hy < 0 || hy >= HOUSE_HEIGHT) {
			hy = 0;
		}

		pthread_mutex_lock(&mapMutex);
		if(!map[hy][hx].type) {
			/* Expand around the selected block in squares */
			for(a = b = 1; b; a++) {
				for(ty = hy; b && hy - ty < a; ty--) {
					for(tx = hx; b && hx - tx < a; tx--) {
						switch(map[ty][tx].type) {
						case TYPE_HOUSE:
						case TYPE_FLOOR:
						case TYPE_WINDOW:
						case TYPE_DOOR:
						case TYPE_WALL:
						case TYPE_GRASS:
							break;
						default:
							hx = tx;
							hy = ty;
							b = 0;
							break;
						}
					}
				}
			}
		}
		pthread_mutex_unlock(&mapMutex);
		pthread_mutex_lock(&updateMutex);
		update[hy][hx] = 1;
		pthread_mutex_unlock(&updateMutex);
	}

	snprintf(str, 32, "%d,%d", hx + 1, hy + 1);

	XtVaSetValues(voice, XmNvalue, str, NULL);

	SetForChange(hx, hy);

}

/***************************************************************************
 * Return the x coordinate of the highlighted block in the house.
 ***************************************************************************/
int GetXPosition() {
	return hx;
}

/***************************************************************************
 * Return the y coordinate of the highlighted block in the house.
 ***************************************************************************/
int GetYPosition() {
	return hy;
}

/***************************************************************************
 * Set animations to the next state.
 ***************************************************************************/
void UpdateAnimations() {
	state = (state + 1) % STATE_COUNT;
}

/***************************************************************************
 * Copy the buffered image of the house to the screen.
 ***************************************************************************/
void RedrawMap() {
	static int first = 1;
	int temp;

	pthread_mutex_lock(&flagMutex);
	temp = exposed;
	pthread_mutex_unlock(&flagMutex);
	if(!temp) {
		return;
	}

	if(first) {
		first = 0;
		DisplayMap();
	} else if(connected) {
		XCopyArea(display, pix, win, gc, 0, 0,
			(1 + HOUSE_WIDTH) * SPRITE_WIDTH,
			(1 + HOUSE_HEIGHT) * SPRITE_HEIGHT,
			0, 0);
	}

}

/***************************************************************************
 * Update the data and controls for the house.
 ***************************************************************************/
void UpdateHouseData() {
	XmString labelString;
	char str[12];
	int currentMinute, currentHour;
	int currentTemp;
	int temp;

	pthread_mutex_lock(&flagMutex);
	temp = connected;
	pthread_mutex_unlock(&flagMutex);

	if(temp) {
		pthread_mutex_lock(&houseMutex);
		currentTemp = houseObject.level[0];
		currentMinute = houseObject.level[1] & 0xFF;
		currentHour = houseObject.level[1] >> 8;
		pthread_mutex_unlock(&houseMutex);

		XtVaSetValues(temperature, XmNvalue, currentTemp, NULL);

		snprintf(str, 12, "Time: %2d:%02d", currentHour, currentMinute);
		labelString = XmStringCreateLocalized(str);
		XtVaSetValues(timeDisplay, XmNlabelString, labelString, NULL);
		XmStringFree(labelString);
	}

}

/***************************************************************************
 * Load the images for the house from the files.
 ***************************************************************************/
void LoadImages() {
	XImage *tempImage;
	char *fileName;
	int x, y;

	display = XtDisplay(house);
	win = XtWindow(house);
	gc = XCreateGC(display, RootWindowOfScreen(XtScreen(house)), 0, NULL);
	pix = XCreatePixmap(display, RootWindowOfScreen(XtScreen(house)),
		(1 + HOUSE_WIDTH) * SPRITE_WIDTH,
		(1 + HOUSE_HEIGHT) * SPRITE_HEIGHT,
		DefaultDepthOfScreen(XtScreen(house)));
	for(x = 0; imageLoadMap[x].block; x++) {
		fileName = (char*)malloc(strlen(imageLoadMap[x].file)
			+ strlen(XPM_PATH) + 1);
		strcpy(fileName, XPM_PATH);
		strcat(fileName, imageLoadMap[x].file);
		XpmReadFileToImage(display, fileName,
			&images[imageLoadMap[x].block], NULL, NULL);
		free(fileName);
	}
	pthread_mutex_lock(&updateMutex);
	for(y = 0; y < HOUSE_HEIGHT; y++) {
		for(x = 0; x < HOUSE_WIDTH; x++) {
			update[y][x] = 1;
		}
	}
	pthread_mutex_unlock(&updateMutex);

	XpmReadFileToImage(display, "xpm/xcoord.xpm",
		&tempImage, NULL, NULL);
	XPutImage(display, pix, gc, tempImage, 0, 0,
		0, 0, (1 + HOUSE_WIDTH) * SPRITE_WIDTH,
		SPRITE_HEIGHT);

	XpmReadFileToImage(display, "xpm/ycoord.xpm",
		&tempImage, NULL, NULL);
	XPutImage(display, pix, gc, tempImage, 0, 0,
		0, 0, SPRITE_WIDTH,
		(1 + HOUSE_HEIGHT) * SPRITE_HEIGHT);
}


/***************************************************************************
 * Update the house display and copy the image to the screen.
 ***************************************************************************/
void DisplayMap() {
	static int first = 1;
	int x, y;
	int imageIndex;
	int temp;

	pthread_mutex_lock(&flagMutex);
	temp = exposed;
	pthread_mutex_unlock(&flagMutex);
	if(!temp) {
		return;
	}

	/* Load the images on the first time this is called */
	if(first) {
		first = 0;
		LoadImages();
	}

	pthread_mutex_lock(&flagMutex);
	temp = connected;
	pthread_mutex_unlock(&flagMutex);

	if(temp) {

		/* Draw the house */
		pthread_mutex_lock(&mapMutex);
		for(y = 0; y < HOUSE_HEIGHT; y++) {
			for(x = 0; x < HOUSE_WIDTH; x++) {
				if(map[y][x].type != TYPE_HOUSE) {
					if(map[y][x].active) {
						imageIndex = animatedObjects[map[y][x].type].states[state];
					} else if(update[y][x]) {
						imageIndex = map[y][x].type;
					} else {
						imageIndex = 0;
					}
					if(imageIndex) {
						pthread_mutex_unlock(&mapMutex);
						XPutImage(display, pix, gc, images[imageIndex],
							0, 0,
							(1 + x) * SPRITE_WIDTH, (1 + y) * SPRITE_HEIGHT,
							8 * SPRITE_WIDTH, 8 * SPRITE_HEIGHT);
						pthread_mutex_lock(&updateMutex);
						update[y][x] = 0;
						pthread_mutex_unlock(&updateMutex);
						pthread_mutex_lock(&mapMutex);
					}
				}
			}
		}
		pthread_mutex_unlock(&mapMutex);
	}

	UpdateHouseData();

	/* Display the cursor */
	XSetForeground(display, gc, BlackPixelOfScreen(XtScreen(house)));
	XDrawRectangle(display, pix, gc,
		(1 + hx) * SPRITE_WIDTH,
		(1 + hy) * SPRITE_HEIGHT,
		SPRITE_WIDTH - 1, SPRITE_HEIGHT - 1);
	XDrawRectangle(display, pix, gc,
		(1 + hx) * SPRITE_WIDTH + 1,
		(1 + hy) * SPRITE_HEIGHT + 1,
		SPRITE_WIDTH - 3, SPRITE_HEIGHT - 3);

	pthread_mutex_lock(&flagMutex);
	if(parseError) {
		XtVaSetValues(voice, XmNvalue, "Parse Error", NULL);
		parseError = 0;
	}
	if(serverShutdown) {
		done = 1;
	}
	pthread_mutex_unlock(&flagMutex);

	XCopyArea(display, pix, win, gc, 0, 0,
		(1 + HOUSE_WIDTH) * SPRITE_WIDTH,
		(1 + HOUSE_HEIGHT) * SPRITE_HEIGHT,
		0, 0);
}

