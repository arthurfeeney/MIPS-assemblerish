
#include <memory>
#include <algorithm>
#include <iostream>

#ifndef REGISTER_H
#define REGISTER_H

// union of possible types that the register can contain.
union reg_type {
    int i;
    char c;
    double f;
    reg_type():i(0) { }
    reg_type(int num):i(num) { }
    reg_type(char ch):c(ch) { }
    reg_type(double num):f(num) { }
    
    reg_type operator|(int num2) {
        return i | num2;
    }
    reg_type operator+=(const reg_type& num) {
        return i += num.i;
    }
    reg_type operator-=(const reg_type& num) {
        return i -= num.i;
    }
    friend std::ostream& operator<<(std::ostream& os, const reg_type& r) {
        os << r.i << r.c << r.f;
        return os;
    }
};

template<typename T> 
class Register {
private:
    std::shared_ptr<T> val;
    
    Register(Register&& r) = delete;

public:
    Register(): val(0) {} 
    Register(T& v): val(v) {}

    ~Register() = default;
    
    Register(const Register& r): val(r.val) {}

    Register& operator=(const Register& r) {
        if(this != &r) val = r.val;
        return *this;
    }
    Register& operator=(T& v) {
        val = std::shared_ptr<T>(v);
        return *this;
    }
    Register& operator=(T v) {
        *val = v;
        return *this;
    }

    Register& operator+(const T& v) {
        *val += v;
        return *this;
    }
    Register& operator+(const Register& r) {
        *val += *r.val;
        return *this;
    }

    Register& operator-(const T& v) {
        *val -= v;
        return *this;
    }
    Register& operator-(const Register& r) {
        *val -= *r.val;
        return *this;
    }
    

    // returns a pointer to the value.
    T& get_val() {
        return *val;
    };
};

#endif
