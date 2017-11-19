#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Praia.h"
#include "PAlbufeira.h"
#include "PRio.h"
#include "Exceptions.h"
#include "Gps.h"

#ifndef DATABASE_H_
#define DATABASE_H_

class Database {
	std::vector<Praia*> praias;
public:
	Database();
	~Database();

	void load(std::string filename);
	void save(std::string filename);

	void addPraia(Praia* p);
	void removePraia(Praia* p);

	//Só chama esta se houver certezas que praia existe em i
	void removePraia(int i);
	int searchPraia(Praia* p);
	int searchPraia(std::string n);
	bool existPraia(Praia* p);

	void orderPraiasNome();
	void orderPraiasConcelho();
	void processLine(json line);

	std::vector<Praia *> withInRangePraia(Praia * p, double r) const;
	std::vector<Praia *> withInRangeGps(Gps g, double r) const;
	void orderRange(std::vector<Praia *> & ps, std::vector<double> ranges) const;
};

#endif /* DATABASE_H_ */
