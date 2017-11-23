#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
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
	 * @brief Sets the data-member praias to the given vector
	 * @param ps Vector with Praia* objects
	 */
	void setPraias(std::vector<Praia*> ps)
	{
		praias = ps;
	}

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

	/**
	 * @brief Search object p in vector "praias"
	 * @param p Object Praia to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	int searchPraia(Praia* p);

	/**
	 * @brief Search object with name n in vector "praias"
	 * @param n Object's name to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	int searchPraia(std::string n);

	/**
	 * @brief Check if object p exists in database
	 * @param p Object Praia to check
	 * @return Return true if it exists or false if it doesn't
	 */
	bool existPraia(Praia* p);

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

	/**
	 * @brief Gives all praias within given range of a certain praia
	 * @param p praia given as center of range
	 * @param r radius/range given
	 * @return Returns a map of ordered of praias ordered by range(as the map key)
	 */
	std::map<double,std::unique_ptr<Praia>> withInRangePraia(Praia * p, double r) const;

	/**
	 * @brief Gives all praias within given range of a certain Gps location
	 * @param p praia given as center of range
	 * @param r radius/range given
	 * @return Returns a map of ordered of praias ordered by range(as the map key)
	 */
	std::map<double,std::unique_ptr<Praia>> withInRangeGps(Gps g, double r) const;

	/**
	 * @brief Creates a map with the ranges (as keys) and praias (as key values)
	 * @param ps Vector of praia pointers which we want to order
	 * @param ranges Vector of doubles representing the ranges
	 * @return Returns a map of ordered of praias ordered by range(as the map key)
	 */
	std::map<double,std::unique_ptr<Praia>> orderRange(std::vector<Praia *> ps, std::vector<double> ranges) const;
};

#endif /* DATABASE_H_ */
