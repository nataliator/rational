#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Rational
{
public:
Rational(int numerator, int denominator = 1);  
~Rational(){}
Rational(const Rational& copy);  
Rational& operator = (const Rational& other);  
Rational& operator = (int i);  

int numerator() const {return numer;}  
int denominator() const {return denom;}  

static Rational normalize(const Rational& other);  
static Rational normalized(int numerator, int denominator);  

Rational operator + (const Rational& other) const;  
Rational operator - (const Rational& other) const;  
Rational operator * (const Rational& other) const;  
Rational operator / (const Rational& other) const;  

Rational operator+() const;
Rational operator-() const;

bool operator == (const Rational& other) const;  
bool operator >= (const Rational& other) const;  
bool operator <= (const Rational& other) const;  
bool operator > (const Rational& other) const;  
bool operator < (const Rational& other) const;  

private:
int numer;
int denom;
int gcdND;

void initialize (int numerator, int denominator);

int gcd (int a, int b);  

friend std::ostream& operator<<(std::ostream&, const Rational&);  
friend std::istream& operator>>(std::istream&, Rational&);  

};

Rational operator+(const Rational& r, int i);
Rational operator+(int i, const Rational& r);

Rational operator-(const Rational& r, int i);
Rational operator-(int i, const Rational& r);

Rational operator*(const Rational& r, int i);
Rational operator*(int i, const Rational& r);

Rational operator/(const Rational& r, int i);
Rational operator/(int i, const Rational& r);

#endif
