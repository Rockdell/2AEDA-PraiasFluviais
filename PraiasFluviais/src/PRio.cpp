#include "PRio.h"

//Constructors
PRio::PRio() : Praia() {
	width = 0;
	flow = 0;
	depth = 0;
}
PRio::PRio(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd, double w, double f, double d) : Praia(n,c,s,cap,bA,cd) {
	width = w;
	flow = f;
	depth = d;
}
PRio::~PRio() {
}

//Get methods
double PRio::getWidth() const {
	return width;
}
double PRio::getFlow() const {
	return flow;
}
double PRio::getDepth() const {
	return depth;
}

//Set methods
void PRio::setWidth(double w) {
	width = w;
}
void PRio::setFlow(double f) {
	flow = f;
}
void PRio::setDepth(double d) {
	depth = d;
}

//Other methods //TODO change later
std::string PRio::savePraia() {

	std::string praia = "R;";

//	praia += getNome() + ";" + getConcelho() + ";";
//
//	if (!getServicos().empty()) {
//		for (size_t i = 0; i < getServicos().size(); i++) {
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
//	praia += std::to_string(largura) + ";" + std::to_string(caudal) + ";" + std::to_string(profundidade);

	return praia;

}

std::string PRio::fullInfoPraia() { //TODO might not need to change
	std::string result = "\n";
//
//	result += " Nome: " + getNome() + "\n" + " Concelho: " + getConcelho() + "\n" + " Servicos: ";
//
//	if (!getServicos().empty()) {
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
//	std::string bandeira = getBandeira() ? "sim" : "nao";
//
//	result += " Bandeira Azul: " + bandeira + "\n" +  " Coordenadas: " + getGps().displayGps() + "\n";
//	result += " Largura: " + std::to_string(largura) + "\n" + " Caudal: " + std::to_string(caudal) + "\n" +
//			" Profundidade: " + std::to_string(profundidade) + "\n";

	return result;

}
