#include <iostream>
#include <vector>
using namespace std;

class MyVec;
class Student;
class Inst;
class Static;
//Question 0
class MyVec{
public:
  MyVec();
  MyVec(int n);
  MyVec(int n, double x);
  MyVec(const MyVec &m);
  MyVec& operator=(const MyVec &m);
  ~MyVec();
  int size() const;
  
  void push_back(double x);

  double operator[] (int i) const;
  double& operator[] (int i);

private:

  double *a;
  int len;
  void init(double x);
  void copy(const MyVec &m);
  void dealloc();

//Question 1:
  bool isEmpty() const{
    if (len==0)return true;
    else return false;
  }
  //const here is necessary as it promises the compiler that the object will not be changed.
};

//Question 2:
MyVec operator+(const MyVec &a, const MyVec &b){
  MyVec temp = a;
  for(int i=0; i<b.size(); i++){
    temp.push_back(b[i]);
  }
  return temp;
}
//declaring the 2 inputs as const is necessary becuase we do not want to change those objects when adding them. 

MyVec:: MyVec(){
  len = 0;
  a = NULL;
}
MyVec:: MyVec(int n){
  if (n<=0){
    len = 0;
    a = NULL;
  }
  else{
    len = n;
    a = new double[len];
    init(0.0);
  }
}
MyVec:: MyVec(int n, double x){
  if (n<=0){
    len = 0;
    a = NULL;
  }
  else{
    len = n;
    a = new double[len];
    init(x);
  }
}
MyVec:: MyVec(const MyVec &m){
  if (m.len<=0){
    len=0;
    a=NULL;
    }
  else{
    len=m.len;
    a= new double[len];
    copy(m);
  }
} 
MyVec& MyVec:: operator=(const MyVec &m){
  if (this==&m) return *this;
  if (m.len<=0){
    len=0;
    delete[] a;
    a=NULL;
  }
  else{
    len=m.len;
    delete[] a;
    a = new double[len];
    copy(m);
  }
  return *this;
}
MyVec:: ~MyVec(){
  this->dealloc();
}
int MyVec:: size() const{
  return len;
}
double MyVec:: operator[] (int i) const{
  if(i>=0 && i<len) return a[i];
  else return 0.0;
}
double& MyVec:: operator[] (int i){
  if(i>=0 && i<len) return a[i];
  else  return *(double*)nullptr;
}
void MyVec:: init(double x){
  for(int i=0; i<len; i++)
    a[i] = x;
}
void MyVec:: copy(const MyVec &m){
  for(int i=0; i<=len-1; i++)
  a[i] = m.a[i];
}
void MyVec:: dealloc(){
  delete [] a;
  a = NULL;
  len = 0;
}
void MyVec:: push_back(double x){
  double *a_old = a;
  a = new double[len+1];
  if (len>0){
    for(int i=0; i<len; i++){
      a[i]=a_old[i];
    }
  }
      a[len]=x;
      len++;
    delete[] a_old;
}

//Question 3:
class Student{
private:
  string name;
  double GPA;
  const Inst *instr;
//Qestion 3.2
  Student& operator=(const Student &s);
  Student(const Student &s); 
 public:
   Student(const string &s, const Inst &iref);
   string getName() const;
   string getIName() const;
   double getGPA() const;
   bool setGPA(double x);
};
 class Inst{
 private:
   string name;
   vector<Student*> v;
//Question 3.3
   Inst(const Inst &i);
   Inst& operator=(const Inst &i);
 public:
   Inst(const string &s);
   string getName() const;
   string getSNames() const;
   bool addStudent(Student &s);
   bool setGPA(int i, double x);
   Student getStudent(int i) const;
};

//non-inline code for Student class
//Question 3.2
Student& Student:: operator=(const Student &s){ 
  return *this; 
}
Student:: Student(const Student &s) {}
Student:: Student(const string &s, const Inst &iref){
  name=s;
  instr= &iref;
  GPA=3.0;
}
string Student:: getName() const{
  return name;
}
string Student:: getIName() const{
  return instr->getName();
}
double Student:: getGPA() const{
  return GPA;
}
bool Student:: setGPA(double x){
  if(x>0){
    GPA=x;
    return true;
  }
  else return false;
}

//Question 3.3
Inst:: Inst(const Inst &i) {}
Inst& Inst:: operator=(const Inst &i){
  return *this;
}
string Inst:: getName() const{
  return name;
}
bool Inst:: addStudent(Student &s){
  if (name==s.getIName()){
    v.push_back(&s);
    return true;
  }
  else return false;
}
bool Inst:: setGPA(int i, double x){
  if(x<=0) return false;
  if (i>=v.size())return false;
  else {
    v[i]->setGPA(x);
    return true;
  }
}
*Student Inst:: getStudent(int i) const{
  if (i>=v.size())return nullptr;
  else return v[i];
}

//Question 4
class Static{
 private:
   static string pos, neg, zero;
 public:
   static string sign(int i){
     if (i>0) return pos;
     if (i<0) return neg;
     else return zero;
   }
   static int RPM(int a, int b){
     int sum = 0;
    while (a != 0){
    if (a%2 != 0) sum = sum + b;
    a = a / 2;
    b = b * 2;
  }
  return sum;
   }
 };
const string Static:: pos="POSITIVE";
const string Static:: neg="NEGATIVE";
const string Static:: zero="ZERO";

int main() {
  return 0;
}