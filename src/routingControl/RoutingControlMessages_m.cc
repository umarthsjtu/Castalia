//
// Generated file, do not edit! Created by opp_msgc 4.2 from RoutingControlMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RoutingControlMessages_m.h"

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




Register_Class(routingcontrolmessage);

routingcontrolmessage::routingcontrolmessage(const char *name, int kind) : cMessage(name,kind)
{
    this->a_var = 0;
    this->b_var = 0;
    this->c_var = 0;
}

routingcontrolmessage::routingcontrolmessage(const routingcontrolmessage& other) : cMessage(other)
{
    copy(other);
}

routingcontrolmessage::~routingcontrolmessage()
{
}

routingcontrolmessage& routingcontrolmessage::operator=(const routingcontrolmessage& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void routingcontrolmessage::copy(const routingcontrolmessage& other)
{
    this->a_var = other.a_var;
    this->b_var = other.b_var;
    this->c_var = other.c_var;
    this->neighbor_var = other.neighbor_var;
}

void routingcontrolmessage::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->a_var);
    doPacking(b,this->b_var);
    doPacking(b,this->c_var);
    doPacking(b,this->neighbor_var);
}

void routingcontrolmessage::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->a_var);
    doUnpacking(b,this->b_var);
    doUnpacking(b,this->c_var);
    doUnpacking(b,this->neighbor_var);
}

double routingcontrolmessage::getA() const
{
    return a_var;
}

void routingcontrolmessage::setA(double a)
{
    this->a_var = a;
}

double routingcontrolmessage::getB() const
{
    return b_var;
}

void routingcontrolmessage::setB(double b)
{
    this->b_var = b;
}

double routingcontrolmessage::getC() const
{
    return c_var;
}

void routingcontrolmessage::setC(double c)
{
    this->c_var = c;
}

IntList& routingcontrolmessage::getNeighbor()
{
    return neighbor_var;
}

void routingcontrolmessage::setNeighbor(const IntList& neighbor)
{
    this->neighbor_var = neighbor;
}

class routingcontrolmessageDescriptor : public cClassDescriptor
{
  public:
    routingcontrolmessageDescriptor();
    virtual ~routingcontrolmessageDescriptor();

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

Register_ClassDescriptor(routingcontrolmessageDescriptor);

routingcontrolmessageDescriptor::routingcontrolmessageDescriptor() : cClassDescriptor("routingcontrolmessage", "cMessage")
{
}

routingcontrolmessageDescriptor::~routingcontrolmessageDescriptor()
{
}

bool routingcontrolmessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<routingcontrolmessage *>(obj)!=NULL;
}

const char *routingcontrolmessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int routingcontrolmessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int routingcontrolmessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *routingcontrolmessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "a",
        "b",
        "c",
        "neighbor",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int routingcontrolmessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "a")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "b")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "c")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "neighbor")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *routingcontrolmessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "IntList",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *routingcontrolmessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int routingcontrolmessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    routingcontrolmessage *pp = (routingcontrolmessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string routingcontrolmessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    routingcontrolmessage *pp = (routingcontrolmessage *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getA());
        case 1: return double2string(pp->getB());
        case 2: return double2string(pp->getC());
        case 3: {std::stringstream out; out << pp->getNeighbor(); return out.str();}
        default: return "";
    }
}

bool routingcontrolmessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    routingcontrolmessage *pp = (routingcontrolmessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setA(string2double(value)); return true;
        case 1: pp->setB(string2double(value)); return true;
        case 2: pp->setC(string2double(value)); return true;
        default: return false;
    }
}

const char *routingcontrolmessageDescriptor::getFieldStructName(void *object, int field) const
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
        "IntList",
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *routingcontrolmessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    routingcontrolmessage *pp = (routingcontrolmessage *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getNeighbor()); break;
        default: return NULL;
    }
}


