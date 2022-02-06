#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

//forward declarations
void RPM_main();
void Catalan_main();
void Paths_main();
void make_Catalan(vector<int> &v, int co);
void print_Catalan(const vector<int> &v);
void sum_Catalan(const vector<int> &v, int a);
vector<vector<int> > make_vec2d(int n);
void print_vec2d(const vector<vector<int> > &v);

int main() {
  //RPM_main(); 
  Catalan_main(); 
  //Paths_main(); 
  return 0;
}

int RPM(int a, int b){
  int sum = 0;
  while (a != 0){
    if (a%2 != 0) sum = sum + b;
    a = a / 2;
    b = b * 2;
  }
  return sum;
}

void RPM_main(){
  int a, b;
  cout << "Enter numbers for a and b separated by a space: ";
  cin >> a >> b;
  cout << RPM(a, b) << endl;
  cout << a * b << endl << endl;
}

void Catalan_main(){
  vector<int> c;
  int cutoff = 1000000, k = 1000; 
  make_Catalan(c, cutoff); 
  print_Catalan(c); 
  sum_Catalan(c, k);
  
  cutoff = 100000000;
  k = 10000; 
  make_Catalan(c, cutoff); 
  print_Catalan(c); 
  sum_Catalan(c, k);
}

void make_Catalan(vector<int> &v, int co){
  v.clear();
  v.push_back(1);
  for (int i = 1; i<=v.size(); i++){
    int sum=0;
    for (int j =0; j<i; j++){
      sum +=v[j] * v[i-1-j];
    }
    v.push_back(sum);
    if (sum>co) break;
  }
}

void print_Catalan(const vector<int> &v){
   cout<< "Size: " << v.size() << endl << "Front: " << v.front() << endl << "Back: " << v.back() << endl;
  for (int i=0; i<v.size(); i++)
    cout<<v[i]<<endl;

}

void sum_Catalan(const vector<int> &v, int a){
  int sum = 0;
  for (int i = 0; i < v.size(); i++){
    sum += v[i] * a;
    if (sum > v.back()) break;
    cout << i << " " << sum << endl;
  }
  return;
}

void Paths_main(){
  int n = 5;
  vector<vector<int> > p = make_vec2d(n); 
  print_vec2d(p);
  cout << endl;

  n = 10;
  p = make_vec2d(n); 
  print_vec2d(p);
}

 vector<vector<int> > make_vec2d(int n){
   vector<vector<int> > p;
   for (int i = 0; i < n; i++){
      p.push_back(vector<int>(i+1));
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

 void print_vec2d(const vector<vector<int> > &v){
   for (int i = 0; i < v.size(); i++){
    for (int j = 0; j < v[i].size(); j++){
      cout << v[i][j] << " ";
    }
    cout << endl;
   }
   return;
 }