#include "rabin.h"
#include "QtCore"
#include <QFile>
#include <QByteArray>


namespace rb{
Rabin::Rabin() {}


bool Rabin::processValues(QString pText, QString qText, QString bText){
    bool okQ,okP,okB;
    int q = qText.toInt(&okQ);
    int p = pText.toInt(&okP);
    int b = bText.toInt(&okB);
    if (okP && okQ && okB){

        if (checkCond(q,p,b)){
            _q = q;
            _p = p;
            _n = p * q;
            _b = b;
            return true;
        }

    }
    return false;
    }



bool Rabin::isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

bool Rabin::encode(QString FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray fileData = file.readAll();
    file.close();

    file.setFileName("temp.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream out(&file);

    for (int i = 0; i < fileData.size(); ++i) {
        unsigned char currentByte = fileData.at(i);
        out <<encodeByte(currentByte)<< " ";
    }
    file.close();
    return true;
}


std::tuple<long unsigned int, long unsigned int> Rabin::gcdex(unsigned int a, unsigned int b) {
    if (b == 0) return std::make_tuple(1, 0);

    auto [x, y] = gcdex(b, a % b);

    return std::make_tuple(y, x - (a / b) * y);
}


bool Rabin::decode(QString FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    QStringList words;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList lineWords = line.split(" ", Qt::SkipEmptyParts);
        words.append(lineWords);
    }
    file.close();


    QFile file1("result.txt");
    if (file1.open(QIODevice::WriteOnly)) {
        for (int i = 0; i < words.size(); ++i) {
            char byte = decodeByte(words.at(i).toInt());
            file1.write(&byte, 1);
        }
        file1.close();
    }
    return true;
}



long unsigned Rabin::encodeByte(unsigned char c){
    return (c*(c + _b)) % _n;
}


unsigned char Rabin::decodeByte(unsigned c){
    const long unsigned  int D = (_b*_b+4*c) % _n;

    const long int  mp = powMod(D, (_p + 1) / 4, _p);
    const long int mq = powMod(D, (_q + 1) / 4,_q);

    long  int yp,yq;
    std::tie(yp, yq) = gcdex(_p, _q);
    long int di[4] = {0};

    di[0] = (yp * _p * mq + yq * _q * mp) % _n;
    di[1] = _n - di[0];
    di[2] = (yp * _p * mq - yq * _q * mp) % _n;
    di[3] = _n - di[2];

    long int mi[4] = {0};

    for (int j = 0; j < 4; ++j) {
        if ((di[j] - _b) % 2 == 0) {
            mi[j] = ((-_b + di[j]) / 2) % _n;
        } else {
            mi[j] = ((-_b + _n + di[j]) / 2) % _n;
        }

        if (mi[j] < 256) {
            return  mi[j];
        }
    }

    return 0;
}


bool Rabin::mod4(int number){
    if (number % 4 == 3) return true;
    return false;
}

long unsigned int Rabin::powMod(long unsigned int b,long unsigned int e,long unsigned int m){
    unsigned result = 1;
    b %= m;

    while (e > 0) {
        if (e % 2 != 0) result = (result * b) % m;
        e = e / 2;
        b = (b * b) % m;
    }

    return result;
}

bool Rabin::checkCond(unsigned int p,unsigned  int q,long unsigned  int b){
    if (p > 65536 || q > 65536) return false;
    return (isPrime(p) && isPrime(q) && mod4(p) && mod4(q) && (b<p*q));
}
}

