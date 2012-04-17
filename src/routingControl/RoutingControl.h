#ifndef _ROUTINGCONTROL_H
#define _ROUTINGCONTROL_H

//#include "RoutingControlMessages_m.h"
//#include <queue>
//#include <omnetpp.h>

#include "CastaliaModule.h"
//#include "TimerService.h"
//#include "CastaliaMessages.h"
//#include "ResourceManager.h"
//#include "RoutingPacket_m.h"

//#include "time.h"
#include <list>
//#include "VirtualMobilityManager.h"

using namespace std;

class RoutingControl: public CastaliaModule {
 private:
    list<int> *a;
    bool collectTraceInfo;

 protected:
     virtual void initialize(int);
     virtual void handleMessage(cMessage * msg);
     virtual void finishSpecific();
	
};

#endif				//_ROUTINGCONTROL_H
