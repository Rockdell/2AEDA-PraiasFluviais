#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

#ifndef GPS_H_
#define GPS_H_

class Gps {
	double lat;
	double lon;
public:
	Gps();
	Gps(double lat, double lon);
	~Gps();

	double getLat() const;
	double getLon() const;
	void setLat(double lat);
	void setLon(double lon);
	double diff(Gps f) const;
	std::string displayGps() const;
};

#endif /* GPS_H_ */
