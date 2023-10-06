# Create your tests here.

from django.test import TestCase

from . import models


class MachineModelTests(TestCase):
    def test_usine_creation(self):
        self.assertEqual(models.Machine.objects.count(), 0)
        models.Machine.objects.create(nom="four", prix=1_000)
        self.assertEqual(models.Machine.objects.count(), 1)


class ModelTestsCosts(TestCase):
    def test_costs(self):
        ing1 = models.Ingredient.objects.create(nom="houblon")
        ing2 = models.Ingredient.objects.create(nom="orge")
        sto1 = models.QuantiteIngredient.objects.create(ingredient=ing1, quantite=50)
        sto2 = models.QuantiteIngredient.objects.create(ingredient=ing2, quantite=100)
        dep = models.Departement.objects.create(numero=31, prixM2=2000)
        models.Prix.objects.create(ingredient=ing1, departement=dep, prix=20)
        models.Prix.objects.create(ingredient=ing2, departement=dep, prix=10)
        Mach1 = models.Machine.objects.create(nom="Mach1", prix=1000)
        Mach2 = models.Machine.objects.create(nom="Mach1", prix=2000)
        Ac1 = models.Action.objects.create(
            machine=Mach1, commandes="malaxer", duree=5, ingredient=ing1
        )
        Rec = models.Recette.objects.create(nom="blonde", action=Ac1)

        usi = models.Usine.objects.create(taille=50, departement=dep)

        usi.machines.add(Mach1)
        usi.machines.add(Mach2)
        usi.recettes.add(Rec)
        usi.stocks.add(sto1)
        usi.stocks.add(sto2)

        print(usi.costs())
        if usi.costs() == 105000:
            print("Test unitaire validé")
