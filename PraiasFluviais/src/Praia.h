#include <string>
#include <vector>
#include <map>

#include "Gps.h"
#include "Servico.h"
#include "Exceptions.h"

#ifndef PRAIA_H_
#define PRAIA_H_

class Praia {
	std::string nome;
	std::string concelho;
	std::vector<Servico> servicos;
	int lotacao;
	bool bandeiraAzul;
	Gps coord;
public:
	Praia();
	Praia(std::string n, std::string c, int lot, bool bA, Gps cd);
	Praia(std::string n, std::string c, std::vector<Servico> s, int lot, bool bA, Gps cd);
	virtual ~Praia() {};

	std::string getNome() const;
	std::string getConcelho() const;
	std::vector<Servico> getServicos() const;
	int getLotacao() const;
	bool getBandeira() const;
	Gps getGps() const;

	void setNome(std::string n);
	void setConcelho(std::string c);
	void setServicos(std::vector<Servico> s);
	void setLotacao(int lot);
	void setBandeira(bool bA);
	void setGps(Gps cd);

	void addServico(Servico s);
	void removeServico(Servico s);
	int searchServico(Servico s);

	//Change and add some more
	bool operator==(const Praia* p1) const;

	std::string reducedInfoPraia();

	virtual std::string savePraia() { return "";}
	virtual std::string fullInfoPraia() {return "";}

};

#endif /* PRAIA_H_ */
