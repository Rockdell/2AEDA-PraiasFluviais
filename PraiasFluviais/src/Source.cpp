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

	//Teste DATABASE

	//PRio(std::string n, std::string c, bool bA, Gps cd, float l, float cl, float p);
	//PAlbufeira(std::string n, std::string c, bool bA,  Gps cd, float a);
	//Gps(double lat, double lon);

	/*

	Gps g1 = Gps(51.0664, -5.7147);
	std::cout << g1.displayGps() << std::endl;
	Gps g2 = Gps(58.6439, -3.07);
	std::cout << g2.displayGps() << std::endl;
	Gps g3 = Gps(-6.9233, 65.3889);
	std::cout << g3.displayGps() << std::endl;
	Gps g4 = Gps(65.0833, -98.2);
	std::cout << g4.displayGps() << std::endl;

	std::vector<std::string> t (0,"3");

	Praia* pr1 = new PRio("pr1", "c1", t,true, g1, 1, 1, 1);
	PAlbufeira pa2 = PAlbufeira("pa2", "c2", t, true, g2, 2);
	PRio pr3 = PRio("pr3", "c3", t, true, g3, 3, 3, 3);
	PAlbufeira pa4 = PAlbufeira("pa4", "c4", t, true, g4, 4);

	std::map<Concelho,Praia*> test1;

	test1.insert(std::make_pair(pr1->getConcelho(), pr1));

	PRio* test_retirar = dynamic_cast<PRio*>(test1[pr1.getConcelho()]);


	std::cout << test_retirar2->getLargura();
	*/

	//std::vector<Praia *> test1;
//	test1.push_back(&pa2);
//	test1.push_back(&pr1);
//	test1.push_back(&pa4);
//	test1.push_back(&pr3);

	//db.setPraias(test1);

	/*
	std::map<double,std::unique_ptr<Praia>> test;
	test = db.withInRangePraia(&pa2, 5000);

	for(auto it = test.begin(); it != test.end(); it++)
	{
		std::cout << it->first << " " << it->second->getNome() << std::endl;
	}
	*/

//	std::vector<Praia*> test1
//	std::map<int, Praia*> test2;
//
//	if(true) {
//
//		Gps g1 = Gps(51.0664, -5.7147);
//		std::vector<std::string> t (0,"3");
//		Praia* pr1 = PRio("pr1", "c1", t,true, g1, 1, 1, 1);
//
//		test1.push_back(pr1);
//		test2[2] = pr1;
//	}



	//Allow to output portuguese characters like 'ç' or 'ã'
	//setlocale(LC_ALL, "");
	//std::locale::global(std::locale(""));
	//std::cout.imbue(std::locale());

	std::string filename_praias;

	std::cout << " Ficheiro de praias: ";
	getline(std::cin, filename_praias);

	//Catch exception while loading
	get_filename:
	try {
		db.load("C:\\Users\\Miguel Teixeira\\git\\2AEDA-PraiasFluviais\\PraiasFluviais\\listPraias.txt");
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
		db.save("C:\\Users\\Miguel Teixeira\\git\\2AEDA-PraiasFluviais\\PraiasFluviais\\listPraias.txt");
	}
	catch (Exception& e) {
		e.display();
	}

	return 0;

	//Load e save estão feitos!

}
