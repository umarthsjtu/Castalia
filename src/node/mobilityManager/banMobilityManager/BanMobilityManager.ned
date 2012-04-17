
package node.mobilityManager.banMobilityManager;

simple BanMobilityManager like node.mobilityManager.iMobilityManager {
 parameters:
	bool collectTraceInfo = default (false);
	double updateInterval = default (1000);
    xml nodesSpecFile;    // The input file that includes the specification of all postures
}
