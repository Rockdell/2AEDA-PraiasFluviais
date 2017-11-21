#include <string>
#include <vector>
#include "Gps.h"
#include "Exceptions.h"
#include <map>

#ifndef PRAIA_H_
#define PRAIA_H_

class Praia {
	std::string nome;
	std::string concelho;
	std::vector<std::string> servicos;
	bool bandeiraAzul;
	Gps coord;
public:
	Praia();
	Praia(std::string n, std::string c, bool bA, Gps cd);
	Praia(std::string n, std::string c, bool bA);
	virtual ~Praia() {};

	std::string getNome() const;
	std::string getConcelho() const;
	std::vector<std::string> getServicos() const;
	bool getBandeira() const;
	Gps getGps() const;

	void setNome(std::string n);
	void setConcelho(std::string c);
	void setServicos(std::vector<std::string> s);
	void setBandeira(bool bA);
	void setGps(Gps cd);

	void addServico(std::string s);
	void removeServico(std::string s);
	int searchServico(std::string s);

	//Change and add some more
	bool operator==(const Praia* p1) const;

	virtual std::string savePraia() = 0;

};

#endif /* PRAIA_H_ */
