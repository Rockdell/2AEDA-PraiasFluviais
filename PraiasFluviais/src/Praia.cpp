#include "Praia.h"

//Constructors/Destructors
Praia::Praia() {
	nome = "";
	concelho = "";
	lotacao = 0;
	bandeiraAzul = false;
	coord = Gps();
}
Praia::Praia(std::string n, std::string c, int lot, bool bA, Gps cd) : nome(n), concelho(c), lotacao(lot), bandeiraAzul(bA), coord(cd) {
}

Praia::Praia(std::string n, std::string c, std::vector<std::string> s, int lot, bool bA, Gps cd) : nome(n), concelho(c), servicos(s), lotacao(lot), bandeiraAzul(bA), coord(cd) {
}

//Get methods
std::string Praia::getNome() const {
	return nome;
}
std::string Praia::getConcelho() const {
	return concelho;
}
std::vector<std::string> Praia::getServicos() const {
	return servicos;
}
int Praia::getLotacao() const {
	return lotacao;
}
bool Praia::getBandeira() const {
	return bandeiraAzul;
}
Gps Praia::getGps() const {
	return coord;
}

//Set methods
void Praia::setNome(std::string n) {
	nome = n;
}
void Praia::setConcelho(std::string c) {
	concelho = c;
}
void Praia::setServicos(std::vector<std::string> s) {
	servicos = s;
}
void Praia::setLotacao(int lot) {
	lotacao = lot;
}
void Praia::setBandeira(bool bA) {
	bandeiraAzul = bA;
}
void Praia::setGps(Gps cd) {
	coord = cd;
}

//Other methods
void Praia::addServico(std::string s) {
	servicos.push_back(s);
}

void Praia::removeServico(std::string s) {
	int i = searchServico(s);

	if(i == -1)
		throw ServicoNotFound(s);
	else
		servicos.erase(servicos.begin() + i);
}

int Praia::searchServico(std::string s) {
	for(size_t i = 0; i < servicos.size(); i++)
	{
		if (s == servicos[i])
			return i;
	}

	return -1;
}

bool Praia::operator ==(const Praia* p1) const {
	if(nome == p1->nome && concelho == p1->concelho)
		return true;
	else
		return false;
}

std::string Praia::reducedInfoPraia() {
	std::string result = "";

	result += " Nome: " + nome + " (" +  concelho + ")";

	return result;
}
