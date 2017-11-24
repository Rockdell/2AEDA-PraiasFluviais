#include "Database.h"

typedef std::string Concelho;

Database::Database() {
}
Database::~Database() {
}

void Database::load(std::string filename) {
	std::ifstream input(filename);
std::string j;

if (!input.is_open())
throw FileNotFound(filename);

std::string line;

while (getline(input, line)) {
	processLine(line);
}

input.close();
}

void Database::save(std::string filename) {
	std::ofstream output(filename);

	if (!output.is_open())
		throw FileNotFound(filename);

	for (iter_map it = praias.begin(); it != praias.end(); it++) {

		for (size_t i = 0; i < it->second.size(); i++)
			output << it->second[i]->savePraia() << std::endl;
	}

	output.close();
}

void Database::addPraia(Praia* p) {

	iter_map it = praias.find(p->getConcelho());

	if (it != praias.end()) {
		it->second.push_back(p);
	}
	else {
		std::vector<Praia*> praiasConcelho;
		praiasConcelho.push_back(p);
		praias.insert(std::make_pair(p->getConcelho(), praiasConcelho));
	}

	sortPraiasNome();
}

void Database::removePraia(Praia* p) {
	iter it = searchPraia(p);

	if (it.second == -1)
		throw PraiaNotFound(p->getNome());
	else {

		//More than 1 element in vector or only 1 element?
		if (it.first->second.size() != 1)
			it.first->second.erase(it.first->second.begin() + it.second);
		else
			praias.erase(p->getConcelho());
	}
}

void Database::showPraias() {

	unsigned int cont = 1;
	unsigned int size = getSize();

	for (iter_map it = praias.begin(); it != praias.end(); it++) {

		for (size_t i = 0; i < it->second.size(); i++) {

			if (i == it->second.size() - 1 && cont == size)
				std::cout << " [" << cont << "]" << it->second[i]->reducedInfoPraia() << std::endl << std::endl;
			else
				std::cout << " [" << cont << "]" << it->second[i]->reducedInfoPraia() << std::endl;

			cont++;
		}
	}
}

iter Database::searchPraia(Praia* p) {

	auto it = praias.find(p->getConcelho());

	if(it != praias.end()) {

		for(size_t i = 0; i < it->second.size(); i++) {

			if(p->getNome() == it->second[i]->getNome())
				return std::make_pair(it, i);
		}

		return std::make_pair(it, -1);
	}
	else
		return std::make_pair(it, -1);
}

iter Database::searchPraia(std::string n, std::string c) {

	auto it = praias.find(c);

	if(it != praias.end()) {

		for(size_t i = 0; i < it->second.size(); i++) {

			if(n == it->second[i]->getNome())
				return std::make_pair(it, i);
		}

		return std::make_pair(it, -1);
	}
	else
		return std::make_pair(it, -1);
}

Praia* Database::searchPraia(int i) {

	unsigned int cont = i;

	for (iter_map it = praias.begin(); it != praias.end(); it++) {
		if (cont >= it->second.size())
			cont -= it->second.size();
		else {

			PRio* p1 = dynamic_cast<PRio*>(it->second[cont]);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(it->second[cont]);

			if (p1 == nullptr)
				return p2;
			else
				return p1;
		}
	}

	//Might not need (when calling this function, it is guaranteed there is a object there
	return nullptr;
}

bool Database::existPraia(Praia* p) {

	iter it = searchPraia(p);

	if(it.second == -1)
		return false;
	else
		return true;
}

bool Database::existPraia(std::string n, std::string c) {

	iter it = searchPraia(n, c);

	if(it.second == -1)
		return false;
	else
		return true;
}

unsigned int Database::getSize() {

	unsigned int cont = 0;

	for(iter_map it = praias.begin(); it != praias.end(); it++) {

		cont += it->second.size();
	}

	return cont;
}

void Database::sortPraiasNome() {

	//Check if there are any Praias to sort
	if(praias.empty())
		return;

	for(iter_map it = praias.begin(); it != praias.end(); it++) {

		if(it->second.empty())
			continue;
		else {

			for(size_t j = it->second.size() - 1; j > 0; j--) {

				bool troca = false;

				for(size_t i = 0; i < j; i++) {

					if(it->second[i+1]->getNome() < it->second[i]->getNome()) {
						std::swap(it->second[i+1],it->second[i]);
						troca = true;
					}
				}

				if(!troca)
					return;
			}
		}
	}
}

