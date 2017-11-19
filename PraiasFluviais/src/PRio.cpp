#include "PRio.h"

using json = nlohmann::json;

//Constructors/Destructors
PRio::PRio() : Praia() {
	largura = 0;
	caudal = 0;
	profundidade = 0;
}
PRio::PRio(std::string n, std::string c, bool bA, Gps cd, float l, float cl, float p) : Praia(n,c,bA,cd) {
	largura = l;
	caudal = cl;
	profundidade = p;
}
PRio::~PRio() {
}

//Get methods
float PRio::getLargura() const {
	return largura;
}
float PRio::getCaudal() const {
	return caudal;
}
float PRio::getProfundidade() const {
	return profundidade;
}

//Set methods
void PRio::setLargura(float l) {
	largura = l;
}
void PRio::setCaudal(float c) {
	caudal = c;
}
void PRio::setProfundidade(float p) {
	profundidade = p;
}

json PRio::savePraia() {

	json j;
	to_json(j, this);

	return j;

}

void PRio::to_json(json &j, const PRio *p) {
	j["type"] = "R";
	j["nome"] = p->getNome();
	j["concelho"] = p->getConcelho();
	j["servicos"] = {};
	j["bandeira"] = p->getBandeira();
	j["gps"] = { p->getGps().getLat(), p->getGps().getLon() };
	j["largura"] = p->getLargura();
	j["caudal"] = p->getCaudal();
	j["profundidade"] = p->getProfundidade();

	for(size_t i = 0; i < p->getServicos().size(); i++)
		j["servicos"].push_back(p->getServicos()[i].getDescricao());
}

void PRio::from_json(const json &j, PRio *p) {
	p->setNome(j.at("nome").get<std::string>());
	p->setConcelho(j.at("concelho").get<std::string>());
	p->setBandeira(j.at("bandeira").get<bool>());
	p->setGps(Gps(j.at("gps").at(0).get<double>(), j.at("gps").at(1).get<double>()));
	p->setLargura(j.at("largura").get<float>());
	p->setCaudal(j.at("caudal").get<float>());
	p->setProfundidade(j.at("profundidade").get<float>());

	std::vector<std::string> servicos_tmp = j.at("servicos").get<std::vector<std::string>>();
	std::vector<Servico> servicos_new;

	for(size_t i = 0; i < servicos_tmp.size(); i++)
		servicos_new.push_back(Servico(servicos_tmp[i]));

	p->setServicos(servicos_new);

}
