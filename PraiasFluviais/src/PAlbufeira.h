#include "Praia.h"

#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

class PAlbufeira : public Praia {
	float area;
public:
	PAlbufeira();
	PAlbufeira(std::string n, std::string c, bool bA,  Gps cd, float a);
	~PAlbufeira();

	float getArea() const;
	void setArea(float a);

	std::string savePraia();
};

#endif /* PALBUFEIRA_H_ */
