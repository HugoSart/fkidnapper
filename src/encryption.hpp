#ifndef __ENCRYPTION_HPP
#define __ENCRYPTION_HPP

#include <iostream>

static const long HASH_CODE = 159785L;

/**
 * Encrypt a 4 byte number
 **/
uint32_t encrypt(uint32_t i)
{
    return i += HASH_CODE;
}

/**
 * Descrypt a 4 byte number
 **/
uint32_t decrypt(uint32_t i) {
    return i -= HASH_CODE;
}

#endif // __ENCRIPTION_HPP