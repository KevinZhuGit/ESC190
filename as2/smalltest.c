#include "a2.h"

int main()
{
    // Task 1
    printf("%d\n", bitwise_xor(67));
    char *bin_string = xor_encrypt('C');
    printf("%c\n", xor_decrypt(bin_string));
    free(bin_string);

    // Task 2
    char *code = gen_code("Program in C!"); // gen code is read
    char *msg = read_code(code);            // read_code is read
    printf("%s\n", msg);
    free(msg);

    // Task 3
    char *hexcode = compress(code); // compress decompress are read
    printf("%s\n", hexcode);
    free(code);

    code = decompress(hexcode);
    free(hexcode);
    char *samehexcode = compress(code);
    printf("%s\n", samehexcode);
    free(code);
    free(samehexcode);

    // Task 4
    printf("%d\n", calc_ld("COMMENCE", "CODING"));
    printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));
    return 0;
}