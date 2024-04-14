#include <stdexcept>
#include "IPC.h"

// Define Message
Message createMessage(int type, const std::vector<float>& data)
{
    Message msg(type, data.size());
    msg.values = data;
    return msg;
};

// Constructor
IPC::IPC(const char* filepath, int proj_id) 
{
    // Mark
    if (!MsgID(filepath, proj_id)) 
    {
        throw std::runtime_error("Failed to set message queue identifier.");
    }
}

// Deconstructor
IPC::~IPC()
{
    // Remove
    msgctl(msgid, IPC_RMID, NULL);
}

// Mark
bool IPC::MsgID(const char* filepath, int proj_id) 
{
    // Key
    key_t key = ftok(filepath, proj_id);
    if (key == -1) 
    {
        return false;
    }
    // Create or access Queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) 
    {
        return false;
    }
    return true;
}

// Send
bool IPC::send(const Message& message)
{
    //convert
    const void* Poi = static_cast<const void*>(message.values.data());
    if (msgsnd(msgid, Poi, message.values.size()*sizeof(float),IPC_NOWAIT) == -1)
    {
        return false;
    }
    return true;
}

// Receive
bool IPC::receive(Message& message)
{   
    if (msgrcv(msgid, message.values.data(), message.values.size() * sizeof(float), 0, 0) == -1)
    {
        return false;
    }
    return true;
}
