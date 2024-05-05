#include "binary_cipher.h"

void my_rol_crypt(void *data, size_t data_len, const void *key, size_t key_len)
{
    unsigned char *data2 = data;
    const unsigned char *key2 = key;
    for (size_t i = 0; i < data_len; i++)
    {
        data2[i] = data2[i] + key2[i % key_len];
    }
}
