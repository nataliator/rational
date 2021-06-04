#include<iostream>
#include <cmath>
#include"rational.h"
#include <numeric>
using namespace std;


class MyException : public exception{
     public:
     const char* what() const noexcept {return "Denominator cannot be zero";}
     
 };
/*
 double isDenomZero(int denominator) noexcept (false)
 {
     if (denominator == 0){
         throw MyException{};
         }else{
             return denominator;
         };
 }

 void errorHandling()
 {

     cout << "errorHandling()..." << endl;
     try{
         cout << "isDenomZero(0) = " << isDenomZero(0) << endl;

     }
     catch (const MyException &e)
     {

         cout << "An exception (" << e.what() << ") was thrown, but was caught here " << endl;
     }
     catch(...)
     {
         cout <<" Default exception handler caught an exception" << endl;
     }
 }*/


Rational::Rational(int numerator, int denominator ):numer{numerator},denom{denominator}{
    gcdND=gcd(numerator, denominator);
    if (denominator == 0) throw MyException{};
};


Rational::Rational(const Rational& copy) : numer{copy.numer}, denom{copy.denom}, gcdND{copy.gcdND}{};


Rational& Rational::operator = (const Rational& other){
    if (&other != this){
    this->numer = other.numer;
    this->denom = other.denom;
    this->gcdND = other.gcdND;
    }

    return *this;
}


Rational& Rational::operator = (int i){
    this->numer = i;
    this->denom = 1;
    this->gcdND = 1;
    return *this;
};

Rational Rational::normalize(const Rational& other)
{  
    std::cout<<"normalizing\n";
    int new_numerator = other.numer/other.gcdND;
    int new_denominator = other.denom/other.gcdND;
    Rational result(new_numerator, new_denominator);
    return result;
/*    Rational res=1;
   if(this->gcdND==1){
     res=*this;
   }else{
    res.numer=(this->numer)/(this->gcdND);
    res.denom=(this->denom)/(this->gcdND);
    res.gcdND= (this->gcdND)/(this->gcdND);
   }
    return res;*/
};

Rational Rational::normalized(int numerator, int denominator){
Rational nowy(numerator, denominator);
return Rational::normalize(nowy);
}

