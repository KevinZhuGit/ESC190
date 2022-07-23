#include "a2.h"

int get_next(int index)
{
    // areas covered by squares
    int bounds[] = {0, 4, 11, 20, 27, 36, 43, 52, 59, 68, 75, 79, 176, 180, 192, 196, 208, 212, 224, 228, 240, 244, 255};

    for (int i = 0; i < 23; i += 2)
    {
        if (index >= bounds[i] && index <= bounds[i + 1])
        {
            return bounds[i + 1] + 1;
        }
    }

    return index;
}

char get_hexidecimal(char *s)
{
    int hex = 0;

    for (int i = 0; i < 4; i++)
    {
        int on_off = s[i] - '0';
        hex += on_off * pow(2, (3 - i));
    }

    if (hex < 10)
    {
        return hex + '0';
    }
    else
    {
        return hex + 55;
    }
}

char *get_binary(char c)
{
    char *code = malloc(sizeof(char) * 4);
    int x, i = 0;

    if (c < 58)
    {
        x = c - '0';
    }
    else
    {
        x = c - 55;
    }

    // convert to binary string

    while (x != 0)
    {
        code[3 - i] = x % 2 + '0';
        x /= 2;
        i++;
    }

    // gets cases for less than 8
    while (i < 4)
    {
        code[3 - i] = '0';
        i++;
    }

    return code;
}

void print_SC(char *sc)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%c ", sc[16 * i + j]);
        }
        printf("\n");
    }
}

int bitwise_xor(int value)
{
    return value ^ KEY;
}

char *xor_encrypt(char c)
{
    // return pointer to dynamic arr of string, NEEDS FREE
    // array is 7 digits, need to fill everything

    int output = bitwise_xor(c);
    unsigned int mask = 0b01;
    char *s = malloc(sizeof(char) * 8);

    for (int i = 6; i >= 0; i--)
    {
        if ((output & mask) != 0)
        {
            s[i] = '1';
            mask = mask << 1;
        }
        else
        {
            s[i] = '0';
            mask = mask << 1;
        }
    }

    s[7] = '\0';

    return s;
}

char xor_decrypt(char *s)
{
    // convert binary to int
    int ascii_int = 0;

    for (int i = 0; i < 7; i++)
    {
        int on_off = s[i] - '0';
        ascii_int += on_off * pow(2, (6 - i));
    }

    return bitwise_xor(ascii_int);
}

char *gen_code(char *msg)
{
    // intialize SC
    char *SC = malloc(sizeof(char) * 257); // add null terminating character? YES PLS DO

    int init_ones[] = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15,
                       16, 20, 27, 31,
                       32, 34, 36, 43, 45, 47,
                       48, 52, 59, 63,
                       64, 65, 66, 67, 68, 75, 76, 77, 78, 79,
                       176, 177, 178, 179, 180,
                       192, 196,
                       208, 210, 212,
                       224, 228,
                       240, 241, 242, 243, 244, 255};

    for (int i = 0; i < 256; i++)
    {
        SC[i] = '0';
    }

    for (int j = 0; j < 52; j++)
    {
        SC[init_ones[j]] = '1';
    }

    // put msg into SC
    int msg_ind = 0;
    int sc_ind = 0;

    while (msg[msg_ind] != '\0')
    {
        char *letter = xor_encrypt(msg[msg_ind]); // 7 digits in here to go through

        for (int i = 0; i < 7; i++)
        {
            sc_ind = get_next(sc_ind);
            SC[sc_ind] = letter[i];
            sc_ind++;
        }

        free(letter); //???????

        msg_ind++;
    }

    // add null terminator, \0

    char *null = xor_encrypt(msg[msg_ind]);

    for (int i = 0; i < 7; i++)
    {
        sc_ind = get_next(sc_ind);
        SC[sc_ind] = null[i];
        sc_ind++;
    }

    free(null);

    // add null terminator to SC
    SC[256] = '\0';

    return SC;
}

char *read_code(char *code)
{
    char *msg = malloc(sizeof(char) * 190); // max size

    int end = 0; // tells when end is reached
    int sc_index = 0;
    int msg_index = 0;

    while (end != 1)
    {
        char str_template[7];

        for (int i = 0; i < 7; i++)
        {
            sc_index = get_next(sc_index);
            str_template[i] = code[sc_index];
            sc_index++;
        }

        // decrypt
        char bit = xor_decrypt(str_template);

        msg[msg_index] = bit;

        msg_index++;

        // check end for null terminating character

        if (xor_decrypt(str_template) == '\0')
        {
            end = 1;
        }
    }

    msg = realloc(msg, sizeof(char) * msg_index);

    return msg;
}

char *compress(char *code)
{
    char *msg = malloc(sizeof(char) * 65);

    // go through each pair of 4 and convert to hex

    for (int i = 0; i < 64; i++)
    {
        char template[4];

        for (int j = 0; j < 4; j++)
        {
            template[j] = code[i * 4 + j];
        }

        msg[i] = get_hexidecimal(template);
    }

    msg[64] = '\0';

    return msg;
}

char *decompress(char *code)
{
    char *msg = malloc(sizeof(char) * 257);

    // go through each hex and convert to binary of 4

    for (int i = 0; i < 64; i++)
    {
        char *template = get_binary(code[i]);

        for (int j = 0; j < 4; j++)
        {
            msg[i * 4 + j] = template[j];
        }

        free(template);
    }

    msg[256] = '\0';

    return msg;
}

int calc_ld(char *sandy, char *cima)
{
    // Initialize array
    int len_s = strlen(sandy) + 1; // ROWS
    int len_c = strlen(cima) + 1;  // COLS

    int **arr = malloc(sizeof(int *) * len_s);

    for (int i = 0; i < len_s; i++)
    {
        arr[i] = malloc(sizeof(int) * len_c);
    }

    // set up first row and first column

    for (int i = 0; i < len_c; i++)
    {
        arr[0][i] = i;
    }

    for (int i = 0; i < len_s; i++)
    {
        arr[i][0] = i;
    }

    // work through inside of array going from left to right

    for (int row = 1; row < len_s; row++)
    {
        for (int col = 1; col < len_c; col++)
        {
            char a = sandy[row - 1];
            char b = cima[col - 1];

            // do comparison
            if (sandy[row - 1] == cima[col - 1]) // strcmp(splice_s, splice_c)
            {
                arr[row][col] = arr[row - 1][col - 1];
            }
            else
            {
                // find min
                int min = arr[row - 1][col - 1];

                if (arr[row - 1][col] < min)
                {
                    min = arr[row - 1][col];
                }
                if (arr[row][col - 1] < min)
                {
                    min = arr[row][col - 1];
                }

                // assign
                arr[row][col] = min + 1;
            }
        }
    }

    // store final answer

    int LD = arr[len_s - 1][len_c - 1];

    // BE VERY CAREFUL OF MEMORY MANAGEMENT | FREE

    for (int i = 0; i < len_s; i++)
    {
        free(arr[i]);
    }

    free(arr);

    // return final answer
    return LD;
}

int main()
{

    // Task 1
    printf("%d\n", bitwise_xor(67));
    char *bin_string = xor_encrypt('C');
    printf("%s\n", bin_string);
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
    printf("%d\n", calc_ld("CO", "CO"));
    printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));

    return 0;
}