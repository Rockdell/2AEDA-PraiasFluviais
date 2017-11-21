#include "Database.h"

Database::Database() {
}
Database::~Database() {
}

void Database::load(std::string filename) {
	std::ifstream input(filename);
	std::string j;

	if(!input.is_open())
		throw FileNotFound(filename);

	std::string line;

	while(getline(input, line)) {
		processLine(line);
	}

	input.close();
}

void Database::save(std::string filename) {
	std::ofstream output(filename);

	if(!output.is_open())
		throw FileNotFound(filename);

	for(size_t i = 0; i < praias.size(); i++) {
		output << praias[i]->savePraia() << std::endl;
	}

	output.close();
}

void Database::addPraia(Praia* p) {
	praias.push_back(p);
}

void Database::removePraia(Praia* p) {
	int i = searchPraia(p);

	if(i == -1)
		throw PraiaNotFound(p->getNome());
	else
		praias.erase(praias.begin() + i);
}

void Database::removePraia(int i) {
	praias.erase(praias.begin() + i);
}

int Database::searchPraia(Praia* p) {
	for(size_t i = 0; i < praias.size(); i++)
	{
		if(*p == praias[i])
			return i;
	}

	return -1;
}

int Database::searchPraia(std::string n) {
	for(size_t i = 0; i < praias.size(); i++)
	{
		if(n == praias[i]->getNome())
			return i;
	}

	return -1;
}

bool Database::existPraia(Praia* p) {
	int i = searchPraia(p);

	if(i == -1)
		return false;
	else
		return true;
}

void Database::orderPraiasNome() {

	for(size_t j = praias.size() - 1; j > 0; j--) {

		bool troca = false;

		for(size_t i = 0; i < j; i++) {
			if(praias[i+1]->getNome() < praias[i]->getNome()) {
				std::swap(praias[i],praias[i+1]);
				troca= true;
			}
		}

		if (!troca)
			return;
	}
}

void Database::orderPraiasConcelho() {

	for(size_t j = praias.size() - 1; j > 0; j--) {

		bool troca = false;

		for(size_t i = 0; i < j; i++) {
			if(praias[i+1]->getConcelho() < praias[i]->getConcelho()) {
				std::swap(praias[i],praias[i+1]);
				troca= true;
			}
		}

		if (!troca)
			return;
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
	ss3 >> lat >> lon;

	Gps gps(lat,lon);

	Praia* p;

	if(type == "R") {

		//Largura
		double largura;
		std::string tmp4 = properties[6];
		std::istringstream ss4(tmp4);
		ss3 >> largura;

		//Caudal
		double caudal;
		std::string tmp5 = properties[7];
		std::istringstream ss5(tmp5);
		ss3 >> caudal;

		//Profundidade
		double profundidade;
		std::string tmp6 = properties[8];
		std::istringstream ss6(tmp6);
		ss3 >> profundidade;

		p = new PRio(nome, concelho, servicos, bandeira, gps, largura, caudal, profundidade);
	}
	else {

		//Area
		double area;
		std::string tmp4 = properties[6];
		std::istringstream ss4(tmp4);
		ss3 >> area;

		p = new PAlbufeira(nome, concelho, servicos, bandeira, gps,area);
	}

	addPraia(p);

}

std::vector<Praia *> Database::withInRangePraia(Praia * p, double r) const {

	std::vector<double> ranges; //Vector with all the ranges to the selected beach "p"
	std::vector<Praia *> b; //Vector with the all the beaches within the selected range

	for (size_t i = 0; i < praias.size(); i++) {
		double d = praias.at(i)->getGps().diff(p->getGps());
		ranges.push_back(d);

		if (d <= r)
			b.push_back(praias.at(i));
	}

	if (b.size() == 0) {
		/*If none of the beaches is within the selected range then we return a vector with
		 * the beaches in ascending order of range, with an "empty" beach as the last element so
		 * we can distinguish between the vector with the beaches within range and the ordered vector*/
		PRio trash = PRio();
		//Now the vector b is will have all the beaches in ascending order or range
		orderRange(b, ranges);
		//Adds the "empty" object
		b.push_back(&trash);
		return b;
	} else {
		//Clears ranges vector
		ranges.clear();

		for (size_t i = 0; i < b.size(); i++) {
			double d = b.at(i)->getGps().diff(p->getGps());
			ranges.push_back(d);
		}

		orderRange(b, ranges);
		return b;
	}
}

std::vector<Praia *> Database::withInRangeGps(Gps g, double r) const {

	std::vector<double> ranges; //Vector with all the ranges to the selected beach "p"
	std::vector<Praia *> b; //Vector with the all the beaches within the selected range

	for (size_t i = 0; i < praias.size(); i++) {
		double d = praias.at(i)->getGps().diff(g);
		ranges.push_back(d);

		if (d <= r)
			b.push_back(praias.at(i));
	}

	if (b.size() == 0) {
		/*If none of the beaches is within the selected range then we return a vector with
		 * the beaches in ascending order of range, with an "empty" beach as the last element so
		 * we can distinguish between the vector with the beaches within range and the ordered vector*/
		PRio trash = PRio();
		//Now the vector b is will have all the beaches in ascending order or range
		orderRange(b, ranges);
		//Adds the "empty" object
		b.push_back(&trash);
		return b;
	} else {
		//Clears ranges vector
		ranges.clear();

		for (size_t i = 0; i < b.size(); i++) {
			double d = b.at(i)->getGps().diff(g);
			ranges.push_back(d);
		}

		orderRange(b, ranges);
		return b;
	}

}

void Database::orderRange(std::vector<Praia *> & ps, std::vector<double> ranges) const {

	std::vector<double>::iterator it;
	std::vector<Praia *>::iterator it_p = ps.begin();

	for (it = ranges.begin(); it != ranges.end() - 1; ++it)
	{
		std::vector<double>::iterator it_min;
		it_min = std::min_element(it, ranges.end());
		size_t index = std::distance(ranges.begin(), it); //Do this operations before switching operators

		std::iter_swap(it, it_min);

		std::vector<Praia *>::iterator it_p_temp = it_p;
		std::advance(it_p_temp, index);

		std::iter_swap(it_p, it_p_temp);

		it_p++;
	}
}
