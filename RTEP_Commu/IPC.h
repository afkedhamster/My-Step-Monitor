#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>

// Define Message
struct Message 
{
    std::vector<float> data;
    // i Messages
    Message(int i) 
    {
        data.resize(i);
    }
};

Message createMessage(const std::vector<float>& data);

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
