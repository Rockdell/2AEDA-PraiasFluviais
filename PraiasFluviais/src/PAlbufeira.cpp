
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

//Other methods
std::string PAlbufeira::savePraia() {

	std::string praia = "A;";

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

	praia += std::to_string(area);

	return praia;
}

void PAlbufeira::fullInfoPraia() {
	std::cout << std::endl;

	std::cout << " Name: " << getName() << "\n" << " Concelho: " << getConcelho() << "\n\n";

	if(!getServicesOpen().empty())
		showServices();
	else
		std::cout << "no services\n";

	std::cout << " Capacity: " << getCapacity() << "\n";

	std::string bandeira = getBandeira() ? "yes" : "no";

	std::cout << " Bandeira azul: " << bandeira << "\n" <<  " Coordinates: " << getGps().displayGps() << "\n";
	std::cout << " Area: " << area << "\n";
}
