#include<iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


using namespace std;
using namespace nlohmann::json_abi_v3_11_2;


/*class Ingredient(models.Model){
    string nom_;
};*/



class Departement {

    int numero_;
    float prixM2_;
    public:
    Departement( int num, float prix ){
        numero_=num;
        prixM2_=prix;
    }
    Departement(json j){
        numero_=j["numero"];
        prixM2_=j["prixM2"];
    }
    Departement(int id){
      string u="http://localhost:8000/departement/"+to_string(id);
      cpr::Response r = cpr::Get(cpr::Url{u});
      std::cout << r.status_code << std::endl; // 200
      json j=json::parse(r.text);
      numero_=j["numero"];
      prixM2_=j["prixM2"];
    }

    //surcharge d'opérateur <<
    friend std::ostream& operator<<(std::ostream& out, const Departement& p) {
        return out <<"Déparetement numéro:"<< p.numero_ << ", prix au m2:" << p.prixM2_;
        }
};


int main() {

    int i=1;
    Departement dep=(i);
    cout<<dep<<endl;


    return 0;
}
