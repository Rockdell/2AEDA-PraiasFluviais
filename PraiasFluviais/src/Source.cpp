#include "Menu.h"
#include "Gps.h"
#include "Globals.h"

//Global database variable
Database db;

int main() {

	//Allow to output portuguese characters like 'ç' or 'ã'
	setlocale(LC_ALL, "");
	std::locale::global(std::locale(""));
	std::cout.imbue(std::locale());

	//Catch exception while loading
	try {
		db.load("listPraias.txt");
	}
	catch(Exception& e) {
		std::cout << " Ocorreu um erro com: " << e.getMessage() << std::endl;
	}

	unsigned int stop = 0;

	while(!stop) {

		//Catch any exception
		try {
		stop = printMenu();
		}
		catch (Exception& e) {
			std::cout << " Ocorreu um erro com: " << e.getMessage() << std::endl;
		}

		std::cin.ignore();
	}

	//Catch exceptions while saving
	try {
		db.save("listPraias.txt");
	}
	catch (Exception& e) {
		std::cout << " Ocorreu um erro com: " << e.getMessage() << std::endl;
	}
	return 0;
}
