#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "codec64.h"
#include <random>

using namespace std;

//=============================================================================
// bool isPrime(uint64_t n)
//   determine if n is prime
//
// Parameter
//   n - number to test for primality
//
// Returns
//   true if n is prime, false if n is not prime
//

bool isPrime(uint64_t n) {

    // if n is less than 2, then it is not prime
    if (n < 2)
        return false;

    // if n is 2, then n is prime
    if (n == 2)
        return true;

    // if n is even, then n is not prime
    if (n % 2 == 0)
        return false;

    // check all odd integers in the range 3 <= f <= sqrt(n)
    // if any of them is a factor of n, then n is not prime
    //
    // note how the check avoids using sqrt()... faster and more accurate
    for (uint64_t f=3;f*f<=n;f+=2) {
        if (n % f == 0)
            return false;
    }
    // if no odd integer in the range 3 <= f <= sqrt(n) is a factor of n,
    // then n is prime
    return true;
}

//=============================================================================
// int64_t modInverse(int64_t a,int64_t n)
//   Calculate c such that (a*c) % n == 1
//
// Parameters
//   a - number to be inverted
//   n - modulus for modular inverse. Must not be zero.
//
// Returns
//   c such that (a * c) % n == 1, if such c exists
//   -1 if no such c value exists, see below
//
// Notes
// - c exists if and only if gcd(a,n) == 1. This is checked.
//
// - See https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Modular_integers
//   for more information
//

int64_t modInverse(int64_t a,int64_t n) {
    int64_t
        t,tNew,
        r,rNew,
        q,tmp;

    // t := 0;     newt := 1
    t = 0;
    tNew = 1;

    // r := n;     newr := a
    r = n;
    rNew = a;

    // note: this loop is also used to find gcd
    // while newr ≠ 0 do
    while (rNew != 0) {
        // quotient := r div newr
        q = r / rNew;

        // this is parallel assignment. Most languages do not support this
        // (Python does). To implement, we use a method similar to the three-
        // line swap.

        // (t, newt) := (newt, t − quotient × newt)
        tmp = tNew;
        tNew = t - q * tNew;
        t = tmp;

        // (r, newr) := (newr, r − quotient × newr)
        tmp = rNew;
        rNew = r - q * rNew;
        r = tmp;
    }

    // r is the gcd if a and n. Must be 1 or no inverse exists
    // if r > 1 then
    if (r > 1)
        // return "a is not invertible"
        return -1;

    // t is the inverse. However, it might be negative. If so, adding n
    // makes it positive, and maintains the property that (a * t) % n == 1
    // if t < 0 then
    if (t < 0)
        // t := t + n
        t += n;

    // return t
    return t;
}

//=============================================================================
// uint64_t modExp(uint64_t base,uint64_t exp,uint64_t mod)
//   Calculate (base ^ exp) % mod
//
// Parameters
//   base - number to raise to a power
//   exp  - power to which base is raised
//   mod  - modulus
//
// Notes
// - uses repeated squaring, as it is the only method that is (a) efficient
//   and (b) accurate
//

uint64_t modExp(uint64_t base,uint64_t exp,uint64_t mod) {

    // ans = 1
    int ans = 1;
    // while exp != 0 {
        while (exp !=0)
        {
        // if exp is odd
        if (exp % 2 != 0)
            // ans = (ans * base) % mod
            ans = (ans * base) % mod;
        // base = (base * base) % mod
        base = (base * base) % mod;
        // exp = exp / 2
        exp = exp / 2;
        }
    return ans;
    // return ans
}

//=============================================================================
// int64_t getFileSize(char *fn)
//   Obtain the size of a file
//
// Parameter
//   fn - C string containing the file name (with path if necessary)
//
// Returns
//   File size, in bytes
//
//
// Notes
// - uses the stat() system call to obtain file information
//

int64_t getFileSize(char *fn) {
    struct stat
        fs{};

    // use the stat() system call to fill in information structure
    stat(fn,&fs);

    // return the size field
    return fs.st_size;
}

//=============================================================================
// void keyGen()
//   generate random key pair
//
// Notes:
// - key pair is displayed, not returned
//

void keyGen() {
    // do loop
    uint32_t
        p, q, e, n, f, d;
    random_device
            rd;
    mt19937
            mt(rd());
    uniform_int_distribution
            dis1(4096,65535);

    do {
        //choose random number P WITH 4096 <= P <= 65535
        p = dis1(mt);
    // while p not prime
    } while (!isPrime(p));


    //do
    do {
        //choose random q with 4096 <= q <= 65535
        q = dis1(mt);
        // while q not prime or p == q
    } while (q == p || !isPrime(q));
    //calculate n = p * q
    n = q * p;
    //calculate f = (p-1) * (q-1)
    f = (p-1) * (q-1);
    //do
    do {
        //Choose random e with 4096 <= 3 <= 65596
        e = dis1(mt);
        // while gcd(e,f) != 1
    } while (gcd(e, f) != 1);
    //compute d such that (d * e)%f == 1
    d = modInverse(e, f);
    //output public key n, e
    cout << "Public key: " << n << ' ' << e << endl;
    //output private key n, d
    cout << "Private key: " << n << ' ' << d << endl;
}

//=============================================================================
// void encrypt(char *inFileName,char *outFileName,int64_t n,int64_t e)
//   Encrypt a file
//
// Parameters
//   inFileName  - name of file to be encrypted
//   outFileName - name of encrypted file
//   n,e         - two numbers that form the public key
//

