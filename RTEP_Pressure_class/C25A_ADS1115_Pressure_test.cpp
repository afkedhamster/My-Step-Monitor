#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include "ADS1115.h"

int main() 
{
    ADS1115 ADS;
    
    while (true) 
    {
        // Set (Different Channels)
        int ret0 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_0, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS);
        /* int ret1 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_1, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS); */
        ret0 = ret0 > 32768 ? 0 : ret0;
        double ret_v0 = (ret0*2.048)/32768;
        /* ret1 = ret1 > 32768 ? 0 : ret1;
        double ret_v1 = (ret1*2.048)/32768; */
        // Display
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        /* std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl; */
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ADS_stop();

    return 0;
}