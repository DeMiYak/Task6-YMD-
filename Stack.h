#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<iostream>
#include"List.h"

template<class T>
class stack : public list<T>
{
public:

    stack(): last(nullptr) {}

    stack(const stack<T> &s) {stackCopy(s);}

    stack<T>(stack<T> &&s): last(s.last) {s.last = nullptr;}





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



    ~stack() {del();}




    enum ERR_CODE {EMPTY, OUT_OF_RANGE};




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
//    stack operator + (const stack &s1, const stack &s2)
//    {
//        s1Temp = s1.stackCopy();
//        s2Temp = s2.stackCopy();
//        node<T> *temp = s2Temp.Front();
//        temp->next = s1.last;
//
//        return s2;
//    }

protected:
    typedef typename list<T>::node node;
    node *last = nullptr;

    virtual void Print(std::ostream &stream) const
    {
        node *temp = last;
        while(temp)
        {
            stream << temp->data;
            if(temp->next) stream << "->";
            temp = temp->next;
        }
        stream << '\n';
    }
private:
//    void stackCopy(const stack &s)
//    {
//        node *temp = s.last;
//        while(temp)
//        {
//            Push(temp->data);
//            temp = temp->next;
//        }
//
//        node *tempNew = last;
//        temp = last->next; // Работает, так как по начальным данным last, next = nullptr.
//
//        if(temp == nullptr) return;
//
//        last->next = nullptr;
//        while(temp->next)
//        {
//            tempNew = temp;
//            temp = temp->next;
//            tempNew->next = last;
//            last = tempNew;
//        }
//        temp->next = last;
//        last = temp;
//    }
//
//     За один проход (здесь два)

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
