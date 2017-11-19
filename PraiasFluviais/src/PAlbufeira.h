#include "Praia.h"

#ifndef PALBUFEIRA_H_
#define PALBUFEIRA_H_

using json = nlohmann::json;

class PAlbufeira : public Praia {
	float area;
public:
	PAlbufeira();
	PAlbufeira(std::string n, std::string c, bool bA,  Gps cd, float a);
	~PAlbufeira();

	float getArea() const;
	void setArea(float a);

	json savePraia();

	void to_json(json &j, const PAlbufeira* p);
	void from_json(const json &j, PAlbufeira* p);
};

#endif /* PALBUFEIRA_H_ */
