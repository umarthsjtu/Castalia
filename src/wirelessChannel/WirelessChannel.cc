/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#include "WirelessChannel.h"

Define_Module(WirelessChannel);

int WirelessChannel::numInitStages() const
{
	return 2;
}

void WirelessChannel::initialize(int stage)
{
	if (stage == 0) {
		readIniFileParameters();//第一次初始化 读取参数
		return;
	}

	/* variable to report initialization run time */
	clock_t startTime;
	startTime = clock();

	/****************************************************
	 * To handle mobile nodes we break up the space into
	 * cells. All path loss calculations are now done
	 * between cells. First we need to find out how many
	 * distinct cells we have in space, based on the
	 * dimensions of the space and the declared cell size.
	 * If we only have static nodes, then we keep the
	 * same variables and abstractions to make the code
	 * more compact and easier to read, but we do not
	 * really need to divide the space into cells. Even
	 * though we keep the variable names, cells in the
	 * static case only correspond to node positions
	 * and we only have numOfNodes cells, much like
	 * we used to do in Castalia 1.3
	 ****************************************************/

	if (onlyStaticNodes) {                   //如果静态，空间cell大小个数等于点的个数
		numOfSpaceCells = numOfNodes;
	} else {                                 //处理场地小于等于0的问题
		if (xFieldSize <= 0) { 
			xFieldSize = 1;
			xCellSize = 1;
		}
		if (yFieldSize <= 0) {
			yFieldSize = 1;
			yCellSize = 1;
		}
		if (zFieldSize <= 0) {
			zFieldSize = 1;
			zCellSize = 1;
		}
		if (xCellSize <= 0)             //处理cell小于等于0的情况
			xCellSize = xFieldSize;
		if (yCellSize <= 0)
			yCellSize = yFieldSize;
		if (zCellSize <= 0)
			zCellSize = zFieldSize;

		numOfZCells = (int)ceil(zFieldSize / zCellSize);
		numOfYCells = (int)ceil(yFieldSize / yCellSize);
		numOfXCells = (int)ceil(xFieldSize / xCellSize);
		numOfSpaceCells = numOfZCells * numOfYCells * numOfXCells;
                
	   /***************************************************************
	    * Calculate some values that  help us transform a 1D index in
	    * [0..numOfSpaceCells -1] to a 3D index x, y, z and vice versa.
	    * Each variable holds index increments (in the 1D large index)
	    * needed to move one space cell in the z, y, and x directions
	    **************************************************************/
		zIndexIncrement = numOfYCells * numOfXCells;
		yIndexIncrement = numOfXCells;
		xIndexIncrement = 1;
	}

	/***************************************************************
	 * Allocate and initialize cellOccupation and nodeLocation.
	 * nodeLocation keeps the state about all nodes locations and
	 * cellOccupation is an array of lists. List at index i contains
	 * the node IDs that reside in cell i. We define and use these
	 * arrays even for the static nodes case as it makes the code
	 * more compact and easier to follow.
	 **************************************************************/
	nodeLocation = new NodeLocation_type[numOfNodes]; //node 位置
	if (nodeLocation == NULL)
		opp_error("Could not allocate array nodeLocation\n");

	cellOccupation = new list<int>[numOfSpaceCells];  //节点cell占用分配
	if (cellOccupation == NULL)
		opp_error("Could not allocate array cellOccupation\n");
	
        if(hasobjectmodel){
		objectmodel = new int**[numOfXCells];
        	for(int i = 0; i< numOfXCells;i++)
			objectmodel[i]= new int*[numOfYCells];
        	for(int i = 0; i< numOfXCells;i++)
			for(int j = 0; j<numOfYCells;j++)
				objectmodel[i][j] = new int[numOfZCells];
		for(int i = 0; i< numOfXCells;i++)
			for(int j = 0; j<numOfYCells;j++)
				for(int k = 0; k<numOfZCells; k++)
					objectmodel[i][j][k] = 0;
		
		handleObjectModel();
          }

	cTopology *topo;	// temp variable to access initial location of the nodes
	topo = new cTopology("topo");          //
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	for (int i = 0; i < numOfNodes; i++) {
		VirtualMobilityManager *nodeMobilityModule =
			check_and_cast<VirtualMobilityManager*>
			(topo->getNode(i)->getModule()->getSubmodule("MobilityManager"));
		nodeLocation[i] = nodeMobilityModule->getLocation();
		nodeLocation[i].cell = i;

		if (!onlyStaticNodes) {
			/******************************************************************
			 * Compute the cell this node is in and initialize cellOccupation.
			 * Cavaet in computing the XYZ indices:
			 * Because we allow cell resolutions that do not perfectly divide
			 * the field (we take the ceiling of the division when calculating
			 * numOfXCells) this means that the edge cells might be smaller than
			 * the others. So in some cases, the calculation we are doing
			 * below, might give the wrong cell by +1. That's why we are doing
			 * the test immediately after.
			 ******************************************************************/
			int xIndex = (int)floor(nodeLocation[i].x / xFieldSize * numOfXCells);
			if (((xIndex - 1) * xCellSize) >= nodeLocation[i].x)
				xIndex--;
			else if (xIndex >= numOfXCells) {
				xIndex = numOfXCells - 1;	// the maximum possible x index
				if (nodeLocation[i].x > xFieldSize)
					trace() << "WARNING at initialization: node position out of bounds in X dimension!\n";
			}

			int yIndex = (int)floor(nodeLocation[i].y / yFieldSize * numOfYCells);
			if (((yIndex - 1) * yCellSize) >= nodeLocation[i].y)
				yIndex--;
			else if (yIndex >= numOfYCells) {
				yIndex = numOfYCells - 1;	// the maximum possible y index
				if (nodeLocation[i].y > yFieldSize)
					trace() << "WARNING at initialization: node position out of bounds in Y dimension!\n";
			}

			int zIndex = (int)floor(nodeLocation[i].z / zFieldSize * numOfZCells);
			if (((zIndex - 1) * zCellSize) >= nodeLocation[i].z)
				zIndex--;
			else if (zIndex >= numOfZCells) {
				zIndex = numOfZCells - 1;	// the maximum possible z index
				if (nodeLocation[i].z > zFieldSize)
					trace() << "WARNING at initialization: node position out of bounds in Z dimension!\n";
			}

			int cell = zIndex * zIndexIncrement + yIndex * yIndexIncrement + xIndex * xIndexIncrement;
			if (cell < 0 || cell >= numOfSpaceCells) {
				opp_error("Cell out of bounds for node %i, please check your mobility module settings\n", i);
			}

			nodeLocation[i].cell = cell;
		}

		/*************************************************
		 * pushing ID i into the list cellOccupation[cell]
		 * (if onlyStaticNodes cell=i )
		 *************************************************/
		cellOccupation[nodeLocation[i].cell].push_front(i);
	}
	delete(topo);

	/**********************************************
	 * Allocate and initialize the pathLoss array.
	 * This is the "propagation map" of our space.
	 **********************************************/
	pathLoss = new list<PathLossElement*>[numOfSpaceCells];//cell的路径损失
	if (pathLoss == NULL)
		opp_error("Could not allocate array pathLoss\n");

	int elementSize = sizeof(PathLossElement) + 3 * sizeof(PathLossElement *);  //why？
	int totalElements = 0;	//keep track of pathLoss size for reporting purposes

	float x1, x2, y1, y2, z1, z2, dist;
	float PLd;		// path loss at distance dist, in dB
	float bidirectionalPathLossJitter; // variation of the pathloss in the two directions of a link, in dB
        
		int objectcellX1,objectcellY1,objectcellZ1,objectcellX2,objectcellY2,objectcellZ2;
		float increX,increY,increZ;
		int index;

		float x,y,z;	
		int objectsize;
		int xx,yy,zz;
		float dist1,dist2;
		int tempmax;
		int tempmax1;
	
	/*******************************************************
	 * Calculate the distance, beyond which we cannot
	 * have connectivity between two nodes. This calculation is
	 * based on the maximum TXPower the signalDeliveryThreshold
	 * the pathLossExponent, the PLd0. For the random
	 * shadowing part we use 3*sigma to account for 99.7%
	 * of the cases. We use this value to considerably
	 * speed up the filling of the pathLoss array,
	 * especially for the mobile case.
	 *******************************************************/
	float distanceThreshold = d0 *
		pow(10.0,(maxTxPower - signalDeliveryThreshold - PLd0 + 3 * sigma) /
		(10.0 * pathLossExponent));
	for (int i = 0; i < numOfSpaceCells; i++) {
		if (onlyStaticNodes) {
			x1 = nodeLocation[i].x;
			y1 = nodeLocation[i].y;
			z1 = nodeLocation[i].z;
		} else {
			z1 = zCellSize * (int)floor(i / zIndexIncrement);
			y1 = yCellSize * (int)floor((i % zIndexIncrement) / yIndexIncrement);
			x1 = xCellSize * (int)floor((i % yIndexIncrement) / xIndexIncrement);
		}

		/* Path loss to yourself is 0.0 */
		pathLoss[i].push_front(new PathLossElement(i, 0.0));
		totalElements++;	//keep track of pathLoss size for reporting purposes

		for (int j = i + 1; j < numOfSpaceCells; j++) {
			if (onlyStaticNodes) {
				x2 = nodeLocation[j].x;
				y2 = nodeLocation[j].y;
				z2 = nodeLocation[j].z;
			} else {
				z2 = zCellSize * (int)(j / zIndexIncrement);
				y2 = yCellSize * (int)((j % zIndexIncrement) / yIndexIncrement);
				x2 = xCellSize * (int)((j % yIndexIncrement) / xIndexIncrement);

				if (fabs(x1 - x2) > distanceThreshold)
					continue;
				if (fabs(y1 - y2) > distanceThreshold)
					continue;
				if (fabs(z1 - z2) > distanceThreshold)
					continue;
			}
                        if(!hasobjectmodel){
				dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
				if (dist > distanceThreshold)
					continue;

				/* if the distance is very small (arbitrarily: smaller than one tenth
			 	* of the reference distance) then make the path loss 0dB
				 */
				if (dist < d0/10.0) {
					PLd = 0;
					bidirectionalPathLossJitter = 0;
				}
				else {
					PLd = PLd0 + 10.0 * pathLossExponent * log10(dist / d0) + normal(0, sigma);
					bidirectionalPathLossJitter = normal(0, bidirectionalSigma) / 2;
				}

				if (maxTxPower - PLd - bidirectionalPathLossJitter >= signalDeliveryThreshold) {
					pathLoss[i].push_front(new PathLossElement(j,PLd + bidirectionalPathLossJitter));
					totalElements++;	//keep track of pathLoss size for reporting purposes
				}

				if (maxTxPower - PLd + bidirectionalPathLossJitter >= signalDeliveryThreshold) {
					pathLoss[j].push_front(new PathLossElement(i,PLd - bidirectionalPathLossJitter));
					totalElements++;	//keep track of pathLoss size for reporting purposes
				}
			}else{					
                                objectcellZ1 = (int)(z1/zCellSize);
				objectcellY1 = (int)(y1/yCellSize);
				objectcellX1 = (int)(x1/xCellSize);

                                objectcellZ2 = (int)(z2/zCellSize);
				objectcellY2 = (int)(y2/yCellSize);
				objectcellX2 = (int)(x2/xCellSize);
		
				tempmax1 = max(abs(objectcellX2-objectcellX1),abs(objectcellY2-objectcellY1));
				tempmax = max(tempmax1,abs(objectcellZ2-objectcellZ1));			

				
				increX = (float)(objectcellX2-objectcellX1)/tempmax;
				increY = (float)(objectcellY2-objectcellY1)/tempmax;
				increZ = (float)(objectcellZ2-objectcellZ1)/tempmax;

				x = (float)objectcellX1;
				y = (float)objectcellY1;
				z = (float)objectcellZ1;
			        index = 0;
				objectsize = 0;
				while(index < tempmax){
					
					xx = int(x);
					yy = int(y);
					zz = int(z);
					if(objectmodel[xx][yy][zz] == 1)
						objectsize++;
					index++;
					x = x + increX;
					y = y + increY;
					z = z + increZ;
				}
                              	
				
				dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
				dist1 = (objectsize/tempmax)*dist;    //身体部分
				dist2 = dist - dist1;		//空气部分
			        PLd = 0;
/*
				if (dist < d0/10.0) {
					PLd = 0;
					bidirectionalPathLossJitter = 0;
				}else{ 
                                	if(dist1 != 0.0)
						PLd = PLd0 + 10.0 * pathLossExponent * log10(dist2 / d0) + normal(0, sigma);
					PLd = PLd + objectPLd0 + 10.0 * objectpathLossExponent * log10(dist1 / objectd0) + normal(0,sigma);	
					bidirectionalPathLossJitter = 0;//normal(0, bidirectionalSigma) / 2;
				}
				
				if (maxTxPower - PLd - bidirectionalPathLossJitter >= signalDeliveryThreshold) {
					pathLoss[i].push_front(new PathLossElement(j,PLd + bidirectionalPathLossJitter));
					totalElements++;	//keep track of pathLoss size for reporting purposes
				}

				if (maxTxPower - PLd + bidirectionalPathLossJitter >= signalDeliveryThreshold) {
					pathLoss[j].push_front(new PathLossElement(i,PLd - bidirectionalPathLossJitter));
					totalElements++;	//keep track of pathLoss size for reporting purposes
				}
*/
	                        
			}
		}
	}
	
	trace() << "Number of distinct space cells: " << numOfSpaceCells;
	trace() << "Each cell affects " <<
		(double)totalElements / numOfSpaceCells << " other cells on average";
	trace() << "The pathLoss array of lists was allocated in " <<
	    (double)(totalElements * elementSize) / 1048576 << " MBytes";
	// The larger this number, the slower your simulation. Consider increasing the cell size,
	// decreasing the field size, or if you only have static nodes, decreasing the number of nodes

	/*********************************************************************
	 * Allocate nodesAffectedByTransmitter even for static nodes.
	 * This makes the code more compact. We also have temporal variations
	 * so the nodes that are affected are not necessarily the same.
	 *********************************************************************/
	nodesAffectedByTransmitter = new list<int>[numOfNodes];
	if (nodesAffectedByTransmitter == NULL)
		opp_error("Could not allocate array nodesAffectedByTransmitter\n");

	/************************************************************
	 * If direct assignment of link qualities is given at the
	 * omnetpp.ini file we parse the input and update pathLoss.
	 * This is only for static nodes. (onlyStaticNodes==TRUE)
	 ************************************************************/
	parsePathLossMap();

	/* Create temporal model object from parameters file (if given) */
	if (strlen(temporalModelParametersFile) > 0) {
		temporalModel = new channelTemporalModel(temporalModelParametersFile, 2);
		temporalModelDefined = true;
	} else {
		temporalModelDefined = false;
	}
		
	declareHistogram("Fade depth distribution", -50, 15, 13);

	trace() << "Time for Wireless Channel module initialization: " <<
	    (double)(clock() - startTime) / CLOCKS_PER_SEC << "secs";		
	
        
    /*    for(int i = 0; i <= numOfXCells; i++)
		for(int j = 0 ; j <= numOfYCells; j++)
			for(int k = 0; k <= numOfZCells; k++)
			{
				trace()<<pathLoss[]
			}
  
	for (int i = 0; i < numOfSpaceCells; i++) {
		cout<<"节点"<<i<<"到各个点的路径损失"<<endl;
		list <PathLossElement *>::iterator j;
	        for(j = pathLoss[i].begin(); j != pathLoss[i].end(); j++)
			cout<<*j<<" ";
		cout<<endl;
	}*/


}

