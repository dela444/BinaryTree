#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <iostream>
using namespace std;

template <typename Tip>
Stablo<Tip>::Stablo() {
  korijen = nullptr;
  broj_elemenata = 0;
}

template <typename Tip>
pair<typename Stablo<Tip>::Cvor*,bool> Stablo<Tip>::Insert(Tip element) {

  if(korijen == nullptr) {
    korijen = new Cvor(element);
    broj_elemenata = 1;
    return {korijen, true};
  }

  Cvor *trenutni = korijen, *prethodni = nullptr;
  while(trenutni != nullptr) {
    if(element == trenutni->element)
        return {trenutni, false};
    prethodni = trenutni;
    if(element < trenutni->element)
        trenutni = trenutni->ld;
    else trenutni = trenutni->dd;
  }
  broj_elemenata++;
  Cvor *novi = new Cvor(element,prethodni);
  if(element < prethodni->element)
    prethodni->ld = novi;
  else prethodni->dd = novi;
  return {novi,true};
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(Tip element) {
  Cvor* trenutni = korijen;
  while(trenutni != nullptr) {
    if(element == trenutni->element)
      return trenutni;
    if(element < trenutni->element)
      trenutni = trenutni->ld;
    else trenutni = trenutni->dd;
  }
  return nullptr;
}

template <typename Tip>
void Stablo<Tip>::InOrderRek(Cvor* cvor) {
  if(cvor==nullptr)
    return;
  InOrderRek(cvor->ld);
  cout<<cvor->element<<" ";
  InOrderRek(cvor->dd);
}

template <typename Tip>
void Stablo<Tip>::InOrder() {
  Cvor* trenutni = NadjiNajmanji(korijen);
  while(trenutni != nullptr) {
    cout<<trenutni->element<<" ";
    trenutni = NadjiSljedbenika(trenutni);
  }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajmanji(Stablo<Tip>::Cvor *cvor) {
  if(cvor == nullptr)
    return nullptr;
  Cvor *trenutni = cvor;
  while(trenutni->ld != nullptr)
    trenutni = trenutni->ld;
  return trenutni;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiSljedbenika(Stablo<Tip>::Cvor *cvor) {
  if(cvor->dd != nullptr)
    return NadjiNajmanji(cvor->dd);
  Cvor* trenutni = cvor;
  while(trenutni != korijen && trenutni == trenutni->rod->dd)
    trenutni = trenutni->rod;
  if(trenutni == korijen)
    return nullptr;
  else return trenutni->rod;
}

template <typename Tip>
int Stablo<Tip>::Erase(const Tip &element) {
  Cvor *za_brisanje = Find(element);
  if(za_brisanje != nullptr) {
    Erase(za_brisanje);
    return 1;
  }
  else return 0;
}

template <typename Tip>
void Stablo<Tip>::Erase(Cvor *za_brisanje) {

  if(za_brisanje->dd == nullptr) {  //ako nema desnog djeteta
    if(za_brisanje->ld == nullptr) { //ako nema ni lijevog
        if(za_brisanje->rod != nullptr) { //ako ima roditelja
            if(za_brisanje->rod->dd == za_brisanje)
                za_brisanje->rod->dd = nullptr;
            else za_brisanje->rod->ld = nullptr;  //ako nema roditelja, tada je korijen
        }
        else korijen = nullptr;
    }
    else {  //ako ima lijevo dijete
        if(za_brisanje->rod != nullptr) { //ako ima roditelja
            if(za_brisanje->rod->dd == za_brisanje)
                za_brisanje->rod->dd = za_brisanje->ld;
            else za_brisanje->rod->ld = za_brisanje->ld;  //ako nema roditelja, tada je korijen
            za_brisanje->ld->rod = za_brisanje->rod;
        }
        else {
            korijen = za_brisanje->ld;
            za_brisanje->ld->rod = nullptr;
        }
    }
  }
  else {
    Cvor* sljedbenik = NadjiSljedbenika(za_brisanje);
    if(sljedbenik->rod == za_brisanje) {
        sljedbenik->rod = za_brisanje->rod;
        if(za_brisanje->rod != nullptr) {
            if(za_brisanje->rod->dd == za_brisanje)
                za_brisanje->rod->dd = sljedbenik;
            else za_brisanje->rod->ld = sljedbenik;
        }
        else korijen = sljedbenik;
        if(za_brisanje->ld != nullptr)
            za_brisanje->ld->rod = sljedbenik;
        sljedbenik->ld = za_brisanje->ld;
    }
    else {
       sljedbenik->rod->ld = sljedbenik->dd;
       if(sljedbenik->dd != nullptr)
         sljedbenik->dd->rod = sljedbenik->rod;
       sljedbenik->dd = za_brisanje->dd;
       za_brisanje->dd->rod = sljedbenik;
       sljedbenik->ld = za_brisanje->ld;
       if(za_brisanje->ld != nullptr)
         za_brisanje->ld->rod = sljedbenik;
       sljedbenik->rod = za_brisanje->rod;
       if(za_brisanje->rod != nullptr) {
          if(za_brisanje->rod->ld == za_brisanje)
            za_brisanje->rod->ld = sljedbenik;
          else za_brisanje->rod->dd = sljedbenik;
       }
       else korijen = sljedbenik;
    }
  }

  delete za_brisanje;
  broj_elemenata--;

}
#endif // STABLO_CPP
