class Client(object):

    def __init__(self, id, commande):

        self.id = id
        self.commande = commande

    def get_id(self):
        return self.id

    def get_commande(self):
        return self.commande

    def set_id(self, id):
        self.id = id

    def set_list_commande(self, list_commande):
        self.commande = list_commande

    def a_un_panier_vide(self):
        return True if self.commande is None else False

    def ajouter_au_panier(self, list):
        self.commande.append(list)