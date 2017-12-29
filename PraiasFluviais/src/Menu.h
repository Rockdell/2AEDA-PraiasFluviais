
#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <conio.h>

#include "MenuFlow.h"
#include "Globals.h"

#include "Praia.h"
#include "Service.h"

int printMenu();

void MainMenu();
void AddMenu();
void RemoveMenu();
void EditMenu();
void WatchMenu();
void ServicesMenu();

int inputHandling(std::string input, char property);
int sendEvent(char c);

#endif /* MENU_H_ */
