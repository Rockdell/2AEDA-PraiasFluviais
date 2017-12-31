
#ifndef DATABASE_H_
#define DATABASE_H_

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
#include "Service.h"

/**
 *  @file Database.h
 */

/**
 *  @fn bool sort(Praia* p1, Praia* p2)
 *  @param p1 First object Praia.
 *  @param p2 Second object Praia.
 *  @return True if first argument is smaller than the second argument.
 */

/**
 *  @fn std::string decapitalize(std::string s)
 *  @param s String to format.
 *  @return Formatted string.
 */

/** @brief Creates a type name for std::string. */
typedef std::string Concelho;

/** @brief Creates a type name for the iterator. */
typedef std::map<Concelho, std::vector<Praia*>>::iterator iter_map;

/** @brief Creates a type name for the std::map */
typedef std::pair<iter_map, int> iter_pair;

/**
 *  @brief Class used to store praias.
 *
 *  Database where we will store all the information about the several praias currently loaded in the program.
 */
class Database {

	/**
	 *  @brief Map with Concelho as a key and a vector of objects Praia (from that concelho) as values.
	 */
	std::map<Concelho, std::vector<Praia*>> praias;

public:

	/**
	 *  @brief Database class constructor.
	 */
	Database();

	/**
	 *  @brief Database class destructor.
	 */
	~Database();

	/**
	 * @brief Add objects Praia from .txt file to the map.
	 * @param filename Path to .txt file.
	 * @see praias
	 */
	void load(std::string filename);

	/**
	 * @brief Save objects Praia from map in .txt file.
	 * @param filename Path to .txt file.
	 * @see praias
	 */
	void save(std::string filename);

	/**
	 * @brief Add object Praia to map.
	 * @param p Object Praia to add.
	 * @see praias
	 */
	void addPraia(Praia* p);

	/**
	 * @brief Remove object Praia from map.
	 * @param p Object Praia to add.
	 * @see praias
	 */
	void removePraia(Praia* p);

	/**
	 * @brief Display reduced information of all object Praia in map.
	 * @see praias
	 */
	void showPraias();

	/**
	 * @brief Search object Praia in map.
	 * @param p Object Praia to search for.
	 * @return Return a pair with second value as -1 if not found or the object's iterator in the map as the first value and its index in the vector as the second value.
	 * @see praias
	 * @see iter_pair
	 */
	iter_pair searchPraia(Praia* p);

	/**
	 * @brief Search object Praia with a specific name in map.
	 * @param n Object's name to search for.
	 * @param c Object's concelho to search for.
	 * @return Return a pair with second value as -1 if not found or the object's iterator in the map as the first value and its index in the vector as the second value.
	 * @see praias
	 * @see iter_pair
	 */
	iter_pair searchPraia(std::string n, std::string c);
	
	/**
	 * @brief Search object Praia in map from user's input.
	 * @param i User's input (when choosing from a list of objects Praia).
	 * @return Pointer to an object Praia.
	 */
	Praia* searchPraia(int i);

	/**
	 * @brief Check if object Praia exists in map.
	 * @param p Object Praia to check for.
	 * @return Return true if it exists or false if it doesn't exist.
	 * @see praias
	 */
	bool existPraia(Praia* p);

	/**
	 * @brief Check if object Praia exists in map.
	 * @param n Object's name.
	 * @param c Object's concelho.
	 * @return Return true if it exists or false if it doesn't
	 * @see praias
	 */
	bool existPraia(std::string n, std::string c);

	/**
	 * @brief Return size of map.
	 * @return Number of elements in map.
	 * @see praias
	 */
	unsigned int getSize();

	/**
	 * @brief Orders each vector of object Praia in map.
	 * @see praias
	 */
	void sortPraias();

	/**
	 * @brief Recieves a line from a .txt file and reads its information.
	 * @param l Line from .txt file.
	 */
	void processLine(std::string l);

	/**
	 * @brief Calculates all objects Praia within the range of a certain object Praia.
	 * @param p Object Praia given as the center.
	 * @param r Radius of the search.
	 * @return Returns a map of an object Praia, sorted by distance.
	 */
	std::map<double,Praia*> withInRangePraia(Praia * p, double r);

	/**
	 * @brief Calculates all objects Praia within the range of a certain GPS location.
	 * @param g Object Gps given as center.
	 * @param r Radius of search.
	 * @return Returns a map of an object Praia, sorted by distance.
	 */
	std::map<double,Praia*> withInRangeGps(Gps g, double r);

	/**
	 * @brief Creates a map with the ranges, as keys, and an object Praia, as value.
	 * @param ps Vector of pointer to an object Praia, which we want to sort.
	 * @param ranges Vector of doubles, representing the range.
	 * @return Returns a map of an object Praia, sorted by range.
	 */
	std::map<double,Praia*> orderRange(std::vector<Praia *> ps, std::vector<double> ranges);
};

bool sort(Praia* p1, Praia* p2);

std::string decapitalize(std::string s);

#endif /* DATABASE_H_ */
