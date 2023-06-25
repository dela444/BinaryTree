#include <iostream>
#include "stablo.h"
using namespace std;

int main() {

  Stablo<int> s;
  s.Insert(20);
  s.Insert(30);
  s.Insert(25);
  s.Insert(35);
  s.Insert(10);
  s.Insert(5);
  s.Insert(15);
  s.Insert(32);
  s.Insert(12);
  s.Insert(17);
  s.Insert(18);

  s.InOrder();
  cout<<endl;
  s.Erase(10);
  s.InOrder();
  cout<<endl;
  s.Erase(25);
  s.InOrder();
  cout<<endl;
  s.Erase(18);
  s.InOrder();
  cout<<endl;
  s.Insert(14);
  s.InOrder();
  cout<<endl;
  s.Erase(20);
  s.InOrder();
  cout<<endl;





}
