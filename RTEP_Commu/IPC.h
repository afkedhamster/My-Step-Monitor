#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>

// Define Message
struct Message 
{
    std::vector<float> DataResult;

    Message() {}
    
    // i Messages
    Message(int i) 
    {
        DataResult.resize(i);
    }
};

Message createMessage(const std::vector<float>& DataResult);

// Message Queue
class IPC
{
private:
    int msgid;

public:
    IPC() : msgid(-1){}
    
    IPC(const char* filepath, char proj_id);
    ~IPC();
    bool MsgID(const char* filepath, char proj_id); 
    bool send(const Message& message);
    bool receive(Message& message);
};

#endif
