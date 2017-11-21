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
		std::string msg = " Ficheiro n�o encontrado: " + getMessage();
		std::cout << msg << std::endl;
	}
};

class PraiaNotFound : public Exception {
public:
	PraiaNotFound(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Praia n�o encontrada: " + getMessage();
		std::cout << msg << std::endl;
	}
};

class ServicoNotFound : public Exception {
public:
	ServicoNotFound(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Servi�o n�o encontrado: " + getMessage();
		std::cout << msg << std::endl;
	}
};

class ReadingLineError : public Exception {
public:
	ReadingLineError(std::string l) : Exception(l) {
	}

	void display() const {
		std::string msg = " Erro ao ler a linha: " + getMessage();
		std::cout << msg << std::endl;
	}
};

class PraiaAlreadyExists : public Exception {
public:
	PraiaAlreadyExists(std::string n) : Exception(n) {
	}

	void display() const {
		std::string msg = " Praia j� existe: " + getMessage();
		std::cout << msg << std::endl;
	}
};

#endif /* EXCEPTIONS_H_ */
