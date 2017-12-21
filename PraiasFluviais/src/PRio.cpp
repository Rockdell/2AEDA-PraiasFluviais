#include "PRio.h"

//Constructors/Destructors
PRio::PRio() : Praia() {
	largura = 0;
	caudal = 0;
	profundidade = 0;
}
PRio::PRio(std::string n, std::string c, std::vector<Servico> s, int lot, bool bA, Gps cd, double l, double cl, double p) : Praia(n,c,s,lot,bA,cd) {
	largura = l;
	caudal = cl;
	profundidade = p;
}
PRio::~PRio() {
}

//Get methods
double PRio::getLargura() const {
	return largura;
}
double PRio::getCaudal() const {
	return caudal;
}
double PRio::getProfundidade() const {
	return profundidade;
}

//Set methods
void PRio::setLargura(double l) {
	largura = l;
}
void PRio::setCaudal(double c) {
	caudal = c;
}
void PRio::setProfundidade(double p) {
	profundidade = p;
}

std::string PRio::savePraia() {

	std::string praia = "R;";

	praia += getNome() + ";" + getConcelho() + ";";

	if (!getServicos().empty()) {
		for (size_t i = 0; i < getServicos().size(); i++) {
			Servico tmp = getServicos()[i];

			if (i == getServicos().size() - 1)
				praia += from_enum(tmp.getTipo()) + " " + tmp.getNome() + " " + tmp.getData().display() + " " + std::to_string(tmp.getStatus());
			else {
				praia += from_enum(tmp.getTipo()) + " " + tmp.getNome() + " " + tmp.getData().display() + " " + std::to_string(tmp.getStatus()) + ", ";
			}
		}
	}
	else
		praia += "null_servicos";

	praia += ";";

	praia += std::to_string(getLotacao()) + ";";

	if(getBandeira())
		praia += "1;";
	else
		praia += "0;";

	praia += std::to_string(getGps().getLat()) + " " + std::to_string(getGps().getLon()) + ";";

	praia += std::to_string(largura) + ";" + std::to_string(caudal) + ";" + std::to_string(profundidade);

	return praia;

}

std::string PRio::fullInfoPraia() {
	std::string result = "\n";

	result += " Nome: " + getNome() + "\n" + " Concelho: " + getConcelho() + "\n" + " Servicos: ";

	if (!getServicos().empty()) {
		for (size_t i = 0; i < getServicos().size(); i++) {
			if (i == getServicos().size() - 1)
				result += getServicos()[i].getNome();
			else {
				result += getServicos()[i].getNome() + ", ";
			}
		}
	}
	else
		result += "sem servicos";

	result += "\n";

	result += " Lotacao: " + std::to_string(getLotacao()) + "\n";

	std::string bandeira = getBandeira() ? "sim" : "nao";

	result += " Bandeira Azul: " + bandeira + "\n" +  " Coordenadas: " + getGps().displayGps() + "\n";
	result += " Largura: " + std::to_string(largura) + "\n" + " Caudal: " + std::to_string(caudal) + "\n" +
			" Profundidade: " + std::to_string(profundidade) + "\n";

	return result;

}
