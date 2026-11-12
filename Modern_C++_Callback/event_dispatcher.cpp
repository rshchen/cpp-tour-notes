#include <vector>
#include <functional>
#include <utility>
#include <cassert>
struct Entry
{
    int id;
    std::function<void(int)> callback;
};


class EventDispatcher
{
    std::vector<Entry> entries_;
    int next_id_ = 1;
public:
    int subscribe(std::function<void(int)> cb)
    {
        entries_.push_back(Entry{next_id_, std::move(cb)});
        return next_id_++;
    }
    bool unsubscribe(int id)
    {
        for (auto it = entries_.begin(); it != entries_.end(); ++it)
        {
            if (it->id == id)
            {
                entries_.erase(it);
                return true;
            }
        }
        return false;
    }
    void emit(int event_val)
    {
        for (const Entry& entry : entries_)
        {
            entry.callback(event_val);
        }
    }
    std::size_t size() const
    {
        return entries_.size();
    }
};

class ScopedSubscription
{
    EventDispatcher& dispatcher_;
    int id_;
public:
    ScopedSubscription(EventDispatcher& dispatcher, int id) :
    dispatcher_{dispatcher}, id_{id}{}
    ScopedSubscription(const ScopedSubscription& other) = delete;
    ScopedSubscription& operator=(const ScopedSubscription& other) = delete;
    ~ScopedSubscription()
    {
        dispatcher_.unsubscribe(id_);
    }
};

int main()
{
    EventDispatcher dispatcher1;
    assert(dispatcher1.size() == 0);

    int result_a = 0, result_b = 0;
    int result_c = 0, result_d = 0;

    auto A = [&result_a, factor = 1](int event_value)
    {
        result_a += event_value * factor;
    };
    auto B = [&result_b, factor = 2](int event_value)
    {
        result_b += event_value * factor;
    };
    auto C = [&result_c, factor = 3](int event_value)
    {
        result_c += event_value * factor;
    };
    auto D = [&result_d, factor = 4](int event_value)
    {
        result_d += event_value * factor;
    };

    int id_a = dispatcher1.subscribe(A);
    dispatcher1.subscribe(B);
    dispatcher1.subscribe(C);
    assert(dispatcher1.size() == 3);
    
    dispatcher1.emit(3);
    assert(result_a == 3 && result_b == 6 && result_c == 9);

    assert(dispatcher1.unsubscribe(id_a));
    dispatcher1.emit(2);
    assert(result_a == 3 && result_b == 10 && result_c == 15);

    {
        int id = dispatcher1.subscribe(D);
        ScopedSubscription scopeSub{dispatcher1, id};
        dispatcher1.emit(1);
        assert(result_b == 12 && result_c == 18 && result_d == 4);
    }

    assert(dispatcher1.size() == 2);
    dispatcher1.emit(2);
    assert(result_a == 3 && result_b == 16
        && result_c == 24 && result_d == 4);

    assert(!dispatcher1.unsubscribe(id_a));
    {
        int id = dispatcher1.subscribe(D);
        ScopedSubscription scopeSub{dispatcher1, id};

        assert(dispatcher1.unsubscribe(id));
    }
    assert(dispatcher1.size() == 2);

    EventDispatcher dispatcher2;
    std::vector<char> call_order;
    auto a = [&call_order](int)
    {
        call_order.push_back('a');
    };
    auto b = [&call_order](int)
    {
        call_order.push_back('b');
    };
    auto c = [&call_order](int)
    {
        call_order.push_back('c');
    };
    dispatcher2.subscribe(a);
    dispatcher2.subscribe(b);
    dispatcher2.subscribe(c);
    dispatcher2.emit(1);
    assert((call_order == std::vector<char>{'a', 'b', 'c'}));
    return 0;
}