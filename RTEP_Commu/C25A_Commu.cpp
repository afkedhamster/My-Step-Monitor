#include <iostream>
#include <chrono>
#include <thread>
#include <cstring> 
#include "ADS1115.h"
#include "IPC.h"

int main() 
{
    ADS1115 ADS;
    ADS.ADS_init();

    // Mark B
    IPC ipc("/tmp", 'B'); 

    while (true) 
    {
        // Set (Different Channels)
        float ret0 = ADS.ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_0, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS);
        /* float ret1 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_1, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS); */
        ret0 = ret0 > 32768 ? 0 : ret0;
        float ret_v0 = (ret0*2.048)/32768;
        /* ret1 = ret1 > 32768 ? 0 : ret1;
        float ret_v1 = (ret1*2.048)/32768; */

        // Perpare Message
        std::vector<float> data = {ret0, ret_v0};
        Message message('B', data); // Type B

        // Send
        if (!ipc.send(message)) 
        {
            std::cerr << "Failed to send message to message queue." << std::endl;
            return -1;
        }

        // Display
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        /* std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl; */
        
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ADS.ADS_stop();

    return 0;
}