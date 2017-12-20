
#include "Servico.h"

Servico::Servico() {
	tipo = null;
	praia = nullptr;
	ult_inspecao.dia = 0;
	ult_inspecao.mes = 0;
	ult_inspecao.ano = 0;;
	status.closed = 0;
}

Servico::Servico(servico_type t, std::string n, unsigned int d, unsigned int m, unsigned int a, Praia* p, unsigned int s) {
	tipo = t;
	nome = n;
	ult_inspecao.dia = d;
	ult_inspecao.mes = m;
	ult_inspecao.ano = a;
	praia = p;
	status.closed = s;
}

Servico::~Servico() {
}

servico_type Servico::getTipo() const {
	return tipo;
}
std::string Servico::getNome() const {
	return nome;
}
Praia* Servico::getPraia() const {
	return praia;
}
Servico::Data Servico::getData() const {
	return ult_inspecao;
}
Servico::Status Servico::getStatus() const {
	return status;
}

void Servico::setTipo(servico_type t) {
	tipo = t;
}
void Servico::setNome(std::string n) {
	nome = n;
}
void Servico::setPraia(Praia* p) {
	praia = p;
}
void Servico::setData(unsigned int d, unsigned int m, unsigned int a) {
	ult_inspecao.dia = d;
	ult_inspecao.mes = m;
	ult_inspecao.ano = a;
}
void Servico::setStatus(unsigned int s) {
	status.closed = s;
}
