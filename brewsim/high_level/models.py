# Create your models here.

from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return self.nom


class Departement(models.Model):
    numero = models.IntegerField()
    prixM2 = models.IntegerField()

    def __str__(self):
        return f"{self.numero}"


class Prix(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    departement = models.ForeignKey(
        Departement,  # ou "self",
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    prix = models.IntegerField()

    def __str__(self):
        return f"{self.departement}, {self.ingredient}"


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField()

    def __str__(self):
        return self.nom

    def costs(self):
        return self.prix


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    quantite = models.IntegerField()

    def __str__(self):
        return f"{self.ingredient}, {self.quantite}"

    def costs(self, numDepartement):
        return (
            self.quantite
            * self.ingredient.prix_set.get(departement__numero=numDepartement).prix
        )


class Action(models.Model):
    machine = models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    commandes = models.CharField(max_length=100)
    duree = models.IntegerField()
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    action = models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        related_name="+",
    )

    def __str__(self):
        return self.commandes


class Recette(models.Model):
    nom = models.CharField(max_length=100)
    action = models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    def __str__(self):
        return self.nom


class Usine(models.Model):
    departement = models.ForeignKey(
        Departement,  # ou "self",
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    taille = models.IntegerField()
    machines = models.ManyToManyField(Machine)
    recettes = models.ManyToManyField(Recette)
    stocks = models.ManyToManyField(QuantiteIngredient)

    def __str__(self):
        return f"Usine du {self.departement}"

    def costs(self):
        coutTerrain = self.taille * self.departement.prixM2
        coutMachines = 0
        for m in self.machines.all():
            coutMachines = coutMachines + m.costs()
        coutStocks = 0
        for m in self.stocks.all():
            coutStocks = coutStocks + m.costs(self.departement.numero)

        return coutTerrain + coutMachines + coutStocks
