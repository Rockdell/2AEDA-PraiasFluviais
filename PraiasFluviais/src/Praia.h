<<<<<<< HEAD
#include <string>
#include <vector>
#include "Gps.h"
#include "Exceptions.h"
#include <map>

#ifndef PRAIA_H_
#define PRAIA_H_

class Praia {
	std::string nome;
	std::string concelho;
	std::vector<std::string> servicos;
	bool bandeiraAzul;
	Gps coord;
public:
	Praia();
	Praia(std::string n, std::string c, bool bA, Gps cd);
	Praia(std::string n, std::string c, std::vector<std::string> s, bool bA, Gps cd);
	//Praia(std::string n, std::string c, bool bA);
	virtual ~Praia() {};

	std::string getNome() const;
	std::string getConcelho() const;
	std::vector<std::string> getServicos() const;
	bool getBandeira() const;
	Gps getGps() const;

	void setNome(std::string n);
	void setConcelho(std::string c);
	void setServicos(std::vector<std::string> s);
	void setBandeira(bool bA);
	void setGps(Gps cd);

	void addServico(std::string s);
	void removeServico(std::string s);
	int searchServico(std::string s);

	//Change and add some more
	bool operator==(const Praia* p1) const;

	std::string reducedInfoPraia();

	virtual std::string savePraia() { return "";}
	virtual std::string fullInfoPraia() {return "";}

};

#endif /* PRAIA_H_ */
=======
#include <string>
#include <vector>
#include "Gps.h"
#include "Exceptions.h"
#include <map>

#ifndef PRAIA_H_
#define PRAIA_H_

/**
 * @brief Class representing a beach
 */
class Praia {
	std::string nome;
	std::string concelho;
	std::vector<std::string> servicos;
	bool bandeiraAzul;
	Gps coord;
public:
	/**
	 * @brief Basic Constructor
	 */
	Praia();

	/**
	 * @brief Constructor
	 * @param n,c,bA,cd All the data members except for the servicos vector
	 */
	Praia(std::string n, std::string c, bool bA, Gps cd);

	/**
	 * @brief Constructor
	 * @param n,c,s,bA,cd All the data members
	 */
	Praia(std::string n, std::string c, std::vector<std::string> s, bool bA, Gps cd);
	//Praia(std::string n, std::string c, bool bA);

	/**
	 * @brief Virtual Destructor
	 */
	virtual ~Praia() {};

	/**
	 * @brief Gets the name of the beach
	 * @return Returns the name of the beach
	 */
	std::string getNome() const;

	/**
	 * @brief Gets the "concelho" of the beach
	 * @return Returns the "concelho" of the beach
	 */
	std::string getConcelho() const;

	/**
	 * @brief Gets the services of the beach
	 * @return Returns the services of the beach
	 */
	std::vector<std::string> getServicos() const;

	/**
	 * @brief Checks if the beach has blue flag
	 * @return Returns the "bandeiraAzul" data member
	 */
	bool getBandeira() const;

	/**
	 * @brief Gets the Gps coordinates of the beach
	 * @return Returns the Gps coordinates of the beach
	 */
	Gps getGps() const;

	/**
	 * @brief Sets the name of the beach
	 * @param n New beach name
	 */
	void setNome(std::string n);

	/**
	 * @brief Sets the "concelho" of the beach
	 * @param c New "concelho" name
	 */
	void setConcelho(std::string c);

	/**
	 * @brief Sets the services of the beach
	 * @param s New services vector
	 */
	void setServicos(std::vector<std::string> s);

	/**
	 * @brief Sets the blue flag condition of the beach
	 * @param bA New blue flag condition
	 */
	void setBandeira(bool bA);

	/**
	 * @brief Sets the Gps coordinates of the beach
	 * @param cd New Gps coordinates
	 */
	void setGps(Gps cd);

	/**
	 * @brief Adds a new service to the beach's vector of services
	 * @param s New service to add
	 */
	void addServico(std::string s);

	/**
	 * @brief Removes a service from the beach's vector of services
	 * @param s Service to remove
	 */
	void removeServico(std::string s);

	/**
	 * @brief Searchs for a specific service
	 * @param s Service to search for
	 * @return Returns the index of the service in the services vector (if it exists)
	 */
	int searchServico(std::string s);

	//Change and add some more
	/**
	 * @brief Compares two Praia objects
	 * @param p1 Praia to compare to
	 * @return Returns true if equal or false if not equal
	 */
	bool operator==(const Praia* p1) const;

	/**
	 * @brief Gives a string with the name and "concelho" of the Praia object
	 * @return Returns the string in that format
	 */
	std::string reducedInfoPraia();

	/**
	 * @brief Virtual for the other functions (PRio, PAlbufeira)
	 */
	virtual std::string savePraia() = 0;

	/**
	 * @brief Virtual for the other functions (PRio, PAlbufeira)
	 */
	virtual std::string fullInfoPraia() = 0;

};

#endif /* PRAIA_H_ */
>>>>>>> branch 'master' of https://github.com/miguelalexbt/2AEDA-PraiasFluviais.git
