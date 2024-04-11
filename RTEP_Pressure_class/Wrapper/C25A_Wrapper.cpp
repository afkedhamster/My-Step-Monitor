#include <iostream>
#include <chrono>
#include <thread>
#include "ADS1115_Wrapper.h"

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

    while (true) 
    {
        // Set (Different Channels)
        int ret0 = ads.measure(ADS1115_REG_CONFIG_MUX_SINGLE_0, 
                               ADS1115_REG_CONFIG_PGA_4_096V, 
                               ADS1115_REG_CONFIG_DR_128SPS,
                               std::chrono::milliseconds(8));
        int ret1 = ads.measure(ADS1115_REG_CONFIG_MUX_SINGLE_1, 
                               ADS1115_REG_CONFIG_PGA_4_096V, 
                               ADS1115_REG_CONFIG_DR_128SPS,
                               std::chrono::milliseconds(8));
        ret0 = ret0 > 32768 ? 0 : ret0;
        double ret_v0 = ret0 / (4.096 / 32768); // Change
        ret1 = ret1 > 32768 ? 0 : ret1;
        double ret_v1 = ret1 / (4.096 / 32768);
        // Display
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
