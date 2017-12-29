
#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

#include "Praia.h"

class PAlbufeira : public Praia {
	double area;
public:
	PAlbufeira();
	PAlbufeira(std::string n, std::string c, std::priority_queue<Service> s, HashTabService hs, unsigned int cap, bool bA,  Gps cd, double a);
	~PAlbufeira();

	double getArea() const;

	void setArea(double a);

	std::string savePraia();
	std::string fullInfoPraia();
};

#endif /* PALBUFEIRA_H_ */
