#include <sstream>
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

	std::string filename_praias;

	get_filename:
	std::cout << " Ficheiro de praias: ";
	getline(std::cin, filename_praias);

	//Catch exception while loading
	try {
		db.load(filename_praias);
	}
	catch(Exception& e) {
		e.display();
		goto get_filename;
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
	}

	//Catch exceptions while saving
	try {
		db.save(filename_praias);
	}
	catch (Exception& e) {
		e.display();
	}

	return 0;
}
