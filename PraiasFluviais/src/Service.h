
#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include <ctime>
#include <sstream>

/**
 *  @file Service.h
 */

/**
 *  @fn service_t to_enum(std::string str)
 *  @param str std::string to convert to the corresponding member of the enumeraton.
 *  @return Returns the corresponding member of the enumeration if the argument is accepted and Null otherwise.
 *  @see service_t
 */

/**
 *  @fn std::string from_enum(service_t s)
 *  @param s Type of service to convert to the corresponding std::string.
 *  @return Returns the corresponding std::string if the argument is accepted and Null otherwise.
 *  @see service_t
 */

/** @brief Enumeration with the possible types of services. */
typedef enum {
	Restauracao,	/**< Service of restauracao */
	Alojamento,		/**< Service of alojamento */
	Aluguer,		/**< Service of aluguer */
	Null			/**< Null service */
} service_t;

/**
 *  @brief Class representing a service
 */
class Service {

	/**
	 *  @brief Class representing a date.
	 *
	 *  This class is nested in class Service.
	 */
	class Date {

		/**
		 *  @brief Day of the date.
		 */
		unsigned int day;

		/**
		 *  @brief Month of the date.
		 */
		unsigned int month;

		/**
		 *  @brief Year of the date.
		 */
		unsigned int year;

	public:

		/**
		 *  @brief Praia class constructor.
		 */
		Date();

		/**
		 *  @brief Praia class constructor with arguments.
		 *  @param d Day of the date.
		 *  @param m Month of the date.
		 *  @param y Year of the date.
		 */
		Date(unsigned int d, unsigned int m, unsigned int y);

		/**
		 *  @brief Praia class destructor.
		 */
		~Date();

		/**
		 *  @brief Gets the day of the object Date.
		 *  @return Returns the day of the object.
		 *  @see day
		 */
		unsigned int getDay() const;

		/**
		 *  @brief Gets the month of the object Date.
		 *  @return Returns the month of the object.
		 *  @see month
		 */
		unsigned int getMonth() const;

		/**
		 *  @brief Gets the year of the object Date.
		 *  @return Returns the name of the object.
		 *  @see year
		 */
		unsigned int getYear() const;

		/**
		 *  @brief Sets the day of the object Date according to the argument received.
		 *  @param d New day to replace current day.
		 *  @see day
		 */
		void setDay(unsigned int d);

		/**
		 *  @brief Sets the month of the object Date according to the argument received.
		 *  @param m New month to replace current month.
		 *  @see month
		 */
		void setMonth(unsigned int m);

		/**
		 *  @brief Sets the year of the object Date according to the argument received.
		 *  @param y New year to replace current year.
		 *  @see year
		 */
		void setYear(unsigned int y);

		/**
		 *  @brief Compares two object Date.
		 *  @param d Comparable object Date.
		 *  @return Returns true if the object is smaller then the argument and false otherwise.
		 */
		bool operator <(const Date &d) const;

		/**
		 *  @brief Formats the object Date's data to a std::string, in order to display it.
		 *  @return Returns a formatted std::string with all the object's data.
		 */
		std::string display();

	};

	/**
	 *  @brief Class representing the status of a service.
	 *
	 *  This class is nested in class Service.
	 */
	class Status {

		/**
		 *  @brief Status of the service.
		 *
		 *  0: Open.
		 *  1: Closed temporarily.
		 *  2: Closed permanently.
		 */
		unsigned int closed;

		/**
		 *  @brief Closing date of the service
		 */
		Date closing_date;

	public:

		/**
		 *  @brief Status class constructor.
		 */
		Status();

		/**
		 *  @brief Status class constructor with arguments.
		 *  @param c Status of the object.
		 *  @param d Day of the closing date of the object.
		 *  @param m Month of the closing date of the object.
		 *  @param y Year of the closing date of the object.
		 */
		Status(unsigned int c, unsigned int d, unsigned int m, unsigned int y);

		/**
		 *  @brief Praia class destructor.
		 */
		~Status();

		/**
		 *  @brief Gets the status of the object Status.
		 *  @return Returns the status of the object.
		 *  @see closed
		 */
		unsigned int getClosed() const;

		/**
		 *  @brief Gets the closing date of the object Status.
		 *  @return Returns the closing date of the object.
		 *  @see closing_date
		 */
		Date getClosingDate() const;

