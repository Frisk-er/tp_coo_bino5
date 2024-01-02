#include<iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


//using namespace std;
//using namespace nlohmann::json_abi_v3_11_2;
using json = nlohmann::json;


class Ingredient{
    std::string nom_;
    public:
    //Ingredient(std::string nom){
    //	nom_=nom;
    //}
    //Ingredient(json j){
    //	nom_=j["nom"];
    //}
    Ingredient(int id){
    	std::string u="http://localhost:8000/Ingredient/"+std::to_string(id);
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
    /*Departement( int num, float prix ){
        numero_=num;
        prixM2_=prix;
    }
    Departement(json j){
        numero_=j["numero"];
        prixM2_=j["prixM2"];
    }*/
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
    	std::string u="http://localhost:8000/Prix/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	ingredient_= std::make_unique<Ingredient>(j["ingredient"]);
    	departement_=std::make_unique<Departement>(j["departement"]);
    	prix_=j["prix"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Prix& p) {
        return out << *p.ingredient_ << ",du departement:" << *p.departement_<< ",est au prix:"<<p.prix_;
        }
};

class Machine{

	std::string nom_;
	int prix_;
	public:
	Machine(int id){
		std::string u="http://localhost:8000/Machine/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	nom_=j["nom"];
    	prix_=j["prix"];
	}
	friend std::ostream& operator<<(std::ostream& out, const Machine& p) {
        return out <<"nom machine:"<< p.nom_ << ", prix:" << p.prix_;
        }

};

class QuantiteIngredient{
	std::unique_ptr<Ingredient> ingredient_;
	int quantite_;
	public:
	QuantiteIngredient(int id){
		std::string u="http://localhost:8000/QuantiteIngredient/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	ingredient_=std::make_unique<Ingredient>(j["ingredient"]);
    	quantite_=j["quantite"];
	}
	friend std::ostream& operator<<(std::ostream& out, const QuantiteIngredient& p) {
        return out << *p.ingredient_ << ", quantite:" << p.quantite_;
        }
};

class Action{
	std::unique_ptr<Machine> machine_;
	std::string commandes_;
	int duree_;
	std::unique_ptr<Ingredient> ingredient_;
	std::optional<std::unique_ptr<Action>> action_;
	public:
	Action(int id){
		std::string u="http://localhost:8000/Action/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	std::cout<<"action1"<<std::endl;
    	machine_=std::make_unique<Machine>(j["machine"]);
    	std::cout<<"action2"<<std::endl;
    	commandes_=j["commandes"];
    	std::cout<<"action2.1"<<std::endl;
    	duree_=j["duree"];
    	std::cout<<"action3"<<std::endl;
    	ingredient_=std::make_unique<Ingredient>(j["ingredient"]);
    	std::cout<<"action4"<<std::endl;
    	if(j.contains("action") )
    	action_=std::make_unique<Action>(j["action"]);

	std::cout<<"action5"<<std::endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const Action& p) {
        return out <<"commandes:"<< p.commandes_ << "," << *p.machine_<<", duree_:"<<p.duree_<<",\t"<< *p.ingredient_;
        }


};


class Recette{
	std::string nom_;
	std::unique_ptr<Action> action_;
	public:
	Recette(int id){
		std::string u="http://localhost:8000/Recette/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	nom_=j["nom"];
    	action_=std::make_unique<Action>(j["action"]);
	}
	friend std::ostream& operator<<(std::ostream& out, const Recette& p) {
        return out <<"nom recette :"<< p.nom_ << ", action(s):" << *p.action_;
        }


};

class Usine{
	std::unique_ptr<Departement> departement_;
	int taille_;
	std::vector<std::unique_ptr<Machine>> machines_;
	std::vector<std::unique_ptr<Recette>> recettes_;
	std::vector<std::unique_ptr<QuantiteIngredient>> stocks_;
	public:
	Usine(int id){
	std::string u="http://localhost:8000/Usine/"+std::to_string(id);
    	cpr::Response r = cpr::Get(cpr::Url{u});

    	std::cout<<"balise 1"<<std::endl;
    	std::cout << r.status_code << std::endl; // 200
    	json j=json::parse(r.text);
    	std::cout<<"balise 2"<<std::endl;
    	departement_=std::make_unique<Departement>(j["departement"]);
    	std::cout<<"balise 3"<<std::endl;
    	taille_=j["taille"];
    	std::cout<<"balise 4"<<std::endl;
    	machines_= std::vector<std::unique_ptr<Machine>>();
    	for(const auto &Mach:j["machines"]){
    		machines_.push_back(std::make_unique<Machine>(Mach));
    	}
    	std::cout<<"balise 5"<<std::endl;
	recettes_= std::vector<std::unique_ptr<Recette>>();
	for(const auto &Rec:j["recettes"]){
    		recettes_.push_back(std::make_unique<Recette>(Rec));
    	}
    	std::cout<<"balise 6"<<std::endl;
	stocks_= std::vector<std::unique_ptr<QuantiteIngredient>>();
	for(const auto &Sto:j["stocks"]){
    		stocks_.push_back(std::make_unique<QuantiteIngredient>(Sto));
    	}
	std::cout<<"balise 7"<<std::endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const Usine& p) {
		out <<"Usine du "<< *p.departement_ << ", taille_:" << p.taille_<<"\t";
        out<<"machine(s):";
	    for(const auto &Mach:p.machines_){
    		out<<*Mach<<",";
    	}
        out<<"\trecette(s):";
	    for(const auto &Rec:p.recettes_){
    		out<<*Rec<<",";
    	}
        out<<"\tstocks:";
    	for(const auto &Sto:p.stocks_){
    		out<<*Sto<<",";
    	}
        return out;
        }
};



int main() {

    int i=1;

    Usine usi=(i);
    std::cout<<usi<<std::endl;


    Departement dep=(i);
    std::cout<<dep<<std::endl;

    Ingredient ing1=(1);
    std::cout<<ing1<<std::endl;

    Ingredient ing2=(2);
    std::cout<<ing2<<std::endl;

    QuantiteIngredient qi1=(1);
    std::cout<<qi1<<std::endl;

    QuantiteIngredient qi2=(2);
    std::cout<<qi2<<std::endl;

    Prix prix1=(1);
    std::cout<<prix1<<std::endl;

    Prix prix2=(2);
    std::cout<<prix2<<std::endl;



    Machine mach1=(1);
    std::cout<<mach1<<std::endl;

    Machine mach2=(2);
    std::cout<<mach2<<std::endl;

    std::cout<<"main1"<<std::endl;

    Action act1=(1);
    std::cout<<act1<<std::endl;

    std::cout<<"main2"<<std::endl;

    Recette rec1=(1);
    std::cout<<rec1<<std::endl;

    std::cout<<"main3"<<std::endl;

    Usine usibis=(i);
    std::cout<<usi<<std::endl;

    std::cout<<"main_fin"<<std::endl;



    return 0;
}
