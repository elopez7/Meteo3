#ifndef ENUMCONVERTERS_H
#define ENUMCONVERTERS_H

#include <type_traits>

//Tool to convert class enum to value of underlying type for easier use
//Look into KDAB videos to see if there is a new way.
template<typename E>
constexpr typename std::underlying_type<E>::type operator+(E e)
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

#endif // ENUMCONVERTERS_H
