package routingControl;

simple RoutingControl {
    parameters:
        int i = default(0);
	bool collectTraceInfo = default (false);
    gates:
        output toNode[];
	input fromNode @ directIn;

}
