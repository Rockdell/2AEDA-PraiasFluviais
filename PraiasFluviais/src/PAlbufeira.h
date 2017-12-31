
#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

#include "Praia.h"

/**
 *  @file PAlbufeira.h
 */

/**
 *  @brief PAlbufeira class is publicly derived from class Praia.
 *
 *  An object PAlbufeira is an object Praia with a lagoon.
 *  @see Praia
 */
class PAlbufeira : public Praia {

	/**
	 *  @brief Area of the lagoon.
	 */
	double area;

public:

	/**
	 *  @brief PAlbufeira class constructor.
	 */
	PAlbufeira();

	/**
	 *  @brief PAlbufeira class constructor with arguments.
	 *  @param n Name of the object.
	 *  @param c Name of concelho of the object.
	 *  @param s Queue of open services of the object.
	 *  @param cap Capacity of the object.
	 *  @param bA Bandeira of the object.
	 *  @param cd Coordinates of the object.
	 *  @param a Area of the lagoon of the object.
	 */
	PAlbufeira(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA,  Gps cd, double a);

	/**
	 *  @brief PAlbufeira class destructor.
	 */
	~PAlbufeira();

	/**
	 *  @brief Gets the area of the object PAlbufeira.
	 *  @return Returns the area of the object.
	 *  @see area
	 */
	double getArea() const;

	/**
	 *  @brief Sets the area of the object PAlbufeira according to the argument received.
	 *  @param a New area to replace current area.
	 *  @see area
	 */
	void setArea(double a);

	/**
	 *  @brief Formats the object PAlbufeira's data to a std::string, in order to save in a .txt file.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	std::string savePraia();

	/**
	 *  @brief Formats the object PAlbufeira's data to a std::string, in order to display it.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	std::string fullInfoPraia();
};

#endif /* PALBUFEIRA_H_ */
