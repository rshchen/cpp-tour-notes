#include <string>
#include <vector>
#include <cassert>
#include <utility>
struct Task
{
    int id;
    std::string name;
    bool completed = false;
};

class TaskManager
{
    std::vector<Task> tasks;
public:
    void add(int id, std::string name)
    {
        tasks.push_back(Task{.id = id, .name = std::move(name)});
    }
    const Task* find(int id) const
    {
        for (const Task& task: tasks)
        {
            if (task.id == id)
            {
                return &task;
            }
        }
        return nullptr;
    }
    bool complete(int id)
    {
        for (Task& task: tasks)
        {
            if (task.id == id)
            {
                task.completed = true;
                return true;
            }
        }
        return false;
    }
    bool remove(int id)
    {
        for (auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            if (it->id == id)
            {
                tasks.erase(it);
                return true;
            }
        }
        return false;
    }
    std::size_t pending_count() const
    {
        std::size_t count{0};
        for (const Task& task: tasks)
        {
            if (!task.completed)
            {
                ++count;
            }
        }
        return count;
    }
    std::size_t size() const
    {
        return tasks.size();
    }
};

int main()
{
    TaskManager taskManager1;
    taskManager1.add(1, "a");
    taskManager1.add(2, "b");
    taskManager1.add(3, "c");
    assert(taskManager1.size() == 3 
        && taskManager1.pending_count() == 3);
    
    assert(taskManager1.complete(2)
        && taskManager1.pending_count() == 2);

    assert(!taskManager1.find(99) && !taskManager1.complete(99));

    assert(taskManager1.remove(1) && taskManager1.size() == 2);

    TaskManager taskManager2 = taskManager1;
    taskManager2.complete(3);
    assert(!taskManager1.find(3)->completed);
    assert(taskManager2.find(3)->completed);
    return 0;
}
