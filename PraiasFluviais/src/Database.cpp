#include "Database.h"

Database::Database() {
}
Database::~Database() {
}

void Database::load(std::string filename) {
	std::ifstream input("listaPraias.txt");
	json j;

	if(!input.is_open())
		throw FileNotFound(filename);

	//May give some trouble! Test better
	while(input >> j) {
		processLine(j);
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

int Database::searchPraia(Praia* p) {
	for(size_t i = 0; i < praias.size(); i++)
	{
		if(*p == praias[i])
			return i;
	}

	return -1;
}

bool Database::existPraia(Praia* p) {
	if(searchPraia(p) == -1)
		return false;
	else if(*p == praias[searchPraia(p)])
		return true;
	else
		return false;
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

void Database::processLine(json j) {

	if(j.at("type").get<std::string>() == "A") {
		PAlbufeira p;
		p.from_json(j, &p);
		praias.push_back(&p);
	}
	else {
		PRio p;
		p.from_json(j, &p);
		praias.push_back(&p);
	}

	/*
	std::istringstream ss(line);
	char type, chaveta;
	std::string nome, concelho, servico;
	int bandeira;
	bool bandeiraAzul;
	std::vector<Servico> servicos;
	double lat, lon;

	ss >> type >> nome >> concelho >> chaveta >> servico;

	while (servico != "}") {
		Servico newServico(servico);
		servicos.push_back(newServico);
		ss >> servico;
	}

	ss >> bandeira;

	if(bandeira)
		bandeiraAzul = true;
	else
		bandeiraAzul = false;

	ss >> lat >> lon;

	Gps gps = Gps(lat,lon);

	if (type == 'A') {
		float area;

		ss >> area;

		PAlbufeira p(nome, concelho, bandeiraAzul, gps, area);

		addPraia(&p);
	}
	else if (type == 'R') {
		float largura, caudal, profundidade;

		ss >> largura >> caudal >> profundidade;

		PRio p(nome, concelho, bandeiraAzul, gps, largura, caudal, profundidade);

		addPraia(&p);
	}
	else
		throw ReadingLineError(line);
		*/

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
