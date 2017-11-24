#include "Praia.h"

#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

/**
 * @brief Class derived from Praia representing a different type of beach
 */
class PAlbufeira : public Praia {
	double area;
public:
	/**
	 * @brief Basic Constructor
	 */
	PAlbufeira();

	/**
	 * @brief Basic Constructor
	 * @param n,c,s,bA,cd arguments for the Praia constructor
	 * @param a area (Data member for PRio class)
	 */
	PAlbufeira(std::string n, std::string c, std::vector<std::string> s, bool bA,  Gps cd, double a);

	/**
	 * @brief Destructor
	 */
	~PAlbufeira();

	/**
	 * @brief Gets the area of the beach
	 * @return Return the area of the beach
	 */
	double getArea() const;

	/**
	 * @brief Sets the area of the beach
	 * @param a new area value
	 */
	void setArea(double a);

	/**
	 * @brief Puts the PAlbufeira object's data in a string format for the output file
	 * @return Returns the string with the object's data
	 */
	std::string savePraia();

	/**
	 * @brief Puts the object's info in a user friendly format
	 * @return Returns the string with the object's data in a user friendly format
	 */
	std::string fullInfoPraia();
};

#endif /* PALBUFEIRA_H_ */
