#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class File{
public:
  virtual ~File() {}
  const string& getName() { return name; }
  const std::string& getType() { return type; }
  int getSize() { return size; }
  virtual void print() const {}
  virtual File* clone() const = 0;
 protected:
  File(const string &n, const string &t, int x) {  
  name = n;
  type = t;
  size = x;
}
  string name;
  string type;
  int size;
};

class PDF : public File{
public:
  PDF(const string& n, const string &text) : File(n,text,text.length()) {
    p_text=new string(text);
  }
 ~PDF() {
    delete p_text;
  }
  PDF(const PDF &orig) : File(orig) {
    p_text= new string(*orig.p_text);
  }
  PDF& operator= (const PDF &rhs) {
    if (this == &rhs) return*this;
    File::operator=(rhs);
    delete p_text;
    p_text = new string;
    p_text = rhs.p_text;
    return *this;
  }
  virtual File* clone() const {
    return new PDF(*this);
  }
  virtual void print() const { 
    cout<<"Name: "<< name <<"  Type: "<< type <<"  Size: "<< size <<"  Text: "<< *p_text<<endl;
  }
protected:
  string *p_text;
};

class JPG : public File{
protected:
  int height, width; 
  double *p_pixels;
public:
  JPG(const string& n, int h, int w, const double rgb[]) : File(n,"jpg", h*w) {
    height=h;
    width=w;
    p_pixels=new double[size];
    for(int i=0;i<size; i++){
      p_pixels[i]=rgb[i];
    }
  }
 ~JPG() {
    delete[] p_pixels;
  }
  JPG(const JPG &orig) : File(orig) {
    height=orig.height;
    width=orig.width;
    p_pixels = new double[orig.size];
    for (int i=0; i<orig.size; i++)
      p_pixels[i]=orig.p_pixels[i];
  }
JPG& operator= (const JPG &rhs) { 
  if (this == &rhs) return *this;
  File::operator=(rhs);
  height=rhs.height;
  width=rhs.width;
  delete[] p_pixels;
  p_pixels = new double[rhs.size];
  for (int i=0; i<rhs.size; i++)
    p_pixels[i]=rhs.p_pixels[i];
  return *this;
}
virtual File* clone() const {
  return new JPG(*this);
}
virtual void print() const {
  cout<<"Name: "<< name <<"  Type: "<< type <<"  Size: "<< size <<"  Height: "<< height << "  Width: " << width << endl;
  for (int i=0; i<height; i++){
    for (int j=0; j<width; j++){
      cout << p_pixels[i*width+j]<<" ";
    }
    cout<<endl;
  }
}
};

class Email{
public:
  Email(const string &f){
    from=f;
  }
  ~Email() {
    for (int i=0; i<v_attachments.size(); i++)
      delete v_attachments[i];
  }
  void sendTo(const string &t){
    v_to.push_back(t);
  }
  void setText(const string &t){
    text=t;
  }
  void setSubject(const string &t) {
    subject=t;
  }
  void addAttachment(const File &f) { 
    File *fptr = f.clone(); 
    v_attachments.push_back(fptr);
  }
  void print() const { 
    cout << "From: " << from << endl;
    cout << "To: ";
    for(int i=0; i<v_to.size();i++)
      cout<< v_to[i]<<", ";
    cout << endl << "Subject: " << subject << endl << endl << text << endl<<endl;
    for(int i=0; i<v_attachments.size();i++){
      v_attachments[i]->print();
      cout<<endl;
    }

  }
private:
  string from;
  string subject;
  string text;
  vector<string> v_to;
  vector<File*> v_attachments;
  Email (const Email &e) {}
  Email& operator=(const Email &e) {return *this;}
};

