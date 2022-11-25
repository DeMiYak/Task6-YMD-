#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
#include"List.h"

template<class T>
class queue : public list<T>
{
public:

    // Queue Constructors

    queue(): front(nullptr), back(nullptr) {}

    queue(const queue<T> &q){queueCopy(q);}

    queue<T>(queue<T> &&q): front(q.front), back(q.back) {q.front = nullptr; q.back = nullptr;}


    // Queue Assignments

    queue<T> &operator = (queue<T> &&q)
    {
        if(&q == this) return *this;
        del();
        front = q.front;
        back = q.back;
        q.front = q.back = nullptr;
        return *this;
    }


    queue<T> &operator = (const queue<T> &q)
    {
        if(&q == this) return *this;
        del();
        queueCopy(q);
        return *this;
    }



    // Queue Destructor

    ~queue() {del();}




    enum ERR_CODE {EMPTY, OUT_OF_RANGE};


    // Standard Methods for Queue

    virtual void Push(T data)
    {
        if(back)
        {
            back->next = new node(data);
            back = back->next;
        } else
        {
            back = new node(data);
            front = back;
        }
    }



    T Pop()
    {
        if(!front) throw EMPTY;
        node *temp = front;
        T frontData = front->data;
        front = front->next;
        if(!front) back = nullptr;
        delete temp;
        return frontData;
    }

//

    T GetFront()
    {
        if(!front) throw EMPTY;
        return front->data;
    }

    T GetFront() const
    {
        if(!front) throw EMPTY;
        return front->data;
    }

    void SetFront() const
    {
        T data;
        std::cin >> data;
        front->data = data;
    }

    bool IsEmpty() const {return front == nullptr;}


    // Print Method

    // Quantity Method

    size_t Size() const
    {
        if(front)
        {
            size_t size = 1;
            node *temp = front;
            while(temp->next)
            {
                size++;
                temp = temp->next;
            }
            return size;
        } else return 0;
    }

    T& operator [] (size_t id)
    {
        id -= 1;
        if(!front) throw EMPTY;
        if(id >= Size()) throw OUT_OF_RANGE;
        node *temp = front;
        for(; id; id--)
            temp = temp->next;
        return temp->data;
    }

    const T& operator [] (size_t id) const
    {
        id -= 1;
        if(!front) throw EMPTY;
        if(id >= Size()) throw OUT_OF_RANGE;
        node *temp = front;
        for(; id; id--)
            temp = temp->next;
        return temp->data;
    }

protected:
    typedef typename list<T>::node node;
    node *front = nullptr, *back = nullptr;

    virtual void Print(std::ostream &stream) const
    {
        node *temp = front;
        stream << '[';
        while(temp)
        {
            if(temp != front) {std::cout << ", ";}
            stream << temp->data;
            temp = temp->next;
        }
        stream << ']' << '\n';
    }
private:

    void queueCopy(const queue<T> &q)
    {
        node *temp = q.front;
        while(temp)
        {
            Push(temp->data);
            temp = temp->next;
        }
    }



    void del()
    {
        while(front)
            Pop();
        back = nullptr;
    }
};

#endif // QUEUE_H_INCLUDED
