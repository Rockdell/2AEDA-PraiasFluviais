
#ifndef PRAIA_H_
#define PRAIA_H_

#include <string>
#include <queue>
#include <unordered_set>
#include <map>

#include "Gps.h"
#include "Exceptions.h"
#include "Service.h"

struct closedServiceHash {

	int operator() (const Service& s) const {
		int v = 0;

		for (unsigned int i = 0; i < s.getName().length(); i++) {
			v = 37 * v + s.getName()[i];
		}

		return v;
	}

	bool operator() (const Service& s1, const Service& s2) const {
		return (s1 == s2);
	}
};

typedef std::unordered_set<Service, closedServiceHash, closedServiceHash> HashTabService;

class Praia {
	std::string name;
	std::string concelho;
	std::priority_queue<Service> services;
	unsigned int capacity;
	bool bandeiraAzul;
	Gps coord;

	HashTabService servicesClosed;

public:
	Praia();
	Praia(std::string n, std::string c, unsigned int cap, bool bA, Gps cd);
	Praia(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cdd);
	virtual ~Praia() {};

	std::string getName() const;
	std::string getConcelho() const;
	std::priority_queue<Service> getServices() const;
	std::priority_queue<Service> getServices(service_t t) const;
	unsigned int getCapacity() const;
	bool getBandeira() const;
	Gps getGps() const;

	void setName(std::string n);
	void setConcelho(std::string c);
	void setServices(std::priority_queue<Service> s);
	void setCapacity(unsigned int lot);
	void setBandeira(bool bA);
	void setGps(Gps cd);

	void addService(Service s);
	void addService(std::priority_queue<Service> s);
	void removeService(Service s);
	bool existService(Service s);
	void showServices();

	//Change and add some more
	bool operator==(const Praia* p1) const;

	std::string reducedInfoPraia();

	virtual std::string savePraia() { return "";}
	virtual std::string fullInfoPraia() {return "";}

};

#endif /* PRAIA_H_ */