class XLS: public File{
protected:
  string **ppxls;
  int row;
  int col;
public:
  XLS(const string& n, int r, int c): File(n, "XLS", r*c){
    row=r;
    col=c;
    ppxls = new string*[row];
    for (int i = 0; i < row; i++){
      ppxls[i]= new string[col];
   }
  }
 ~XLS(){
     for (int i = 0; i < row; i++)
        delete[] ppxls[i];;  
      delete[] ppxls;
    }
    XLS(const XLS &orig) : File(orig) {
    ppxls = new string*[orig.row];
    for (int i = 0; i < row; i++){
      ppxls[i]= new string[col];
   }
    for (int i=0; i<orig.row; i++)
      for(int j=0; j<orig.col; j++)
        ppxls[i][j]=orig.ppxls[i][j];
  }
  XLS& operator= (const XLS &rhs) { 
  if (this == &rhs) return *this;
  File::operator=(rhs);
  row=rhs.row;
  col=rhs.col;
  for (int i = 0; i < row; i++)
        delete[] ppxls[i];;  
      delete[] ppxls;
  ppxls = new string*[row];
  for (int i = 0; i < row; i++){
      ppxls[i]= new string[col];
   }
   for(int i=0;i<row; i++)
   for(int j=0; j<col; j++)
    ppxls[i][j]=rhs.ppxls[i][j];
  return *this;
  }  
  virtual File* clone() const {
    XLS *x=new XLS(name, row, col);
    *x=*this;
    return x;
  }
  virtual void print() const {
    cout<<"Name: "<< name <<"  Type: "<< type <<"  Size: "<< size <<"  Rows: "<< row << "  Columns: " << col << endl;
    for (int i=0; i<row; i++){
      for (int j=0; j<col; j++){
        cout << ppxls[i][j]<<" ";
      }
      cout<<endl;
    }
  }
  int getR(){return row;}
  int getC(){return col;}
  void set(string str, int r, int c){
    ppxls[r][c]=str;
  }
};

// void hw6_main(){
//   XLS xls("spreadsheet.xls", 2, 3);
//   string a="a";
//   for (int i=0; i<xls.getR(); i++){
//     for (int j=0; j<xls.getC(); j++){
//       xls.set(a, i, j);
//     }
//     a="b";
//   }

//   PDF pdf1("class1.pdf", "This is my first class.");
//   PDF pdf2("class2.pdf", "This is my second class.");
//   double arr1[100];
//   double arr2[100];
//   for (int i=0; i<100; i++){
//     arr1[i]=i+1;
//     arr2[i]=(i+1)*2;
//   }
//   JPG jpg1("pic1.jpg",4,6,arr1);
//   JPG jpg2("pic2.jpg",5,7,arr2);
//   string sender="Chaya Chrein";
//   Email em1(sender); 
//   em1.sendTo("Professor Sateesh Mane");
//   em1.sendTo("Professor Sally Sun");
//   em1.setText("This is my first email.");
//   em1.setSubject("Email #1");
//   em1.addAttachment(pdf1);
//   em1.addAttachment(jpg1);
//   em1.print();
//   Email em2(sender);
//   em2.sendTo("Professor Sateesh Mane");
//   em2.sendTo("Professor Sally Sun");
//   em2.setText("This is my second email.");
//   em2.setSubject("Email #2");
//   em2.addAttachment(pdf2);
//   em2.addAttachment(jpg2);
//   em2.addAttachment(xls);
//   em2.print();
// }
// int main() {
//   hw6_main();
//   return 0; 
// }

static void addPDF(Email &e)
{
  PDF p("p", "abcdefghijkl");
  p.print();
  std::cout << endl;
  e.addAttachment(p);
} 
  
static void addJPG(Email &e)
{
  double d[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.1};
  JPG j("j", 2, 4, d);
  j.print();
  std::cout << endl;
  e.addAttachment(j);
}
  
int main()
{
  Email e("Mane");
  
  e.sendTo("Alice");
  e.sendTo("Bob");
  
  e.setText("Hope you are well");
  e.setSubject("hello");
  // PDF p("p", "abcdefghijkl");
  // double d[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.1};
  // JPG j("j", 2, 4, d);

  addJPG(e);
  addPDF(e);

  // e.addAttachment(p);
  // e.addAttachment(j);

  e.print();
  return 0;
}