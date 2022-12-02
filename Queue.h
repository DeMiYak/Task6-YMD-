#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
#include<algorithm>
#include"List.h"

template<class T>
class queue : public list<T>
{
public:

    // Iterator Methods

    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::const_iterator const_iterator;

    iterator begin() {return iterator(front);}
    iterator end() {return iterator(nullptr);}

    const_iterator begin() const {return const_iterator(front);}
    const_iterator end() const {return const_iterator(nullptr);}

    const_iterator cbegin() const {return const_iterator(front);}
    const_iterator cend() const {return const_iterator(nullptr);}


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

    virtual void Print() const
    {
        node *temp = front;
        std::cout << '[';
        while(temp)
        {
            if(temp != front) {std::cout << ", ";}
            std::cout << temp->data;
            temp = temp->next;
        }
        std::cout << ']' << '\n';
    }

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

protected:
    typedef struct node<T> node;
    node *front = nullptr, *back = nullptr;

//    virtual void Print(std::ostream &stream) const
//    {
//        node *temp = front;
//        stream << '[';
//        while(temp)
//        {
//            if(temp != front) {std::cout << ", ";}
//            stream << temp->data;
//            temp = temp->next;
//        }
//        stream << ']' << '\n';
//    }

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
