#include <string>

#ifndef SERVICO_H_
#define SERVICO_H_

class Servico {
	std::string descricao;
public:
	Servico();
	Servico(std::string d);
	~Servico();

	std::string getDescricao();
	void setDescricao(std::string d);
	bool operator==(const Servico s1) const;
};

#endif /* SERVICO_H_ */