/*****************************************************************************
 * This is where the main work is done by processing all the messages received
 *****************************************************************************/
void WirelessChannel::handleMessage(cMessage * msg)
{
	switch (msg->getKind()) {

	case WC_NODE_MOVEMENT:{

			WirelessChannelNodeMoveMessage *mobilityMsg =
				check_and_cast <WirelessChannelNodeMoveMessage*>(msg);
			int srcAddr = mobilityMsg->getNodeID();

	    /*****************************************************
	     * A node notified the wireless channel that it moved
	     * to a new space cell. Update the nodeLocation and
	     * based on the new cell calculation decide if the
	     * cellOccupation array needs to be updated.
	     *****************************************************/

			if (onlyStaticNodes)
				opp_error("Error: Rerceived WS_NODE_MOVEMENT msg, while onlyStaticNodes is TRUE");

			int oldCell = nodeLocation[srcAddr].cell;
			nodeLocation[srcAddr].x = mobilityMsg->getX();
			nodeLocation[srcAddr].y = mobilityMsg->getY();
			nodeLocation[srcAddr].z = mobilityMsg->getZ();
			nodeLocation[srcAddr].phi = mobilityMsg->getPhi();
			nodeLocation[srcAddr].theta = mobilityMsg->getTheta();
			nodeLocation[srcAddr].gamma = mobilityMsg->getGamma();
			if ((nodeLocation[srcAddr].x < 0.0) ||
				(nodeLocation[srcAddr].y < 0.0) ||
				(nodeLocation[srcAddr].z < 0.0))
					opp_error("Wireless channel received faulty WC_NODE_MOVEMENT msg. We cannot have negative node coordinates");

			int xIndex = (int)floor(nodeLocation[srcAddr].x / xFieldSize * numOfXCells);
			if (((xIndex - 1) * xCellSize) >= nodeLocation[srcAddr].x)
				xIndex--;
			else if (xIndex >= numOfXCells) {
				xIndex = numOfXCells - 1;	// the maximum possible x index
				if (nodeLocation[srcAddr].x > xFieldSize)
					debug() << "WARNING at WC_NODE_MOVEMENT: node position out of bounds in X dimension!\n";
			}

			int yIndex = (int)floor(nodeLocation[srcAddr].y / yFieldSize * numOfYCells);
			if (((yIndex - 1) * yCellSize) >= nodeLocation[srcAddr].y)
				yIndex--;
			else if (yIndex >= numOfYCells) {
				yIndex = numOfYCells - 1;	// the maximum possible y index
				if (nodeLocation[srcAddr].y > yFieldSize)
					debug() << "WARNING at WC_NODE_MOVEMENT: node position out of bounds in Y dimension!\n";
			}

			int zIndex = (int)floor(nodeLocation[srcAddr].z / zFieldSize * numOfZCells);
			if (((zIndex - 1) * zCellSize) >= nodeLocation[srcAddr].z)
				zIndex--;
			else if (zIndex >= numOfZCells) {
				zIndex = numOfZCells - 1;	// the maximum possible z index
				if (nodeLocation[srcAddr].z > zFieldSize)
					debug() << "WARNING at WC_NODE_MOVEMENT: node position out of bounds in Z dimension!\n";
			}

			int newCell = zIndex * zIndexIncrement + yIndex * yIndexIncrement + xIndex * xIndexIncrement;
			if (newCell != oldCell) {
				cellOccupation[oldCell].remove(srcAddr);
				cellOccupation[newCell].push_front(srcAddr);
				nodeLocation[srcAddr].cell = newCell;
			}

			break;
		}

	case WC_SIGNAL_START:{

			WirelessChannelSignalBegin *signalMsg =
			    check_and_cast <WirelessChannelSignalBegin*>(msg);
			int srcAddr = signalMsg->getNodeID();
			int receptioncount = 0;

			/* Find the cell that the transmitting node resides */
			int cellTx = nodeLocation[srcAddr].cell;

			/* Iterate through the list of cells that are affected
			 * by cellTx and check if there are nodes there.
			 * Update the nodesAffectedByTransmitter array
			 */
			list < PathLossElement * >::iterator it1;
			for (it1 = pathLoss[cellTx].begin(); it1 != pathLoss[cellTx].end(); it1++) {
				/* If no nodes exist in this cell, move on. */
				if (cellOccupation[(*it1)->cellID].empty())
					continue;

				/* Otherwise there are some nodes in that cell.
				 * Calculate the signal received by these nodes
				 * It is exactly the same for all of them.
				 * The signal may be variable in time.
				 */
				float currentSignalReceived = signalMsg->getPower_dBm() - (*it1)->avgPathLoss;
				if (temporalModelDefined) {
					simtime_t timePassed_msec = (simTime() - (*it1)->lastObservationTime) * 1000;
					simtime_t timeProcessed_msec =
							temporalModel->runTemporalModel(SIMTIME_DBL(timePassed_msec),
							&((*it1)->lastObservedDiffFromAvgPathLoss));
					currentSignalReceived += (*it1)->lastObservedDiffFromAvgPathLoss;
					collectHistogram("Fade depth distribution",
						     (*it1)->lastObservedDiffFromAvgPathLoss);
					/* Update the observation time */
					(*it1)->lastObservationTime = simTime() -
							(timePassed_msec - timeProcessed_msec) / 1000;
				}

				/* If the resulting current signal received is not strong enough,
				 * to be delivered to the radio module, continue to the next cell.
				 */
				if (currentSignalReceived < signalDeliveryThreshold)
					continue;

				/* Else go through all the nodes of that cell.
				 * Iterator it2 returns node IDs.
				 */
				list < int >::iterator it2;
				for (it2 = cellOccupation[(*it1)->cellID].begin();
						it2 != cellOccupation[(*it1)->cellID].end(); it2++) {
					if (*it2 == srcAddr)
						continue;
					receptioncount++;
					WirelessChannelSignalBegin *signalMsgCopy = signalMsg->dup();
					signalMsgCopy->setPower_dBm(currentSignalReceived);
					send(signalMsgCopy, "toNode", *it2);
					nodesAffectedByTransmitter[srcAddr].push_front(*it2);
				}	//for it2
			}	//for it1

			if (receptioncount > 0)
				trace() << "signal from node[" << srcAddr << "] reached " <<
						receptioncount << " other nodes";
			break;
		}

	case WC_SIGNAL_END:{
			WirelessChannelSignalEnd *signalMsg =
			    check_and_cast <WirelessChannelSignalEnd*>(msg);
			int srcAddr = signalMsg->getNodeID();

			/* Go through the list of nodes that were affected
			 *  by this transmission. *it1 holds the node ID
			 */
			list <int>::iterator it1;
			for (it1 = nodesAffectedByTransmitter[srcAddr].begin();
					it1 != nodesAffectedByTransmitter[srcAddr].end(); it1++) {
				WirelessChannelSignalEnd *signalMsgCopy = signalMsg->dup();
				send(signalMsgCopy, "toNode", *it1);
			}	//for it1

			/* Now that we are done processing the msg we delete the whole list
			 * nodesAffectedByTransmitter[srcAddr], since srcAddr in not TXing anymore.
			 */
			nodesAffectedByTransmitter[srcAddr].clear();
			break;
		}

	default:{
			opp_error("ERROR: Wireless Channel received unknown message kind=%i", msg->getKind());
			break;
		}
	}
	delete msg;
}

