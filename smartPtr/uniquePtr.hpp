#pragma once
#include <iostream>
#include <concepts>

//默认删除器的实现
template<class T>
struct defaultDeleter
{
    void operator()(T* p) const
    {
        std::cout << "default deleter!\r\n";
        delete p;
    }
};

template<>
struct defaultDeleter<FILE>
{
    void operator()(FILE* p) const
    {
        std::cout << "FILE CLOSE!\r\n";
        if(p)
            fclose(p);
    }
};

template<class T, class U>
T exchange(T& dst, U&& val)
{
    T tmp = std::move(dst);
    dst = std::forward<U>(val);
    return tmp;
}

template<class T, class Deleter = defaultDeleter<T>>
struct UniquePtr
{
private:
    T* m_p;
public:
    UniquePtr(){ m_p = nullptr; }
    UniquePtr(T* p){ m_p = p; };
    ~UniquePtr()
    {
        if(m_p)
            Deleter{}(m_p); 
    }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    //因为是UniquePtr 所以 智能指针只能够 一次 指向一个变量
    //所以应该 做 move
    UniquePtr(UniquePtr&& that) 
    {
        m_p = exchange(that.m_p, nullptr);
    }

    UniquePtr& operator=(UniquePtr&& that) 
    {
        if(this != &that) [[likely]]
        {
            printf("!= this = %p, that = %p \r\n", this, &that);
            m_p = exchange(that.m_p, nullptr);
        }
            printf("== this = %p, that = %p \r\n", this, &that);
        return *this;
    }

    //父子类继承
    template<class U, class UDeleter>
    friend struct UniquePtr;

    template<class U, class UDeleter>
        requires (std::convertible_to<U*, T*>)  //限定 U 必须可以隐式转化为 T
    UniquePtr(UniquePtr<U, UDeleter> that)
    {
        m_p = exchange(that.m_p, nullptr);
    }

    T& operator*() const { return *m_p; }
    T& operator->() const { return *m_p; }
    T* get() const { return m_p; }
};

/*总结：
1、Unique ptr 实现需要移除 赋值构造和拷贝构造
    防止内置野指针被多个对象拥有。
2、Unique ptr 实现需要实现 移动构造和移动赋值
    确保内置指针只被单一对象拥有
3、实现删除器，满足不同类型的uniquePtr的删除
4、实现不同类之间的隐式转换？
*/
