#include<iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann::json_abi_v3_11_2;

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

    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/departement/1"});


    std::cout << r.status_code << std::endl; // 200
    std::cout << r.text << std::endl;

    json j=json::parse(r.text);
    cout<<j<<endl;
    cout<<j["numero"]<<endl;
    cout<<j["prixM2"]<<endl;

    return 0;
}
