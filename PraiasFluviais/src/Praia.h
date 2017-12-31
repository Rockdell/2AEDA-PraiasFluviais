
#ifndef PRAIA_H_
#define PRAIA_H_

#include <string>
#include <queue>
#include <unordered_set>
#include <map>

#include "Gps.h"
#include "Exceptions.h"
#include "Service.h"

/**
 *  @file Praia.h
 */

/**
 * @struct closedServiceHash
 * @brief Struct with the hash functions used in an unordered set.
 * @see Service
 * @see servicesClosed
 */
struct closedServiceHash {

	/**
	 *  @brief Hash function.
	 *  @param s Object Service to hash.
	 *  @return Returns the position of the object.
	 */
	int operator() (const Service& s) const {
		int v = 0;

		for (unsigned int i = 0; i < s.getName().length(); i++) {
			v = 37 * v + s.getName()[i];
		}

		return v;
	}

	/**
	 *  @brief Equality function.
	 *  @param s1 Object Service to compare.
	 *  @param s2 Object Service to compare.
	 *  @return Returns true if the arguments are equal and false otherwise.
	 */
	bool operator() (const Service& s1, const Service& s2) const {
		return (s1 == s2);
	}
};

/** @brief Creates a type name for std::unordered_set<Service, closedServiceHash, closedServiceHash>. */
typedef std::unordered_set<Service, closedServiceHash, closedServiceHash> HashTabService;

/**
 *  @brief Base class representing a beach.
 *
 *  This class has two child classes: PAlbufeira and PRio.
 *  @see PAlbufeira
 *  @see PRio
 */
class Praia {

	/**
	 *  @brief Name of the beach.
	 */
	std::string name;

	/**
	 *  @brief Name of the concelho of the beach.
	 */
	std::string concelho;

	/**
	 *  @brief Priority queue of services currently opened, sorted by the date of their last inspection.
	 *  @see Service
	 */
	std::priority_queue<Service> services;

	/**
	 *  @brief Maximum capacity of the beach.
	 */
	unsigned int capacity;

	/**
	 *  @brief True if beach has bandeira azul and false otherwise.
	 */
	bool bandeiraAzul;

	/**
	 *  @brief Gps coordinates of the beach.
	 *  @see Gps
	 */
	Gps coord;

	/**
	 *  @brief Unordered set of services currently closed, temporarily or permanently.
	 *  @see HashTabService
	 *  @see Service
	 */
	HashTabService servicesClosed;

public:

	/**
	 *  @brief Praia class constructor.
	 */
	Praia();

	/**
	 *  @brief Praia class constructor with arguments (without std::priority_queue).
	 *  @param n Name of the object.
	 *  @param c Name of concelho of the object.
	 *  @param cap Capacity of the object.
	 *  @param bA Bandeira of the object.
	 *  @param cd Coordinates of the object.
	 */
	Praia(std::string n, std::string c, unsigned int cap, bool bA, Gps cd);

	/**
	 *  @brief Praia class constructor with arguments (with std::priority_queue).
	 *  @param n Name of the object.
	 *  @param c Name of concelho of the object.
	 *  @param s List of open services of the object.
	 *  @param cap Capacity of the object.
	 *  @param bA Bandeira of the object.
	 *  @param cd Coordinates of the object.
	 */
	Praia(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd);

	/**
	 *  @brief Praia class destructor.
	 */
	virtual ~Praia() {};

	/**
	 *  @brief Gets the name of the object Praia.
	 *  @return Returns the name of the object.
	 *  @see name
	 */
	std::string getName() const;

	/**
	 *  @brief Gets the concelho of the object Praia.
	 *  @return Returns the concelho of the object.
	 *  @see concelho
	 */
	std::string getConcelho() const;

	/**
	 *  @brief Gets the open services of the object PRio.
	 *  @return Returns the width of the object.
	 *  @see services
	 */
	std::priority_queue<Service> getServicesOpen() const;

	/**
	 *  @brief Gets the open services of a certain type of the object PRio.
	 *  @param t Type of services.
	 *  @return Returns the services of that type of the object.
	 *  @see services
	 */
	std::priority_queue<Service> getServicesOpen(service_t t) const;

	/**
	 *  @brief Gets the closed services of the object PRio.
	 *  @return Returns the closed services of the object.
	 *  @see servicesClosed
	 */
	HashTabService getServicesClosed() const;