void WirelessChannel::finishSpecific()
{

	/*****************************************************
	 * Delete dynamically allocated arrays. Some allocate
	 * lists of objects so they need an extra nested loop
	 * to properly deallocate all these objects
	 *****************************************************/

	/* delete pathLoss */
	for (int i = 0; i < numOfSpaceCells; i++) {
		list <PathLossElement*>::iterator it1;
		for (it1 = pathLoss[i].begin(); it1 != pathLoss[i].end(); it1++) {
			delete(*it1);	// deallocate the memory occupied by the object
		}
	}
	delete[]pathLoss;	// the delete[] operator releases memory allocated with new []

	/* delete nodesAffectedByTransmitter */
	delete[]nodesAffectedByTransmitter;	// the delete[] operator releases memory allocated with new []

	/* delete cellOccupation */
	delete[]cellOccupation;	// the delete[] operator releases memory allocated with new []

	/* delete nodeLocation */
	delete[]nodeLocation;

	if (temporalModelDefined)
		delete temporalModel;

	//close the output stream that CASTALIA_DEBUG is writing to
	DebugInfoWriter::closeStream();
}

void WirelessChannel::readIniFileParameters(void)
{
	DebugInfoWriter::setDebugFileName(
		getParentModule()->par("debugInfoFileName").stringValue());

	onlyStaticNodes = par("onlyStaticNodes");
	pathLossExponent = par("pathLossExponent");
	sigma = par("sigma");
	bidirectionalSigma = par("bidirectionalSigma");
	PLd0 = par("PLd0");
	d0 = par("d0");

	pathLossMapFile = par("pathLossMapFile");
	temporalModelParametersFile = par("temporalModelParametersFile");
	signalDeliveryThreshold = par("signalDeliveryThreshold");

	numOfNodes = getParentModule()->par("numNodes");
	xFieldSize = getParentModule()->par("field_x");
	yFieldSize = getParentModule()->par("field_y");
	zFieldSize = getParentModule()->par("field_z");
	xCellSize = par("xCellSize");
	yCellSize = par("yCellSize");
	zCellSize = par("zCellSize");

	maxTxPower = 0.0;
        hasobjectmodel = par("hasobjectmodel");
        objectStyle = par("objectStyle");
	objectStyleID = par("objectStyleID");
}				// readIniParameters

