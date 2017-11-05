// Copyright (c) 2017 wbb.
//     All rights reserved.
//
// Author: wbbtiger@gmail.com
//

#pragma once

#include <functional>

class Benchmark {
public:
    struct Stat {
        Stat()
            : concurrency(0),
              actual_concurrency(0),
              time_taken(0.0),
              complete_requests(0),
              failed_requests(0),
              requests_per_second(0.0),
              time_per_request_per_thread(0.0),
              time_per_request(0.0),
              percentiles{0}
        {}
        
        int concurrency;
        int actual_concurrency;
        double time_taken;
        int complete_requests;
        int failed_requests;
        double requests_per_second;
        double time_per_request_per_thread;
        double time_per_request;
        // Percentiles: 55, 66, 75, 80, 90, 95, 98, 99, 100.
        uint32_t percentiles[9];
    };
    
    Benchmark()
        : m_n_requests(0),
          m_concurrency(0)
    {}
    
    Benchmark(int n_requests, int concurrency, const std::function<int()>& op)
        : m_n_requests(n_requests),
          m_concurrency(concurrency),
          m_op(op)
    {}

    void SetNumOfRequests(int n_requests)
    {
        m_n_requests = n_requests;
    }

    void SetConcurrency(int concurrency)
    {
        m_concurrency = concurrency;
    }

    void SetOp(const std::function<int()>& op)
    {
        m_op = op;
    }

    void Run();

    Stat GetResult();

    void PrintResult();
    
private:
    int m_n_requests;  // number of requests
    int m_concurrency; // how many threads to do requests concurrently?
    std::function<int()> m_op;
    Stat m_stat;
};

