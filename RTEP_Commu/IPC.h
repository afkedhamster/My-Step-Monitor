// IPC.h
#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include <string>
#include <variant>

// Define Message
struct Message 
{
    char type;
    
    enum class DataType
    {
        Float,
        String 
    } dataType;
    
    union Data
    {
        std::vector<float> floatN;
        std::string strN;
        
        Data() {}
        ~Data() {}
    } data;
};

Message createFloatMessage(char type, const std::vector<float>& data);
Message createStringMessage(char type, const std::string& data);

// Message Queue
class IPC
{
private:
    int msgid;

public:
    IPC(const char* filepath, int proj_id);
    ~IPC();
    bool MsgID(const char* filepath, int proj_id); 
    bool send(const Message& message);
    bool receive(Message& message);
};

#endif