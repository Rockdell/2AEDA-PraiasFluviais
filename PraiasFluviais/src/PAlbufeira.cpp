#include "PAlbufeira.h"

//Constructors/Destructors
PAlbufeira::PAlbufeira() {
	area = 0;
}
PAlbufeira::PAlbufeira(std::string n, std::string c, std::vector<std::string> s, bool bA,  Gps cd, double a) : Praia(n,c,s,bA,cd) {
	area = a;
}
PAlbufeira::~PAlbufeira(){
}

//Get methods
double PAlbufeira::getArea() const {
	return area;
}

//Set methods
void PAlbufeira::setArea(double a) {
	area = a;
}

std::string PAlbufeira::savePraia() {

	std::string praia = "A;";

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

	praia += std::to_string(getGps().getLat()) + "," + std::to_string(getGps().getLon()) + ";";

	praia += std::to_string(area);

	return praia;
}

//TODO not done yet
std::string PAlbufeira::fullInfoPraia() {
	std::string result = "";

	result += " Nome: " + getNome() + "\n" + " Concelho: " + getConcelho() + "\n" + " Serviços: ";

	for(size_t i = 0; i < getServicos().size(); i++) {
		if(i == getServicos().size() - 1)
			result += getServicos()[i] + "\n";
		else {
			result += getServicos()[i] + ", ";
		}
	}

	//result += " Bandeira Azul: " +  getBandeira() + "\n" +  " Coordenadas: " + caudal + " ";

	return result;

}