		/**
		 *  @brief Sets the status of the object Status according to the argument received.
		 *  @param c New status to replace current status.
		 *  @see status
		 */
		void setClosed(unsigned int c);

		/**
		 *  @brief Sets the closing date of the object Status according to the arguments received.
		 *  @param d New day to replace current day.
		 *  @param m New month to replace current month.
		 *  @param y New year to replace current year.
		 *  @see closing_date
		 */
		void setClosingDate(unsigned int d, unsigned int m, unsigned int y);
	};

	/**
	 *  @brief Type of the service.
	 */
	service_t type;

	/**
	 *  @brief Name of the service.
	 */
	std::string name;

	/**
	 *  @brief Last inspection of the service.
	 */
	Date last_inspection;

	/**
	 *  @brief Status of the service.
	 */
	Status status;

public:

	/**
	 *  @brief Service class constructor.
	 */
	Service();

	/**
	 *  @brief Service class constructor.
	 *  @param t Type of the object.
	 *  @param n Name of of the object.
	 *  @param inspection_d Day of the last inspection of the object.
	 *  @param inspection_m Month of the last inspection of the object.
	 *  @param inspection_y Year of the last inpection of the object.
	 */
	Service(service_t t, std::string n, unsigned int inspection_d, unsigned int inspection_m, unsigned int inspection_y);

	/**
	 *  @brief Service class constructor.
	 *  @param t Type of the object.
	 *  @param n Name of of the object.
	 *  @param inspection_d Day of the last inspection of the object.
	 *  @param inspection_m Month of the last inspection of the object.
	 *  @param inspection_y Year of the last inpection of the object.
	 *  @param c Status of the object (closed or open).
	 *  @param closed_d Day of the closing date of the object.
	 *  @param closed_m Month of the closing date of the object.
	 *  @param closed_y Year of the closing date of the object.
	 */
	Service(service_t t, std::string n, unsigned int inspection_d, unsigned int inspection_m, unsigned int inspection_y, unsigned int c, unsigned int closed_d, unsigned int closed_m, unsigned int closed_y);

	/**
	 *  @brief Service class destructor.
	 */
	~Service();

	/**
	 *  @brief Gets the type of the object Service.
	 *  @return Returns the type of the object.
	 *  @see type
	 */
	service_t getType() const;

	/**
	 *  @brief Gets the name of the object Service.
	 *  @return Returns the name of the object.
	 *  @see name
	 */
	std::string getName() const;

	/**
	 *  @brief Gets the date of the last inspection of the object Service.
	 *  @return Returns the date of the last inspection of the object.
	 *  @see last_inspection
	 */
	Date getDate() const;

	/**
	 *  @brief Gets the status of the object Service.
	 *  @return Returns the status of the object.
	 *  @see status
	 */
	Status getStatus() const;

	/**
	 *  @brief Sets the type of the object Service according to the argument received.
	 *  @param t New type to replace current type.
	 *  @see type
	 */
	void setType(service_t t);

	/**
	 *  @brief Sets the name of the object Service according to the argument received.
	 *  @param n New name to replace current name.
	 *  @see name
	 */
	void setName(std::string n);

	/**
	 *  @brief Sets the date of the last inspection of the object Service according to the arguments received.
	 *  @param d New day to replace current day.
	 *  @param m New month to replace current month.
	 *  @param y New year to replace current year.
	 *  @see last_inspection
	 */
	void setDate(unsigned int d, unsigned int m, unsigned int y);

	/**
	 *  @brief Sets the status of the object Service according to the argument received.
	 *  @param s New status to replace current status.
	 *  @param s_d New day to replce current day.
	 *  @param s_m New month to replace current month.
	 *  @param s_y New year to replace current year.
	 *  @see status
	 */
	void setStatus(unsigned int s, unsigned int s_d, unsigned int s_m, unsigned int s_y);

	/**
	 *  @brief Compares two object Service.
	 *  @param s Comparable object Service.
	 *  @return Returns true if they are equal and false otherwise.
	 */
	bool operator ==(const Service &s) const;

	/**
	 *  @brief Compares two object Service.
	 *  @param s Comparable object Service.
	 *  @return Returns true if the object is smaller then the argument and false otherwise.
	 */
	bool operator <(const Service &s) const;

	/**
	 *  @brief Formats the object Service's data to a std::string, in order to display it.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	std::string displayService() const;

};

service_t to_enum(std::string str);
std::string from_enum(service_t s);

#endif
