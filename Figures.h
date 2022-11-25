#ifndef FIGURES_H_INCLUDED
#define FIGURES_H_INCLUDED

#define M_PI 3.14159265359

// Дедлайн: 11.11.2022. №5 - дедлайн в конце семестра.

/*
Задача №4
Создать абстрактный базовый класс фигура, поддерживающий чисто виртуальные методы
1) "площадь" и "периметр"
2) "печать" (отправка на ostream) - защищенный
3*) операцию присваивания из ссылки на другую фигуру

Реализовать перегрузку операции << для фигуры.

Создать производные классы "окружность", "прямоугольник", "эллипс" и др.
(по желанию), реализующие конструкторы по необходимым значениям параметров, определяющих фигуру,
и конкретизацию необходимых абстрактных методов базового класса (*операцию присваивания из абстрактной фигуры
реализовать путем динамического приведения типа к конкретной фигуре).
*/

#include<iostream>



template<class T>
class figure
{
public:
    figure() {}

    virtual T perimeter() const = 0;
    virtual T area() const = 0;

    virtual ~figure() {}

protected:
    virtual void print (std::ostream &stream) const = 0;
    friend std::ostream& operator << (std::ostream &stream, const figure<T>& f)
    {
        f.print(stream);
        // << "Perimeter = " << perimeter << ' ' << "Area = " << area;
        return stream;
    }
private:
};

template<class T>
class rectangle : public figure<T>
{
public:
    rectangle(T _len, T _width): len(_len), width(_width) {}
    ~rectangle() {}

    T perimeter() const {return 2*len + 2*width;}
    T area() const {return len*width;}

protected:
    virtual void print (std::ostream &stream) const
    {
        stream << "Rectangle: " << std::endl << "Length: " << len << '\t' << "Width: " << width << std::endl << "Perimeter: " << perimeter() << '\t' << "Area: " << area() << std::endl << std::endl;
    }

    rectangle& operator = (const rectangle& r)
    {
        len = r.len;
        width = r.width;
        return *this;
    }

private:
    T len, width;
};

template<class T>
class circle : public figure<T>
{
public:
    circle(T _radius): radius(_radius) {}
    ~circle() {}

    T perimeter() const {return 2*M_PI*radius;}
    T area() const {return M_PI*radius*radius;}
private:
    T radius;
protected:
    virtual void print (std::ostream &stream) const
    {
        stream << "Circle: " << std::endl << "Radius: " << radius << std::endl << "Perimeter: " << perimeter() << '\t' << "Area: " << area() << std::endl << std::endl;
    }

    circle& operator = (const circle& c)
    {
        radius = c.radius;
        return *this;
    }
};

template<class T>
class ellipse : public figure<T>
{
public:
    ellipse(T _a, T _b): a(_a), b(_b) {}
    ~ellipse() {}

    T perimeter() const {return M_PI*(a+b);}
    T area() const {return 2*M_PI*a*b;}
private:
    T a, b;
protected:
    virtual void print (std::ostream &stream) const
    {
        stream << "Ellipse: " << std::endl << "A: " << a << '\t' << "B: " << b << std::endl << "Perimeter: " << perimeter() << '\t' << "Area: " << area() << std::endl << std::endl;
    }

    ellipse& operator = (const ellipse& e)
    {
        a = e.a;
        b = e.b;
        return *this;
    }
};

/*
class figure
{
public:
    figure() {std::cout << "The chosen figure is ";}

    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual ~figure() {std::cout << std::endl;}

//    virtual figure& operator += (T df)
//    {
//
//    }
protected:
    friend std::ostream& operator << (std::ostream &stream, const figure &f)
    {
        stream << "Perimeter = " << f.perimeter() << ' ' << "Area = " << f.area();
        return stream;
    }
private:
};


class rectangular : public figure
{
public:
    rectangular(double _len, double _width): len(_len), width(_width) {std::cout << "Rectangular";}
    ~rectangular() {std::cout << std::endl;}

    double perimeter() const {return 2*len + 2*width;}
    double area() const {return len*width;}
protected:
    rectangular& operator = (const rectangular& r)
    {
        len = r.len;
        width = r.width;
        return *this;
    }
private:
    double len, width;
};


class circle : public figure
{
public:
    circle(double _radius): radius(_radius) {std::cout << "Circle: ";}
    ~circle() {std::cout << std::endl;}

    double perimeter() const {return 2*M_PI*radius;}
    double area() const {return M_PI*radius*radius;}
private:
    double radius;
protected:
    circle& operator = (const circle& c)
    {
        radius = c.radius;
        return *this;
    }

};


class ellipse : public figure
{
public:
    ellipse(double _a, double _b): a(_a), b(_b) {std::cout << "Ellipse: ";}
    ~ellipse() {std::cout << std::endl;}

    double perimeter() const {return M_PI*(a+b);}
    double area() const {return 2*M_PI*a*b;}
private:
    double a, b;
protected:
    ellipse& operator = (const ellipse& e)
    {
        a = e.a;
        b = e.b;
        return *this;
    }

};
*/

#endif // FIGURES_H_INCLUDED
