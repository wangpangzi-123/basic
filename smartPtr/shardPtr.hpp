#pragma once
#include <iostream>
#include <thread>
#include <mutex>

template<class T>
class defaultDeleter
{
public:
    void operator()(T* p)
    {
        delete p;
    }
};

template<class T, class deleter = defaultDeleter<T>>
class sharedPtr
{
public:
    // sharedPtr
    size_t use_count() const 
    {
        if(m_p == nullptr) 
            *refrenceNum = 0;
        return *refrenceNum; 
    }

    sharedPtr() 
        : m_p(nullptr), refrenceNum(new int(0)), _pMutex(new std::mutex)
    {
        //判断是否是不同的 sharedP
    }
    sharedPtr(T* p) : m_p(p), refrenceNum(new int(1)), _pMutex(new std::mutex)
    {
        puts("sharedPtr(T* p)");
    }
    sharedPtr(const sharedPtr& that)
        : m_p(that.m_p) ,
          refrenceNum(that.refrenceNum) ,
          _pMutex(that._pMutex)
    {
        addRefNum();
    }

    sharedPtr& operator= (const sharedPtr& that)
    {
        if(m_p != that.m_p)
        {
            //先释放原先的对象 m_p
            release();
            m_p = that.m_p;
            ++(*that.refrenceNum);
            refrenceNum = that.refrenceNum;
            _pMutex = that._pMutex;
        }
        return *this;
    }
    ~sharedPtr()
    {
        release();
    }

    void addRefNum()
    {
        _pMutex->lock();
        ++(*refrenceNum);
        _pMutex->unlock();
    }

    void release() 
    { 
        bool isOver = false;
        _pMutex->lock();
        if(*refrenceNum == 1)
        {
            deleter{}(m_p);
            delete refrenceNum;
            isOver = true;
        }
        else
        {
            --(*refrenceNum);
        }
        _pMutex->unlock();
        if(isOver == true)
            delete _pMutex;
    }
      
private:
    T* m_p; //内置指针
    int* refrenceNum;
    std::mutex* _pMutex;
};