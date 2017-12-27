
#ifndef PRIO_H_
#define PRIO_H_

#include "Praia.h"

class PRio : public Praia {
	double width;
	double flow;
	double depth;
public:
	PRio();
	PRio(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd, double w, double f, double d);
	~PRio();

	double getWidth() const;
	double getFlow() const;
	double getDepth() const;

	void setWidth(double w);
	void setFlow(double f);
	void setDepth(double d);

	std::string savePraia();
	std::string fullInfoPraia();
};

#endif /* PRIO_H_ */
