// Copyright (c) 2017 wbb.
//     All rights reserved.
//
// Author: wbbtiger@gmail.com
//

#include "benchmark.h"
#include <thread>
#include <chrono>

int main()
{
    Benchmark bench(10000, 100, []() -> int {
                        // int r = rand() % 200;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        return 0;
                                });
    bench.Run();
    bench.PrintResult();
    return 0;
}
