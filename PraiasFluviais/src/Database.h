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
#include <memory>

#include "Praia.h"
#include "PAlbufeira.h"
#include "PRio.h"
#include "Exceptions.h"

#ifndef DATABASE_H_
#define DATABASE_H_

typedef std::string Concelho;
typedef std::map<Concelho, std::vector<Praia*>>::iterator iter_map;
typedef std::pair<iter_map, int> iter_pair;

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
	 * @brief Populate map "praias" with objects from file
	 * @param filename File to open
	 */
	void load(std::string filename);

	/**
	 * @brief Save objects from map "praias" in file
	 * @param filename File to open
	 */
	void save(std::string filename);

	/**
	 * @brief Add object p to map"praias"
	 * @param p Object Praia to add
	 */
	void addPraia(Praia* p);

	/**
	 * @brief Remove object p from map "praias"
	 * @param p Object Praia to add
	 */
	void removePraia(Praia* p);

	/**
	 * @brief Display's a specific Praia object in a reduced way
	 */
	void showPraias();

	/**
	 * @brief Search object p in map "praias"
	 * @param p Object Praia to search for
	 * @return Return a pair with -1 if not found or the object's iterator in the map and it's index in the vector
	 */
	iter_pair searchPraia(Praia* p);

	/**
	 * @brief Search object with name n in vector "praias"
	 * @param n Object's name to search for
	 * @param c Object's region to search for
	 * @return Return a pair with -1 if not found or the object's iterator in the map and it's index in the vector
	 */
	iter_pair searchPraia(std::string n, std::string c);
	
	/*
	 * @brief Search praia from user's input and returns a pointer to it
	 * @param i User's input (when choosing from a list of objects Praia)
	 * @return Pointer to an object Praia
	 */
	Praia* searchPraia(int i);

	/**
	 * @brief Check if object p exists in database
	 * @param p Object Praia to check
	 * @return Return true if it exists or false if it doesn't
	 */
	bool existPraia(Praia* p);

	/**
	 * @brief Check if object p exists in database
	 * @param n Object's name
	 * @param c Object's region
	 * @return Return true if it exists or false if it doesn't
	 */
	bool existPraia(std::string n, std::string c);

	/*
	 * @brief Return size of map praias
	 * @return Size of map praias
	 */
	unsigned int getSize();

	/**
	 * @brief Orders the vector inside the map "praias" by name
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

/*
 * @brief Turns all characters in string to lower case and capitalizes the first letter
 * @param s String to change
 * @return New string
 */
std::string decapitalize(std::string s);

#endif /* DATABASE_H_ */
