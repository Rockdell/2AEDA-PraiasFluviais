#include "Praia.h"

#ifndef PRIO_H_
#define PRIO_H_

class PRio : public Praia {
	float largura, caudal, profundidade;
public:
	PRio();
	PRio(std::string n, std::string c, bool bA, Gps cd, float l, float cl, float p);
	~PRio();

	float getLargura() const;
	float getCaudal() const;
	float getProfundidade() const;
	void setLargura(float l);
	void setCaudal(float c);
	void setProfundidade(float p);

	std::string savePraia();
};

#endif /* PRIO_H_ */
