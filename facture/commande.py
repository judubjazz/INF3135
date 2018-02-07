class Commande(object):
    def __init__(self,produit, quantite):
        self.produit = produit
        self.quantite = quantite

    def get_produit(self):
        return self.produit

    def get_quantite(self):
        return self.quantite

    def set_produit(self, produit):
        self.produit = produit

    def set_quantite(self, quantite):
        self.quantite = quantite

    def __str__(self):
        return "produit :  %s, quantite:  %s" % (self.produit, self.quantite)