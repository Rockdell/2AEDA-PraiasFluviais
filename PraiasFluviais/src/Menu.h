
#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <conio.h>

#include "MenuFlow.h"
#include "Globals.h"

#include "Praia.h"
#include "Service.h"

/**
 *  @file Menu.h
 */

/**
 *  @fn int printMenu()
 *  @brief Checks the current state of the state machine and prints the corresponding menu
 *  @returns Returns 1 to exit the program or 0 to continue.
 */

/**
 *  @fn void MainMenu()
 *  @brief Prints the main menu.
 */

/**
 *  @fn void AddMenu()
 *  @brief Prints the add menu.
 */

/**
 *  @fn void RemoveMenu()
 *  @brief Prints the remove menu.
 */

/**
 *  @fn void EditMenu()
 *  @brief Prints the edit menu.
 */

/**
 *  @fn void SearchMenu()
 *  @brief Prints the search menu.
 */

/**
 *  @fn void ServicesMenu()
 *  @brief Prints the services menu.
 */

/**
 *  @fn int inputHandling(std::string input, char property)
 *  @brief Handles the input of the user.
 *  @param input User's input.
 *  @param property Property of the input (double, bool, string, ...).
 *  @return Returns 0 for invalid input, 1 to continue the operation and 2 to cancel the operation.
 */

/**
 *  @fn int sendEvent(char c)
 *  @brief Sends an event to the state machine.
 *  @param c Type of event to send.
 *  @return Returns 1 on success and 0 otherwise.
 */

/**
 *  @fn Praia* selectPraia()
 *  @brief Prints a selection menu, where the user chooses an object Praia.
 *  @return Returns a pointer to an object Praia.
 *  @see Praia
 */

/**
 *  @fn Service selectService(Praia* p)
 *  @brief Prints a selection menu, where the user chooses an object Service of a certain object Praia.
 *  @param p Pointer to an object Praia.
 *  @return Returns an object Service.
 *  @see Praia
 *  @see Service
 */

int printMenu();

void MainMenu();
void AddMenu();
void RemoveMenu();
void EditMenu();
void SearchMenu();
void ServicesMenu();

int inputHandling(std::string input, char property);
int sendEvent(char c);

Praia* selectPraia();
Service selectService(Praia* p);

#endif /* MENU_H_ */
