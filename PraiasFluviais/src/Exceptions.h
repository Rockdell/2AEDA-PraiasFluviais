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
	 * @brief Exception Class constructor
	 */
	Exception(std::string m) {
		message = m;
	}

	/**
	 * @brief Gets the message data member
	 * @return Returns string with the message data member
	 */
	std::string getMessage() const {
		return message;
	}

	/**
	 * @brief Virtual function for the other classes
	 */
	virtual void display() const = 0;

};

/**
 * @brief FileNotFound is derived from class Exception
 */
class FileNotFound : public Exception {
public:
	/**
	 * @brief FileNotFound Class constructor
	 */
	FileNotFound(std::string f) : Exception(f) {
	}

	/**
	 * @brief Displays the message data member
	 */
	void display() const {
		std::string msg = " Ficheiro não encontrado: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief PraiaNotFound is derived from class Exception
 */
class PraiaNotFound : public Exception {
public:
	/**
	 * @brief PraiaNotFound Class constructor
	 */
	PraiaNotFound(std::string n) : Exception(n) {
	}

	/**
	 * @brief Displays the message data member
	 */
	void display() const {
		std::string msg = " Praia não encontrada: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief ServicoNotFound is derived from class Exception
 */
class ServicoNotFound : public Exception {
public:
	/**
	 * @brief ServicoNotFound Class constructor
	 */
	ServicoNotFound(std::string n) : Exception(n) {
	}

	/**
	 * @brief Displays the message data member
	 */
	void display() const {
		std::string msg = " Serviço não encontrado: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief ReadingLineError is derived from class Exception
 */
class ReadingLineError : public Exception {
public:
	/**
	 * @brief ReadingLineError Class constructor
	 */
	ReadingLineError(std::string l) : Exception(l) {
	}

	/**
	 * @brief Displays the message data member
	 */
	void display() const {
		std::string msg = " Erro ao ler a linha: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief PraiaAlreadyExists is derived from class Exception
 */
class PraiaAlreadyExists : public Exception {
public:
	/**
	 * @brief PraiaAlreadyExists Class constructor
	 */
	PraiaAlreadyExists(std::string n) : Exception(n) {
	}

	/**
	 * @brief Displays the message data member
	 */
	void display() const {
		std::string msg = " Praia já existe: " + getMessage();
		std::cout << msg << std::endl;
	}
};

#endif /* EXCEPTIONS_H_ */
