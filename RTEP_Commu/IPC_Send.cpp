// Send

#include "IPC.h"
#include <cstring> 

// Define Message
struct Message 
{
    long mtype; // Positive Integer
    double data; // Floating-Point Number
};

int main() 
{
    // Access Queue
    int msgid = getOrCreateMessageQueue("/tmp", 'A');
    if (msgid == -1) 
    {
        std::cerr << "Failed to create or access message queue." << std::endl;
        return -1;
    }

    // Perpare Message
    Message message;
    message.mtype = 1; // Change
    message.data = 1.0; // Change

    // Convert Floating-Point
    char buffer[sizeof(double)];
    memcpy(buffer, &message.data, sizeof(double));

    // Send
    if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) 
    {
        std::cerr << "Failed to send message to message queue." << std::endl;
        return -1;
    }

    std::cout << "Message sent to message queue." << std::endl;

    return 0;
}
