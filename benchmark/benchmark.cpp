// Copyright (c) 2017 wbb.
//     All rights reserved.
//
// Author: wbbtiger@gmail.com
//

#include "benchmark.h"

#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

void Benchmark::Run()
{
    vector<vector<uint32_t>> stats_per_thread(m_concurrency);
    vector<std::thread> threads;
    atomic<int> n_started_requests(0);
    atomic<int> n_done_requests(0);
    auto start_time = std::chrono::system_clock::now();
    int actual_concurrency = 0;
    atomic<int> failed_requests(0);
    for (int i = 0; i < m_concurrency; ++i) {
        try {
        threads.push_back(std::thread([&, i]() {
                                          for (;;) {
                                              int old = n_started_requests.load(std::memory_order_relaxed);
                    do {
                        if (old >= m_n_requests) {
                            return;
                        }
                    } while (!n_started_requests.compare_exchange_weak(old, old+1, std::memory_order_relaxed));
                    auto start_time = std::chrono::system_clock::now();
                    int err = [this]() -> int {
                        try {
                            return m_op();
                        } catch (...) {
                            return -1;
                        }
                    }();
                    if (err) {
                        ++failed_requests;
                    } else {
                            auto end_time = std::chrono::system_clock::now();
                            auto latency_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    end_time-start_time);
                            old = n_done_requests.load(std::memory_order_relaxed);
                            do {
                                if (old >= m_n_requests)
                                    return;
                            } while (!n_done_requests.compare_exchange_weak(old, old+1, std::memory_order_relaxed));
                            stats_per_thread[i].push_back(latency_ms.count());
                    }
                                          }
                }));
        ++actual_concurrency;
        } catch (...) {
        }
    }
    for (auto& t : threads) {
        try {
            t.join();
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    auto end_time = std::chrono::system_clock::now();
    double time_taken = chrono::duration_cast<chrono::duration<double>>(end_time-start_time).count();

    m_stat.concurrency = m_concurrency;
    m_stat.actual_concurrency = actual_concurrency;
    m_stat.time_taken = time_taken;
    m_stat.complete_requests = n_done_requests;
    m_stat.failed_requests = failed_requests;
    m_stat.requests_per_second = m_stat.complete_requests/m_stat.time_taken;
    m_stat.time_per_request_per_thread = (m_stat.actual_concurrency*m_stat.time_taken*1000/m_stat.complete_requests);
    m_stat.time_per_request = m_stat.time_taken*1000/m_stat.complete_requests;
    
    vector<uint32_t> latencies;
    for (const auto& s : stats_per_thread) {
        latencies.insert(latencies.end(), s.begin(), s.end());
    }
    sort(latencies.begin(), latencies.end());
    size_t idx = 0;
    for (int perc : { 50, 66, 75, 80, 90, 95, 98, 99, 100 }) {
        if (perc >= 100) {
            m_stat.percentiles[idx] = latencies.back();
        } else {
            m_stat.percentiles[idx] = latencies[perc*latencies.size()/100];
        }
        ++idx;
    }
}

Benchmark::Stat Benchmark::GetResult()
{
    return m_stat;
}

void Benchmark::PrintResult()
{
    cout << "Set concurrency Level: " << m_stat.concurrency << endl;
    cout << "Acutual concurrency level: " << m_stat.actual_concurrency << endl;
    cout << "Time taken for tests: " << m_stat.time_taken << "s" << endl;
    cout << "Complete requests: " << m_stat.complete_requests << endl;
    cout << "Failed requests: " << m_stat.failed_requests << endl;
    cout << "Requests per second: " << m_stat.requests_per_second << " [#/s] (mean)" << endl;
    cout << "Time per request per thread: " << m_stat.time_per_request_per_thread << " [ms] (mean)" << endl;
    cout << "Time per request: " << m_stat.time_per_request << " [ms] (mean)" << endl;
    cout << "Percentage of the requests served within a certain time (ms)" << endl;
    size_t idx = 0;
    for (int percentile : { 50, 66, 75, 80, 90, 95, 98, 99, 100 }) {
        cout << "  " << percentile << "%    " << m_stat.percentiles[idx] << endl;
        ++idx;
    }
}
