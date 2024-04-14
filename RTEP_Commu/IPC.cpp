#include <stdexcept>
#include <cstring>
#include "IPC.h"

// Define Message
Message createFloatMessage(char type, const std::vector<float>& data)
{
    Message msg;
    msg.type = type;
    msg.dataType = Message::DataType::Float;
    msg.data.floatN = data;
    return msg;
}

Message createStringMessage(char type, const std::string& data)
{
    Message msg;
    msg.type = type;
    msg.dataType = Message::DataType::String;
    msg.data.strN = data;
    return msg;
}

// Constructor
IPC::IPC(const char* filepath, int proj_id) : msgid(-1) 
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
    if (msgid != -1)
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
    size_t size = sizeof(message);
    const void* dataPtr = static_cast<const void*>(&message);
    if (msgsnd(msgid, dataPtr, size, IPC_NOWAIT) == -1) 
    {
        return false;
    }
    return true;
}

// Receive
bool IPC::receive(Message& message)
{
    ssize_t receivedSize = msgrcv(msgid, &message, sizeof(message.data), 0, 0);
    if (receivedSize == -1)
    {
        return false;
    }
    return true;
}