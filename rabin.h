#ifndef RABIN_H
#define RABIN_H

#include <QObject>
#include <tuple>


namespace rb {

class Rabin
{
public:
    Rabin();
    bool processValues(QString pText, QString qText, QString bText);
    bool encode(QString FileName);
    bool decode(QString FileName);

private:
    bool isPrime(int number);
    bool mod4(int number);
    long unsigned powMod(long unsigned int b,long unsigned int e,long unsigned int m);
    bool checkCond(unsigned int p,unsigned  int q,long unsigned  int b);
    std::tuple<long unsigned int, long unsigned int> gcdex(unsigned int a, unsigned int b);
    long unsigned encodeByte(unsigned char c);
    unsigned char decodeByte(unsigned c);

    unsigned int _q;
    unsigned int _p;
    long unsigned int _b;
    long unsigned int _n;
};
}
#endif // RABIN_H
