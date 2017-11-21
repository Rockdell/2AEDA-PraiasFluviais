#include "Praia.h"

#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

class PAlbufeira : public Praia {
	double area;
public:
	PAlbufeira();
	PAlbufeira(std::string n, std::string c, std::vector<std::string> s, bool bA,  Gps cd, double a);
	~PAlbufeira();

	double getArea() const;
	void setArea(double a);

	std::string savePraia();
};

#endif /* PALBUFEIRA_H_ */
