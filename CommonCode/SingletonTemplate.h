//
//  SingletonTemplate.h
//
//  @提供单例模式模板，方便单例模式的构建

#ifndef __CPPSolitaire__SingletonTemplate__
#define __CPPSolitaire__SingletonTemplate__

template<typename T>
class SingletonTemplate
{
public:
    static T* getInstance()
    {
        static T _instance;
        return &_instance;
    }
protected:
    SingletonTemplate(){}
    virtual ~SingletonTemplate(){}
    SingletonTemplate(const SingletonTemplate<T>&); //拷贝构造函数不实现
    SingletonTemplate<T>& operator=(const SingletonTemplate<T>&); //赋值函数不实现
};
#endif /* defined(__CPPSolitaire__SingletonTemplate__) */
