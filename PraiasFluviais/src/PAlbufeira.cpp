#include "PAlbufeira.h"

using json = nlohmann::json;

//Constructors/Destructors
PAlbufeira::PAlbufeira() {
	area = 0;
}
PAlbufeira::PAlbufeira(std::string n, std::string c, bool bA,  Gps cd, float a) : Praia(n,c,bA,cd) {
	area = a;
}
PAlbufeira::~PAlbufeira(){
}

//Get methods
float PAlbufeira::getArea() const {
	return area;
}

//Set methods
void PAlbufeira::setArea(float a) {
	area = a;
}

json PAlbufeira::savePraia() {

	json j;
	to_json(j, this);

	return j;
}

void PAlbufeira::to_json(json &j, const PAlbufeira *p) {
	j["type"] = "A";
	j["nome"] = p->getNome();
	j["concelho"] = p->getConcelho();
	j["servicos"] = {};
	j["bandeira"] = p->getBandeira();
	j["gps"] = { p->getGps().getLat(), p->getGps().getLon() };
	j["area"] = p->getArea();

	for(size_t i = 0; i < p->getServicos().size(); i++)
		j["servicos"].push_back(p->getServicos()[i].getDescricao());
}

void PAlbufeira::from_json(const json &j, PAlbufeira *p) {
	p->setNome(j.at("nome").get<std::string>());
	p->setConcelho(j.at("concelho").get<std::string>());
	p->setBandeira(j.at("bandeira").get<bool>());
	p->setGps(Gps(j.at("gps").at(0).get<double>(), j.at("gps").at(1).get<double>()));
	p->setArea(j.at("area").get<float>());

	std::vector<std::string> servicos_tmp = j.at("servicos").get<std::vector<std::string>>();
	std::vector<Servico> servicos_new;

	for(size_t i = 0; i < servicos_tmp.size(); i++)
		servicos_new.push_back(Servico(servicos_tmp[i]));

	p->setServicos(servicos_new);

}
