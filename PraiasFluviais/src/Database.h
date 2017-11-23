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

/**
 * @brief Database where we will store all the information about Praias
 */
class Database {
	std::vector<Praia*> praias;
public:

	/**
	 * @brief Class constructor
	 */
	Database();

	/**
	 * @brief Class destructor
	 */
	~Database();

	/**
	 * @brief Populate vector "praias" with objects from file
	 * @param filename File to open
	 */
	void load(std::string filename);

	/**
	 * @brief Save objects from vector "praias" in file
	 * @param filename File to open
	 */
	void save(std::string filename);

	/**
	 * @brief Add object p to vector "praias"
	 * @param p Object Praia to add
	 */
	void addPraia(Praia* p);

	/**
	 * @brief Remove object p from vector "praias"
	 * @param p Object Praia to add
	 */
	void removePraia(Praia* p);

	/**
	 * @brief Remove object with index i from vector "praias"
	 * @param i Index of the object Praia to remove
	 */
	void removePraia(int i);

	//TODO add description
	void showPraias();

	void showPraia(int i);

	/**
	 * @brief Search object p in vector "praias"
	 * @param p Object Praia to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	int searchPraia(Praia* p);

	/**
	 * @brief Search object with name n in vector "praias"
	 * @param n Object's name to search for
	 * @param c Object's region to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	int searchPraia(std::string n, std::string c);

	/**
	 * @brief Check if object p exists in database
	 * @param p Object Praia to check
	 * @return Return true if it exists or false if it doesn't
	 */
	bool existPraia(Praia* p);

	//TODO add description
	bool existPraia(std::string n, std::string c);

	//TODO add description
	int getSize() const;

	/**
	 * @brief Orders vector "praias" by name
	 */
	void sortPraiasNome();

	/**
	 * @brief Orders vector "praias" by region
	 */
	void sortPraiasConcelho();

	/**
	 * @brief Processes line from file
	 * @param l Line from file
	 */
	void processLine(std::string l);

	std::vector<Praia *> withInRangePraia(Praia * p, double r) const;
	std::vector<Praia *> withInRangeGps(Gps g, double r) const;
	void orderRange(std::vector<Praia *> & ps, std::vector<double> ranges) const;
};

#endif /* DATABASE_H_ */
