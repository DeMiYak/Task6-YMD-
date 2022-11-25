#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<iostream>
#include<algorithm>
#include"List.h"

template<class T>
class stack : public list<T>
{
public:

    // Iterator Methods

    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::const_iterator const_iterator;

    iterator begin() {return iterator(last);}
    const_iterator begin() const {return const_iterator(last);}
    const_iterator cbegin() const {return const_iterator(last);}

    // Stack Constructors

    stack(): last(nullptr) {}

    stack(const stack<T> &s) {stackCopy(s);}

    stack<T>(stack<T> &&s): last(s.last) {s.last = nullptr;}



    // Stack Operators

    stack<T> &operator = (const stack<T> &s)
    {
        if(&s == this) return *this;
        del();
        stackCopy(s);
        return *this;
    }




    stack<T> &operator = (stack<T> &&s)
    {
        if(&s == this) return *this;
        del();
        last = s.last;
        s.last = nullptr;
        return *this;
    }


    T& operator [] (size_t id)
    {
        if(!last) throw EMPTY;
        size_t j = Size();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    const T& operator [] (size_t id) const
    {
        if(!last) throw EMPTY;
        size_t j = Size();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }
    // Stack Destructor

    ~stack() {del();}




    enum ERR_CODE {EMPTY, OUT_OF_RANGE};


    // Stack Methods

    virtual void Push(T data) {last = new node(data, last);}

    T Pop()
    {
        if(!last) throw EMPTY;
        T lastData = last->data;
        node *temp = last;
        last = last->next;
        delete temp;
        return lastData;

    }

    T GetFront()
    {
        if(!last) throw EMPTY;
        node *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }

    T GetFront() const
    {
        if(!last) throw EMPTY;
        node *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }


    void SetFront() const
    {
            T data;
            std::cin >> data;
            last->data = data;
    }

    bool IsEmpty() const {return last == nullptr;}

    size_t Size() const
    {
        if(last)
        {
            size_t size = 1;
            node *temp = last;
            while(temp->next)
            {
                size++;
                temp = temp->next;
            }
            return size;
        } else return 0;
    }

    // Print Method

    virtual void Print() const
    {
        node *temp = last;
        while(temp)
        {
            std::cout << temp->data;
            if(temp->next) std::cout << "->";
            temp = temp->next;
        }
        std::cout << '\n';
    }

protected:
    typedef node<T> node;
    node *last = nullptr;

//     virtual void Print(std::ostream &stream) const
//    {
//        node *temp = last;
//        while(temp)
//        {
//            stream << temp->data;
//            if(temp->next) stream << "->";
//            temp = temp->next;
//        }
//        stream << '\n';
//    }

private:

    void stackCopy(const stack &s)
    {
        node *temp = s.last;

        if(temp == nullptr) return;

        Push(temp->data);

        if(temp->next == nullptr) return;

        temp = temp->next;
        node *lastTrue = last;
        Push(temp->data);
        node *preLast = last;
        preLast->next = nullptr;
        lastTrue->next = preLast;
        last = lastTrue;

        while(temp->next)
        {
            temp = temp->next;
            Push(temp->data);
            last->next = nullptr;
            preLast->next = last;
            preLast = last;
            last = lastTrue;
        }

    }

    void del()
    {
        while(last) Pop();
    }
};

#endif // STACK_H_INCLUDED
