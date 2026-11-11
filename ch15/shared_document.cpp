#include <utility>
#include <string>
#include <memory>
#include <cassert>
#include <iostream>
struct Document
{
    std::string name;
    explicit Document(std::string name) : name{std::move(name)}{}
};
class DocumentOwner
{
    std::shared_ptr<Document> data_;
public:
    DocumentOwner(std::shared_ptr<Document> data) : 
    data_{std::move(data)} 
    {}
    std::shared_ptr<Document> get() const
    {
        return data_;
    }
    void reset()
    {
        data_.reset();
    }
    long use_count() const
    {
        return data_.use_count();
    }
};

class DocumentObserver
{
    std::weak_ptr<Document> view_;
public:
    DocumentObserver(const std::shared_ptr<Document>& data) : 
    view_{data}
    {} 

    bool expired() const
    {
        return view_.expired();
    }
    std::string name() const
    {
        if(auto p = view_.lock())
        {
            return p -> name;
        }
        return "<expired>";
    }
};

int main()
{

    DocumentOwner owner1{std::make_shared<Document>("Hello world!")};
    assert(owner1.use_count() == 1);

    DocumentOwner owner2{owner1.get()};
    assert(owner2.use_count() == 2);

    DocumentObserver observer1{owner1.get()};
    assert(owner2.use_count() == 2);

    owner1.reset();
    assert(owner2.use_count() == 1);
    assert(observer1.name() == "Hello world!");

    owner2.reset();
    assert(observer1.expired() && observer1.name() == "<expired>");
    return 0;
}