/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    n = n << 3;
    return (x >> n) & 0xff;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
    // (x, 0) is corner case
    int mask  = ~(1 << 31 >> n << 1);
    return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int mask_1, mask_2, mask_4, mask_8, mask_16;
    mask_1 = 0x55 | ( 0x55 << 8);
    mask_1 = mask_1 | ( mask_1 << 16);
    mask_2 = 0x33 | ( 0x33 << 8);
    mask_2 = mask_2 | (mask_2 << 16);
    mask_4 = 0x0f | ( 0x0f << 8);
    mask_4 = mask_4 | ( mask_4 << 16);
    mask_8 = 0xff | (0xff << 16);
    mask_16 = 0xff | (0xff << 8);
    // printf("mask_1:%x, mask_2:%x, mask_4:%x, mask_8:%x, mask_16:%x \n", mask_1 ,mask_2 ,mask_4 ,mask_8 ,mask_16);
    x = (x & mask_1) + ((x >> 1) & mask_1);
    x = (x & mask_2) + ((x >> 2) & mask_2);
    x = (x & mask_4) + ((x >> 4) & mask_4);
    x = (x & mask_8) + ((x >> 8) & mask_8);
    x = (x & mask_16) + ((x >> 16) & mask_16);
    return x;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    // 0xffffffff is a corner case, which will cause overflow by using (x | -x)
    // MSB of (x | -x) is 0 when x is not 0
    // printf("%d\n", ~x + 1);
    return (~((~x + 1) | x) >> 31) & 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    // 10000000
    return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int m;
    m = 33 + ~n;
    return !((x << m >> m) ^ x);
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    // 10 >> 1 = 1, 11 >> 1 = 1
    // 01111 >> 1 = 0111
    // -33 = 0b1011111 >> 4 = 0b1111101 = 1 + 4 + 8 + 16 + 32 - 64 = -3
    // -4 = 0b100 >> 2 = -1 = 0b1
    // -5 = 0b1011 >> 1 = 0b101 = -3
    //  1 + 2 + 4 + 8 + 16 = 31, 64 - 31 = 33
    int mask = (1 << n) + ~0;
    int bias = mask & (x >> 31);
    return (x + bias) >> n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // corner case is 0
    return (x >> 31 & 1) ^ 1 ^ !x;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int signx=x >> 31 & 1;
    int signy=y >> 31 & 1;
    int signSame=((x + (~y)) >> 31) & (!(signx ^ signy));
    int signDiffer = signx & (!signy);
    return signDiffer | signSame;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int mask_1, mask_2, mask_4, mask_8, mask_16, index = x;
    // find the index of the first 1 in x by pass MSB to end
    // suppose x = 0b00010100010111001111
    // x >> 1 =       00010100010111001111
    // x >> 1 | x =  00011110011111101111
    // x >> 2 =        00011110011111101111
    // x >> 2 | x =  00011111111111111111
    // ...
    // count the number of 1 which is the index of the first 1 in x
    index = index | (index >> 1);
    index = index | (index >> 2);
    index = index | (index >> 4);
    index = index | (index >> 8);
    index = index | (index >> 16);
    mask_1 = 0x55 | ( 0x55 << 8);
    mask_1 = mask_1 | ( mask_1 << 16);
    mask_2 = 0x33 | ( 0x33 << 8);
    mask_2 = mask_2 | (mask_2 << 16);
    mask_4 = 0x0f | ( 0x0f << 8);
    mask_4 = mask_4 | ( mask_4 << 16);
    mask_8 = 0xff | (0xff << 16);
    mask_16 = 0xff | (0xff << 8);
    index = (index & mask_1) + ((index >> 1) & mask_1);
    index = (index & mask_2) + ((index >> 2) & mask_2);
    index = (index & mask_4) + ((index >> 4) & mask_4);
    index = (index & mask_8) + ((index >> 8) & mask_8);
    index = (index & mask_16) + ((index >> 16) & mask_16);
    return index + ~0;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    // NaN
    if (!(uf >> 23 & 0xff ^ 0xff) && ((uf & 0x7fffff) ^ 0))
        return uf;
    // toggle the MSB
    return uf ^ 0x80000000;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    // int 16 = 0x10 = 1.0*2^1=> float 0
    // int -16 = 0xffffff0f
    /*
    int frac, exp;
    int sign = x >> 31 & 1;
    // get the bit of...
    int i = 0;
    printf("x: %d\n", x);
    if ( x == 0)
        return 0;
    printf("sign: %d\n", sign);
    // this method will cause negative overflow
    if (x < 0) {
        // negative
        x = -x;
    }
    printf("x: %d\n", x);
    //
    while ((x >> i) ^ 0) {
        i++;
    }
    frac = x & 0x7fffff;
    exp = (127 + i) & 0xff;
    printf("sign: %d\n, i: %d\n, frac: %d, exp: %d", sign, i, frac, exp);
    return (sign << 31) | (exp << 23) | frac;
    */
    unsigned shiftLeft=0;
    unsigned afterShift, tmp, flag;
    unsigned absX=x;
    unsigned sign=0;
    //special case
    if (x==0) return 0;
    //if x < 0, sign = 1000...,abs_x = -x
    if (x<0)
    {
        sign=0x80000000;
        absX=-x;
    }
    afterShift=absX;
    //count shift_left and after_shift
    while (1)
    {
        tmp=afterShift;
        afterShift <<= 1;
        shiftLeft++;
        if (tmp & 0x80000000) break;
    }

    if ((afterShift & 0x01ff) > 0x0100)
        flag = 1;
    else if ((afterShift & 0x03ff) == 0x0300)
        flag=1;
    else
        flag=0;

    return sign + (afterShift>>9) + ((159-shiftLeft)<<23) + flag;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    // for normalized number, just add 1 to exponent, note infinite number
    // for denormalized number, just << 1
    int sign = uf & 0x80000000;
    int exp = uf & 0x7f800000;
    int frac = uf & 0x7fffff;
    // denormalized number
//    printf("sign:%d, exp:%0x, frac:%d\n", sign , exp, frac);
    if (exp == 0) { return sign | (uf << 1);}
    else if (exp == 0x7f000000) {
        // exp = 1111 1110
        return sign | 0x7f800000;
    } else if (exp != 0x7f000000 && exp != 0x7f800000) {

        return sign + (exp + 0x800000) + frac;
    }
    return uf;
}
