#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

#ifndef GPS_H_
#define GPS_H_

/**
 * @brief Gps coordinates used as data-member in class Praia
 */
class Gps {
	double lat;
	double lon;
public:
	/**
	 * @brief "Empty" Class constructor
	 */
	Gps();

	/**
	 * @brief Class constructor
	 */
	Gps(double lat, double lon);

	/**
	 * @brief Class destructor
	 */
	~Gps();

	/**
	 * @brief Gets the latitude data-member
	 * @return Returns lat data-member
	 */
	double getLat() const;

	/**
	 * @brief Gets the longitude data-member
	 * @return Returns lon data-member
	 */
	double getLon() const;

	/**
	 * @brief Sets the latitude data-member according to user's given argument
	 * @param lat latitude to replace current one
	 */
	void setLat(double lat);

	/**
	 * @brief Sets the longitude data-member according to user's given argument
	 * @param lon longitude to replace current one
	 */
	void setLon(double lon);

	/**
	 * @brief Calculates the distance between places
	 * @param f Gps coordinates to calculate distance to
	 * return Returns distance from the two Gps coordinates in km
	 */
	double diff(Gps f) const;

	/**
	 * @brief Puts Gps coordinates in "easy to read" format
	 * return Returns a string in that format
	 */
	std::string displayGps() const;
};

#endif /* GPS_H_ */
