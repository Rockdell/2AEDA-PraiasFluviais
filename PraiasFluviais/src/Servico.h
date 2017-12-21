#include <string>

#ifndef SERVICO_H_
#define SERVICO_H_

typedef enum {Restauracao, Alojamento, Aluguer, Null} servico_t;

class Praia;

class Servico {

	typedef struct {
		unsigned int dia = 0;
		unsigned int mes = 0;
		unsigned int ano = 0;

		std::string display() {
			std::string result = "";
			result += std::to_string(dia) + " " + std::to_string(mes) + " " + std::to_string(ano);
			return result;
		}

	} Data;

	servico_t tipo;
	std::string nome;
	Praia* praia;
	Data ult_inspecao;
	unsigned int closed;

public:

	Servico();
	Servico(servico_t t, std::string n, Praia* p, unsigned int s);
	Servico(servico_t t, std::string n, unsigned int d, unsigned int m, unsigned int a, Praia* p, unsigned int s);
	~Servico();

	servico_t getTipo() const;
	std::string getNome() const;
	Praia* getPraia() const;
	Servico::Data getData() const;
	unsigned int getStatus() const;

	void setTipo(servico_t t);
	void setNome(std::string n);
	void setPraia(Praia* p);
	void setData(unsigned int d, unsigned int m, unsigned int a);
	void setStatus(unsigned int s);

	bool operator ==(const Servico &s) const;

};

servico_t to_enum(std::string str);
std::string from_enum(servico_t s);


#endif
