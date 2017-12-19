#include <sstream>
#include "Menu.h"
#include "Gps.h"
#include "Globals.h"
#include <map>
#include <utility>
#include "Praia.h"

//Global database variable
Database db;

int main() {

	//Allow to output portuguese characters like 'ç' or 'ã'
	//setlocale(LC_ALL, "");
	//std::locale::global(std::locale(""));
	//std::cout.imbue(std::locale());
	//Merging thid branch with master


	std::string filename_praias;

	std::cout << " Ficheiro de praias: ";
	getline(std::cin, filename_praias);

	//Catch exception while loading
	get_filename:
	try {
		db.load(filename_praias);
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
		db.save(filename_praias);
	}
	catch (Exception& e) {
		e.display();
	}

	return 0;

}
