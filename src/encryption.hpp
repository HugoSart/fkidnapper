#ifndef __ENCRYPTION_HPP
#define __ENCRYPTION_HPP

#include <iostream>

/**
 * Encrypt a 4 byte number
 **/
uint32_t encrypt(uint32_t i)
{
    return ~i;
}

/**
 * Descrypt a 4 byte number
 **/
uint32_t decrypt(uint32_t i) {
    return ~i;
}

#endif // __ENCRIPTION_HPP
