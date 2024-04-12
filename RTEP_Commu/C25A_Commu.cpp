#include <iostream>
#include <chrono>
#include <thread>
#include <cstring> 
#include "ADS1115_Wrapper.h"
#include "IPC.h"

// Define Message
struct Message 
{
    int ret0;
    double ret_v0;
    int ret1;
    double ret_v1;
};


int main() 
{
    // Wrapper
    ADS1115_Wrapper ads;

    // Initialization ADS
    if (!ads.init(1)) 
    {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    // Access Queue
    int msgid = getOrCreateMessageQueue("/tmp", 'B'); // Mark B
    if (msgid == -1) 
    {
        std::cerr << "Failed to create or access message queue." << std::endl;
        return -1;
    }

    while (true) 
    {
        // Process
        ads.Process(ret0, ret_v0, ret1, ret_v1);
        
        // Perpare Message
        Message message;
        message.accelX_g = accelX_g;
        message.accelY_g = accelY_g;
        message.accelZ_g = accelZ_g;
        message.gyroX_degPerSec = gyroX_degPerSec;
        message.gyroY_degPerSec = gyroY_degPerSec;
        message.gyroZ_degPerSec = gyroZ_degPerSec;

        // Send
        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) 
        {
            std::cerr << "Failed to send message to message queue." << std::endl;
            return -1;
        }

        // Display
        std::cout << "Message sent to message queue." << std::endl;
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl;
        
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ads.stop();

    return 0;
}
