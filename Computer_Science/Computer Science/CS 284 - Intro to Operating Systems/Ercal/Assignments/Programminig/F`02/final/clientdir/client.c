/****************************************************************************
 * File to contain the main entry point for the client as well as the
 * code to draw and handle the basic interface.
 ****************************************************************************/

#include "main.h"
#include "display.h"
#include "event.h"
#include "client.h"
#include "network.h"
#include "../global/debug.h"

Widget activateButton;
Widget unlockButton;
Widget levels[LEVEL_COUNT];
Widget temperature;
Widget voice;
Widget timeDisplay;

static XtIntervalId timeout;
static XtAppContext app;

static void ActivateEvent(Widget, XtPointer, XtPointer);
static void UnlockEvent(Widget, XtPointer, XtPointer);
static void ScaleEvent(Widget, XtPointer, XtPointer);
static void TemperatureChangeEvent(Widget, XtPointer, XtPointer);
static void DoExit(Widget, XtPointer, XtPointer);
static void SendCommand(Widget, XtPointer, XtPointer);
static void Select(Widget, XtPointer, XtPointer);
static void Update(XtPointer data, XtIntervalId *interval);

/****************************************************************************
 * Entry point. Set up the interface and begin execution.
 ****************************************************************************/
int main(int argc, char *argv[]) {

	Widget topLevel, rows, cols, frame;
	XEvent event;
	XmString str;
	int x;

	if(argc != 2) {
		printf("usage: %s <hostname>\n", argv[0]);
		exit(1);
	}
	pthread_mutex_lock(&flagMutex);
	parseError = 0;
	serverShutdown = 0;
	pthread_mutex_unlock(&flagMutex);

	Connect(argv[1]);

	XtSetLanguageProc(NULL, NULL, NULL);

	topLevel = XtVaAppInitialize(&app, "Smart House Client", NULL, 0,
		&argc, argv, NULL,
		XmNwidth, (1 + HOUSE_WIDTH) * SPRITE_WIDTH + 240,
		XmNheight, (1 + HOUSE_HEIGHT) * SPRITE_HEIGHT + 15,
		NULL);

	cols = XtVaCreateManagedWidget("cols", xmPanedWindowWidgetClass,
		topLevel, XmNorientation, XmHORIZONTAL, NULL);

	frame = XtVaCreateManagedWidget("frame",
		xmFrameWidgetClass, cols, NULL);
	house = XtVaCreateManagedWidget("house",
		xmDrawingAreaWidgetClass, frame,
		XmNwidth, (1 + HOUSE_WIDTH) * SPRITE_WIDTH,
		XmNheight, (1 + HOUSE_HEIGHT) * SPRITE_HEIGHT,
		NULL);

	rows = XtVaCreateManagedWidget("rows", xmRowColumnWidgetClass, cols,
		XmNorientation, XmVERTICAL,
		NULL);

	/* Create house controls */
	str = XmStringCreateLocalized("House Controls:");
	XtVaCreateManagedWidget("label2", xmLabelWidgetClass, rows,
		XmNlabelString, str,
		NULL);
	XmStringFree(str);

	CreateButton("Exit", rows, DoExit);

	str = XmStringCreateLocalized("Time: 0:00");
	timeDisplay = XtVaCreateManagedWidget("time",
		xmLabelWidgetClass, rows, XmNlabelString, str, NULL);
	XmStringFree(str);

	str = XmStringCreateLocalized("Temperature");
	temperature = XtVaCreateManagedWidget("temp",
		xmScaleWidgetClass, rows,
		XmNminimum, 55, XmNmaximum, 90,
		XmNshowValue, True,
		XmNtitleString, str,
		XmNorientation, XmHORIZONTAL,
		NULL);
	XmStringFree(str);

	voice = XtVaCreateManagedWidget("voice", xmTextWidgetClass, rows,
		NULL);

	CreateButton("Send Command", rows, SendCommand);

	str = XmStringCreateLocalized(" ");
	XtVaCreateManagedWidget("spacer", xmLabelWidgetClass, rows,
		XmNlabelString, str, NULL);
	XmStringFree(str);

	/* Create object controls */
	str = XmStringCreateLocalized("Object Controls:");
	XtVaCreateManagedWidget("label1", xmLabelWidgetClass, rows,
		XmNlabelString, str,
		NULL);
	XmStringFree(str);

	activateButton = CreateButton("activate", rows, ActivateEvent);
	XtUnmanageChild(activateButton);
	unlockButton = CreateButton("unlock", rows, UnlockEvent);
	XtUnmanageChild(unlockButton);

	for(x = 0; x < LEVEL_COUNT; x++) {
		levels[x] = XtVaCreateWidget("level",
			xmScaleWidgetClass, rows,
			XmNminimum, 0, XmNmaximum, 100,
			XmNshowValue, True,
			XmNorientation, XmHORIZONTAL,
			NULL);
		XtAddCallback(levels[x], XmNvalueChangedCallback, ScaleEvent, NULL);
	}

	XtAddCallback(temperature, XmNvalueChangedCallback,
		TemperatureChangeEvent, NULL);
	XtAddCallback(house, XmNinputCallback, Select, NULL);
	XtAddCallback(house, XmNexposeCallback, Select, NULL);

	XtRealizeWidget(topLevel);

	timeout = XtAppAddTimeOut(app, 500, Update, NULL);

	for(;;) {
		pthread_mutex_lock(&flagMutex);
		x = done;
		pthread_mutex_unlock(&flagMutex);
		if(x) {
			break;
		}
		XtAppNextEvent(app, &event);
		XtDispatchEvent(&event);
	}

	XtRemoveTimeOut(timeout);

	Disconnect();

	pthread_mutex_lock(&flagMutex);
	if(serverShutdown) {
		printf("The server has shut down!\n");
	}
	pthread_mutex_unlock(&flagMutex);

	return 0;
}

/****************************************************************************
 * "Activate" button click event handler.
 ****************************************************************************/
void ActivateEvent(Widget widget, XtPointer clientData, XtPointer callData) {
	DoActivate(GetXPosition(), GetYPosition());
}

/****************************************************************************
 * "Unlock" button click event handler.
 ****************************************************************************/
void UnlockEvent(Widget widget, XtPointer clientData, XtPointer callData) {
	DoUnlock(GetXPosition(), GetYPosition());
}

/****************************************************************************
 * Event handler for a scale widget changing values.
 ****************************************************************************/
void ScaleEvent(Widget widget, XtPointer clientData, XtPointer callData) {

	const char *COMMAND_MAP[] = {
		"channel",
		"volume"
	};

	int x, value;
	char str[64];

	for(x = 0; x < LEVEL_COUNT; x++) {
		if(levels[x] == widget) {
			break;
		}
	}
	XtVaGetValues(levels[x], XmNvalue, &value, NULL);

	snprintf(str, 64, "%d,%d %s %d", GetXPosition() + 1,
		GetYPosition() + 1, COMMAND_MAP[x], value);

	XtVaSetValues(voice, XmNvalue, str, NULL);

	SendMessage(str);
}

/****************************************************************************
 * Event handler for the temperature scale object changing values.
 ****************************************************************************/
void TemperatureChangeEvent(Widget widget, XtPointer clientData,
	XtPointer callData) {

	int value;
	char str[64];

	XtVaGetValues(temperature, XmNvalue, &value, NULL);
	snprintf(str, 64, "%d,%d temp %d", 0, 0, value);
	XtVaSetValues(voice, XmNvalue, str, NULL);

	SendMessage(str);
	SendMessage(str);
	SendMessage(str);

}

/****************************************************************************
 * Button click event handler for the "Send Command" button.
 ****************************************************************************/
void SendCommand(Widget widget, XtPointer clientData, XtPointer callData) {
	char *msg;

	msg = XmTextGetString(voice);
	SendMessage(msg);

}

/****************************************************************************
 * "Exit" button click event handler.
 ****************************************************************************/
void DoExit(Widget widget, XtPointer clientData, XtPointer callData) {
	pthread_mutex_lock(&flagMutex);
	done = 1;
	pthread_mutex_unlock(&flagMutex);
}

/****************************************************************************
 * Event handler for a click on the house.
 ****************************************************************************/
void Select(Widget widget, XtPointer clientData, XtPointer callData) {
	XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct*)callData;
	XEvent *event = cbs->event;
	char *msg;
	char *newMsg;
	int x, y;

	if(cbs->reason == XmCR_INPUT) {
		if(event->xany.type == ButtonPress) {
			x = event->xbutton.x / SPRITE_WIDTH - 1;
			y = event->xbutton.y / SPRITE_HEIGHT - 1;
			if(modeMoveParent) {
				modeMoveParent = 0;
				msg = XmTextGetString(voice);
				newMsg = (char*)malloc(strlen(msg) + 8);
				sprintf(newMsg, "%s %d,%d", msg, x + 1, y + 1);
				SendMessage(newMsg);
			}
			SetHighlight(x, y);
			DisplayMap();
		}
	} else if(cbs->reason == XmCR_EXPOSE) {
		pthread_mutex_lock(&flagMutex);
		exposed = 1;
		pthread_mutex_unlock(&flagMutex);
		RedrawMap();
	}
}

/****************************************************************************
 * Update animations and update display with data from the server.
 ****************************************************************************/
void Update(XtPointer data, XtIntervalId *interval) {
	UpdateAnimations();
	SetForChange(GetXPosition(), GetYPosition());
	DisplayMap();
	timeout = XtAppAddTimeOut(app, 500, Update, NULL);
}

