class Produit(object):
    def __init__(self, id, prix, taxable_federal, taxable_provincial):
        self.id = id
        self.prix = prix
        self.taxable_federal = taxable_federal
        self.taxable_provincial = taxable_provincial

    def get_id(self):
        return self.id

    def get_prix(self):
        return self.prix

    def set_id(self, id):
        self.id = id

    def set_prix(self, prix):
        self.prix = prix

    def __str__(self):
        return "id :  %s, prix:  %s, taxable federal :  %s, taxable provincial:  %s" % (self.id, self.prix, self.taxable_federal, self.taxable_provincial)