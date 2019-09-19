#pragma once
#ifndef REGISTER_H
#define REGISTER_H

#include <string>

template <class T> 
class Register
{
    public:
        Register(const std::string name, const T initialValue);
        
        T read();
        uint8_t readBit(const uint8_t bitNr);
        void writeBit(const uint8_t bitNr, const bool bitValue);

        void operator=(T newValue);
        void operator+=(T addValue);
        void operator-=(T subValue);
        void operator++(int ignored);
        void operator--(int ignored);

        std::string name;
    
    private:
        T value = 0;
};

template<class T> Register<T>::Register(const std::string name, const T initialValue) : name(name), value(initialValue) { }
template<class T> T Register<T>::read() { return value; }
template<class T> uint8_t Register<T>::readBit(const uint8_t bitNr) {  return (value >> bitNr) & 0x1; }
template<class T> void Register<T>::writeBit(const uint8_t bitNr, const bool bitValue) { if(bitValue) value |= (0x1 << bitNr); else value &= ~(0x1 << bitNr); }
template<class T> void Register<T>::operator=(T newValue) { value = newValue; }
template<class T> void Register<T>::operator+=(T addValue) { value += addValue; }
template<class T> void Register<T>::operator-=(T subValue) { value -= subValue; }
template<class T> void Register<T>::operator++(int ignored) { value ++; }
template<class T> void Register<T>::operator--(int ignored) { value --; }

class RegisterPair
{
    public:
        RegisterPair(Register<uint8_t>& high, Register<uint8_t>& low) : high(high), low(low) { }

        void write(uint16_t newValue)
        {
            high = (newValue & 0xFF00) >> 8;
            low = (newValue & 0x00FF);
        }

        uint16_t read()
        {
            return (high.read() << 8) | low.read();
        }

        void operator++(int ignored)
        {
            uint16_t combined = read();
            combined++;
            write(combined);
        }

        void operator--(int ignored)
        {
            uint16_t combined = read();
            combined--;
            write(combined);
        }

    private:
        Register<uint8_t>& high;
        Register<uint8_t>& low;
};

#endif // REGISTER_H