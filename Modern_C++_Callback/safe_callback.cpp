#include <functional>
#include <utility>
#include <memory>
#include <cassert>
struct Counter
{
    int value{0};
    void add(int x)
    {
        value += x;
    }
};

class CallbackRunner
{
    std::function<bool()> callback_;
public:
    void set_callback(std::function<bool()> cb)
    {
        callback_ = std::move(cb);
    }

    bool run()
    {
        if (callback_)
        {
            return callback_();
        }
        return false;
    }
    void clear()
    {
        callback_ = nullptr;
    }
};

int main()
{
    int offset = 3;
    auto pCounter = std::make_shared<Counter>();
    std::weak_ptr<Counter> weak = pCounter;
    auto callback = [weak, offset]() -> bool
        {
            if (auto p = weak.lock())
            {
                p -> add(offset);
                return true;
            }
            return false;
        };
    
    CallbackRunner callbackRunner;
    assert(!callbackRunner.run());

    callbackRunner.set_callback(callback);
    assert(callbackRunner.run() && pCounter ->value == 3);
    
    assert(callbackRunner.run() && pCounter ->value == 6);

    offset = 10;
    assert(callbackRunner.run() && pCounter ->value == 9);

    pCounter.reset();
    assert(!callbackRunner.run());

    callbackRunner.clear();
    assert(!callbackRunner.run());
    return 0;
}