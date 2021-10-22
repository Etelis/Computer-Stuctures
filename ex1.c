//
// 209041474 Itay Etelis
//

#include <stddef.h>

/*
 * The following function will check if the machine is big endian machine or a small endian machine.
 */
int is_big_endian(){
    // 00010010 - 18, 00110100 - 52 => x = 00010010 00110100
    int x = 0x1234, BIG_ENDIAN = 18;
    // Will be using unsigned char to ensure 1 byte variable.
    unsigned char *check =(unsigned char*) &x;
    // as mentioned above if the int equivalent of the char is 18 than it's a big endian machine.
    return (int) *check == BIG_ENDIAN;
}

/*
 * The following function will merge two unsigned longs, assuming unsigned long is size of 8 byte.
 * @param long x - the second half number.
 * @param long int y - the first half number.
 */
unsigned long long merge_bytes(unsigned long long x, unsigned long long y){
    // maskY = 00000000 00000000 00000000 00000000 11111111 11111111 11111111 11111111
    // maskX = 11111111 11111111 11111111 11111111 00000000 00000000 00000000 00000000
    unsigned long long maskY = 0x00000000FFFFFFFF, maskX = 0xFFFFFFFF00000000;
    return (maskY & y) | (maskX & x);
}

/*
 * The following function recieves a number and a char and places that char in the offset calculated.
 * @param x - the number.
 * @param b - the byte we will replace.
 * @param i - the offset.
 */
unsigned long long put_byte(unsigned long long x, unsigned char b, int i){
    // x = 00010010 00110100 01010110 01111000 11001101 11101111 00110100 01010110
    // b = 10101011 - AB - 1011
    // y = 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10101011
    size_t offset = (sizeof (x) - (1 + i));
    // if machine is big endian calculate from back to front.
    if (!is_big_endian()){
        offset = sizeof (x) - offset;
    }
    // otherwise calculate regulary.
    unsigned char *jump = (unsigned char*) &(x);
    jump += offset;
    *jump = b;
    return x;
}


