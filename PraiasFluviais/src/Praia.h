#include <string>
#include <vector>
#include "Servico.h"
#include "Gps.h"
#include "Exceptions.h"
#include "json.hpp"

#ifndef PRAIA_H_
#define PRAIA_H_

using json = nlohmann::json;

class Praia {
	std::string nome;
	std::string concelho;
	std::vector<Servico> servicos;
	bool bandeiraAzul;
	Gps coord;
public:
	Praia();
	Praia(std::string n, std::string c, bool bA, Gps cd);
	Praia(std::string n, std::string c, bool bA);
	virtual ~Praia() {};

	std::string getNome() const;
	std::string getConcelho() const;
	std::vector<Servico> getServicos() const;
	bool getBandeira() const;
	Gps getGps() const;

	void setNome(std::string n);
	void setConcelho(std::string c);
	void setServicos(std::vector<Servico> s);
	void setBandeira(bool bA);
	void setGps(Gps cd);

	void addServico(Servico s);
	void removeServico(Servico s);
	int searchServico(Servico s);

	//Change and add some more
	bool operator==(const Praia* p1) const;

	virtual json savePraia() = 0;

};

#endif /* PRAIA_H_ */
