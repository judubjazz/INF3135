from client import Client
from produit import Produit
from commande import Commande


facture = dict()


def lire_fichier_input():
    with open('input.txt') as file:
        data = file.read()
    file.close()

    return data


def splitter_data(data):
    return data.split('\n')


def ajouter_facture(client):
    list_commande = list()

    if client.get_id() in facture.keys():
        list_commande = facture[client.get_id()]
        list_commande.append(client.get_commande())
        facture[client.get_id()] = list_commande
    else:
        list_commande.append(client.get_commande())
        facture[client.get_id()] = list_commande

    return facture


def est_taxable_federale(taxe):
   return True if 'F' in taxe else False


def est_taxable_provinciale(taxe):
    return True if 'P' in taxe else False


def trier_list(data):
    list = data.split()
    id_client = list[0]
    id_produit = list[1]
    quantite = list[2]
    prix = list[3]

    try:
        taxe = list[4]
        taxable_federal = est_taxable_federale(taxe)
        taxable_provincial= est_taxable_provinciale(taxe)
    except:
        taxable_federal = False
        taxable_provincial = False

    produit = Produit(id_produit, prix, taxable_federal, taxable_provincial)
    commande = Commande(produit, quantite)
    client = Client(id_client, commande)
    factures = ajouter_facture(client)

    return factures


def produire_des_factures(data_list):
    for list in data_list:
        factures = trier_list(list)
    return factures


def calculer_prix_total(commande):
    taxe_federal = float(1.05)
    taxe_provincial = float(1.09975)
    quantite = float(commande.quantite)
    prix = float(commande.produit.prix)

    if commande.produit.taxable_provincial and commande.produit.taxable_federal:
        return ((prix * taxe_federal)*taxe_provincial)*quantite
    elif not commande.produit.taxable_provincial and not commande.produit.taxable_federal:
        return prix * quantite
    elif commande.produit.taxable_provincial and not commande.produit.taxable_federal:
        return (prix*taxe_provincial)*quantite
    else:
        return (prix*taxe_federal)*quantite


def calculer_rabais_100_articles(nbr_article, prix_totaux):
    if nbr_article < 101 :
        return 0
    else:
        rabais = round((prix_totaux * .15),2)
        return rabais


def imprimer_facture(factures):
    for client in factures:
        string_no_client = 'Client numero ' + client + '\n'
        string_entete = '             No de produit    Qte     Prix   Total(tx)'
        with open(string_no_client+'.txt', 'w') as file:
            file.write(string_no_client)
            file.write('\n')
            file.write(string_entete)
            file.write('\n')
            no_produit = 1
            prix_totaux = 0
            nbr_article = 0
            for commande in factures[client]:
                prix_total = round(calculer_prix_total(commande),2)
                prix_totaux += prix_total
                nbr_article += int(commande.quantite)
                file.write('Produit # ' + str(no_produit) + '    ' + commande.produit.id + '       ' + commande.quantite + '      ' + commande.produit.prix + '   ' + str(prix_total))
                file.write('\n')
                no_produit += 1

            rabais = calculer_rabais_100_articles(nbr_article, prix_totaux)
            file.write('\n')
            file.write('Total avant rabais : ' + str(prix_totaux))
            file.write('\n')
            file.write('Rabais : ' + str(rabais))
            file.write('\n')
            file.write('Total : ' + str(prix_totaux-rabais))



def executer():
    data= lire_fichier_input()
    data_list = splitter_data(data)
    factures = produire_des_factures(data_list)
    imprimer_facture(factures)


def main():
    executer()


if __name__ == "__main__":
    main()