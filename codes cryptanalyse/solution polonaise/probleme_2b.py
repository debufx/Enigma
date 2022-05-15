"""
objectif : déterminer les paires de lettres échangées par le tableau de connextion (on connait la position initiale des rotors)
"""
from itertools import product as ensemble_puissance #product(string, reapat=int) : toutes les combinaison de int lettres de string
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
liste_choix=[('B', 'A', 'E'), ('B', 'O', 'B'), ('B', 'U', 'W')]

def l_equation_est_verifiee(alpha,beta,sigma):
    for lettre in alphabet:
        if sigma[beta[sigma[lettre]]] != alpha[lettre]:
            return False
    return True

def resout_probleme_2b(betas,alphas,n):
    solutions=[] #initialisation de la liste solution (liste de paire de lettres échangées ?)
    for choix in liste_choix :#ensemble_puissance(alphabet,repeat=n): # pour toutes les combinaisons de n lettres de alphabet
        sigma = dict([[lettre,lettre] for lettre in alphabet]) #initialisation d'un dictionnaire clé:valeur = lettre:lettre
        nb_cables = 0 #initialisation du nombre de cable branchés
        for i in range(n):
            lettre = chr(ord("A")+i)
            if lettre != choix[i]:
                # brancher lettre et choix[i]
                nb_cables += 1
                sigma[lettre] = choix[i]
                sigma[choix[i]] = lettre
            for j in range(len(betas)):
                alpha = alphas[j]
                beta = betas[j]
                if alpha[lettre] != beta[sigma[lettre]]:
                    # utiliser alpha = sigma^(-1) * beta * sigma
                    nb_cables += 1
                    sigma[beta[sigma[lettre]]] = alpha[lettre]
                    sigma[alpha[lettre]] = beta[sigma[lettre]]
        if nb_cables < 2*n:
            print ("cas non-determine pour choix=",choix)
            continue
        if l_equation_est_verifiee(alpha,beta,sigma):
            solutions.append(sigma)
    return solutions

alpha0 = {'A': 'M', 'C': 'C', 'B': 'J', 'E': 'Z', 'D': 'H', 'G': 'G', 'F': 'O', 'I': 'N', 'H': 'T', 'K': 'E', 'J': 'A', 'M': 'X', 'L': 'V', 'O': 'P', 'N': 'R', 'Q': 'L', 'P': 'F', 'S': 'W', 'R': 'B', 'U': 'U', 'T': 'S', 'W': 'Q', 'V': 'D', 'Y': 'Y', 'X': 'I', 'Z': 'K'}
alpha1 = {'A': 'E', 'C': 'L', 'B': 'X', 'E': 'G', 'D': 'Y', 'G': 'M', 'F': 'H', 'I': 'K', 'H': 'B', 'K': 'O', 'J': 'D', 'M': 'F', 'L': 'Q', 'O': 'U', 'N': 'C', 'Q': 'W', 'P': 'A', 'S': 'Z', 'R': 'N', 'U': 'S', 'T': 'R', 'W': 'I', 'V': 'J', 'Y': 'P', 'X': 'V', 'Z': 'T'}
alpha2 = {'A': 'I', 'C': 'G', 'B': 'B', 'E': 'N', 'D': 'Y', 'G': 'S', 'F': 'F', 'I': 'Z', 'H': 'M', 'K': 'U', 'J': 'D', 'M': 'Q', 'L': 'W', 'O': 'E', 'N': 'O', 'Q': 'A', 'P': 'K', 'S': 'R', 'R': 'V', 'U': 'C', 'T': 'T', 'W': 'H', 'V': 'P', 'Y': 'J', 'X': 'X', 'Z': 'L'}

beta0 = {'A': 'A', 'C': 'B', 'B': 'J', 'E': 'W', 'D': 'I', 'G': 'M', 'F': 'T', 'I': 'O', 'H': 'N', 'K': 'S', 'J': 'G', 'M': 'X', 'L': 'V', 'O': 'E', 'N': 'C', 'Q': 'L', 'P': 'P', 'S': 'Z', 'R': 'R', 'U': 'U', 'T': 'Y', 'W': 'Q', 'V': 'D', 'Y': 'F', 'X': 'H', 'Z': 'K'}
beta1 = {'A': 'M', 'C': 'N', 'B': 'X', 'E': 'Z', 'D': 'P', 'G': 'S', 'F': 'I', 'I': 'B', 'H': 'K', 'K': 'T', 'J': 'D', 'M': 'F', 'L': 'Q', 'O': 'C', 'N': 'R', 'Q': 'W', 'P': 'Y', 'S': 'A', 'R': 'L', 'U': 'E', 'T': 'U', 'W': 'H', 'V': 'J', 'Y': 'G', 'X': 'V', 'Z': 'O'}
beta2 = {'A': 'E', 'C': 'V', 'B': 'B', 'E': 'C', 'D': 'P', 'G': 'H', 'F': 'F', 'I': 'M', 'H': 'Z', 'K': 'U', 'J': 'D', 'M': 'Q', 'L': 'W', 'O': 'O', 'N': 'T', 'Q': 'G', 'P': 'J', 'S': 'N', 'R': 'A', 'U': 'R', 'T': 'S', 'W': 'I', 'V': 'Y', 'Y': 'K', 'X': 'X', 'Z': 'L'}

solutions = resout_probleme_2b([beta0,beta1],[alpha0,alpha1],3)

print ("solutions sigma=",solutions)
