#include "Praia.h"

#ifndef PRIO_H_
#define PRIO_H_

/**
 * @brief Class derived from Praia representing a different type of beach
 */
class PRio : public Praia {
	double largura, caudal, profundidade;
public:
	/**
	 * @brief Basic Constructor
	 */
	PRio();

	/**
	 * @brief Constructor
	 * @param n,c,s,bA,cd arguments for the Praia constructor
	 * @param l,cl,p largura, caudal, profundidade (Data members for PRio class)
	 */
	PRio(std::string n, std::string c, std::vector<std::string> s, bool bA, Gps cd, double l, double cl, double p);

	/**
	 * @brief Destructor
	 */
	~PRio();

	/**
	 * @brief Gets the "largura" of the beach
	 * @return Returns the "largura" of the beach
	 */
	double getLargura() const;

	/**
	 * @brief Gets the "caudal" of the beach
	 * @return Returns the "caudal" of the beach
	 */
	double getCaudal() const;

	/**
	 * @brief Gets the "profundidade" of the beach
	 * @return Returns the "profundidade" of the beach
	 */
	double getProfundidade() const;

	/**
	 * @brief Sets the "largura" of the beach
	 * @param a new "largura" value
	 */
	void setLargura(double l);

	/**
	 * @brief Sets the "caudal" of the beach
	 * @param a new "caudal" value
	 */
	void setCaudal(double c);

	/**
	 * @brief Sets the "profundidade" of the beach
	 * @param a new "profundidade" value
	 */
	void setProfundidade(double p);

	/**
	 * @brief Puts the PRio object's data in a string format for the output file
	 * @return Returns the string with the object's data
	 */
	std::string savePraia();

	/**
	 * @brief Puts the object's info in a user friendly format
	 * @return Returns the string with the object's data in a user friendly format
	 */
	std::string fullInfoPraia();
};

#endif /* PRIO_H_ */
