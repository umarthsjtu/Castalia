//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/application/valueReporting/ValueReportingPacket.msg.
//

#ifndef _VALUEREPORTINGPACKET_M_H_
#define _VALUEREPORTINGPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "ApplicationPacket_m.h"
// }}



/**
 * Struct generated from src/node/application/valueReporting/ValueReportingPacket.msg by opp_msgc.
 */
struct ValueReportData
{
    ValueReportData();
    unsigned short nodeID;
    double locX;
    double locY;
};

void doPacking(cCommBuffer *b, ValueReportData& a);
void doUnpacking(cCommBuffer *b, ValueReportData& a);

/**
 * Class generated from <tt>src/node/application/valueReporting/ValueReportingPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet ValueReportingDataPacket extends ApplicationPacket {
 * 	ValueReportData extraData;
 * }
 * </pre>
 */
class ValueReportingDataPacket : public ::ApplicationPacket
{
  protected:
    ValueReportData extraData_var;

  private:
    void copy(const ValueReportingDataPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ValueReportingDataPacket&);

  public:
    ValueReportingDataPacket(const char *name=NULL, int kind=0);
    ValueReportingDataPacket(const ValueReportingDataPacket& other);
    virtual ~ValueReportingDataPacket();
    ValueReportingDataPacket& operator=(const ValueReportingDataPacket& other);
    virtual ValueReportingDataPacket *dup() const {return new ValueReportingDataPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual ValueReportData& getExtraData();
    virtual const ValueReportData& getExtraData() const {return const_cast<ValueReportingDataPacket*>(this)->getExtraData();}
    virtual void setExtraData(const ValueReportData& extraData);
};

inline void doPacking(cCommBuffer *b, ValueReportingDataPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ValueReportingDataPacket& obj) {obj.parsimUnpack(b);}


#endif // _VALUEREPORTINGPACKET_M_H_
