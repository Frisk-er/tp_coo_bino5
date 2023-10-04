# Create your views here.
from json import dumps

from django.http import HttpResponse
from django.views.generic import DetailView

from . import models


class IngredientDetailView(DetailView):
    model = models.Ingredient

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class DepartementDetailView(DetailView):
    model = models.Departement

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class PrixDetailView(DetailView):
    model = models.Prix

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class MachineDetailView(DetailView):
    model = models.Machine

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class QuantiteIngredientDetailView(DetailView):
    model = models.QuantiteIngredient

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class ActionDetailView(DetailView):
    model = models.Action

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class RecetteDetailView(DetailView):
    model = models.Recette

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class UsineDetailView(DetailView):
    model = models.Usine

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json()))


class apiDetailView(DetailView):
    model = models.Usine

    def render_to_response(self, context, **respose_kwargs):
        return HttpResponse(dumps(self.object.json_extended()))
