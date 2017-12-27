
#include "PAlbufeira.h"

//Constructors
PAlbufeira::PAlbufeira() {
	area = 0;
}
PAlbufeira::PAlbufeira(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA,  Gps cd, double a) : Praia(n,c,s,cap,bA,cd) {
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

//Other methods //TODO change later
std::string PAlbufeira::savePraia() {

	std::string praia = "A;";

//	praia += getNome() + ";" + getConcelho() + ";";
//
//	if (!getServicos().empty()) {
//		for (size_t i = 0; i < getServicos().size(); i++) {
//
//			Servico tmp = getServicos()[i];
//
//			if (i == getServicos().size() - 1)
//				praia += from_enum(tmp.getTipo()) + " " + tmp.getNome() + " " + tmp.getData().display() + " " + std::to_string(tmp.getStatus());
//			else {
//				praia += from_enum(tmp.getTipo()) + " " + tmp.getNome() + " " + tmp.getData().display() + " " + std::to_string(tmp.getStatus()) + ", ";
//			}
//		}
//	}
//	else
//		praia += "null_servicos";
//
//	praia += ";";
//
//	praia += std::to_string(getLotacao()) + ";";
//
//	if(getBandeira())
//		praia += "1;";
//	else
//		praia += "0;";
//
//	praia += std::to_string(getGps().getLat()) + " " + std::to_string(getGps().getLon()) + ";";
//
//	praia += std::to_string(area);

	return praia;
}

//TODO may need to change the way servicos are displayed
std::string PAlbufeira::fullInfoPraia() {
	std::string result = "\n";

//	result += " Nome: " + getNome() + "\n" + " Concelho: " + getConcelho() + "\n" + " Servicos: \n";
//
//	if (!getServicos().empty()) {
//
//		for (size_t i = 0; i < getServicos().size(); i++) {
//			if (i == getServicos().size() - 1)
//				result += " #" + std::to_string(i + 1) + " " + getServicos()[i].getNome() + " (" + from_enum(getServicos()[i].getTipo()) + ")";
//			else {
//				result += " #" + std::to_string(i + 1) + " " + getServicos()[i].getNome() + " (" + from_enum(getServicos()[i].getTipo()) + ")\n";
//			}
//		}
//	}
//	else
//		result += "sem servicos";
//
//	result += "\n";
//
//	result += " Lotacao: " + std::to_string(getLotacao()) + "\n";
//
//	std::string bandeira = getBandeira() ? "sim" : "não";
//
//	result += " Bandeira Azul: " + bandeira + "\n" +  " Coordenadas: " + getGps().displayGps() + "\n";
//	result += " Area: " + std::to_string(area) + "\n";

	return result;
}
