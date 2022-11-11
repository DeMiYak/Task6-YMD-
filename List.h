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

template<class T>
class list
{
public:

    list() {}
    virtual ~list() {}

    virtual void Push(T data) = 0;
    virtual T Pop() = 0;
    virtual T GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;

protected:
    virtual void Print (std::ostream &stream) const = 0;
    friend std::ostream& operator << (std::ostream &stream, const list<T> &l)
    {
        l.Print(stream);
        return stream;
    }

    struct node
    {
        T data;
        struct node *next;
        node(T _data, struct node *_next = nullptr) : data(_data), next(_next) {}
    };

    friend std::istream& operator >> (std::istream &stream, list<T> &l)
    {
        T data;
        std::cin >> data;
        l.Push(data);
        return stream;
    }

private:

};

#endif // LIST_H_INCLUDED
