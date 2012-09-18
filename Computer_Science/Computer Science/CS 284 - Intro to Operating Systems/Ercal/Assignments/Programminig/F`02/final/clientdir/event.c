/****************************************************************************
 * Functions for handling actions on objects in the house by the user.
 ****************************************************************************/

#include "main.h"
#include "client.h"
#include "display.h"
#include "network.h"
#include "../global/debug.h"

typedef struct {
	BlockType type;
	char *active;
	char *inactive;
	char *locked;
	char *unlocked;
} ChangeType;

typedef struct {
	BlockType type;
	char *activate[2];
	char *unlock[2];
	char *levels[LEVEL_COUNT];
} ControlType;

static const ChangeType changeMap[] = {
	{ TYPE_DOOR,	"open",	"close",		"lock",		"unlock"		},
	{ TYPE_LAMP,	"on",		"off",		NULL,			NULL			},
	{ TYPE_WINDOW,	"open",	"close",		"lock",		"unlock"		},
	{ TYPE_TOILET,	"use",	"flush",		NULL,			NULL			},
	{ TYPE_TV,		"on",		"off",		NULL,			NULL			},
	{ TYPE_SHOWER,	"on",		"off",		NULL,			NULL			},
	{ TYPE_SINK,	"on",		"off",		NULL,			NULL			},
	{ TYPE_STOVE,	"on",		"off",		NULL,			NULL			},
	{ TYPE_FRIDGE,	"on",		"off",		NULL,			NULL			},
	{ TYPE_PERSON, "to",		NULL,			NULL,			NULL			},
	{ TYPE_HOUSE,	NULL,		NULL,			NULL,			NULL			}
};

static const ControlType controlMap[] = {
	{ TYPE_DOOR,
		{ "Open Door", "Close Door" },
		{ "Unlock Door", "Lock Door" },
		{ NULL }
	},

	{ TYPE_WINDOW,
		{ "Open Window", "Close Window" },
		{ "Unlock Window", "Lock Window" },
		{ NULL }
	},

	{ TYPE_SINK,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_TOILET,
		{ "Use", "Flush" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_FRIDGE,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_STOVE,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_SHOWER,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_LAMP,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ NULL }
	},

	{ TYPE_TV,
		{ "Turn On", "Turn Off" },
		{ NULL },
		{ "Channel", "Volume" }
	},

	{ TYPE_PERSON,
		{ "Move", NULL },
		{ NULL },
		{ NULL }
	},
 
	{ TYPE_HOUSE,
		{ NULL }, { NULL }, { NULL }
	}

};

/****************************************************************************
 ****************************************************************************/
void SetForChange(int x, int y) {
	XmString str;
	ObjectType object;
	int a, b;

	pthread_mutex_lock(&mapMutex);
	object = map[y][x];
	pthread_mutex_unlock(&mapMutex);

	for(a = 0; controlMap[a].type; a++) {
		if(controlMap[a].type == object.type) {
			if(object.active && controlMap[a].activate[0]) {
				str = XmStringCreateLocalized(controlMap[a].activate[1]);
				XtVaSetValues(activateButton, XmNlabelString, str, NULL);
				XmStringFree(str);
				XtManageChild(activateButton);
				XtUnmanageChild(unlockButton);
			} else if(object.locked && controlMap[a].unlock[0]) {
				str = XmStringCreateLocalized(controlMap[a].unlock[0]);
				XtVaSetValues(unlockButton, XmNlabelString, str, NULL);
				XmStringFree(str);
				XtManageChild(unlockButton);
				XtUnmanageChild(activateButton);
			} else if(controlMap[a].activate[0]) {
				str = XmStringCreateLocalized(controlMap[a].activate[0]);
				XtVaSetValues(activateButton, XmNlabelString, str, NULL);
				XmStringFree(str);
				XtManageChild(activateButton);
				if(controlMap[a].unlock[0]) {
					str = XmStringCreateLocalized(controlMap[a].unlock[1]);
					XtVaSetValues(unlockButton, XmNlabelString, str, NULL);
					XmStringFree(str);
					XtManageChild(unlockButton);
				} else {
					XtUnmanageChild(unlockButton);
				}
			} else {
				XtUnmanageChild(activateButton);
				XtUnmanageChild(unlockButton);
			}

			if(object.active) {
				for(b = 0; b < LEVEL_COUNT; b++) {
					if(!controlMap[a].levels[b]) {
						XtUnmanageChild(levels[b]);
					} else {
						str = XmStringCreateLocalized(controlMap[a].levels[b]);
						XtVaSetValues(levels[b], XmNtitleString, str,
							XmNvalue, object.level[b],
							NULL);
						XmStringFree(str);
						XtManageChild(levels[b]);
					}
				}
			} else {
				b = 0;
			}
			for(; b < LEVEL_COUNT; b++) {
				XtUnmanageChild(levels[b]);
			}

			break;
		}
	}

	if(controlMap[a].type == TYPE_HOUSE) {
		XtUnmanageChild(activateButton);
		XtUnmanageChild(unlockButton);
		for(b = 0; b < LEVEL_COUNT; b++) {
			XtUnmanageChild(levels[b]);
		}
	}
}

/****************************************************************************
 ****************************************************************************/
void DoActivate(int x, int y) {
	char str[MESSAGE_LENGTH];
	const char *temp;
	int z;

	pthread_mutex_lock(&mapMutex);
	for(z = 0; changeMap[z].type; z++) {
		if(changeMap[z].type == map[y][x].type) {
			break;
		}
	}

	if(map[y][x].active) {
		temp = changeMap[z].inactive;
	} else {
		temp = changeMap[z].active;
	}
	pthread_mutex_unlock(&mapMutex);

	snprintf(str, MESSAGE_LENGTH, "%d,%d %s",
		x + 1, y + 1, temp);
	XtVaSetValues(voice, XmNvalue, str, NULL);
	if(map[y][x].type == TYPE_PERSON) {
		modeMoveParent = 1;
	} else {
		SendMessage(str);
	}

}

/****************************************************************************
 ****************************************************************************/
void DoUnlock(int x, int y) {
	char str[MESSAGE_LENGTH];
	const char *temp;
	int z;

	pthread_mutex_lock(&mapMutex);
	for(z = 0; changeMap[z].type; z++) {
		if(changeMap[z].type == map[y][x].type) {
			break;
		}
	}

	if(map[y][x].locked) {
		temp = changeMap[z].unlocked;
	} else {
		temp = changeMap[z].locked;
	}
	pthread_mutex_unlock(&mapMutex);

	if(temp) {
		snprintf(str, MESSAGE_LENGTH, "%d,%d %s",
			x + 1, y + 1, temp);
		XtVaSetValues(voice, XmNvalue, str, NULL);

		SendMessage(str);
	}

}

