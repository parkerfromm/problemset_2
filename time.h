
#include <chrono>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
#define TIMER_ON

class timer
{
public:
    explicit timer(const string &label = "some function/ code");
    ~timer();
    static void silence();
    void set_label(const string &label);
    const timer &print() const;
    timer &start();
    timer &stop();
    timer &reset();
    timer &reset_and_print();
    // template<typename T>
    // string to_pretty_str(T n);

private:
    template <typename T>
    string to_pretty_str(T n) const;

    bool timing;
    string label;
    std::chrono::steady_clock::time_point start_t;
    std::chrono::steady_clock::time_point end_t;
    std::chrono::steady_clock::duration elapsed_t;
};
