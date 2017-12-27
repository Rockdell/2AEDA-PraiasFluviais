
#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include <ctime>
#include <sstream>

typedef enum {Restauracao, Alojamento, Aluguer, Null} service_t;

class Service {

	//Nested class Date
	class Date {
		unsigned int day;
		unsigned int month;
		unsigned int year;

	public:
		Date();
		Date(unsigned int d, unsigned int m, unsigned int y);
		~Date();

		unsigned int getDay() const;
		unsigned int getMonth() const;
		unsigned int getYear() const;

		void setDay(unsigned int d);
		void setMonth(unsigned int m);
		void setYear(unsigned int y);

		bool operator <(const Date &d) const;

		std::string display();

	};

	//Nested class Status
	class Status {

		/* 0: Open
		 * 1: Closed temporarily
		 * 2: Closed permanently
		 */
		unsigned int closed;
		Date closing_date;

	public:
		Status();
		Status(unsigned int c, unsigned int d, unsigned int m, unsigned int y);
		~Status();

		unsigned int getClosed() const;
		Date getClosingDate() const;

		void setClosed(unsigned int c);
		void setClosingDate(unsigned int d, unsigned int m, unsigned int y);

	};

	service_t type;
	std::string name;
	Date last_inspection;
	Status status;

public:

	Service();
	Service(service_t t, std::string n, unsigned int c, unsigned int s_d, unsigned int s_m, unsigned int s_a);
	Service(service_t t, std::string n, unsigned int d, unsigned int m, unsigned int a, unsigned int c, unsigned int s_d, unsigned int s_m, unsigned int s_a);
	~Service();

	service_t getType() const;
	std::string getName() const;
	Date getDate() const;
	Status getStatus() const;

	void setType(service_t t);
	void setName(std::string n);
	void setDate(unsigned int d, unsigned int m, unsigned int a);
	void setStatus(unsigned int s, unsigned int s_d, unsigned int s_m, unsigned int s_a);

	bool operator ==(const Service &s) const;
	bool operator <(const Service &s) const;

	std::string displayService() const;

};

service_t to_enum(std::string str);
std::string from_enum(service_t s);


#endif
