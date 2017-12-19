<<<<<<< HEAD
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
	iter searchPraia(Praia* p);

	/**
	 * @brief Search object with name n in vector "praias"
	 * @param n Object's name to search for
	 * @param c Object's region to search for
	 * @return Return a pair with -1 if not found or the object's iterator in the map and it's index in the vector
	 */
	iter searchPraia(std::string n, std::string c);
	
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
 * @brief Compares two strings
 * @param strFirst First string
 * @param strSecond Second string
 * @return True if equal, false if not
 */
bool compararCaseInsensitive(std::string strFirst, std::string strSecond);

/*
 * @brief Turns all characters in string to lower case
 * @param s String to change
 * @return New string
 */
std::string decapitalize(std::string s);

#endif /* DATABASE_H_ */
=======
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

	/**
	 * @brief Display's all the Praia objects in a reduced way
	 */
	void showPraias();

	/**
	 * @brief Display's a specific Praia object in a reduced way
	 */
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
>>>>>>> branch 'master' of https://github.com/miguelalexbt/2AEDA-PraiasFluviais.git
