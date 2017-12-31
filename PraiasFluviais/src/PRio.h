
#ifndef PRIO_H_
#define PRIO_H_

#include "Praia.h"

/**
 *  @file PRio.h
 */

/**
 *  @brief PRio class is publicly derived from class Praia.
 *
 *  An object PRio is an object Praia with a river.
 *  @see Praia
 */
class PRio : public Praia {

	/**
	 *  @brief Width of the river.
	 */
	double width;

	/**
	 *  @brief Flow of the river.
	 */
	double flow;

	/**
	 *  @brief Dpeth of the river.
	 */
	double depth;

public:

	/**
	 *  @brief PRio class constructor.
	 */
	PRio();

	/**
	 *  @brief PRio class constructor with arguments.
	 *  @param n Name of the object.
	 *  @param c Name of concelho of the object.
	 *  @param s Queue of open services of the object.
	 *  @param cap Capacity of the object.
	 *  @param bA Bandeira of the object.
	 *  @param cd Coordinates of the object.
	 *  @param w Width of the river of the object.
	 *  @param f Flow of the river of the object.
	 *  @param d Depth of the river of the object.
	 */
	PRio(std::string n, std::string c, std::priority_queue<Service> s, unsigned int cap, bool bA, Gps cd, double w, double f, double d);

	/**
	 *  @brief PRio class destructor.
	 */
	~PRio();

	/**
	 *  @brief Gets the width of the object PRio.
	 *  @return Returns the width of the object.
	 *  @see width
	 */
	double getWidth() const;

	/**
	 *  @brief Gets the flow of the object PRio.
	 *  @return Returns the flow of the object.
	 *  @see flow
	 */
	double getFlow() const;

	/**
	 *  @brief Gets the depth of the object PRio.
	 *  @return Returns the depth of the object.
	 *  @see depth
	 */
	double getDepth() const;

	/**
	 *  @brief Sets the width of the object PRio according to the argument received.
	 *  @param w New width to replace current width.
	 *  @see width
	 */
	void setWidth(double w);

	/**
	 *  @brief Sets the flow of the object PRio according to the argument received.
	 *  @param f New flow to replace current flow.
	 *  @see flow
	 */
	void setFlow(double f);

	/**
	 *  @brief Sets the depth of the object PRio according to the argument received.
	 *  @param d New depth to replace current depth.
	 *  @see depth
	 */
	void setDepth(double d);

	/**
	 *  @brief Formats the object PRio's data to a std::string, in order to save in a .txt file.
	 *  @return Returns a formatted std::string with all the object's data.
	 */
	std::string savePraia();

	/**
	 *  @brief Prints the object PRio's data to the screen.
	 */
	void fullInfoPraia();
};

#endif /* PRIO_H_ */
