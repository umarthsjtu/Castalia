
#include "BanMobilityManager.h"

Define_Module(BanMobilityManager);
/*
 *   Ajouter    1 neck, 1 Stomach, 2 Elbows (coudes), 2 knees, 2 ankles (cheville ?)
 * 
 *   Voir si peut trouver des traces ou modèles utilisables avant mercredi
 * 
*/
void BanMobilityManager::initialize()
{
	VirtualMobilityManager::initialize();
	
	updateInterval = par("updateInterval");
	updateInterval = updateInterval / 1000;
	currentIntervalNumber = 0;
	direction = true;
	
	if (!readNodesSpecificationFile(index))
		error("Mobility Module: error in reading the node positions file");
		
	nodeLocation.x = nodePositions->getPs(0).x;
	nodeLocation.y = nodePositions->getPs(0).y;
	nodeLocation.z = nodePositions->getPs(0).z;
	nodeLocation.phi = nodePositions->getAngle(0).x;
	nodeLocation.theta = nodePositions->getAngle(0).y;
	nodeLocation.gamma = nodePositions->getAngle(0).z;
	nodeLocation.a = nodePositions->getAcceleration(0);
	notifyWirelessChannel();

	trace() << "Initial node location is (" << nodeLocation.x <<","<< nodeLocation.y << "," << nodeLocation.z <<")";;
	//trace()	<<" with input location parameter t = "<< currentIntervalNumber <<" for this node";		
	//trace() << "totalNumber of location parameters in the input file for this node =" << totalNumberOfTimeIntervals-1;
	
	currentIntervalNumber++;
	scheduleAt(simTime() + updateInterval,new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));
}

void BanMobilityManager::handleMessage(cMessage * msg)
{
	int msgKind = msg->getKind();
	
	switch (msgKind) {
		
		case MOBILITY_PERIODIC:{
			if(currentIntervalNumber == 0)
				direction = true;   //go
			if(currentIntervalNumber == totalNumberOfTimeIntervals-1)
				direction = false;   //return
					
			nodeLocation.x = nodePositions->getPs(currentIntervalNumber).x;
			nodeLocation.y = nodePositions->getPs(currentIntervalNumber).y;
			nodeLocation.z = nodePositions->getPs(currentIntervalNumber).z;
			nodeLocation.phi = nodePositions->getAngle(currentIntervalNumber).x;
			nodeLocation.theta = nodePositions->getAngle(currentIntervalNumber).y;
			nodeLocation.gamma = nodePositions->getAngle(currentIntervalNumber).z;
			nodeLocation.a = nodePositions->getAcceleration(currentIntervalNumber);
			notifyWirelessChannel();
			
			trace() << "New node location is (" << nodeLocation.x <<","<< nodeLocation.y << "," << nodeLocation.z <<")";;
			//trace()	<<" with input location parameter t = "<< currentIntervalNumber <<" for this node";	
	
			if (direction) 
				currentIntervalNumber++;
			 else 
				currentIntervalNumber--;

			scheduleAt(simTime() + updateInterval, new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));
			break;
		}

		default:{
			trace() << "WARNING: Unexpected message " << msgKind;
		}
	}
	delete msg;
	msg = NULL;
}

/**
 * Function to read the specified nodes specification input file and make the nodes data base.
 * The function will be called in the initialization phase.
*/
bool BanMobilityManager::readNodesSpecificationFile(int nodeIndex) {
	
	cXMLElement* xmlDatas = par("nodesSpecFile").xmlValue();
	
	if (xmlDatas == 0)
		return false;
	
	const char* str;
	int numNodes;
	
	//read the specification of every nodes from file and make a list of nodes movements
	cXMLElementList nodes;

	nodes = xmlDatas->getElementsByTagName("node");

	//Find the number of defined nodes
	numNodes = nodes.size();
	if (numNodes == 0)
		error("No node is defined in the input posture specification file");

	unsigned int nodeID;
	totalNumberOfTimeIntervals = 0;  
	int p=0;
	cXMLElementList::const_iterator node;
	
	for (node = nodes.begin(); node != nodes.end(); node++)
	{
		str = (*node)->getAttribute("nodeID");
		const long lNodeID = strtol(str, 0, 0);
		if ( lNodeID < 0 || static_cast<unsigned int>(lNodeID) >= numNodes)
			error ("Node ID in input positions file is out of the range.");
		
		if (lNodeID == nodeIndex){
			int i = 0;                     //used to count the number of time intervals			         
			double x, y, z, a, phi, theta, gamma;
			
			cXMLElementList nodeParameters;
			nodeParameters = (*node)->getElementsByTagName("nodeParameters");
			
			totalNumberOfTimeIntervals = nodeParameters.size();
			nodeID = static_cast<unsigned int>(lNodeID);
			const char* nodeName = (*node)->getAttribute("name");
			
			nodePositions = new NodePositions(nodeID, totalNumberOfTimeIntervals);
			//nodePositions.setNodeName(nodeName);   // TODO : don't work
			
			cXMLElementList::const_iterator param;
			
			for (param = nodeParameters.begin(); param!= nodeParameters.end(); param++)
			{	
				str = (*param)->getAttribute("positionX");
				x = strtod(str, 0);

				str = (*param)->getAttribute("positionY");
				y = strtod(str, 0);

				str = (*param)->getAttribute("positionZ");
				z = strtod(str, 0);

				str = (*param)->getAttribute("phi");
				phi = strtod(str, 0);
				
				str = (*param)->getAttribute("theta");
				theta = strtod(str, 0);
				
				str = (*param)->getAttribute("gamma");
				gamma = strtod(str, 0);

				str = (*param)->getAttribute("acceleration");
				a = strtod(str, 0);
				
				nodePositions->setPs(i, Coord(x, y, z));
				nodePositions->setAngle(i, Coord(phi, theta, gamma));
				nodePositions->setAcceleration(i, a);
				
				// Report the obtained specification of the nodes. 
				/*
				trace()  << "Interval of time "<< i 
							<< ", position: "<< nodePositions->getPs(i).info()
							<<"|| angles: "<< nodePositions->getAngle(i).info()
							<<" || acceleration: "<< nodePositions->getAcceleration(i);
				*/
				i++;
			}
			
		}
		p++;
	}	
	return true;
}

BanMobilityManager::~BanMobilityManager(){
	delete[] nodePositions;
	delete[] xmlDatas;
}


