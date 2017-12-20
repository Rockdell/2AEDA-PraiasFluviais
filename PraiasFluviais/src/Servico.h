
#include <string>
#include "Praia.h";

typedef enum {Restauracao, Alojamento, Aluguer} servico_type;

class Servico {

	typedef struct {
		unsigned int dia;
		unsigned int mes;
		unsigned int ano;
	} Data;

	typedef struct {

		//TODO check ingrish plz
		/* 0: open
		 * 1: closed temporarily
		 * 2: closed permanentely
		 */
		unsigned int closed;
	} Status;

	servico_type tipo;
	std::string nome;
	Praia* p;
	Data ult_inspecao;
	Status status;

public:

	Servico();
	Servico(servico_type t, std::string n, unsigned int d, unsigned int m, unsigned int a, Praia* p = nullptr, unsigned int s = 0);
	~Servico();

	servico_type getTipo() const;
	std::string getNome() const;
	Praia* getPraia() const;
	Data getData() const;
	Status getStatus() const;

	void setTipo(servico_type t);
	void setNome(std::string n);
	void setPraia(Praia* p);
	void setData(unsigned int d, unsigned int m, unsigned int a);
	void setStatus(unsigned int s);

};
