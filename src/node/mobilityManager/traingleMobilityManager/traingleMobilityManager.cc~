/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Yuriy Tselishchev                                            *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *  
 ****************************************************************************/

#include "traingleMobilityManager.h"

Define_Module(traingleMobilityManager);

void traingleMobilityManager::initialize()
{
	VirtualMobilityManager::initialize();

	updateInterval = par("updateInterval");
	updateInterval = updateInterval / 1000;

	loc1_x = nodeLocation.x;
	loc1_y = nodeLocation.y;
	loc1_z = nodeLocation.z;
	loc2_x = par("xCoorDestination");
	loc2_y = par("yCoorDestination");
	loc2_z = par("zCoorDestination");
        locmid_x = par("xCoorDestinationmid");
	locmid_y = par("yCoorDestinationmid");
	locmid_z = par("zCoorDestinationmid");
	speed = par("speed");

	//distance = sqrt(pow(loc1_x - loc2_x, 2) + pow(loc1_y - loc2_y, 2) +
	//	 pow(loc1_z - loc2_z, 2));

	direction = 1;
        markup = 1;
        handover = 0;
	if (speed > 0) {
		//if( (loc1_x <= locmid_x) && (loc1_y <= locmid_y) && (loc1_z <= locmid_z)){
                 	distance_1 = sqrt(pow(loc1_x - locmid_x, 2) + pow(loc1_y - locmid_y, 2) +
		 			pow(loc1_z - locmid_z, 2));
                        double tmp_1 = (distance_1 / speed) / updateInterval;
		        incr_x_1 = (locmid_x - loc1_x) / tmp_1;
			incr_y_1 = (locmid_y - loc1_y) / tmp_1;
			incr_z_1 = (locmid_z - loc1_z) / tmp_1;

                 	distance_2 = sqrt(pow(locmid_x - loc2_x, 2) + pow(locmid_y - loc2_y, 2) +
		 			pow(locmid_z - loc2_z, 2));
                        double tmp_2 = (distance_2 / speed) / updateInterval;
		        incr_x_2 = (loc2_x - locmid_x) / tmp_2;
			incr_y_2 = (loc2_y - locmid_y) / tmp_2;
			incr_z_2 = (loc2_z - locmid_z) / tmp_2;

			setLocation(loc1_x, loc1_y, loc1_z);
			scheduleAt(simTime() + updateInterval,
					new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));

	}
}

void traingleMobilityManager::handleMessage(cMessage * msg)
{
	int msgKind = msg->getKind();
	switch (msgKind) {

		case MOBILITY_PERIODIC:{
		if(markup == 1){
			if (direction) {
				nodeLocation.x += incr_x_1;
				nodeLocation.y += incr_y_1;
				nodeLocation.z += incr_z_1;
				if (   (incr_x_1 > 0 && nodeLocation.x > locmid_x)
				    || (incr_x_1 < 0 && nodeLocation.x < locmid_x)
				    || (incr_y_1 > 0 && nodeLocation.y > locmid_y)
				    || (incr_y_1 < 0 && nodeLocation.y < locmid_y)
				    || (incr_z_1 > 0 && nodeLocation.z > locmid_z)
				    || (incr_z_1 < 0 && nodeLocation.z < locmid_z)) {
					//direction = 0;
                                        markup = 2;
					//trace()<<"---------------------"<<markup<<"----------------------------"<<endl;
					nodeLocation.x -= incr_x_1;//(nodeLocation.x - locmid_x) * 2;
					nodeLocation.y -= incr_y_1;//(nodeLocation.y - locmid_y) * 2;
					nodeLocation.z -= incr_z_1;//(nodeLocation.z - locmid_z) * 2;
				}
			} else {
				nodeLocation.x -= incr_x_1;
				nodeLocation.y -= incr_y_1;
				nodeLocation.z -= incr_z_1;
				if (   (incr_x_1 > 0 && nodeLocation.x < loc1_x)
				    || (incr_x_1 < 0 && nodeLocation.x > loc1_x)
				    || (incr_y_1 > 0 && nodeLocation.y < loc1_y)
				    || (incr_y_1 < 0 && nodeLocation.y > loc1_y)
				    || (incr_z_1 > 0 && nodeLocation.z < loc1_z)
				    || (incr_z_1 < 0 && nodeLocation.z > loc1_z)) {
					direction = 1;
					nodeLocation.x += incr_x_1;//(nodeLocation.x - loc1_x) * 2;
					nodeLocation.y += incr_y_1;//(nodeLocation.y - loc1_y) * 2;
					nodeLocation.z += incr_z_1;//(nodeLocation.z - loc1_z) * 2;
				}
			}
			notifyWirelessChannel();
			scheduleAt(simTime() + updateInterval,
				new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));

			trace() << "changed location(x:y:z) to " << nodeLocation.x << 
					":" << nodeLocation.y << ":" << nodeLocation.z;
			break;
                 }
                 if(markup == 2){
                  	if (direction) {
				nodeLocation.x += incr_x_2;
				nodeLocation.y += incr_y_2;
				nodeLocation.z += incr_z_2;
				if (   (incr_x_2 > 0 && nodeLocation.x > loc2_x)
				    || (incr_x_2 < 0 && nodeLocation.x < loc2_x)
				    || (incr_y_2 > 0 && nodeLocation.y > loc2_y)
				    || (incr_y_2 < 0 && nodeLocation.y < loc2_y)
				    || (incr_z_2 > 0 && nodeLocation.z > loc2_z)
				    || (incr_z_2 < 0 && nodeLocation.z < loc2_z)) {
					direction = 0;
					nodeLocation.x -= incr_x_2;//(nodeLocation.x - loc2_x) * 2;
					nodeLocation.y -= incr_y_2;//(nodeLocation.y - loc2_y) * 2;
					nodeLocation.z -= incr_z_2;//(nodeLocation.z - loc2_z) * 2;
				}
			} else {
				nodeLocation.x -= incr_x_2;
				nodeLocation.y -= incr_y_2;
				nodeLocation.z -= incr_z_2;
				if (   (incr_x_2 > 0 && nodeLocation.x < locmid_x)
				    || (incr_x_2 < 0 && nodeLocation.x > locmid_x)
				    || (incr_y_2 > 0 && nodeLocation.y < locmid_y)
				    || (incr_y_2 < 0 && nodeLocation.y > locmid_y)
				    || (incr_z_2 > 0 && nodeLocation.z < locmid_z)
				    || (incr_z_2 < 0 && nodeLocation.z > locmid_z)) {
					//direction = 1;
                                        markup = 1;
                                       // trace()<<"----------------------------"<<markup<<"-------------------------"<<endl;
					nodeLocation.x += incr_x_2;//(nodeLocation.x - loc1_x) * 2;
					nodeLocation.y += incr_y_2;//(nodeLocation.y - loc1_y) * 2;
					nodeLocation.z += incr_z_2;//(nodeLocation.z - loc1_z) * 2;
				}
			}
			notifyWirelessChannel();
			scheduleAt(simTime() + updateInterval,
				new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));

			trace() << "changed location(x:y:z) to " << nodeLocation.x << 
					":" << nodeLocation.y << ":" << nodeLocation.z;
			break;
		  }
		}

		default:{
			trace() << "WARNING: Unexpected message " << msgKind;
		}
	}

	delete msg;
	msg = NULL;
}

