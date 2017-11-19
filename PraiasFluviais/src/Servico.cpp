#include "Servico.h"

//Constructors/Destructors
Servico::Servico() {
}
Servico::Servico(std::string d) : descricao(d) {
}
Servico::~Servico() {
}

//Get methods
std::string Servico::getDescricao() {
	return descricao;
}

//Set methods
void Servico::setDescricao(std::string d) {
	descricao = d;
}

//Operators
bool Servico::operator ==(const Servico s1) const {
	if(descricao == s1.descricao)
		return true;
	else
		return false;
}





