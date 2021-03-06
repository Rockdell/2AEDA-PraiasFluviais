#define _CRT_SECURE_NO_WARNINGS
#include "Praia.h"

//Constructors
Praia::Praia() {
	name = "";
	concelho = "";
	capacity = 0;
	bandeiraAzul = false;
	coord = Gps();
}

Praia::Praia(std::string n, std::string c, unsigned int cap, bool bA, Gps cd) : name(n), concelho(c), capacity(cap), bandeiraAzul(bA), coord(cd) {
}

Praia::Praia(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd) : name(n), concelho(c), services(s), capacity(cap), bandeiraAzul(bA), coord(cd) {
}

//Get methods
std::string Praia::getName() const {
	return name;
}

std::string Praia::getConcelho() const {
	return concelho;
}

std::priority_queue<Service> Praia::getServicesOpen() const {
	return services;
}

std::priority_queue<Service> Praia::getServicesOpen(service_t t) const {

	std::priority_queue<Service> result;
	std::priority_queue<Service> tmp = services;

	while(!tmp.empty()) {

		if(tmp.top().getType() == t)
			result.push(tmp.top());

		tmp.pop();
	}

	return result;
}

HashTabService Praia::getServicesClosed() const {
	return servicesClosed;
}

unsigned int Praia::getCapacity() const {
	return capacity;
}

bool Praia::getBandeira() const {
	return bandeiraAzul;
}

Gps Praia::getGps() const {
	return coord;
}

//Set methods
void Praia::setName(std::string n) {
	name = n;
}

void Praia::setConcelho(std::string c) {
	concelho = c;
}

void Praia::setServices(std::priority_queue<Service> s) {
	services = s;
}

void Praia::setCapacity(unsigned int cap) {
	capacity = cap;
}

void Praia::setBandeira(bool bA) {
	bandeiraAzul = bA;
}

void Praia::setGps(Gps cd) {
	coord = cd;
}

//Service-related methods
void Praia::addServiceOpen(Service s) {

	if(existService(s))
		throw ServiceAlreadyExists(s.getName());

	services.push(s);
}

void Praia::addServiceClosed(Service s) {

	if(existService(s))
		throw ServiceAlreadyExists(s.getName());

	servicesClosed.insert(s);
}

void Praia::removeService(Service s) {

	if(!existService(s))
		throw ServicoNotFound(s.getName());

	unsigned int service_status = s.getStatus().getClosed();

	//Checks if the service is on the queue or hash table according to its status
	if (service_status == 0) {

		std::priority_queue<Service> new_services;

		while (!services.empty()) {

			if (s == services.top()) {
				services.pop();
				continue;
			}

			new_services.push(services.top());
			services.pop();
		}

		services = new_services;
	}
	else {

		for (auto it = servicesClosed.begin(); it != servicesClosed.end(); it++) {
			Service tmp = *it;

			if (tmp == s) {
				servicesClosed.erase(it);
				break;
			}
		}
	}
}

int Praia::inspectionService(Service s) {

	if (s.getStatus().getClosed() != 0) {
		std::cerr << " # Can't perform an inspection if service is closed. ";
		return 1;
	}

	//Current day, month and year
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	int day = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int year = now->tm_mday;

	std::priority_queue<Service> pq_tmp;
	Service tmp;

	//Searches for the service
	while (!services.empty()) {

		tmp = services.top();
		services.pop();

		if (tmp == s)
			break;

		pq_tmp.push(tmp);
	}

	//Puts the other services back on the queue
	while (!pq_tmp.empty()) {

		Service o = pq_tmp.top();
		services.push(o);
		pq_tmp.pop();
	}

	//Alters the date of the last_inspection of the service
	tmp.setDate(day, month, year);

	//And finally puts it back on the queue
	services.push(tmp);

	return 0;
}

int Praia::openService(Service s) {

	//Servico recebido ja foi verificado se esta aberto ou nao!
	if (s.getStatus().getClosed() == 0) {
		std::cerr << " # Service is currently open. ";
		return 1;
	}
	else if (s.getStatus().getClosed() == 2) {
		std::cerr << " # Service is permanently closed. ";
		return 1;
	}

	for (auto it = servicesClosed.begin(); it != servicesClosed.end(); it++) {
		Service s_tmp = *it;

		if (s == s_tmp) {
			servicesClosed.erase(it);
			//s_tmp.setDate(day, month, year);
			s_tmp.setStatus(0, 0, 0, 0);

			//Puts the service ON THE QUEUE NOW THAT IT'S OPEN!!!
			services.push(s_tmp);
			break;
		}
	}

	return 0;
}

int Praia::closeService(Service s, unsigned int closed_type) {

	if (s.getStatus().getClosed() != 0) {
		std::cerr << " # Service is currently closed. ";
		return 1;
	}

	//Current day, month and year
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	int day = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int year = now->tm_mday;

	std::priority_queue<Service> pq_tmp;
	Service tmp;

	//Searches for the service
	while (!services.empty()) {
		tmp = services.top();
		services.pop();

		if (tmp == s)
			break;

		pq_tmp.push(tmp);
	}

	//Puts the other services back on the queue
	while (!pq_tmp.empty()) {
		Service o = pq_tmp.top();
		services.push(o);
		pq_tmp.pop();
	}

	//Alters the service status
	tmp.setStatus(closed_type, day, month, year);

	//And finally puts it ON THE HASH TABLE NOW THAT IT'S CLOSED!!!
	servicesClosed.insert(tmp);

	return 0;
}

Service Praia::accessService(unsigned int index) const {

	//Checks if the service is on the queue or on the hash table
	if (services.size() == 0)
		goto next;

	if (index <= services.size() - 1) {

		std::priority_queue<Service> pq_tmp = services;

		while (index != 0) {

			pq_tmp.pop();
			index--;
		}

		return pq_tmp.top();
	}
	else {

		next:
		index -= services.size();
		auto it = servicesClosed.begin();

		while (index != 0) {

			it++;
			index--;
		}

		return *it;
	}
}

bool Praia::existService(Service s) {

	std::priority_queue<Service> search = services;

	while (!search.empty()) {

		if (s == search.top())
			return true;

		search.pop();
	}

	for (auto it = servicesClosed.begin(); it != servicesClosed.end(); it++) {
		if (s == *it)
			return true;
	}

	return false;
}

int Praia::showServices() {

	if (getServicesOpen().size() == 0 && getServicesClosed().size() == 0) {
		std::cerr << " There are no services open in this praia. ";
		return 1;
	}

	//Show the services from the priority queue (currently open)
	std::priority_queue<Service> tmp = services;
	unsigned int cont = 1;

	while(!tmp.empty()) {
		Service ts = tmp.top();
		std::cout << " Service #" << cont << ":\n" << ts.displayService() << "\n";
		tmp.pop();
		cont++;
	}

	//Show the services from the hash table (currently close)
	for (auto it = servicesClosed.begin(); it != servicesClosed.end(); it++) {
		Service ts = *it;
		std::cout << " Service #" << cont << ":\n" << ts.displayService() << "\n";
		cont++;
	}

	return 0;
}

//Operator overloading
bool Praia::operator ==(const Praia* p1) const {
	return (name == p1->name && concelho == p1->concelho);
}

//Other methods
std::string Praia::reducedInfoPraia() {
	std::string result = "";

	result += " Nome: " + name + " (" +  concelho + ")";

	return result;
}
