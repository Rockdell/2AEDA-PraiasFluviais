#include "PRio.h"

//Constructors
PRio::PRio() : Praia() {
	width = 0;
	flow = 0;
	depth = 0;
}
PRio::PRio(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd, double w, double f, double d) : Praia(n, c, s, cap, bA, cd) {
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

//Other methods
std::string PRio::savePraia() {

	std::string praia = "R;";

	praia += getName() + ";" + getConcelho() + ";";

	if (getServicesOpen().empty() && getServicesClosed().empty()) {
		praia += "null_servicos";
	}
	else {
		if (!getServicesOpen().empty()) {
			std::priority_queue<Service> s_tmp = getServicesOpen();

			while (!s_tmp.empty()) {

				Service tmp = s_tmp.top();

				if (s_tmp.size() == 1 && getServicesClosed().empty())
					praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed()) + " " + tmp.getStatus().getClosingDate().display();
				else {
					praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed()) + " " + tmp.getStatus().getClosingDate().display() + ", ";
				}

				s_tmp.pop();
			}
		}

		if (!getServicesClosed().empty()) {
			HashTabService ht_tmp = getServicesClosed();

			for (auto it = ht_tmp.begin(); it != ht_tmp.end(); it++) {
				Service tmp = *it;

				praia += from_enum(tmp.getType()) + " " + tmp.getName() + " " + tmp.getDate().display() + " " + std::to_string(tmp.getStatus().getClosed()) + " " + tmp.getStatus().getClosingDate().display() + ", ";
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

void PRio::fullInfoPraia() {
	std::cout << std::endl;

	std::cout << " Nome: " << getName() << "\n" << " Concelho: " << getConcelho() << "\n\n";

	if(!getServicesOpen().empty())
		showServices();
	else
		std::cout << "sem servicos\n";

	std::cout << " Lotacao: " << getCapacity() << "\n";

	std::string bandeira = getBandeira() ? "sim" : "nao";

	std::cout << " Bandeira Azul: " << bandeira << "\n" <<  " Coordenadas: " << getGps().displayGps() << "\n";
	std::cout << " Largura: " << width << "\n" << " Caudal: " << flow << "\n" << " Profundidade: " << depth << "\n";
}