/* Parsing of custom pathloss map from a file,
 * filename given by the parameter pathLossMapFile
 */
void WirelessChannel::parsePathLossMap(void)
{
	if (strlen(pathLossMapFile) == 0)
		return;
	ifstream f(pathLossMapFile);
	if (!f.is_open())
		opp_error("\n[Wireless Channel]:\n Error reading from pathLossMapFile %s\n", pathLossMapFile);

	string s;
	const char *ct;
	int source, destination;
	float pathloss_db;

	/* each line in a file is in the same format:
	 * Transmitter_id>Receiver_id:PathLoss_dB, ... ,Receiver_id:PathLoss_dB
	 * based on these values we will update the pathloss array
	 * (using updatePathLossElement function)
	 */
	while (getline(f, s)) {
		ct = s.c_str();	//ct points to the beginning of a line
		while (ct[0] && (ct[0] == ' ' || ct[0] == '\t'))
			ct++;
		if (!ct[0] || ct[0] == '#')
			continue;	// skip comments
		if (parseInt(ct, &source))
			opp_error("\n[Wireless Channel]:\n Bad syntax in pathLossMapFile, expecting source identifier\n");
		while (ct[0] && ct[0] != '>')
			ct++;	//skip untill '>' character
		if (!ct[0])
			opp_error("\n[Wireless Channel]:\n Bad syntax in pathLossMapFile, expecting comma separated list of values\n");
		cStringTokenizer t(++ct, ",");	//divide the rest of the strig with comma delimiter
		while ((ct = t.nextToken())) {
			if (parseInt(ct, &destination))
				opp_error("\n[Wireless Channel]:\n Bad syntax in pathLossMapFile, expecting target identifier\n");
			while (ct[0] && ct[0] != ':')
				ct++;	//skip untill ':' character
			if (parseFloat(++ct, &pathloss_db))
				opp_error("\n[Wireless Channel]:\n Bad syntax in pathLossMapFile, expecting dB value for path loss\n");
			updatePathLossElement(source, destination, pathloss_db);
		}
	}
}

