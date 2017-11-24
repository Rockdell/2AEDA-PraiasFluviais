#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include "Praia.h"
#include "PAlbufeira.h"
#include "PRio.h"
#include "Exceptions.h"
#include "Gps.h"
#include <memory>

#ifndef DATABASE_H_
#define DATABASE_H_

typedef std::string Concelho;
typedef std::map<Concelho, std::vector<Praia*>>::iterator iter_map;
typedef std::pair<iter_map, int> iter;

/**
 * @brief Database where we will store all the information about Praias
 */
class Database {

	std::map<Concelho, std::vector<Praia*>> praias;

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
//	void setPraias(std::map<Concelho,Praia*> ps)
//	{
//		praias = ps;
//	}

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

	//TODO add description
	void showPraias();

	/**
	 * @brief Search object p in vector "praias"
	 * @param p Object Praia to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	iter searchPraia(Praia* p);

	/**
	 * @brief Search object with name n in vector "praias"
	 * @param n Object's name to search for
	 * @param c Object's region to search for
	 * @return Return -1 if not found or the object's index if found
	 */
	iter searchPraia(std::string n, std::string c);
	
	//TODO add description
	Praia* searchPraia(int i);

	/**
	 * @brief Check if object p exists in database
	 * @param p Object Praia to check
	 * @return Return true if it exists or false if it doesn't
	 */
	bool existPraia(Praia* p);

	//TODO add description
	bool existPraia(std::string n, std::string c);

	//TODO add description
	unsigned int getSize();

	/**
	 * @brief Orders vector "praias" by name
	 */
	void sortPraiasNome();

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
	std::map<double,Praia*> withInRangePraia(Praia * p, double r);

	/**
	 * @brief Gives all praias within given range of a certain Gps location
	 * @param p praia given as center of range
	 * @param r radius/range given
	 * @return Returns a map of ordered of praias ordered by range(as the map key)
	 */
	std::map<double,Praia*> withInRangeGps(Gps g, double r);

	/**
	 * @brief Creates a map with the ranges (as keys) and praias (as key values)
	 * @param ps Vector of praia pointers which we want to order
	 * @param ranges Vector of doubles representing the ranges
	 * @return Returns a map of ordered of praias ordered by range(as the map key)
	 */
	std::map<double,Praia*> orderRange(std::vector<Praia *> ps, std::vector<double> ranges);
};

bool compararCaseInsensitive(std::string strFirst, std::string strSecond);
std::string decapitalize(std::string s);

#endif /* DATABASE_H_ */
