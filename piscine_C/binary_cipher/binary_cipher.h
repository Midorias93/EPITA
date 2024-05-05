#ifndef BINARY_CIPHER_H
#define BINARY_CIPHER_H

#include <stddef.h>

/*
** XOR byte by byte the data of size data_len with the key of size
** key_len.
*/
void my_xor_crypt(void *data, size_t data_len, const void *key, size_t key_len);

/*
** Rotate byte by byte the data of size data_len with the key of size
** key_len.
** Rotating a byte by another means adding them together with potential
** overflow.
*/
void my_rol_crypt(void *data, size_t data_len, const void *key, size_t key_len);

#endif /* !BINARY_CIPHER_H */
