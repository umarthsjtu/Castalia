//
// Generated file, do not edit! Created by opp_msgc 4.2 from FloodingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "FloodingPacket_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(FloodingPacket);

FloodingPacket::FloodingPacket(const char *name, int kind) : RoutingPacket(name,kind)
{
    this->numhop_var = 0;
    this->source_var = 0;
    this->destination_var = 0;
}

FloodingPacket::FloodingPacket(const FloodingPacket& other) : RoutingPacket(other)
{
    copy(other);
}

FloodingPacket::~FloodingPacket()
{
}

FloodingPacket& FloodingPacket::operator=(const FloodingPacket& other)
{
    if (this==&other) return *this;
    RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void FloodingPacket::copy(const FloodingPacket& other)
{
    this->numhop_var = other.numhop_var;
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
}

void FloodingPacket::parsimPack(cCommBuffer *b)
{
    RoutingPacket::parsimPack(b);
    doPacking(b,this->numhop_var);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
}

void FloodingPacket::parsimUnpack(cCommBuffer *b)
{
    RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->numhop_var);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
}

int FloodingPacket::getNumhop() const
{
    return numhop_var;
}

void FloodingPacket::setNumhop(int numhop)
{
    this->numhop_var = numhop;
}

const char * FloodingPacket::getSource() const
{
    return source_var.c_str();
}

void FloodingPacket::setSource(const char * source)
{
    this->source_var = source;
}

const char * FloodingPacket::getDestination() const
{
    return destination_var.c_str();
}

void FloodingPacket::setDestination(const char * destination)
{
    this->destination_var = destination;
}

class FloodingPacketDescriptor : public cClassDescriptor
{
  public:
    FloodingPacketDescriptor();
    virtual ~FloodingPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FloodingPacketDescriptor);

FloodingPacketDescriptor::FloodingPacketDescriptor() : cClassDescriptor("FloodingPacket", "RoutingPacket")
{
}

FloodingPacketDescriptor::~FloodingPacketDescriptor()
{
}

bool FloodingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FloodingPacket *>(obj)!=NULL;
}

const char *FloodingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FloodingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int FloodingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *FloodingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "numhop",
        "source",
        "destination",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int FloodingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numhop")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FloodingPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *FloodingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FloodingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FloodingPacket *pp = (FloodingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FloodingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FloodingPacket *pp = (FloodingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNumhop());
        case 1: return oppstring2string(pp->getSource());
        case 2: return oppstring2string(pp->getDestination());
        default: return "";
    }
}

bool FloodingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FloodingPacket *pp = (FloodingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumhop(string2long(value)); return true;
        case 1: pp->setSource((value)); return true;
        case 2: pp->setDestination((value)); return true;
        default: return false;
    }
}

const char *FloodingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *FloodingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FloodingPacket *pp = (FloodingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


