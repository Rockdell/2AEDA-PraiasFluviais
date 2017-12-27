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
std::priority_queue<Service> Praia::getServices() const {
	return services;
}
std::priority_queue<Service> Praia::getServices(service_t t) const {

	std::priority_queue<Service> result;
	std::priority_queue<Service> tmp = services;

	while(!tmp.empty()) {

		if(tmp.top().getType() == t)
			result.push(tmp.top());

		tmp.pop();
	}

	return result;
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
void Praia::setCapacity(unsigned int lot) {
	capacity = lot;
}
void Praia::setBandeira(bool bA) {
	bandeiraAzul = bA;
}
void Praia::setGps(Gps cd) {
	coord = cd;
}

//Service-related methods
void Praia::addService(Service s) {
	services.push(s);
}

void Praia::addService(std::priority_queue<Service> s) {

	while(!s.empty()) {

		addService(s.top());
		s.pop();
	}
}

void Praia::removeService(Service s) {

	if(!existService(s))
		throw ServicoNotFound(s.getName());

	std::priority_queue<Service> new_services;

	while(!services.empty()) {

		if(s == services.top()) {
			services.pop();
			continue;
		}

		new_services.push(services.top());
		services.pop();
	}

	services = new_services;

	//TODO rever exceptions
}

//Access a Service in the priority queue with a specific index
Service Praia::accessService(unsigned int index) const {

	index--;
	std::priority_queue<Service> pq_tmp;

	while(index != 0)
	{
		pq_tmp.pop();
		index--;
	}

	return pq_tmp.top();
}

bool Praia::existService(Service s) {

	std::priority_queue<Service> search = services;

	while(!search.empty()) {

		if(s == search.top())
			return true;

		search.pop();
	}

	return false;
}

void Praia::showServices() {

	std::priority_queue<Service> tmp = services;
	unsigned int cont = 1;

	while(!tmp.empty()) {
		Service ts = tmp.top();
		std::cout << " Service #" << cont << ":\n" << ts.displayService() << "\n";
		tmp.pop();
		cont++;
	}
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
