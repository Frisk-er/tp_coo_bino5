# Create your views here.
from django.views.generic import DetailView, HttpResponse, dumps

from .models import Departement


class DepartementDetailView(DetailView):
    model = Departement

    def render_to_response(self):
        return HttpResponse(dumps(self.object.json()))