void encrypt(char *inFileName,char *outFileName,int64_t n,int64_t e) {
    char
        c1,
        c2,
        c3;
    uint32_t
        m,
        M,
        fileSize;
    ifstream
            fileEncrypt;
    Codec64
            myCodec;
    // open input file and make sure it worked
    fileEncrypt.open(inFileName);
    if(!fileEncrypt)
    {
        cout << "Could not open the specified file" << endl;
        exit(1);
    }
    // prepare codec for output
    myCodec.beginEncode(outFileName);
    // get input file size and send to codec
    fileSize = getFileSize(inFileName);
    myCodec.put32(getFileSize(inFileName));
    // loop over all bytes in file, count by 3
    for(int filePlace = 0; filePlace < fileSize; filePlace+=3) {
        //Read 3 bytes from file (use 0 if bytes unavailable)
        fileEncrypt.get(c1);
        if(filePlace+1 < fileSize) {
            fileEncrypt.get(c2);
        } else {
            c2 = 0;
        }
        if(filePlace+2 < fileSize) {
            fileEncrypt.get(c3);
        } else {
            c3 = 0;
        }
        //combine bytes into single value m
        m = c1 + 256 * c2 + 65536 * c3;
        //use modExp to calculate M = (m ^ e) % n
        M = modExp(m, e, n);
        //Feed M to codec
        myCodec.put32(M);
        // End loop
    }
    //Tell codec we're done
    myCodec.endEncode();
    //Close input file
    fileEncrypt.close();
}

//=============================================================================
// void decrypt(char *inFileName,char *outFileName,int64_t n,int64_t d)
//   Decrypt a file
//
// Parameters
//   inFileName  - name of file to be decrypted
//   outFileName - name of decrypted file
//   n,d         - two numbers that form the private key
//

void decrypt(char *inFileName,char *outFileName,int64_t n,int64_t d) {
    uint32_t
        M,
        m,
        fileSize;
    char
        c1,
        c2,
        c3;
    ofstream
        fileDecrypt;
    Codec64
        myCodec;
    //open output file and make sure it worked

    fileDecrypt.open(outFileName);
    if(!outFileName) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    // prepare codec for decoding
    myCodec.beginDecode(inFileName);
    // get files size from file
    fileSize = myCodec.get32();
    // loop over all bytes in file, count by 3
    for(int filePlace = 0; filePlace < fileSize; filePlace+=3) {
        //get M from codec
        M = myCodec.get32();
        // use modExp to calc m = (M^d) % n
        m = modExp(M, d, n);
        //split m into 3 bytes
        c1 = m%256;
        m /= 256;
        c2 = m % 256;
        m /= 256;
        c3 = m%256;
        // output bytes (if needed)
        fileDecrypt << c1;
        if (filePlace + 1 < fileSize)
        {
            fileDecrypt << c2;
        }
        if (filePlace + 2 < fileSize)
        {
            fileDecrypt << c3;
        }
        //End loop
    }
    //Tell codec we're done
    myCodec.endDecode();
    //Close output
    fileDecrypt.close();
}

//=============================================================================
// void usage(char *pgmName)
//   Display usage message and stop program
//
// Parameter
//   pgmName - C-string holding program name (argv[0] from main)
//

void usage(char *pgmName) {

    cout << "Usage: " << pgmName << " -k" << endl;
    cout << "       " << pgmName << " -e n e inFileName outFileName" << endl;
    cout << "       " << pgmName << " -d n d inFileName outFileName" << endl;

    exit(1);
}

//=============================================================================
// int main(int argc,char *argv[])
//   process user options and call appropriate function
//
// Parameters
//   argc - number of command line arguments
//   argv - array of C-strings, each holding one command line argument
//
// Returns
//   0 if program ran successfully, 1 if an error was encountered
//

int main(int argc,char *argv[]) {
    int64_t
        d,e,n;  // values for encrypting or decrypting

    // if less than 2 parameters, bail
    if (argc < 2)
        usage(argv[0]);

    // if second string, first char is not -, bail
    if (argv[1][0] != '-')
        usage(argv[0]);

    // second string should only have two characters
    if (argv[1][2] != 0)
        usage(argv[0]);

    // if second string, second char is k, generate key pair
    if (argv[1][1] == 'k') {
        // make sure no more command line parameters
        if (argc != 2)
            usage(argv[0]);

        // call the key generation function
        keyGen();

    // if second string, second char is e, encrypt a file
    } else if (argv[1][1] == 'e') {
        // make sure there are six command line parameters
        if (argc != 6)
            usage(argv[0]);

        // convert n and e into text
        n = strtoll(argv[2], nullptr, 10);
        e = strtoll(argv[3], nullptr, 10);

        // call encryption function
        encrypt(argv[4],argv[5],n,e);

    // if second string, second char is d, decrypt a file
    } else if (argv[1][1] == 'd') {
        // make sure there are six command line parameters
        if (argc != 6)
            usage(argv[0]);

        // convert n and e into text
        n = strtoll(argv[2], nullptr, 10);
        d = strtoll(argv[3], nullptr, 10);

        // call decryption function
        decrypt(argv[4],argv[5],n,d);

    // otherwise, option is invalid, bail
    } else
        usage(argv[0]);

    return 0;
}
