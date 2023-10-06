#include<iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;

class Departement {

    int numero_;
    float prixM2_;
    public:
    Departement( int num, float prix ){
        numero_=num;
        prixM2_=prix;
    }
    void affichage(){
    cout<<"Departement numéro:"<<numero_<<", prix au m2:"<<prixM2_<<endl;
    }


};


int main() {
    Departement dep(31,2000);
    dep.affichage();

    return 0;
}
