#include "RoutingControl.h"

Define_Module(RoutingControl);

void RoutingControl::initialize(int i)
{
     int a=par("i");
}

void RoutingControl::handleMessage(cMessage * msg)
{
	int msgKind = msg->getKind();
	switch (msgKind)
	{
		case 1 :
		{
         		delete(msg);
		}
		default:{
			delete(msg);
		}
	}
}

void RoutingControl::finishSpecific(){
	int b=9;
}
	
