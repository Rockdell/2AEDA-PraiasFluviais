
#include "Servico.h"

Servico::Servico() {
	tipo = Null;
	nome = "";
	praia = nullptr;
	closed = 0;
}

Servico::Servico(servico_t t, std::string n, Praia* p, unsigned int s) {
	tipo = t;
	nome = n;
	praia = p;
	closed = s;
}

Servico::Servico(servico_t t, std::string n, unsigned int d, unsigned int m, unsigned int a, Praia* p, unsigned int s) {
	tipo = t;
	nome = n;
	ult_inspecao.dia = d;
	ult_inspecao.mes = m;
	ult_inspecao.ano = a;
	praia = p;
	closed = s;
}

Servico::~Servico() {
}

servico_t Servico::getTipo() const {
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
unsigned int Servico::getStatus() const {
	return closed;
}

void Servico::setTipo(servico_t t) {
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
	closed = s;
}

bool Servico::operator ==(const Servico &s) const {
	return (tipo == s.tipo && nome == s.nome && praia == s.praia);
}

servico_t to_enum(std::string str) {

	if (str == "Restauracao")
		return Restauracao;
	else if (str == "Alojamento")
		return Alojamento;
	else
		return Null;
}

std::string from_enum(servico_t s) {
	if (s == Restauracao)
		return "Restauracao";
	else if (s == Alojamento)
		return "Alojamento";
	else
		return "Null";
}
