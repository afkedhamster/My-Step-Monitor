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
    int size = 0;
    const void* dataPtr = nullptr;
    // Judge Tpye
    if (message.data.index() == 0) // Float
    {
        const auto& values = std::get<std::vector<float>>(message.data);
        size = values.size() * sizeof(float);
        dataPtr = static_cast<const void*>(values.data());
    }
    else if (message.data.index() == 1) // Char
    {
        const auto& str = std::get<std::string>(message.data);
        size = str.size() + 1; 
        dataPtr = static_cast<const void*>(str.c_str());
    }
    // Send
    if (msgsnd(msgid, dataPtr, size, IPC_NOWAIT) == -1)
    {
        return false;
    }
    return true;
}

// Receive
bool IPC::receive(Message& message)
{   
    // Receive
    ssize_t receivedSize = msgrcv(msgid, message.dataPtr(), message.maxSize(), 0, 0);
    if (receivedSize == -1)
    {
        return false;
    }
    // Judge type
    if (message.data.index() == 0) // Float
    {
        if (static_cast<size_t>(receivedSize) != message.values.size() * sizeof(float))
        {
            return false;
        }
    }
    else if (message.data.index() == 1) // Char
    {
        if (static_cast<size_t>(receivedSize) > message.maxSize())
        {
            return false; 
        }
        // Null Character
        std::get<std::string>(message.data).resize(receivedSize);
        std::get<std::string>(message.data)[receivedSize - 1] = '\0';
    }

    return true;
}