	/**
	 *  @brief Gets the capacity of the object PRio.
	 *  @return Returns the capacity of the object.
	 *  @see capacity
	 */
	unsigned int getCapacity() const;

	/**
	 *  @brief Gets the bandeira of the object PRio.
	 *  @return Returns the bandeira of the object.
	 *  @see bandeiraAzul
	 */
	bool getBandeira() const;

	/**
	 *  @brief Gets the coordinates of the object PRio.
	 *  @return Returns the coordinates of the object.
	 *  @see services
	 */
	Gps getGps() const;

	/**
	 *  @brief Sets the name of the object Praia according to the argument received.
	 *  @param n New name to replace current name.
	 *  @see name
	 */
	void setName(std::string n);

	/**
	 *  @brief Sets the concelho of the object Praia according to the argument received.
	 *  @param c New concelho to replace current concelho.
	 *  @see concelho
	 */
	void setConcelho(std::string c);

	/**
	 *  @brief Sets the open services of the object Praia according to the argument received.
	 *  @param s New open services to replace current open services.
	 *  @see services
	 */
	void setServices(std::priority_queue<Service> s);

	/**
	 *  @brief Sets the capacity of the object Praia according to the argument received.
	 *  @param cap New capacity to replace current capacity.
	 *  @see capacity
	 */
	void setCapacity(unsigned int cap);

	/**
	 *  @brief Sets the bandeira of the object Praia according to the argument received.
	 *  @param bA New bandeira to replace current bandeira.
	 *  @see bandeiraAzul
	 */
	void setBandeira(bool bA);

	/**
	 *  @brief Sets the coordinates of the object Praia according to the argument received.
	 *  @param cd New coordinates to replace current coordinates.
	 *  @see coord
	 */
	void setGps(Gps cd);

	/**
	 *  @brief Add an object Service (open) to the object.
	 *  @param s Object Service to add.
	 *  @see services
	 */
	void addServiceOpen(Service s);

	/**
	 *  @brief Add an object Service (closed) to the object.
	 *  @param s Object Service to add.
	 *  @see servicesClosed
	 */
	void addServiceClosed(Service s);

	/**
	 *  @brief Removs an object Service from the object.
	 *  @param s Object Service to remove.
	 *  @see services
	 *  @see servicesClosed
	 */
	void removeService(Service s);

	/**
	 *  @brief Performs an inspection to an object Service (open) of the object.
	 *  @param s Object Service to inspect.
	 *  @see services
	 */
	int inspectionService(Service s);

	/**
	 *  @brief Re-opens an object Service (closed) of the object.
	 *  @param s Object Service to re-open.
	 *  @return Returns 0 on success and 1 otherwise.
	 *  @see servicesClosed
	 */
	int openService(Service s);

	/**
	 *  @brief Closes an object Service (open) of the object.
	 *  @param s Object Service to close.
	 *  @param closed_type Type of closing (temporary or permanent).
	 *  @return Returns 0 on success and 1 otherwise.
	 *  @see services
	 */
	int closeService(Service s, unsigned int closed_type);

	/**
	 *  @brief Retrieves an object Service of the object.
	 *  @param index Position of the object Service to retrieve.
	 *  @see services
	 */
	Service accessService(unsigned int index) const;

	/**
	 *  @brief Check if a certain object Service exist in the object.
	 *  @param s Object Service to check.
	 */
	bool existService(Service s);

	/**
	 *  @brief Displays all the objects Service of the object in a friendly way.
	 *  @return Returns 0 on success and 1 otherwise.
	 */
	int showServices();

	/**
	 *  @brief Compares two object Praia.
	 *  @param p1 Comparable object Praia.
	 *  @return Returns true if they are equal and false otherwise.
	 *  @see HashTabService
	 */
	bool operator==(const Praia* p1) const;

	/**
	 *  @brief Displays the object's name and concelho to a std::string.
	 *  @return Returns a formatted std::string.
	 */
	std::string reducedInfoPraia();

	/**
	 *  @brief Abstract method that formats the object's data to a std::string, in order to save in a .txt file.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	virtual std::string savePraia() { return "";}

	/**
	 *  @brief Abstract method that prints the object's data to the screen
	 */
	virtual void fullInfoPraia() {}
};

#endif /* PRAIA_H_ */
