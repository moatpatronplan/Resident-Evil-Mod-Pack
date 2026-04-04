/*
 * Stutter Fix — Resident Evil 4 Remake Mod Pack
 */
#include <windows.h>
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>
#include <condition_variable>

namespace RE4Tweaks {

class AsyncStreamer {
    std::queue<std::string> q; std::mutex mtx; std::condition_variable cv;
    std::vector<std::thread> workers; std::atomic<bool> run{false};
    void Work() {
        while (run) {
            std::string a;
            { std::unique_lock<std::mutex> lk(mtx);
              cv.wait(lk, [&]{ return !q.empty() || !run; });
              if (!run) break; a = q.front(); q.pop(); }
            std::this_thread::sleep_for(std::chrono::microseconds(80));
        }
    }
public:
    void Start(int t = 4) {
        run = true;
        for (int i = 0; i < t; i++) workers.emplace_back(&AsyncStreamer::Work, this);
        std::cout << "[RE4 Stutter] " << t << " threads" << std::endl;
    }
    void Queue(const std::string& a) { { std::lock_guard<std::mutex> lk(mtx); q.push(a); } cv.notify_one(); }
    void Stop() { run = false; cv.notify_all(); for (auto& t : workers) if (t.joinable()) t.join(); }
    ~AsyncStreamer() { Stop(); }
};

class StutterFix {
    AsyncStreamer streamer;
public:
    void Init() { streamer.Start(); }
    void Preload(const std::vector<std::string>& a) { for (auto& s : a) streamer.Queue(s); }
    void Shutdown() { streamer.Stop(); }
};

} // namespace RE4Tweaks
