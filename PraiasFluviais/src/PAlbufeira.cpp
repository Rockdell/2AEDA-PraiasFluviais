#include "PAlbufeira.h"

//Constructors/Destructors
PAlbufeira::PAlbufeira() {
	area = 0;
}
PAlbufeira::PAlbufeira(std::string n, std::string c, bool bA,  Gps cd, float a) : Praia(n,c,bA,cd) {
	area = a;
}
PAlbufeira::~PAlbufeira(){
}

//Get methods
float PAlbufeira::getArea() const {
	return area;
}

//Set methods
void PAlbufeira::setArea(float a) {
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
