// need to know how to convert between binary and hexidecimal
// how it corresponds to addresses

// logic gates
// and, or, xor, not
// (~) ??? not
// ^ is xor  --> only true iff they are different, ie. 1 xor 0 = 1,
// ex: y&y = y, depends if y is ture or not

// EACH BIT IS COMPARED AND ADDED BY LOGIC OPERATIONS, NOT THE ENTIRE THING???

// types have signed positive/negative values
// unsigned?? IMPORTANT TO DECLARE UNSIGNED VARAIBLES ---> allows for leading zeros when bit shifting
// if shifting make sure unsigned

/* MASKS

(~0b0 ^ ((~0b0)>>1)) >> n;

0b0 is all zeros, declaring thing in bits????????

gets 00000....1....0000 where 1 is placed at location n

for some x, find if nth MSB is high(ie turned on and = 1)
    - use mask

if (x & mask != 0){         // since mask is zeros everywhere but at position n, all the bits through & will be zero, only case needed to be checked is at position n, if n at x = 1, then will not be all zeros
    return 1
}

*/