void Database::processLine(std::string l) {

	std::istringstream ss1(l);
	std::vector<std::string> properties;
	std::string token;

	//Parse line
	while (getline(ss1, token, ';')) {
		properties.push_back(token);
	}

	//Type
	std::string type = properties[0];

	//Nome
	std::string nome = properties[1];

	//Concelho
	std::string concelho = properties[2];

	//Servicos
	std::string tmp1 = properties[3];
	std::istringstream ss2(tmp1);
	std::vector<std::string> servicos;

	if(tmp1 != "null_servicos") {
		while(getline(ss2, token, ',')) {
			servicos.push_back(token);
		}
	}

	//Bandeira
	bool bandeira;
	std::string tmp2 = properties[4];

	if(tmp2 == "1")
		bandeira = true;
	else
			bandeira = false;

	//Gps
	double lat, lon;
	std::string tmp3 = properties[5];
	std::istringstream ss3(tmp3);
	std::string s_lat, s_lon;
	ss3 >> s_lat >> s_lon;
	lat = std::stod(s_lat);
	lon = std::stod(s_lon);

	Gps gps(lat,lon);

	if(type == "R") {

		//Largura
		double largura;
		std::string tmp4 = properties[6];
		std::istringstream ss4(tmp4);
		std::string s_largura;
		ss4 >> s_largura;
		largura = std::stod(s_largura);

		//Caudal
		double caudal;
		std::string tmp5 = properties[7];
		std::istringstream ss5(tmp5);
		std::string s_caudal;
		ss5 >> s_caudal;
		caudal = std::stod(s_caudal);

		//Profundidade
		double profundidade;
		std::string tmp6 = properties[8];
		std::istringstream ss6(tmp6);
		std::string s_profundidade;
		ss6 >> s_profundidade;
		profundidade = std::stod(s_profundidade);

		PRio* p = new PRio(nome, concelho, servicos, bandeira, gps, largura, caudal, profundidade);

		addPraia(p);
	}
	else {

		//Area
		double area;
		std::string tmp4 = properties[6];
		std::istringstream ss4(tmp4);
		std::string s_area;
		ss4 >> s_area;
		area = std::stod(s_area);

		PAlbufeira* p = new PAlbufeira(nome, concelho, servicos, bandeira, gps, area);

		addPraia(p);
	}
}

std::map<double,Praia*> Database::withInRangePraia(Praia * p, double r) {

	std::vector<double> ranges; //Vector with all the ranges to the selected beach "p"
	std::vector<Praia *> b; //Vector with the all the beaches within the selected range

	for(iter_map it = praias.begin(); it != praias.end(); it++) {

		for(size_t i = 0; i < it->second.size(); i++) {
			double d = it->second[i]->getGps().diff(p->getGps());
			ranges.push_back(d);

			if(d <= r)
				b.push_back(it->second[i]);
		}
	}

	if (b.size() == 0) {
		/*If none of the beaches is within the selected range then we return a vector with
		 * the beaches in ascending order of range, with an "empty" beach as the last element so
		 * we can distinguish between the vector with the beaches within range and the ordered vector*/

		//b = praias;
		for(iter_map it = praias.begin(); it != praias.end(); it++) {

			for(size_t i = 0; i < it->second.size(); i++) {
				b.push_back(it->second[i]);
			}
		}

		std::map<double,Praia*> ret = orderRange(b, ranges);
		//Adds the "empty" object
		PRio* trash = new PRio();
		ret.insert(std::make_pair(-1,trash));
		return ret;
	} 
	else {
		//Clears ranges vector
		ranges.clear();

		//Gets the ranges for the selected praias
		for (size_t i = 0; i < b.size(); i++) {
			double d = b.at(i)->getGps().diff(p->getGps());
			ranges.push_back(d);
		}

		std::map<double,Praia*> ret = orderRange(b, ranges);
		return ret;
	}
}

std::map<double,Praia*> Database::withInRangeGps(Gps g, double r) {

	std::vector<double> ranges; //Vector with all the ranges to the selected beach "p"
	std::vector<Praia *> b; //Vector with the all the beaches within the selected range

	for(iter_map it = praias.begin(); it != praias.end(); it++) {

		for(size_t i = 0; i < it->second.size(); i++) {
			double d = it->second[i]->getGps().diff(g);
			ranges.push_back(d);

			if(d <= r)
				b.push_back(it->second[i]);
		}
	}

	if (b.size() == 0) {
		/*If none of the beaches is within the selected range then we return a vector with
		 * the beaches in ascending order of range, with an "empty" beach as the last element so
		 * we can distinguish between the vector with the beaches within range and the ordered vector*/

		//b = praias;
		for(iter_map it = praias.begin(); it != praias.end(); it++) {

			for(size_t i = 0; i < it->second.size(); i++) {
				b.push_back(it->second[i]);
			}
		}

		std::map<double, Praia*> ret = orderRange(b, ranges);
		//Adds the "empty" object
		PRio* trash = new PRio();
		ret.insert(std::make_pair(-1, trash));
		return ret;
	} else {
		//Clears ranges vector
		ranges.clear();

		for (size_t i = 0; i < b.size(); i++) {
			double d = b.at(i)->getGps().diff(g);
			ranges.push_back(d);
		}

		std::map<double,Praia*> ret = orderRange(b, ranges);
		return ret;
	}

}

std::map<double,Praia*> Database::orderRange(std::vector<Praia *> ps, std::vector<double> ranges) {

	std::map<double,Praia*> ord;

	for(size_t i = 0; i < ps.size() ; i++)
	{
		ord.insert(std::make_pair(ranges.at(i),ps.at(i)));
	}

	return ord;
}

bool compararCaseInsensitive(std::string strFirst, std::string strSecond)
{
	// Convert both strings to upper case by transfrom() before compare.
	std::transform(strFirst.begin(), strFirst.end(), strFirst.begin(), toupper);
	std::transform(strSecond.begin(), strSecond.end(), strSecond.begin(), toupper);

	if (strFirst == strSecond)
		return true;
	else
		return false;
}

std::string decapitalize(std::string s) {

	std::string str = s;
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	return str;
}
