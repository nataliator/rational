#include<iostream>
#include"rational.h"
using namespace std;


class MyException : public exception{
     public:
     const char* what() const noexcept {return "Denominator cannot be zero";}
     
 };



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

int Rational::gcd(int a, int b)
{
    //cout << a << "GCD" << b << endl;
    // Everything divides 0
    if (a == 0)
       return b;
    if (b == 0)
       return a;

    // We look at absolute values of a and b only
    if (a < 0) a = -1 * a;
    if (b < 0) b = -1 * b;
  
    // base case
    if (a == b)
        return a;
  
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

Rational& Rational::operator = (int i){
    this->numer = i;
    this->denom = 1;
    this->gcdND = 1;
    return *this;
};

Rational Rational::normalize(const Rational& other)
{  
    int new_numerator = other.numer/other.gcdND;
    int new_denominator = other.denom/other.gcdND;

    if (new_denominator < 0) {
        new_denominator = -1 * new_denominator;
        new_numerator = -1 * new_numerator;
    }

    Rational result(new_numerator, new_denominator);
    return result;
};


Rational Rational::normalized(int numerator, int denominator){
Rational nowy(numerator, denominator);
return Rational::normalize(nowy);
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
    return r +i_rat;
}
Rational operator+(int i, const Rational& r){
    Rational i_rat(i,1);
    return r +i_rat;
}

Rational operator-(const Rational& r, int i){
    Rational i_rat(i,1);
    return r - i_rat;
}
Rational operator-(int i, const Rational& r)
{
    Rational i_rat(i,1);
    return i_rat - r;
}
Rational operator*(const Rational& r, int i){
    Rational i_rat(i,1);
    return r * i_rat;
}

Rational operator*(int i, const Rational& r){
    Rational i_rat(i,1);
    return r * i_rat;
}

Rational operator/(const Rational& r, int i){
    Rational i_rat(i,1);
    return r / i_rat;
}

Rational operator/(int i, const Rational& r){
    Rational i_rat(i,1);
    return i_rat / r;
}

// END OF IMPLEMENTATION

int test1(){
    Rational ts(3,-4);
    cout << ts.numerator() << "/" << ts.denominator() << endl;
    return 1;
}

int test2(){
    Rational ts(4,5);
    Rational ty(ts);
    cout << ty.numerator() << "/" << ty.denominator() << endl;
    return 1;
}

int test3(){
    Rational ts(5,6);
    Rational ty = ts;
    cout << ty.numerator() << "/" << ty.denominator() << endl;
    return 1;
}

int test4(){
    Rational ty(7);
    cout << ty.numerator() << "/" << ty.denominator() << endl;
    return 1;
}

int test5(){
    Rational ts(7,8);
    Rational ty = Rational::normalize(ts);
    cout << ty.numerator() << "/" << ty.denominator() << endl;
    return 1;
}

int test6(){
    Rational ty = Rational::normalized(8,9);
    cout << ty.numerator() << "/" << ty.denominator() << endl;
    return 1;
}

int test7(){
    Rational ts(1,2);
    Rational tx(2,5);
    Rational ty = ts + tx;
    cout << ty.numerator() << "+/+" << ty.denominator() << endl;
    return 1;
}

int test8(){
    Rational ts(21,22);
    Rational tx(1,22);
    Rational ty = ts - tx;
    cout << ty.numerator() << "-/-" << ty.denominator() << endl;
    return 1;
}

int test9(){
    Rational ts(5,3);
    Rational tx(2,4);
    Rational ty = ts * tx;
    cout << ty.numerator() << "*/*" << ty.denominator() << endl;
    return 1;
}

int test10(){
    Rational ts(5,3);
    Rational tx(2,4);
    Rational ty = ts / tx;
    cout << ty.numerator() << ":/:" << ty.denominator() << endl;
    return 1;
}

int test10a(){
    Rational ts(5,3);
    Rational tx(0,4);
    Rational ty = ts / tx;
    cout << ty.numerator() << ":/:" << ty.denominator() << endl;
    return 1;
}

int test11(){
    Rational ty(5,3);
    Rational tx(10,6);
    if (tx == ty) cout << "Equality true" << endl; else  cout << "Equality false" << endl;
    return 1;
}

int test12(){
    Rational ty(6,3);
    Rational tx(10,6);
    if (tx == ty) cout << "Equality true" << endl; else cout << "Equality false" << endl;
    return 1;
}

int test13(){
    cout << "test 13" << endl;
    Rational ts(-12,13);
    cout << -ts.numerator() << "/" << -ts.denominator() << endl;
    return 1;
}

int test14(){
    Rational ty(6,3);
    Rational tx(10,6);
    if (ty > tx) cout << "Inequality true" << endl; else cout << "Test failed" << endl;
    return 1;
}

int test15(){
    Rational ty(4,3);
    Rational tx(10,6);
    if (ty < tx) cout << "Inequality true" << endl; else cout << "Test failed" << endl;
    return 1;
}
int test16(){
    Rational ty(6,3);
    Rational tx(10,6);
    if (ty >= tx) cout << "(In)equality true" << endl; else cout << "Test failed" << endl;
    return 1;
}

int test17(){
    Rational ty(4,3);
    Rational tx(10,6);
    if (ty <= tx) cout << "(In)equality true" << endl; else cout << "Test failed" << endl;
    return 1;
}

int test18(){
    Rational ty(6,3);
    Rational tx(12,6);
    if (ty >= tx) cout << "(In)equality true" << endl; else cout << "Test failed" << endl;
    return 1;
}

int test19(){
    Rational ty(4,3);
    Rational tx(8,6);
    if (ty <= tx) cout << "(In)equality true" << endl; else cout << "Test failed" << endl;
    return 1;
}

int test20(){
    Rational ty(4,3);
    cin >> ty ;
    cout << "Entered value: " <<ty << endl;
    return 1;
}

int test21(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = ts + 7;
    cout << "Po operacji + "<< ty << endl;
    return 1;
}

int test22(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = 7 + ts;
    cout << "Po operacji + "<< ty << endl;
    return 1;
}

int test23(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = 7 - ts;
    cout << "Po operacji - "<< ty << endl;
    return 1;
}

int test24(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = ts - 7;
    cout << "Po operacji - "<< ty << endl;
    return 1;
}

int test25(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = ts * 7;
    cout << "Po operacji * "<< ty << endl;
    return 1;
}

int test26(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = 7 * ts;
    cout << "Po operacji * "<< ty << endl;
    return 1;
}

int test27(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = ts / 7;
    cout << "Po operacji / "<< ty << endl;
    return 1;
}

int test28(){
    Rational ts(1,2);
    cout << "Przed operacja "<< ts << endl;
    Rational ty = 7 / ts;
    cout << "Po operacji / "<< ty << endl;
    return 1;
}

int main(){


    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test21();
    test22();
    test23();
    test24();
    test25();
    test26();
    test27();
    test28();
    cout <<"U mnie dziala" << endl;

    Rational r2(2, 11), r3(1, -3), r5(18, 6);
    Rational res1 = 3 + r2 * r3;
    Rational res2 = (3 + r2) * r3;
    Rational res3 = 3 + r3 * (r2 + 2)/(r5 - r3);

    cout << 3 << " + "<< r2 << " * " << r3 <<" = " << res1 << endl;
    cout << "(" << 3 << " + " << r2 << ")" << " * " << r3 << " = " << res2 << endl;
    cout << 3 << " + " << r3 << " * " << "(" << r2 << " + " << 2 << ")" << "/" << "(" << r5 << " - " << r3 << ")" << " = " << res3 << endl;



    try{
        Rational r1(1,0);
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
}
