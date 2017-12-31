#include "Gps.h"

//Constructors
Gps::Gps() : lat(0), lon(0){
}
Gps::Gps(double lat, double lon) : lat(lat), lon(lon) {
}
Gps::~Gps() {
}

//Get Methods
double Gps::getLat() const {
	return lat;
}
double Gps::getLon() const {
	return lon;
}

//Set Methods
void Gps::setLat(double lat) {
	this->lat = lat;
}
void Gps::setLon(double lon) {
	this->lon = lon;
}

//Additional Methods
double Gps::diff(Gps f) const {

	//Formula to calculate distance between locations using GPS parameters
	double R = 6371; // km
	double pi = 3.14159265359;
	double vlat = (f.getLat() - lat) * (pi / 180);
	double vlon = (f.getLon() - lon) * (pi / 180);

	double a = pow(sin(vlat/2),2) + cos(lat*(pi/180)) * cos(f.getLat()*(pi/180)) * pow(sin(vlon/2),2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	double d = R * c;

	return d;
}

std::string Gps::displayGps() const {

	std::ostringstream oss;

	//Latitude calculations
	double tlat = fabs(lat);
	oss << trunc(tlat) << " deg ";
	tlat -= trunc(tlat);
	tlat *= 60;

	oss << trunc(tlat) << "' ";
	tlat -= trunc(tlat);
	tlat *= 60;
	tlat = round(tlat * 10) / 10;

	oss << tlat << "'' ";

	if(lat > 0)
		oss << "N" << " / ";
	else
		oss << "S" << " / ";

	//Longitude calculations
	double tlon = fabs(lon);
	oss << trunc(tlon) << " deg ";
	tlon -= trunc(tlon);
	tlon *= 60;

	oss << trunc(tlon) << "' ";
	tlon -= trunc(tlon);
	tlon *= 60;
	tlon = round(tlon * 10) / 10;

	oss << tlon << "'' ";

	if(lon > 0)
		oss << "E";
	else
		oss << "W";

	return oss.str();
}
