//
// Created by Aubrey on 6/16/2024.
//

#ifndef SOFTCPU2_REGISTER_HPP
#define SOFTCPU2_REGISTER_HPP

template <typename T>
class Register
{
private:
    T reg = 0;
public:
    T read() const { return reg; }
    void write(T data) { reg = data; }
};

#endif //SOFTCPU2_REGISTER_HPP
