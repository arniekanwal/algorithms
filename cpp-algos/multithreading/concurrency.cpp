#include <iostream>
#include <deque>
#include <algorithm>

// concurrency libraries
#include <thread>
#include <future>

using namespace std;

template<size_t BUF_SIZE>
class Producer {
private:
    int start;
    int delta;
    int limit;

    deque<int> buf; 
    int cap;

public:
    Producer(int start, int delta, int limit) : start(start), delta(delta), limit(limit), cap(BUF_SIZE) {}

    void produce_values() {
        int num = start;
        while (num <= limit) {
            buf.push_back(num);
            num += delta;
        }
    }

    int read_values() {
        int res = buf.front();
        buf.pop_front();
        cout << res << " ";
        return res;
    }
};

int main() {
    return 0; 
}
