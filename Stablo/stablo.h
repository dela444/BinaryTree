#ifndef STABLO_H
#define STABLO_H
#include <utility>
using namespace std;

template <typename Tip>
class Stablo {
  public:
  struct Cvor {
      Tip element;
      Cvor *ld, *dd, *rod;
      Cvor(Tip el, Cvor* rod = nullptr, Cvor* ld = nullptr, Cvor* dd = nullptr):
          element(el), rod(rod), ld(ld), dd(dd) {}
  };
  private:
  int broj_elemenata;
  Cvor* korijen;
  void InOrderRek(Cvor*);
  Cvor* NadjiNajmanji(Cvor*);
  Cvor* NadjiSljedbenika(Cvor *cvor);
  public:
  Stablo();
  pair<Cvor*,bool> Insert(Tip element);
  Cvor* Find(Tip element);
  void InOrderRek() { InOrderRek(korijen);}
  void InOrder();
  void Erase(Cvor* za_brisanje);
  int Erase(const Tip &element);
};

#include "stablo.cpp"

#endif // STABLO_H
