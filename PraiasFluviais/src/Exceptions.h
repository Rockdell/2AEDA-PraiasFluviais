#include <string>
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class FileNotFound {
	std::string file;
public:
	FileNotFound(std::string f) {
		file = f;
	}
};

class PraiaNotFound {
	std::string nome;
public:
	PraiaNotFound(std::string n) {
		nome = n;
	}
};

class ServicoNotFound {
	std::string nome;
public:
	ServicoNotFound(std::string n) {
		nome = n;
	}
};

class ReadingLineError {
	std::string line;
public:
	ReadingLineError(std::string l) {
		line = l;
	}
};

class PraiaAlreadyExists {
	std::string nome;
public:
	PraiaAlreadyExists(std::string n) {
		nome = n;
	}
};

#endif /* EXCEPTIONS_H_ */