//This function will update a pathloss element for given source and destination cells with a given value of pathloss
//If this pair is already defined in pathloss array, the old value is replaced, otherwise a new pathloss element is created
void WirelessChannel::updatePathLossElement(int src, int dst, float pathloss_db)
{
	if (src >= numOfSpaceCells || dst >= numOfSpaceCells) return;
	list <PathLossElement*>::iterator it1;
	for (it1 = pathLoss[src].begin(); it1 != pathLoss[src].end(); it1++) {
		if ((*it1)->cellID == dst) {
			(*it1)->avgPathLoss = pathloss_db;
			return;
		}
	}
	pathLoss[src].push_front(new PathLossElement(dst, pathloss_db));
}

//wrapper function for atoi(...) call. returns 1 on error, 0 on success
int WirelessChannel::parseInt(const char *c, int *dst)
{
	while (c[0] && (c[0] == ' ' || c[0] == '\t'))
		c++;
	if (!c[0] || c[0] < '0' || c[0] > '9')
		return 1;
	*dst = atoi(c);
	return 0;
}

//wrapper function for strtof(...) call. returns 1 on error, 0 on success
int WirelessChannel::parseFloat(const char *c, float *dst)
{
	char *tmp;
	*dst = strtof(c, &tmp);
	if (c == tmp)
		return 1;
	return 0;
}
void WirelessChannel::handleObjectModel(void)
{
	cXMLElement* xmlObject = par("objectFile").xmlValue();
	if (xmlObject == 0)
		opp_error("\n[Wireless Channel]:\n there is no such objectfile\n");
        const char* str;
        
        cXMLElementList locations;
         
        locations = xmlObject->getElementsByTagName("location");
	int numOfObject;
        numOfObject = locations.size();
        if(numOfObject == 0)
       		opp_error("\n[Wireless Channel]:\n there are no object parameters\n");
	cXMLElementList::const_iterator location;
        unsigned int locationID;
        for (location = locations.begin(); location != locations.end(); location++){
		str = (*location)->getAttribute("ID");
		locationID = strtol(str,0,0);
		str = (*location)->getAttribute("name");		
		if(strcmp(objectStyle,str) == 0 && objectStyleID == locationID)
			break;
	}
	if(location == locations.end())
		opp_error("\n[Wireless Channel]:\n there are no such object\n");

	str = (*location)->getAttribute("numvertex");
	int numOfVertex;
	numOfVertex = strtol(str,0,0);
	
	str = (*location)->getAttribute("objectpathLossExponent");
	objectpathLossExponent = strtod(str,0);
	
	str = (*location)->getAttribute("objectPLd0");
	objectPLd0 = strtod(str,0);

	str = (*location)->getAttribute("objectd0");
	objectd0 = strtod(str,0);

	NodeLocation_type *objectVertex;
	objectVertex = new NodeLocation_type[numOfVertex];
	
	cXMLElementList vertexParameters;	
	vertexParameters = (*location)->getElementsByTagName("vertexParameters");
	if (vertexParameters.size() != numOfVertex)
		opp_error ("Some vertexs may not have specified parameter in input specification file.");
	int i = 0;
	cXMLElementList::const_iterator param;
	for(param = vertexParameters.begin(); param !=vertexParameters.end(); param++){

		str = (*param)->getAttribute("positionX");
		objectVertex[i].x = strtod(str,0);
		
		str = (*param)->getAttribute("positionY");
		objectVertex[i].y = strtod(str,0);

		str = (*param)->getAttribute("positionZ");
		objectVertex[i].z = strtod(str,0);

		int xIndex = (int)floor(objectVertex[i].x / xFieldSize * numOfXCells);
		if (((xIndex - 1) * xCellSize) >= objectVertex[i].x)
			xIndex--;
		else if (xIndex >= numOfXCells) {
			xIndex = numOfXCells - 1;	// the maximum possible x index
			if (objectVertex[i].x > xFieldSize)
				debug() << "WARNING at objectvertex: vertex position out of bounds in X dimension!\n";
		}

		int yIndex = (int)floor(objectVertex[i].y / yFieldSize * numOfYCells);
		if (((yIndex - 1) * yCellSize) >= objectVertex[i].y)
			yIndex--;
		else if (yIndex >= numOfYCells) {
			yIndex = numOfYCells - 1;	// the maximum possible y index
			if (objectVertex[i].y > yFieldSize)
				debug() << "WARNING at objectvertex: vertex position out of bounds in Y dimension!\n";
		}

		int zIndex = (int)floor(objectVertex[i].z / zFieldSize * numOfZCells);
		if (((zIndex - 1) * zCellSize) >= objectVertex[i].z)
			zIndex--;
		else if (zIndex >= numOfZCells) {
			zIndex = numOfZCells - 1;	// the maximum possible z index
			if (objectVertex[i].z > zFieldSize)
				debug() << "WARNING at objectvertex: vertex position out of bounds in Z dimension!\n";
		}		

		objectVertex[i].x = xIndex;
		objectVertex[i].y = yIndex;
		objectVertex[i].z = zIndex;
		i++;
	}

	//---------------------------handle with your own module----------------------------
		
        for(int i = objectVertex[0].z ; i<= objectVertex[4].z ; i++)
		for(int j = objectVertex[0].y ; j <= objectVertex[3].y ; j++)
			for(int k = objectVertex[0].x ; k <= objectVertex[1].x ; k++)
				objectmodel[k][j][i] = 1; 
	
	/*for(int i = 0; i< numOfXCells;i++){
		trace()<<"第"<<i<<"x行";
		for(int j = 0; j<numOfYCells;j++){
			trace()<<"第"<<j<<"y行";
			for(int k = 0; k<numOfZCells; k++){
				trace()<<k<<"z行"<<objectmodel[i][j][k]<<" ";
			}
		}
	} */   
}













