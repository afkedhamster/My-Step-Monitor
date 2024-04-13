// Receive

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

    // Perpare Buffer
    Message message;
    memset(&message, 0, sizeof(message)); // Clear

    // Receive
    if (msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, 0) == -1) 
    {
        std::cerr << "Failed to receive message from message queue." << std::endl;
        return -1;
    }

    std::cout << "Received message from message queue." << std::endl;
    std::cout << "Data: " << message.data << std::endl;

    return 0;
}
