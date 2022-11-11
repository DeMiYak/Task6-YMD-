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
