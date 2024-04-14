#include <stdexcept>
#include <cstring>
#include "IPC.h"

// Define Message
Message::Message(char t, const std::variant<std::vector<float>, std::string>& d) : type(t), data(d) {}

Message createMessage(char type, const std::variant<std::vector<float>, std::string>& data)
{
    return Message(type, data);
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
// Send
bool IPC::send(const Message& message)
{
    // Judge Type
    std::visit([&](const auto& arg) 
    {
        if constexpr (std::is_same_v<decltype(arg), std::vector<float>>)
        {
            const std::vector<float>& values = arg;
            size = values.size() * sizeof(float);
            dataPtr = static_cast<const void*>(values.data());
            if (msgsnd(msgid, dataPtr, size, IPC_NOWAIT) == -1) 
            {
                return false;
            }
        } 
        else if constexpr (std::is_same_v<decltype(arg), std::string>)
        {
            const std::string& str = arg;
            size = str.size() + 1;
            dataPtr = static_cast<const void*>(str.c_str());
            if (msgsnd(msgid, dataPtr, size, IPC_NOWAIT) == -1) 
            {
                return false;
            }
        }
        return true;
    }, 
    message.data);

    return true;
}

// Receive
bool IPC::receive(Message& message)
{   
    // Receive
    ssize_t receivedSize = msgrcv(msgid, &message, sizeof(message), 0, 0);
    if (receivedSize == -1)
    {
    return false;
    }

    // Judge Type
    std::visit([&](auto& arg) 
    {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::vector<float>>) 
        {
            std::vector<float> values(std::get<std::vector<float>>(message.data).size());
            std::memcpy(values.data(), std::get<std::vector<float>>(message.data).data(), receivedSize);
            arg = std::move(values);
        } 
        else if constexpr (std::is_same_v<T, std::string>) 
        {
            arg = std::get<std::string>(message.data);
        }
    }, 
    message.data);

    return true;
}