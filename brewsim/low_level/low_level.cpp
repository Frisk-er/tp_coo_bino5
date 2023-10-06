#include<iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


//using namespace std;
//using namespace nlohmann::json_abi_v3_11_2;
using json = nlohmann::json;


class Ingredient{
    std::string nom_;
    public:
    Ingredient(std::string nom){
    	nom_=nom;
    }
    Ingredient(json j){
    	nom_=j["nom"];
    }
    Ingredient(int id){
    	std::string u="http://localhost:8000/departement/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	nom_=j["nom"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Ingredient& p) {
        return out <<"Ingredient:"<< p.nom_;
        }
};



class Departement {

    int numero_;
    int prixM2_;
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
    	std::string u="http://localhost:8000/departement/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	numero_=j["numero"];
    	prixM2_=j["prixM2"];
    }

    //surcharge d'opérateur <<
    friend std::ostream& operator<<(std::ostream& out, const Departement& p) {
        return out <<"Département numéro:"<< p.numero_ << ", prix au m2:" << p.prixM2_;
        }
};

class Prix{
    std::unique_ptr<Ingredient> ingredient_;
    std::unique_ptr<Departement> departement_;
    int prix_;

    public:/* unique_ptr affecttaion ?
    Prix(std::unique_ptr<Ingredient> ingredient, std::unique_ptr<Departement> departement,int prix ){
    	ingredient_=ingredient;
    	departement_=departement;
    	prix_=prix;
    }
    Prix(json j){
    	ingredient_=j["ingredient"];
    	departement_=j["departement"];
    	prix_=j["prix"];
    }*/
    Prix(int id){
    	std::string u="http://localhost:8000/departement/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	ingredient_= std::make_unique<Ingredient>(j["ingredient"]);
    	departement_=std::make_unique<Departement>(j["departement"]);
    	prix_=j["prix"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Prix& p) {
        return out <<"ingredient:"<< *p.ingredient_ << ", departement:" << *p.departement_<< ", prix:"<<p.prix_;
        }
};


int main() {

    int i=1;
    Departement dep=(i);
    std::cout<<dep<<std::endl;


    return 0;
}
