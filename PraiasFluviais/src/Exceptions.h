#include <string>
#include <iostream>

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

/**
 * @brief Exceptions's base class
 */
class Exception {
	std::string message;
public:
	/**
	 * @brief Class constructor
	 */
	Exception(std::string m) {
		message = m;
	}

	std::string getMessage() const {
		return message;
	}
	virtual void display() const = 0;

};

class FileNotFound : public Exception {
public:
	FileNotFound(std::string f) : Exception(f) {
	}

	void display() const {
		std::string msg = " Ficheiro não encontrado: " + getMessage();
		std::cout << msg;
	}
};

class PraiaNotFound : public Exception {
public:
	PraiaNotFound(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Praia não encontrada: " + getMessage();
		std::cout << msg;
	}
};

class ServicoNotFound : public Exception {
public:
	ServicoNotFound(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Serviço não encontrado: " + getMessage();
		std::cout << msg;
	}
};

class ReadingLineError : public Exception {
public:
	ReadingLineError(std::string l) : Exception(l) {
	}

	void display() const {
		std::string msg = " Erro ao ler a linha: " + getMessage();
		std::cout << msg;
	}
};

class PraiaAlreadyExists : public Exception {
public:
	PraiaAlreadyExists(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Praia já existe: " + getMessage();
		std::cout << msg;
	}
};

#endif /* EXCEPTIONS_H_ */
