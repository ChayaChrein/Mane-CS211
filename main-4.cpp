#include <iostream>
using namespace std;

class Book{
private:
    string title; // The book's title.
    string author; //The book's author.
    double price;//The book's price.
public:
    Book(){
      title="";
      author="";
      price=0.0;
    }
    Book(string title, string author,double price){
      this->title=title;
      this->author=author;
      this->price=price;
    }
    void printInfo() const{
      cout<<"Book Info =====\nTitle: "<< title << "\nAuthor: " << author << "\nPrice: $"<<price <<"\n=============== \n";
    }
};

int main() {
  cout << "Enter a number greater than 5: ";
  int n;
  cin>>n;
  Book *b = new Book[n];
  b[1]=Book("Harry Potter", "JK Rowling", 100);
  b[4]=Book("The Animal world", "ABC",50);
  for(int i=0;i<n;i++){
    b[i].printInfo();
  }
  delete[] b;
}