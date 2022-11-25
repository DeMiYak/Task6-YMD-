#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/**
«адача є6
—оздать абстрактный базовый класс "односв€зный список" ((a) - целых чисел, (б) - шаблонный), имеющий абстрактные методы
1) Push +
2) Pop +
3) GetFront +
4) IsEmpty +
5) Size +
6) Print (защищенный) +

7) ќперацию присваивани€ из ссылки на "список" +
и внутренний тип node (защищенный), реализовать перегрузку операции вывода (<< - через Print) и ввода (>> - через Push).


–еализовать конкретные классы —тек и ќчередь, имеющие необходимые конструкторы пустого списка, копировани€, перемещени€,
операции присваивани€ и присваивани€ по перемещению из ссылки на себ€ *и ссылки на фигуру
(копирование должно работать за O(1) и один проход списка, IsEmpty - за O(1)), реализацию абстрактных методов.
*/
#include<iostream>
#include<algorithm>

template<class T>
struct node
    {
        T data;
        struct node *next;
        node(T _data, struct node *_next = nullptr) : data(_data), next(_next) {}
    };



template<class T>
class list
{
public:

    list() {}
    virtual ~list() {}


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
            stream << node.data << ' ';
        };
        stream << '\n';
        return stream;
    }




    class const_iterator;
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = node<T>;
        using pointer = node<T>*;
        using reference = node<T>&;

        iterator(pointer _ptr = nullptr): ptr(_ptr) {}

        reference operator *() const {return *ptr;}
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

        friend const_iterator;
    private:

        bool operator <= (const iterator& i2) = delete;
        bool operator >= (const iterator& i2) = delete;

        pointer ptr;

    };

    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = node<T>;
        using pointer = const node<T>*;
        using reference = const node<T>&;

        const_iterator(pointer _ptr = nullptr): ptr(_ptr) {}
        const_iterator(const iterator& i2): ptr(i2.ptr) {}

        reference operator *() const {return *(ptr->data);}
        pointer operator ->() const {return ptr->data;}

        const_iterator &operator ++() {ptr = ptr->next; return *this;}
        const_iterator operator ++(int)
        {
            const_iterator temp = *this;
            ++(*this);
            return *this;
        }

        bool operator == (const const_iterator &i2) const {return ptr == i2.ptr;}
        bool operator != (const const_iterator &i2) const {return ptr != i2.ptr;}


    private:

        const_iterator(const iterator&& i2) = delete;
        bool operator <= (const const_iterator &i2) const = delete;
        bool operator >= (const const_iterator &i2) const = delete;

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
    node<T>* lastFront = nullptr;

private:

};

#endif // LIST_H_INCLUDED
