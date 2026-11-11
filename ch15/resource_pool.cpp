#include <vector>
#include <memory>
#include <cassert>
#include <utility>
struct Resource
{
    int id_;
    explicit Resource(int id) : id_{id}
    {}
};

class ResourcePool
{
    std::vector<std::unique_ptr<Resource>> data_;
public:
    void add(int id)
    {
        data_.push_back(std::make_unique<Resource>(id));
    }
    const Resource* find(int id) const
    {
        for (auto& x : data_)
        {
            if (x->id_ == id) return x.get();
        }
        return nullptr;
    }
    std::unique_ptr<Resource> extract(int id)
    {
        for (auto it = data_.begin();it != data_.end(); ++it)
        {
            if ((*it)->id_ == id)
            {
                auto result = std::move(*it);
                data_.erase(it);
                return result;
            }
        }
        return nullptr;
    }
    void insert(std::unique_ptr<Resource> source)
    {
        if (!source) return;
        data_.push_back(std::move(source));
    }
    std::size_t size() const
    {
        return data_.size();
    }
};

int main()
{
    ResourcePool pool;
    pool.add(10);
    pool.add(20);
    assert(pool.size() == 2);
    
    assert(pool.find(10)->id_ == 10 && pool.find(90) == nullptr);
    
    std::unique_ptr<Resource> temp = pool.extract(10);
    assert(pool.size() == 1);
    assert(temp != nullptr);
    assert(temp->id_ == 10);
    assert(pool.find(10) == nullptr);

    pool.insert(std::move(temp));
    assert(pool.size() == 2 && !temp);

    assert(pool.extract(99) == nullptr);
    assert(pool.size() == 2);
    pool.insert(nullptr);
    assert(pool.size() == 2);


}