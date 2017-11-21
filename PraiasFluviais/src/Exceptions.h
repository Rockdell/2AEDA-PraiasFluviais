#include <string>
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

	/**
	 * @brief Class constructor
	 * @return Returns exception's message
	 */
	std::string getMessage() const {
		return message;
	}
};

class FileNotFound : public Exception {
public:
	FileNotFound(std::string f) : Exception(f) {
	}
};

class PraiaNotFound : public Exception {
public:
	PraiaNotFound(std::string n) : Exception(n) {
	}
};

class ServicoNotFound : public Exception {
public:
	ServicoNotFound(std::string n) : Exception(n) {
	}
};

class ReadingLineError : public Exception {
public:
	ReadingLineError(std::string l) : Exception(l) {
	}
};

class PraiaAlreadyExists : public Exception {
public:
	PraiaAlreadyExists(std::string n) : Exception(n) {
	}
};

#endif /* EXCEPTIONS_H_ */