int Rational::gcd(int a, int b)
{
    // Everything divides 0
    if (a == 0)
       return b;
    if (b == 0)
       return a;
  
    // base case
    if (a == b)
        return a;
  
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

Rational Rational::operator + (const Rational& other) const{
    Rational res(1);
    Rational temp=*this;
    Rational tempO=other;

    tempO.numer*=this->denom;
    tempO.denom*=this->denom;
    temp.numer*=other.denom;
    temp.denom*=other.denom;

    res.denom=temp.denom;
    res.numer=temp.numer+tempO.numer;
    res.gcdND=res.gcd(res.numer, res.denom);
   // res.normalize();
    return Rational::normalize(res);
}

Rational Rational::operator - (const Rational& other) const{
    Rational res=1;
    Rational temp=*this;
    Rational tempO=other;

    tempO.numer*=this->denom;
    tempO.denom*=this->denom;
    temp.numer*=other.denom;
    temp.denom*=other.denom;
    
    res.denom=temp.denom;
    res.numer=temp.numer-tempO.numer;
    res.gcdND=res.gcd(res.numer, res.denom);
   // res.normalize();
    return Rational::normalize(res);
}

Rational Rational::operator * (const Rational& other) const{
Rational temp=*this;    
int new_numerator = temp.numer * other.numer;
int new_denominator = temp.denom * other.denom;

return Rational::normalized(new_numerator, new_denominator);
}


Rational Rational::operator / (const Rational& other) const{
Rational temp=*this;    
int new_numerator = temp.numer * other.denom;
int new_denominator = temp.denom * other.numer;

return Rational::normalized(new_numerator, new_denominator);
}

Rational Rational::operator+() const{return *this;}

Rational Rational::operator-() const{
    Rational temp=*this; 
    Rational result((-1)*temp.numer, temp.denom);
    return result;}

bool Rational::operator == (const Rational& other) const{
    Rational norm_left = Rational::normalize(*this);
    Rational norm_right = Rational::normalize(other);

    return (norm_left.numer == norm_right.numer) && (norm_left.denom == norm_right.denom);
}


bool Rational::operator > (const Rational& other) const {
   Rational  bigger_rational = Rational::normalize(*this);
   Rational smaller_rational = Rational::normalize(other);
   int bigger_int = bigger_rational.numer * smaller_rational.denom;
   int smaller_int = bigger_rational.denom * smaller_rational.numer; 
   return bigger_int > smaller_int;
}
bool Rational::operator < (const Rational& other) const {return other > *this;}
bool Rational::operator >= (const Rational& other) const  {return !(*this < other);}
bool Rational::operator <= (const Rational& other) const {return !(*this > other);}



ostream& operator<<(ostream& os, const Rational& fraction)
{
    os << "(" << fraction.numer << "/" << fraction.denom<< ")";
    return os;
}


istream& operator >> (istream &is,  Rational &fraction)
{   int denominator;
    cout << "numerator = ";
    is >> fraction.numer;
    cout << "denominator = ";
    is >> denominator;
     if (denominator == 0){
         throw MyException{};
         }else{
             fraction.denom=denominator;
             fraction.gcdND=fraction.gcd(fraction.numer, denominator);
         };
    
    return is;
}

Rational operator+(const Rational& r, int i) {
    Rational i_rat(i,1);
    return r +i;
}
Rational operator+(int i, const Rational& r){
    Rational i_rat(i,1);
    return r +i;
}

Rational operator-(const Rational& r, int i){
    Rational i_rat(i,1);
    return r - i;
}
Rational operator-(int i, const Rational& r)
{
    Rational i_rat(i,1);
    return i - r;
}
Rational operator*(const Rational& r, int i){
    Rational i_rat(i,1);
    return r * i;
}

Rational operator*(int i, const Rational& r){
    Rational i_rat(i,1);
    return r * i;
}

Rational operator/(const Rational& r, int i){
    Rational i_rat(i,1);
    return r / i;
}

Rational operator/(int i, const Rational& r){
    Rational i_rat(i,1);
    return i / r;
}

int main(){

    //Rational r2( int numerator, int denumerator);

    cout <<"U mnie dziala" << endl;

  //  cin >> r2(2,11);
   // Rational r2(2, 11)//, r3(1, -3), r5(18, 6);
   // Rational res1 = 3 + r2;//
  //  Rational res2 = (3 + r2) * r3;
   // Rational res3 = 3 + r3 * (r2 + 2)/(r5 - r3);
  //  cout << 3 << " + "<< r2 <<" = " << res1 << endl;
   // cout << 3 << " + "<< r2 <<" * " << r3 << " = " << res1 << endl;
   // cout << "(" << 3 << " + " << r2 << ")" << " * " << r3 << " = " << res2 << endl;
   // cout << 3 << " + " << r3 << " * " << "(" << r2 << " + " << 2 << ")" << "/" << "(" << r5 << " - " << r3 << ")" << " = " << res3 << endl;



 /*Rational r1(2);
    Rational r2(r1);
    try{
      cin>>r1;  
    }
     catch (const MyException &e)
     {

         cout << "An exception (" << e.what() << ") was thrown, but was caught here " << endl;
     }
     catch(...)
     {
         cout <<" Default exception handler caught an exception" << endl;
     }
    //cin>>r1; 
    Rational rn(r1);
    //cout<<"normalize"<<r1.normalize();
    cout << r1<< endl;
    Rational* pr;
    pr= &r1;pr->denominator();
    
    r1.denominator();
    r2.denominator();
    Rational r3(1,2);
    r2 = r3; cout<<"sum "<<r2+r3;*/

}

//return 1;
//};

