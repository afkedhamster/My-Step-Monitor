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
    };    
        // Constructor
        Data(const Data& other) 
        {
            switch (other.dataType) 
            {
                case DataType::Float:
                    new (&floatN) std::vector<float>(other.floatN);
                    break;
                case DataType::String:
                    new (&strN) std::string(other.strN);
                    break;
            }
        }
        
        // Destructor
        ~Data() 
        {
            switch (dataType) 
            {
                case DataType::Float:
                    floatN.~vector<float>();
                    break;
                case DataType::String:
                    strN.~basic_string<char>();
                    break;
            }
        }
    } data;
    
    // Copy Constructor
    Message(const Message& other) : type(other.type), dataType(other.dataType), data(other.data) {}
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