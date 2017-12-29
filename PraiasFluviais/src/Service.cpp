
#include "Service.h"

//Implementation of nested classes:

//DATE
//Constructor
Service::Date::Date() {
	//Current day, month and year
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

	day = now->tm_year + 1900;
	month = now->tm_mon + 1;
	year = now->tm_mday;
}


Service::Date::Date(unsigned int d, unsigned int m, unsigned int y): day(d), month(m), year(y) {
}

Service::Date::~Date() {
}

//Get methods
unsigned int Service::Date::getDay() const {
	return day;
}

unsigned int Service::Date::getMonth() const {
	return month;
}

unsigned int Service::Date::getYear() const {
	return year;
}

//Set methods
void Service::Date::setDay(unsigned int d) {
	day = d;
}

void Service::Date::setMonth(unsigned int m) {
	month = m;
}

void Service::Date::setYear(unsigned int y) {
	year = y;
}

//Operator overloading
bool Service::Date::operator <(const Date &d) const {

	if(year == d.year) {
		if(month == d.month) {
			return (day > d.day);
		}
		else
			return (month > d.month);
	}
	else
		return (year > d.year);
}

//Other method
std::string Service::Date::display() {
	std::string result = "";
	result += std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
	return result;
}

//STATUS
//Constructor
Service::Status::Status() {
	closed = 0;
}

Service::Status::Status(unsigned int c, unsigned int d, unsigned int m, unsigned int y) {
	closed = c;
	closing_date = Date(d, m, y);
}

Service::Status::~Status() {
}

//Get methods
unsigned int Service::Status::getClosed() const {
	return closed;
}

Service::Date Service::Status::getClosingDate() const {
	return closing_date;
}

//Set methods
void Service::Status::setClosed(unsigned int c) {
	closed = c;
}

void Service::Status::setClosingDate(unsigned int d, unsigned int m, unsigned int a) {
	closing_date = Date(d, m, a);
}

//Implementation of class Service
//Constructors
Service::Service() {
	type = Null;
	name = "";
}

Service::Service(service_t t, std::string n, unsigned int s_d, unsigned int s_m, unsigned int s_a) {
	type = t;
	name = n;
	last_inspection = Date(s_d, s_m, s_a);
	status = Status(); //Poe o status a 0 -> ou seja so cria servicos abertos
}

Service::Service(service_t t, std::string n, unsigned int d, unsigned int m, unsigned int a,unsigned int c, unsigned int s_d, unsigned int s_m, unsigned int s_a) {
	type = t;
	name = n;
	last_inspection = Date(d, m, a);
	status = Status(c, s_d, s_m, s_a);
}

Service::~Service() {
}

//Get methods
service_t Service::getType() const {
	return type;
}
std::string Service::getName() const {
	return name;
}
Service::Date Service::getDate() const {
	return last_inspection;
}
Service::Status Service::getStatus() const {
	return status;
}

//Set methods
void Service::setType(service_t t) {
	type = t;
}
void Service::setName(std::string n) {
	name = n;
}
void Service::setDate(unsigned int d, unsigned int m, unsigned int a) {
	last_inspection = Date(d, m, a);
}
void Service::setStatus(unsigned int c, unsigned int d, unsigned int m, unsigned int a) {
	status = Status(c, d, m, a);
}

//Operator overloading
bool Service::operator ==(const Service &s) const {
	return (type == s.type && name == s.name);
}

bool Service::operator <(const Service &s) const {
	return (last_inspection < s.last_inspection);
}

//Display Service
std::string Service::displayService() const {

	std::ostringstream oss;

	oss << name << " (" << from_enum(type) << ")" << "\n" << "Status : ";

	switch(status.getClosed()) {
	case 0:
		oss << "Open" << "\n";
		break;
	case 1:
		oss << "Closed temporarily since " << status.getClosingDate().display() << "\n";
		break;
	case 2:
		oss << "Closed permanently since " << status.getClosingDate().display() << "\n";
		break;
	}

	oss << "Last inspection on " << getDate().display() << "\n";

	return oss.str();
}

//Other methods
service_t to_enum(std::string str) {

	//Capitalize all letters
	for (size_t i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}

	if (str == "RESTAURACAO")
		return Restauracao;
	else if (str == "ALOJAMENTO")
		return Alojamento;
	else if (str == "ALUGUER")
		return Aluguer;
	else
		return Null;
}

std::string from_enum(service_t s) {
	if (s == Restauracao)
		return "Restauracao";
	else if (s == Alojamento)
		return "Alojamento";
	else if (s == Aluguer)
		return "Aluguer";
	else
		return "Null";
}
