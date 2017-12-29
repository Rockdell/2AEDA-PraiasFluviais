#include "PRio.h"

//Constructors
PRio::PRio() : Praia() {
	width = 0;
	flow = 0;
	depth = 0;
}
PRio::PRio(std::string n, std::string c, std::priority_queue<Service> s, HashTabService hs, unsigned int cap, bool bA, Gps cd, double w, double f, double d) : Praia(n, c, s, hs, cap, bA, cd) {
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

	praia += getName() + ";" + getConcelho() + ";";

	if (getServices().empty() && getServicesClosed().empty())
	{
		praia += "null_servicos";
	}
	else {
		if (!getServices().empty()) {
			std::priority_queue<Service> s_tmp = getServices();
			while (!s_tmp.empty()) {

				Service tmp = s_tmp.top();

				if (s_tmp.size() == 1 && getServicesClosed().empty())
					praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed());
				else {
					praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed()) + ", ";
				}

				s_tmp.pop();
			}
		}

		if (!getServicesClosed().empty()) {
			HashTabService ht_tmp = getServicesClosed();
			for (auto it = ht_tmp.begin(); it != ht_tmp.end(); it++)
			{
				Service tmp = *it;

				praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed()) + ", ";
			}
			//Livra-se do espaço e da virgula a mais
			praia.pop_back();
			praia.pop_back();
		}
	}

	praia += ";";

	praia += std::to_string(getCapacity()) + ";";

	if(getBandeira())
		praia += "1;";
	else
		praia += "0;";

	praia += std::to_string(getGps().getLat()) + " " + std::to_string(getGps().getLon()) + ";";

	praia += std::to_string(width) + ";" + std::to_string(flow) + ";" + std::to_string(depth);

	return praia;

}

std::string PRio::fullInfoPraia() { //TODO might not need to change
	std::string result = "\n";

	result += " Nome: " + getName() + "\n" + " Concelho: " + getConcelho() + "\n" + " Servicos: ";

	if(!getServices().empty())
			showServices();
		else
			result += "sem servicos\n";

	result += " Lotacao: " + std::to_string(getCapacity()) + "\n";

	std::string bandeira = getBandeira() ? "sim" : "nao";

	result += " Bandeira Azul: " + bandeira + "\n" +  " Coordenadas: " + getGps().displayGps() + "\n";
	result += " Largura: " + std::to_string(width) + "\n" + " Caudal: " + std::to_string(flow) + "\n" +	" Profundidade: " + std::to_string(depth) + "\n";

	return result;

}
