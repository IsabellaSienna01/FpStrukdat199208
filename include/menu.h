#ifndef MENU_H
#define MENU_H

extern const char * menuoptions[6];

void textcolor(int color);
void showmenu(int highlight);
int keyint(char key);
int useroption(void);

#endif