#include "Praia.h"

#ifndef PRIO_H_
#define PRIO_H_

class PRio : public Praia {
	double largura, caudal, profundidade;
public:
	PRio();
	PRio(std::string n, std::string c, std::vector<std::string> s, int lot, bool bA, Gps cd, double l, double cl, double p);
	~PRio();

	double getLargura() const;
	double getCaudal() const;
	double getProfundidade() const;
	void setLargura(double l);
	void setCaudal(double c);
	void setProfundidade(double p);

	std::string savePraia();
	std::string fullInfoPraia();
};

#endif /* PRIO_H_ */
