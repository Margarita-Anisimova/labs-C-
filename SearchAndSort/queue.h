#pragma once
class queueInt
{
public:
    class queueItem
    {
    public:
        queueItem(int val) : value(val), next(nullptr) { }
        int value;
        queueItem* next;
    };

    queueInt() : head(nullptr), tail(nullptr) { }
    void push(int val)
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
