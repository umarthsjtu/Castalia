#ifndef _MOBILITYMODULE_H_
#define _MOBILITYMODULE_H_

#include "MobilityManagerMessage_m.h"
#include "VirtualMobilityManager.h"
#include "NodePositions.h"

#include <cxmlelement.h>
#include <vector>

using namespace std;

class BanMobilityManager: public VirtualMobilityManager {
 public:
   /** Reading the input positions file and making the positions data base for this node. */
   bool readNodesSpecificationFile(int nodeIndex);
   virtual ~BanMobilityManager();
 
 private:
	/*--- The .ned file's parameters ---*/
	double updateInterval;
	cXMLElement* xmlDatas;

	/*--- Custom class parameters ---*/
	bool direction;
	unsigned int currentIntervalNumber;
	unsigned int totalNumberOfTimeIntervals;
	/** @brief The list of all predefined positions of the cureent node (node data base) */
    NodePositions* nodePositions;

 protected:
	void initialize();
	void handleMessage(cMessage * msg);
};

#endif
