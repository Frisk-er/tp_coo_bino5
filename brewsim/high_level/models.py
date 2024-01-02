# Create your models here.


from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return self.nom

    def json(self):
        return {"nom": self.nom}


class Departement(models.Model):
    numero = models.IntegerField()
    prixM2 = models.IntegerField()

    def __str__(self):
        return f"{self.numero}"

    def json(self):
        return {"numero": self.numero, "prixM2": self.prixM2}


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

    def json(self):
        return {
            "ingredient": self.ingredient.id,
            "departement": self.departement.id,
            "prix": self.prix,
        }

    def json_extended(self):
        return {
            "ingredient": self.ingredient.json(),
            "departement": self.departement.json(),
            "prix": self.prix,
        }


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField()

    def __str__(self):
        return self.nom

    def costs(self):
        return self.prix

    def json(self):
        return {"nom": self.nom, "prix": self.prix}


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

    def json(self):
        return {"ingredient": self.ingredient.id, "quantite": self.quantite}

    def json_extended(self):
        return {
            "ingredient": self.ingredient.json(),
            "quantite": self.quantite,
        }


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

    def json(self):
        if self.action:
            return {
                "machine": self.machine.id,
                "commandes": self.commandes,
                "duree": self.duree,
                "ingredient": self.ingredient.id,
                "action": self.action,
            }
        else:
            return {
                "machine": self.machine.id,
                "commandes": self.commandes,
                "duree": self.duree,
                "ingredient": self.ingredient.id,
            }

    def json_extended(self):
        if self.action:
            return {
                "machine": self.machine.json(),
                "commandes": self.commandes,
                "duree": self.duree,
                "ingredient": self.ingredient.id,
                "action": self.action.json_extended(),
            }
        else:
            return {
                "machine": self.machine.json(),
                "commandes": self.commandes,
                "duree": self.duree,
                "ingredient": self.ingredient.id,
            }


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

    def json(self):
        return {"nom": self.nom, "action": self.action.id}

    def json_extended(self):
        return {"nom": self.nom, "action": self.action.json_extended()}


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

    def json(self):
        mach = []
        for m in self.machines.all():
            mach.append(m.id)
        rec = []
        for m in self.recettes.all():
            rec.append(m.id)
        sto = []
        for m in self.stocks.all():
            sto.append(m.id)

        return {
            "departement": self.departement.id,
            "taille": self.taille,
            "machines": mach,
            "recettes": rec,
            "stocks": sto,
        }

    def json_extended(self):
        mach = []
        for m in self.machines.all():
            mach.append(m.json())
        rec = []
        for m in self.recettes.all():
            rec.append(m.json())
        sto = []
        for m in self.stocks.all():
            sto.append(m.json())

        return {
            "departement": self.departement.json(),
            "taille": self.taille,
            "machines": mach,
            "recettes": rec,
            "stocks": sto,
        }
