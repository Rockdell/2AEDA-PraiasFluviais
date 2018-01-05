
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
#include <iostream>

/**
 *  @file Exceptions.h
 */

/**
 * @brief Exceptions's base class
 */
class Exception {

	/**
	 * @brief Exception's error message.
	 */
	std::string message;

public:

	/**
	 * @brief Exception class constructor.
	 * @param m Error message.
	 */
	Exception(std::string m) {
		message = m;
	}

	/**
	 * @brief Abstract Exception class destructor.
	 */
	virtual ~Exception() {}

	/**
	 * @brief Gets the error message.
	 * @return Returns error message.
	 * @see message
	 */
	std::string getMessage() const {
		return message;
	}

	/**
	 * @brief Pure virtual function that displays the error message.
	 * @see message
	 */
	virtual void display() const = 0;

};

/**
 * @brief FileNotFound class is publicly derived from class Exception.
 */
class FileNotFound : public Exception {
public:

	/**
	 * @brief FileNotFound class constructor.
	 * @param f Path of .txt file.
	 */
	FileNotFound(std::string f) : Exception(f) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " File not found: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief PraiaNotFound class is publicly derived from class Exception.
 */
class PraiaNotFound : public Exception {
public:

	/**
	 * @brief PraiaNotFound class constructor.
	 */
	PraiaNotFound(std::string n) : Exception(n) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " Praia not found: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief ServicoNotFound class is publicly derived from class Exception.
 */
class ServicoNotFound : public Exception {
public:

	/**
	 * @brief ServicoNotFound class constructor.
	 */
	ServicoNotFound(std::string n) : Exception(n) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " Service not found: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief ReadingLineError class is publicly derived from class Exception.
 */
class ReadingLineError : public Exception {
public:

	/**
	 * @brief ReadingLineError class constructor.
	 */
	ReadingLineError(std::string l) : Exception(l) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " Error while reading line: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief PraiaAlreadyExists class is publicly derived from class Exception.
 */
class PraiaAlreadyExists : public Exception {
public:

	/**
	 * @brief PraiaAlreadyExists class constructor.
	 */
	PraiaAlreadyExists(std::string n) : Exception(n) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " Praia já existe: " + getMessage();
		std::cout << msg << std::endl;
	}
};

/**
 * @brief Service AlreadyExists class is publicly derived from class Exception.
 */
class ServiceAlreadyExists : public Exception {
public:

	/**
	 * @brief ServiceAlreadyExists class constructor.
	 * @param f Path of .txt file.
	 */
	ServiceAlreadyExists(std::string f) : Exception(f) {
	}

	/**
	 * @brief Implementation of the virtual function.
	 */
	void display() const {
		std::string msg = " Service already exists: " + getMessage();
		std::cout << msg << std::endl;
	}
};

#endif /* EXCEPTIONS_H_ */
