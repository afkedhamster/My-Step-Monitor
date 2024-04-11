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
        // Process
        ads.Process(ret0, ret_v0, ret1, ret_v1);
        
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
