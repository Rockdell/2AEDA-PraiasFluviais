#include <iostream>
#include "MenuFlow.h"
#include "Globals.h"

#ifndef MENU_H_
#define MENU_H_

int printMenu();

void MainMenu();
void AddMenu();
void RemoveMenu();
void EditMenu();
void WatchMenu();

int sendEvent(char c);

#endif /* MENU_H_ */
