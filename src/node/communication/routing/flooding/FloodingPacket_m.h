//
// Generated file, do not edit! Created by opp_msgc 4.2 from FloodingPacket.msg.
//

#ifndef _FLOODINGPACKET_M_H_
#define _FLOODINGPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "RoutingPacket_m.h"
// }}



/**
 * Class generated from <tt>FloodingPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet FloodingPacket extends RoutingPacket {
 * 	int numhop;
 * 	string source;
 * 	string destination;
 * }
 * </pre>
 */
class FloodingPacket : public ::RoutingPacket
{
  protected:
    int numhop_var;
    opp_string source_var;
    opp_string destination_var;

  private:
    void copy(const FloodingPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FloodingPacket&);

  public:
    FloodingPacket(const char *name=NULL, int kind=0);
    FloodingPacket(const FloodingPacket& other);
    virtual ~FloodingPacket();
    FloodingPacket& operator=(const FloodingPacket& other);
    virtual FloodingPacket *dup() const {return new FloodingPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNumhop() const;
    virtual void setNumhop(int numhop);
    virtual const char * getSource() const;
    virtual void setSource(const char * source);
    virtual const char * getDestination() const;
    virtual void setDestination(const char * destination);
};

inline void doPacking(cCommBuffer *b, FloodingPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, FloodingPacket& obj) {obj.parsimUnpack(b);}


#endif // _FLOODINGPACKET_M_H_
