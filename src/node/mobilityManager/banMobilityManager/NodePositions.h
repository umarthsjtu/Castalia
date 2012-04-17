
#include "Coord.h"

class NodePositions {
	protected:
		/** @brief Number of time intervals full in the input xml file for this node */
		unsigned int numberOfTimeIntervals;
		/** @brief A given name to the node  */
		char* node_name;
		/** @brief The unique ID of the node */
		unsigned int nodeID;
		Coord* nodePs;
		Coord* nodeAngle;
		double* nodeAcceleration;

	public:
		/** @brief Construct a posture object with the given ID and number of nodes, respectively */
		NodePositions(unsigned int, unsigned int);
		NodePositions(const NodePositions&);
		virtual ~NodePositions();
		
		/*** Setters ***/
		bool setNodeName(const char*);
		bool setNodeId(unsigned int);
		bool setPs(unsigned int, Coord );
		bool setAngle(unsigned int, Coord);
		bool setAcceleration(unsigned int, double);
		
		/*** Getters ***/
		const char* getNodeName() const;	
		unsigned int getNodeId() const;
		Coord getPs(unsigned int) const;
		Coord getAngle(unsigned int) const;
		double getAcceleration(unsigned int) const;
};
