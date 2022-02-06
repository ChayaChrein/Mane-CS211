#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

//forward declarations
void swap(int *p1, int *p2);
void swap(double *p1, double *p2);
void swap(string *p1, string *p2);
void swap(string str1, string str2);
void swap(double d1, double d2);
void swap(int int1, int int2);
void swap_main();
void math_main();
void ptr_neg_main();
void set_ptr_neg(double *p, int n, const double *a);
void print_ptr_neg(const double *p, int n);
void Paths_ptr_main();
int** make_ptr2d(int n);
void delete_ptr2d(int **p, int n);
void print_ptr2d(const int *const *p, int n);

int main() {
  swap_main(); 
  math_main(); 
  ptr_neg_main(); 
  Paths_ptr_main(); 
  return 0;
}

void swap_main(){
  int i1, i2;
  double d1, d2;
  string s1, s2;
  
  cout<<"Type 2 integers separated by a space: ";
  cin>> i1 >> i2;
  cout<< "Before: First: " << i1 << " Second: " << i2 << endl;
  swap (i1, i2);
  cout<< "After: First: " << i1 << " Second: " << i2 << endl;

  cout<<"Type 2 double values separated by a space: ";
  cin>> d1 >> d2;
  cout<< "Before: First: " << d1 << " Second: " << d2 << endl;
  swap (d1, d2);
  cout<< "After: First: " << d1 << " Second: " << d2 << endl;

  cout<<"Type 2 strings separated by a space: ";
  cin>> s1 >> s2;
  cout<< "Before: First: " << s1 << " Second: " << s2 << endl;
  swap (s1, s2);
  cout<< "After: First: " << s1 << " Second: " << s2 << endl;

  int *pi1 = new int;
  *pi1 = i1; 
  int *pi2 = new int;
  *pi2 = i2; 
  double *pd1 = new double;
  *pd1 = d1; 
  double *pd2 = new double;
  *pd2 = d2; 
  string *ps1 = new string;
  *ps1 = s1;
  string *ps2 = new string;
  *ps2 = s2;
  
  cout<<"Type 2 integers separated by a space: ";
  cin>> *pi1 >> *pi2;
  cout<< "Before: First: " << *pi1 << " Second: " << *pi2 << endl;
  swap (pi1, pi2);
  cout<< "After: First: " << *pi1 << " Second: " << *pi2 << endl;

  cout<<"Type 2 double values separated by a space: ";
  cin>> *pd1 >> *pd2;
  cout<< "Before: First: " << *pd1 << " Second: " << *pd2 << endl;
  swap (pd1, pd2);
  cout<< "After: First: " << *pd1 << " Second: " << *pd2 << endl;

  cout<<"Type 2 strings separated by a space: ";
  cin>> *ps1 >> *ps2;
  cout<< "Before: First: " << *ps1 << " Second: " << *ps2 << endl;
  swap (ps1, ps2);
  cout<< "After: First: " << *ps1 << " Second: " << *ps2 << endl;

  delete pi1;
  delete pi2;
  delete pd1;
  delete pd2;
  delete ps1;
  delete ps2;
}

void swap(string str1, string str2){
  string tmp = str1;
  str1 = str2;
  str2 = tmp;
}
void swap(int int1, int int2){
  int tmp = int1;
  int1 = int2;
  int2 = tmp;
}
void swap(double d1, double d2){
  double tmp = d1;
  d1 = d2;
  d2 = tmp;
}
void swap(int *p1, int *p2){
  int tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}
void swap(double *p1, double *p2){
  double tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}
void swap(string *p1, string *p2){
  string tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

void math_main(){
  double *d1 = new double;
  double *d2 = new double;
  double *d3 = new double;
  double *d4 = new double;

  cout<< "Enter 4 double values separated by a space: ";
  cin >> *d1 >> *d2 >> *d3 >> *d4;
  cout << *d1 << " " << *d2 << " " << *d3 << " " << *d4 << endl;

  double sum = *d1 + *d2;
  double diff = *d1 - *d2;
  double mult = *d1 * *d2;
  double div =  *d1 / *d2;
  double mixed =  *d1 * (*d2 + *d3 / *d4);
  cout << "sum: " << sum << " diff: " << diff << " mult: " << mult << " div: " << div << " mixed: " << mixed << endl;

  double *divp = new double;
  *divp = div;
  double *mixedp = new double;
  *mixedp = mixed;
  swap(divp, mixedp);
  cout<< "After: div: "<<*divp<< " mixed: "<< *mixedp<<endl;
  delete d1;
  delete d2;
  delete d3;
  delete d4;
  delete divp;
  delete mixedp;
}

void ptr_neg_main() {
  const int n = 4;

  double a[3];
  cout << "Enter 3 double values separated by a space: ";
  cin >> a[0] >> a[1] >> a[2];

  double arr[2*n+1];
  double *p = &arr[n];

  set_ptr_neg(p, n, a); 
  print_ptr_neg(p, n); 
  cout << endl;

  const int n2 = n+2;
  double *brr = new double[2*n2+1];
  p = &brr[n2];
  
  set_ptr_neg(p, n2, a); 
  print_ptr_neg(p, n2);
  cout<<endl;

  delete[] brr;
}

void set_ptr_neg(double *p, int n, const double *a){
  for (int i = (-1 * n); i<=n; i++)
    p[i]=a[0] + a[1]*i + a[2]*i*i;
}

void print_ptr_neg(const double *p, int n){
  for (int i = (-1 * n); i<=n; i++)
  cout<<p[i]<<" ";
}

void Paths_ptr_main() {
  int n = 5;
  int **p = make_ptr2d(n); 
  print_ptr2d(p, n); 
  delete_ptr2d(p, n);
  cout << endl;

  n = 10;
  p = make_ptr2d(n); 
  print_ptr2d(p, n); 
  delete_ptr2d(p, n);
}

int** make_ptr2d(int n){
  int **p= new int*[n];

   for (int i = 0; i < n; i++){
      p[i]= new int[i+1];
   }
   p[0][0]=1;

   for (int i = 1; i < n; i++){
    for (int j = 0; j <=i; j++){
      if (j == 0) p[i][j] = 1;
      else if (j == i) p[i][j] = p[i][j-1];
      else p[i][j] = p[i][j-1] + p[i-1][j];
    }
  }

  return p;
}

void delete_ptr2d(int **p, int n){
  for (int i=0; i<n; i++){
    delete[] p[i];
  }
  delete[] p;
}

void print_ptr2d(const int *const *p, int n){
  for (int i=0; i<n; i++){
    for (int j=0; j<=i; j++){
      cout<<p[i][j]<< " ";
    }
    cout<<endl;
  }
}