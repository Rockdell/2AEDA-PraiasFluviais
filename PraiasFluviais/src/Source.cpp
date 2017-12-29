#include <sstream>
#include <map>
#include <utility>

#include "Menu.h"
#include "Globals.h"

//Global database variable
Database db;

int main() {

	//Allow to output portuguese characters like 'ç' or 'ã'
	//setlocale(LC_ALL, "");
	//std::locale::global(std::locale(""));
	//std::cout.imbue(std::locale());
	std::string path = "C:\\Users\\Xavi\\git\\2AEDA-PraiasFluviais\\PraiasFluviais\\listPraias.txt";

	std::string filename_praias;

	std::cout << " Ficheiro de praias: ";
	//getline(std::cin, filename_praias);

	//Catch exception while loading
	get_filename:
	try {
		db.load(path);
	}
	catch(Exception& e) {
		std::cout << " Erro com o ficheiro: " << e.getMessage() << std::endl;
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
		db.save(path);
	}
	catch (Exception& e) {
		e.display();
	}

	return 0;

}
