// IPC.h
#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>

// Define Message
struct Message 
{
    char type; // Pos
    std::vector<float> values; // Value

    Message(char t, size_t i) : type(t)
    {
        values.resize(i);
    }
};

Message createMessage(int type, const std::vector<float>& data);


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