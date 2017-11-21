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
	 * @brief Exception Class constructor
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
};

#endif /* EXCEPTIONS_H_ */
