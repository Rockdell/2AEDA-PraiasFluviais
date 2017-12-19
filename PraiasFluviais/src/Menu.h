#include <iostream>
#include <conio.h>
#include "MenuFlow.h"
#include "Globals.h"

#ifndef MENU_H_
#define MENU_H_

/**
 * @brief Goes to the menu depending on the state
 */
int printMenu();

void MainMenu();
void AddMenu();
void RemoveMenu();
void EditMenu();
void WatchMenu();

/**
 * @brief Treats the input of the user and says if it's acceptable or not
 * @param input User's input string which will be evaluated
 * @param property Depending on what type of variable you want to evaluate (s-string, d-double, b-bool, i-int)
 * @return Returns: 0-invalid input, 1-continue operation(valid input), 2-cancel operation
 */
int inputHandling(std::string input, char property);

/**
 * @brief Sends an event to the State Machine, which will then update its state
 * @param c According to what this variable is, sends a specific event to the State Machine
 * @return Returns 1 if successful, otherwise displays a message and returns 0
 */
int sendEvent(char c);

#endif /* MENU_H_ */
