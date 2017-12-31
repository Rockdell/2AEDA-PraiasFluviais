#include <sstream>
#include <map>
#include <utility>

#include "Menu.h"
#include "Globals.h"

//Global database variable
Database db;

int main() {

	/**
	 *  @mainpage Praias Fluviais Index Page
	 *
	 *  @section intro_sec Introduction
	 *
	 *  This is the documentation for a project developed in the classes of AEDA.
	 *
	 *  @section usage_sec Usage
	 *
	 *  Follow the instructions on the screen and press the number corresponding to what you want to do.
	 *  At any moment, you can write '0' to cancel any operation.
	 *
	 *  Have fun!
	 *
	 *  @section done_sec Work done by:
	 *
	 *  Pedro Tavares and Miguel Teixeira
	 */

	std::string filename_praias;

	std::cout << " Path to .txt file: ";
	getline(std::cin, filename_praias);

	//Catch exception while loading
	get_filename:
	try {
		db.load(filename_praias);
	}
	catch(Exception& e) {
		std::cout << "\n Erro com o ficheiro: " << e.getMessage() << std::endl;
		_getch();
		goto get_filename;
	}

	unsigned int stop = 0;

	while(!stop) {

		//Catch any exception
		try {
		stop = printMenu();
		}
		catch (Exception& e) {
			e.display();
			_getch();
		}
	}

	//Catch exceptions while saving
	try {
		db.save(filename_praias);
	}
	catch (Exception& e) {
		e.display();
		_getch();
	}

	return 0;
}
