#include "PRio.h"

//Constructors/Destructors
PRio::PRio() : Praia() {
	largura = 0;
	caudal = 0;
	profundidade = 0;
}
PRio::PRio(std::string n, std::string c, bool bA, Gps cd, float l, float cl, float p) : Praia(n,c,bA,cd) {
	largura = l;
	caudal = cl;
	profundidade = p;
}
PRio::~PRio() {
}

//Get methods
float PRio::getLargura() const {
	return largura;
}
float PRio::getCaudal() const {
	return caudal;
}
float PRio::getProfundidade() const {
	return profundidade;
}

//Set methods
void PRio::setLargura(float l) {
	largura = l;
}
void PRio::setCaudal(float c) {
	caudal = c;
}
void PRio::setProfundidade(float p) {
	profundidade = p;
}

std::string PRio::savePraia() {

	std::string praia = "R;";

	praia += getNome() + ";" + getConcelho() +";";

	if(getServicos().empty())
		praia += "null_servicos;";
	else {
		for(size_t i = 0; i < getServicos().size(); i++) {

			if(i == getServicos().size() - 1)
				praia += getServicos()[i] + ";";
			else
				praia += getServicos()[i] + ",";
		}
	}

	if(getBandeira())
		praia += "1;";
	else
		praia += "0;";

	praia += std::to_string(getGps().getLat()) + " " + std::to_string(getGps().getLon()) + ";";

	praia += std::to_string(largura) + ";" + std::to_string(caudal) + ";" + std::to_string(profundidade);

	return praia;

}
