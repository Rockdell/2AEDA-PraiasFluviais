
#ifndef GPS_H_
#define GPS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

/**
 *  @file Gps.h
 */

/**
 *  @brief Class representing GPS coordinates
 */
class Gps {

	/**
	 *  @brief Latitude of the coordinates.
	 */
	double lat;

	/**
	 *  @brief Longitude of the coordinates.
	 */
	double lon;

public:

	/**
	 *  @brief Gps class constructor.
	 */
	Gps();

	/**
	 *  @brief Gps class constructor with arguments.
	 *  @param lat Latitude of the object.
	 *  @param lon Longitude of the object.
	 *  @see lat
	 *  @see lon
	 */
	Gps(double lat, double lon);

	/**
	 * @brief Gps class destructor.
	 */
	~Gps();

	/**
	 *  @brief Gets the latitude of the object Gps.
	 *  @return Returns latitutde of the object.
	 *  @see lat
	 */
	double getLat() const;

	/**
	 *  @brief Gets the longitude of the object Gps.
	 *  @return Returns longitude of the object.
	 *  @see lon
	 */
	double getLon() const;

	/**
	 *  @brief Sets the latitude of the object Gps according to the argument received.
	 *  @param lat New latitude to replace current latitude.
	 *  @see lat
	 */
	void setLat(double lat);

	/**
	 *  @brief Sets the longitude of the object Gps according to the argument received.
	 *  @param lon New longitude to replace current longitude.
	 *  @see lon
	 */
	void setLon(double lon);

	/**
	 *  @brief Calculates the distance between two object Gps coordinates.
	 *  @param f Object Gps coordinates to calculate distance to.
	 *  @return Returns distance betweem the two object Gps coordinates (in kilometers).
	 */
	double diff(Gps f) const;

	/**
	 *  @brief Formats the object Gps's data to a std::string.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	std::string displayGps() const;
};

#endif /* GPS_H_ */
