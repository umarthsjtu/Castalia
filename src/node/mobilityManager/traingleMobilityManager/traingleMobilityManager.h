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

#ifndef _MOBILITYMODULE_H_
#define _MOBILITYMODULE_H_

#include "MobilityManagerMessage_m.h"
#include "VirtualMobilityManager.h"

using namespace std;

class traingleMobilityManager: public VirtualMobilityManager {
 private:
	/*--- The .ned file's parameters ---*/
	double updateInterval;
	double loc1_x;
	double loc1_y;
	double loc1_z;
	double loc2_x;
	double loc2_y;
	double loc2_z;
	double locmid_x;
	double locmid_y;
	double locmid_z;
	double speed;

	/*--- Custom class parameters ---*/
	double incr_x_1;
	double incr_y_1;
	double incr_z_1;
	double incr_x_2;
	double incr_y_2;
	double incr_z_2;
	double distance_1;
        double distance_2;
	int direction;
	int markup;
        int handover;

 protected:
	void initialize();
	void handleMessage(cMessage * msg);
};

#endif
