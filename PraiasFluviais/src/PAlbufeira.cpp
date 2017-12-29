
#include "PAlbufeira.h"

//Constructors
PAlbufeira::PAlbufeira() {
	area = 0;
}
PAlbufeira::PAlbufeira(std::string n, std::string c, std::priority_queue<Service> s, HashTabService hs, unsigned int cap, bool bA,  Gps cd, double a) : Praia(n,c,s,hs,cap,bA,cd) {
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

	praia += std::to_string(area);

	return praia;
}

//TODO may need to change the way servicos are displayed
std::string PAlbufeira::fullInfoPraia() {
	std::string result = "\n";

	result += " Nome: " + getName() + "\n" + " Concelho: " + getConcelho() + "\n" + " Servicos: \n";

	if(!getServices().empty())
		showServices();
	else
		result += "sem servicos\n";

	result += " Lotacao: " + std::to_string(getCapacity()) + "\n";

	std::string bandeira = getBandeira() ? "sim" : "não";

	result += " Bandeira Azul: " + bandeira + "\n" +  " Coordenadas: " + getGps().displayGps() + "\n";
	result += " Area: " + std::to_string(area) + "\n";

	return result;
}
