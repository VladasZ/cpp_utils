#include <iostream>
#include <ctime>

using namespace std;

template<typename A>
class Value
{
public:
    Value();

    void setData(A data);
    A getData() const;
private:
    A data;
};

template <typename T, typename D, int size = 5>
class Repository
{
public:
    Repository();

    D operator[](int index);
private:
    T object[size];
};

template<typename A>
Value<A>::Value() : data(0) {
}

template<>
Value<string>::Value() : data(" ") {
}


int main()
{
    srand((int)time(0));

    Value<int> v_int;
    Value<string>v_string;
    Value<void*> v_void_ptr;

    v_int.setData(42);
    v_string.setData("Hello");
    v_void_ptr.setData((void*)0xAABBCCDD);

    cout << v_int.getData() << endl;
    cout << v_string.getData() << endl;
    cout << v_void_ptr.getData() << endl;

//    Repository<Value<int>, int, 10> repository;
//
//    for (int i = 0; i < 10; i++)
//    {
//        cout << repository[i] << " ";
//    }

    cout << endl;


    return 0;
}


template<typename A>
void Value<A>::setData(A data) {
    this->data = data;
}

template<typename A>
A Value<A>::getData() const {
    return data;
}

template <typename T, typename D, int size>
Repository<T, D, size>::Repository()
{
    D data;
    for (size_t i = 0; i < size; i++)
    {
        data = rand() % 128;
        object[i].setData(data);
    }
}

template <typename T, typename D, int size>
D Repository<T, D, size>::operator[](int index)
{
    return object[index].getData();
}

