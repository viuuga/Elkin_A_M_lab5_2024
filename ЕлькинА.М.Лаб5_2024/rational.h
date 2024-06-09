/*
Елькин Александр Михайлович ИВТ-11БО 2024


Реализованно задание 1

*/
// рациональная арифметика


#pragma once
#include <iostream>

class RationalFraction
{
public:
    RationalFraction(long long a = 0, long long b = 1)
        : num{ a }, den{ b }
    { }
  
    RationalFraction& operator-() { num = -num; return *this; }
    
    RationalFraction& operator+=(const RationalFraction& rh) {
        num = num * rh.den + rh.num * den;
        den *= rh.den;
        return *this;
    }
    RationalFraction& operator-=(const RationalFraction& rh) {
        num = num * rh.den - rh.num * den;
        den *= rh.den;
        return *this;
    }
    RationalFraction& operator*=(const RationalFraction& rh) {
        num *= rh.num;
        den *= rh.den;
        return *this;
    }
    RationalFraction& operator/=(const RationalFraction& rh) {
        num *= rh.den;
        den *= rh.num;
        return *this;
    }

    long long getNumerator() const { return num; }
    void setNumerator(long long new_numer) { num = new_numer; }

    long long getDenominator() const { return den; }
    void setDenominator(long long new_denom) { den = new_denom; }

    friend std::ostream& operator<< (std::ostream& out, const RationalFraction& f) {
        RationalFraction fr = f;
        fr.reduce();
        if (fr.num == 0) return out << fr.num;
        if (fr.den != 1)
            return out << fr.num << "/" << fr.den;
        else return out << fr.num;
    }

    void reduce() {
        if (num == 0) {
            den = 1;
            return;
        }
        long long mygcd = gcd(num, den);
        num /= mygcd;
        den /= mygcd;
        if (den < 0) {
            den = -den;
            num = -num;
        }
    }
    long long gcd(long long a, long long b) const {
        long long  c;
        while (b != 0) {
            c = a % b;
            a = b;
            b = c;
        }
        return a;
    }

private:
    
    long long num, den;
};

inline RationalFraction operator+(RationalFraction lh, const RationalFraction& rh)
{
    lh += rh;
    lh.reduce();
    return lh;
}

inline RationalFraction operator-(RationalFraction lh, const RationalFraction& rh)
{
    lh -= rh;
    lh.reduce();
    return lh;
}

inline RationalFraction operator*(RationalFraction lh, const RationalFraction& rh)
{
    lh *= rh;
    lh.reduce();
    return lh;
}

inline RationalFraction operator/(RationalFraction lh, const RationalFraction& rh)
{
    lh /= rh;
    lh.reduce();
    return lh;
}

inline RationalFraction operator^(RationalFraction lh, const int& rh)
{
    RationalFraction buff = lh;
    if (rh == 0) return 1;
    for (int i = 1; i < rh; ++i) {
        lh *= buff;
    }
    return lh;
}

inline bool operator==(RationalFraction lh, RationalFraction rh)
{
    lh.reduce(); rh.reduce();

    if (lh.getNumerator() == rh.getNumerator() && lh.getDenominator() == rh.getDenominator())
        return true;
    return false;
}

inline bool operator>(RationalFraction lh, RationalFraction rh)
{
    lh.reduce(); rh.reduce();

    if (lh.getDenominator() != rh.getDenominator()) {
        lh.setDenominator(rh.getDenominator() * lh.getDenominator());
        lh.setNumerator(lh.getNumerator() * rh.getDenominator());

        rh.setDenominator(rh.getDenominator() * lh.getDenominator());
        rh.setNumerator(rh.getNumerator() * lh.getDenominator());

        if (lh.getNumerator() > rh.getNumerator()) return 1;
        else return 0;
    }
    if (lh.getNumerator() > rh.getNumerator()) return 1;
    else return 0;

}

inline bool operator<(RationalFraction lh, RationalFraction rh)
{
    lh.reduce(); rh.reduce();

    if (lh.getDenominator() != rh.getDenominator()) {
        lh.setDenominator(rh.getDenominator() * lh.getDenominator());
        lh.setNumerator(lh.getNumerator() * rh.getDenominator());

        rh.setDenominator(rh.getDenominator() * lh.getDenominator());
        rh.setNumerator(rh.getNumerator() * lh.getDenominator());

        if (lh.getNumerator() < rh.getNumerator()) return 1;
        else return 0;
    }
    if (lh.getNumerator() < rh.getNumerator()) return 1;
    else return 0;

}









