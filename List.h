#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/**
������ �6
������� ����������� ������� ����� "����������� ������" ((a) - ����� �����, (�) - ���������), ������� ����������� ������
1) Push +
2) Pop +
3) GetFront +
4) IsEmpty +
5) Size +
6) Print (����������) +

7) �������� ������������ �� ������ �� "������" +
� ���������� ��� node (����������), ����������� ���������� �������� ������ (<< - ����� Print) � ����� (>> - ����� Push).


����������� ���������� ������ ���� � �������, ������� ����������� ������������ ������� ������, �����������, �����������,
�������� ������������ � ������������ �� ����������� �� ������ �� ���� *� ������ �� ������
(����������� ������ �������� �� O(1) � ���� ������ ������, IsEmpty - �� O(1)), ���������� ����������� �������.
*/
#include<iostream>
#include<algorithm>

//
//09.12
//
//* ������ � ������ ������, �������, ���, �� ����� �������� ���������� ������ ��� �������, � �� ��� �������������
//* �������� ����������������� � Node, � �� � T - ��� �� ������, �.�. Node - ���������� ���� ����������, � ������ ���� � ����������

template<class T>
struct node
    {
        T data;
        struct node<T> *next;
        node(T _data, struct node *_next = nullptr) : data(_data), next(_next) {}
    };



template<class T>
class list
{
public:

    typedef struct node<T> node;

    list() {}
    virtual ~list() {}

    // List input/output operators

    friend std::istream& operator >> (std::istream &stream, list<T> &l)
    {
        T data;
        std::cin >> data;
        l.Push(data);
        return stream;
    }



    friend std::ostream& operator << (std::ostream &stream, list<T> &l)
    {
        for (const auto& node: l)
        {
            stream << node << '\t' << &(node) << '\n';
        };
        stream << '\n' << '\n' << std::endl;
        return stream;
    }


    // List Iterators

    class const_iterator;
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = node*;
        using reference = T&;

        iterator(pointer _ptr = nullptr): ptr(_ptr) {}

        reference operator *() const {return ptr->data;}
        pointer operator ->() const {return ptr;}

        iterator &operator ++() {ptr = ptr->next; return *this;}
        iterator operator ++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator == (const iterator& i2) {return ptr == i2.ptr;}
        bool operator != (const iterator& i2) {return ptr != i2.ptr;}

        bool operator <= (const iterator& i2) {return ptr <= i2.ptr;}
        bool operator >= (const iterator& i2) {return ptr >= i2.ptr;}

        bool operator < (const iterator& i2) {return ptr < i2.ptr;}
        bool operator > (const iterator& i2) {return ptr > i2.ptr;}


        friend const_iterator;
    private:
        pointer ptr;

    };

    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const node*;
        using reference = const T&;

        const_iterator(pointer _ptr = nullptr): ptr(_ptr) {}

        reference operator *() const {return ptr->data;}
        pointer operator ->() const {return ptr;}

        const_iterator &operator ++() {ptr = ptr->next; return *this;}
        const_iterator operator ++(int)
        {
            const_iterator temp = *this;
            ++(*this);
            return *this;
        }

        bool operator == (const const_iterator&i2) const {return ptr == i2.ptr;}
        bool operator != (const const_iterator& i2) const {return ptr != i2.ptr;}

        bool operator <= (const const_iterator& i2) const {return ptr <= i2.ptr;}
        bool operator >= (const const_iterator& i2) const {return ptr >= i2.ptr;}

        bool operator < (const const_iterator& i2) const {return ptr < i2.ptr;}
        bool operator > (const const_iterator& i2) const {return ptr > i2.ptr;}

    private:

        pointer ptr;

    };


    virtual void Push(T data) = 0;
    virtual T Pop() = 0;
    virtual T GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;

    virtual iterator begin() {return iterator(lastFront);}
    virtual iterator end() {return iterator(nullptr);}

    virtual const_iterator begin() const {return const_iterator(lastFront);}
    virtual const_iterator end() const {return const_iterator(nullptr);}

    virtual const_iterator cbegin() const {return const_iterator(lastFront);}
    virtual const_iterator cend() const {return const_iterator(nullptr);}

    virtual void Print () const = 0;

protected:
    // virtual void Print (std::ostream &stream) const = 0;
    node* lastFront = nullptr;

private:

};

#endif // LIST_H_INCLUDED
