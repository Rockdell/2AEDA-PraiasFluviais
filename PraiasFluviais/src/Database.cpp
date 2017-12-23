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
	iter_pair it = searchPraia(p);

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

iter_pair Database::searchPraia(Praia* p) {

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

iter_pair Database::searchPraia(std::string n, std::string c) {

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

	//Might not need (when calling this function, it is guaranteed there is a object there)
	return nullptr;
}

bool Database::existPraia(Praia* p) {

	iter_pair it = searchPraia(p);

	if(it.second == -1)
		return false;
	else
		return true;
}

bool Database::existPraia(std::string n, std::string c) {

	iter_pair it = searchPraia(n, c);

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

					if(it->second[i+1]->getBandeira() == it->second[i]->getBandeira()) {
						if (it->second[i + 1]->getNome() < it->second[i]->getNome()) {
							std::swap(it->second[i + 1], it->second[i]);
							troca = true;
						}
					}
					else {
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

	std::istringstream iss(l);
	std::vector<std::string> properties;
	std::string token;

	//Parse line
	while (getline(iss, token, ';')) {
		properties.push_back(token);
	}

	if(properties.empty())
		return;

	//Type
	std::string type = properties[0];

	//Nome
	std::string nome = properties[1];

	//Concelho
	std::string concelho = properties[2];

	//Servicos
	std::string str_servicos = properties[3];
	std::istringstream iss_servicos(str_servicos);
	std::vector<Servico> servicos;

	if(str_servicos != "null_servicos") {
		while(getline(iss_servicos, token, ',')) {
			std::string t, n;
			unsigned int d, m, a, s;

			std::istringstream iss_serv(token);
			iss_serv >> t >> n >> d >> m >> a >> s;

			servico_t type = to_enum(t);

			Servico tmp(type, n, d, m, a, nullptr, s);

			servicos.push_back(tmp);
		}
	}

	//Lotacao
	int lotacao;
	std::string str_lotacao = properties[4];
	std::istringstream iss_lotacao(str_lotacao);
	std::string s_lotacao;
	iss_lotacao >> s_lotacao;
	lotacao = std::stoi(s_lotacao);

	//Bandeira
	bool bandeira;
	std::string str_bandeira = properties[5];

	if(str_bandeira == "1")
		bandeira = true;
	else
		bandeira = false;

	//Gps
	double lat, lon;
	std::string str_gps = properties[6];
	std::istringstream iss_gps(str_gps);
	std::string s_lat, s_lon;
	iss_gps >> s_lat >> s_lon;
	lat = std::stod(s_lat);
	lon = std::stod(s_lon);

	Gps gps(lat,lon);

	if (type == "R") {

		//Largura
		double largura;
		std::string str_largura = properties[7];
		std::istringstream iss_largura(str_largura);
		std::string s_largura;
		iss_largura >> s_largura;
		largura = std::stod(s_largura);

		//Caudal
		double caudal;
		std::string str_caudal = properties[8];
		std::istringstream iss_caudal(str_caudal);
		std::string s_caudal;
		iss_caudal >> s_caudal;
		caudal = std::stod(s_caudal);

		//Profundidade
		double profundidade;
		std::string str_profundidade = properties[9];
		std::istringstream iss_profundidade(str_profundidade);
		std::string s_profundidade;
		iss_profundidade >> s_profundidade;
		profundidade = std::stod(s_profundidade);

		PRio* p = new PRio(nome, concelho, servicos, lotacao, bandeira, gps, largura, caudal, profundidade);

		//Set Praia nos servicos
		for (size_t i = 0; i < servicos.size(); i++) {
			servicos[i].setPraia(p);
		}

		addPraia(p);
	}
	else if (type == "A"){

		//Area
		double area;
		std::string str_area = properties[7];
		std::istringstream iss_area(str_area);
		std::string s_area;
		iss_area >> s_area;
		area = std::stod(s_area);

		PAlbufeira* p = new PAlbufeira(nome, concelho, servicos, lotacao, bandeira, gps, area);

		//Set Praia nos servicos
		for (size_t i = 0; i < servicos.size(); i++) {
			servicos[i].setPraia(p);
		}

		addPraia(p);
	}
	else
		throw ReadingLineError(l);
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

std::string decapitalize(std::string s) {

	std::string str = s;
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	str[0] = toupper(str[0]);

	return str;
}

//TODO quando um nome tem mais que uma palavra, mudar o modo como é guardado. Adicionar o compararCaseInsensitive para enum type
