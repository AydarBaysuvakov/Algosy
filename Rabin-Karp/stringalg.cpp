#include <stdio.h>
#include <string.h>

unsigned long hash(const char *str, const int size)
{
    unsigned long hash = 5381;

    for (int i = 0; i < size; ++i)
        hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + c */

    return hash;
}


const char* RabinKarp(const char* str, const char* substr) {
    int n = strlen(str);
    int m = strlen(substr);
    unsigned long subhash = hash(substr, m);
    for (int i = 0; i < n - m; i++) {
        if (hash(str + i, m) == subhash) {
            int cmp = 1;
            for (int j = 0; j < m; j++) {
                if (str[i + j] != substr[j]) {
                    cmp = 0;
                    break;
                }
            if (cmp) {
                return str + i;
            }
            }
        }
    }
    return NULL;
}
