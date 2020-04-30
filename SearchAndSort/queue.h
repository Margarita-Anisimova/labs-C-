#pragma once
template<typename T>
class queue
{
public:
    class queueItem
    {
    public:
        queueItem(T val) : value(val), next(nullptr) { }
        T value;
        queueItem* next;
    };

    queue() : head(nullptr), tail(nullptr) { }
    void push(T val)
    {
        if (!head)
            head = tail = new queueItem(val);
        else
        {
            tail->next = new queueItem(val);
            tail = tail->next;
        }
    }
    void pop()
    {
        if (head)
            head = head->next;
    }
    queueItem* head;
    queueItem* tail;
};
