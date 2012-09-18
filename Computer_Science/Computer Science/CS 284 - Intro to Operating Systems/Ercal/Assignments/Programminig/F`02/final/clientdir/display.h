
#ifndef DISPLAY_H
#define DISPLAY_h

void DisplayMap();
Widget CreateButton(char *label, Widget parent, CallBackType callback);
void SetHighlight(int x, int y);
void UpdateAnimations();
void RedrawMap();

int GetXPosition();
int GetYPosition();

#endif

