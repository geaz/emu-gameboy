#pragma once
#ifndef REGISTER_H
#define REGISTER_H

#include <string>

template <class T> 
class Register
{
    public:
        Register(const std::string name, const T initialValue);
        
        T get();
        uint8_t getBit(const uint8_t bitNr);
        
        void operator=(T newValue);
        void operator+=(T addValue);
        void operator++(int ignored);
        void operator--(int ignored);

        std::string name;
    
    private:
        T value = 0;
};

template<class T> Register<T>::Register(const std::string name, const T initialValue) : name(name), value(initialValue) { }
template<class T> T Register<T>::get() { return value; }
template<class T> uint8_t Register<T>::getBit(const uint8_t bitNr) {  return (value >> bitNr) & 0x1; }
template<class T> void Register<T>::operator=(T newValue) { value = newValue; }
template<class T> void Register<T>::operator+=(T addValue) { value += addValue; }
template<class T> void Register<T>::operator++(int ignored) { value ++; }
template<class T> void Register<T>::operator--(int ignored) { value --; }

#endif // REGISTER_H