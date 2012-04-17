
#include "NodePositions.h"

NodePositions::NodePositions(unsigned int id, unsigned int num)
	/*: numberOfTimeIntervals(num)
	, node_name(NULL)
	, nodeID(id)
	, nodePs(NULL)
	, nodeAngle(NULL)
	, nodeAcceleration(NULL) */
{
	numberOfTimeIntervals = num;
	nodeID = id;
	node_name=NULL;
	nodePs = new Coord[numberOfTimeIntervals];
	nodeAngle = new Coord[numberOfTimeIntervals];
	nodeAcceleration =  new double[numberOfTimeIntervals];
}

NodePositions::NodePositions(const NodePositions& o)
	: numberOfTimeIntervals(o.numberOfTimeIntervals)
	, node_name()
	, nodeID(o.nodeID)
	, nodePs(NULL)
	, nodeAngle(NULL)
	, nodeAcceleration(NULL)
{
	strcpy(node_name, o.node_name);
	nodePs     = new Coord[numberOfTimeIntervals];
	nodeAngle     = new Coord[numberOfTimeIntervals];
	nodeAcceleration  = new double[numberOfTimeIntervals];

	for (unsigned j=0; j < numberOfTimeIntervals; ++j) {
		nodePs[j]     = o.nodePs[j];
		nodeAngle[j] = o.nodeAngle[j];
		nodeAcceleration[j]  = o.nodeAcceleration[j];
	}
}

NodePositions::~NodePositions(){
	delete[] node_name;
	delete[] nodePs;
	delete[] nodeAngle;
	delete[] nodeAcceleration;
}

/**** SETTERS ****/


bool NodePositions::setNodeName(const char *str){
	strncpy(node_name, str, sizeof(node_name)/sizeof(node_name[0]));
	return true;
}

bool NodePositions::setNodeId(unsigned int nodeId){
	nodeID = nodeId;
	return true;
}

bool NodePositions::setPs(unsigned int i , Coord ps){
	if (i<numberOfTimeIntervals){
		nodePs[i] = ps;
		return true;
	}
	return false;
}

bool NodePositions::setAngle(unsigned int i, Coord agl){
	if (i<numberOfTimeIntervals){
		nodeAngle[i] = agl;
		return true;
	}
	return false;
}

bool NodePositions::setAcceleration(unsigned int i , double acceleration){
	if (i<numberOfTimeIntervals){
		nodeAcceleration[i] = acceleration;
		return true;
	}
	return false;
}

/**** GETTERS ****/
const char* NodePositions::getNodeName() const{
	return node_name;
}

unsigned int NodePositions::getNodeId() const{
	return nodeID;
}

Coord NodePositions::getPs(unsigned int i) const{
	if (i<numberOfTimeIntervals)
		return nodePs[i];

	return Coord(-1,-1,-1);
}

Coord NodePositions::getAngle(unsigned int i) const{
	if (i<numberOfTimeIntervals)
		return nodeAngle[i];

	return Coord(0,0,0);
}

double NodePositions::getAcceleration(unsigned int i) const{
	if (i<numberOfTimeIntervals)
		return nodeAcceleration[i];
	return -1;
}




