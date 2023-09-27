# Create your models here.

from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)


class Departement(models.Model):
    numero = models.IntegerField()
    prixM2 = models.IntegerField()


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


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField()


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )
    quantite = models.IntegerField()


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


class Recette(models.Model):
    nom = models.CharField(max_length=100)
    action = models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )


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
