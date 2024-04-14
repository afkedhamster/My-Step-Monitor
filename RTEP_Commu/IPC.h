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
    char type; // Pos
    std::variant<std::vector<float>, std::string> data; // Value

    Message(char t, size_t i);
};

Message createMessage(char type, const std::variant<std::vector<float>, std::string>& data);


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