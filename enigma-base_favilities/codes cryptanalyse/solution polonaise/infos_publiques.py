from itertools import product as ensemble_puissance #product(string, reapat=int) : toutes les combinaison de int lettres de string
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def inverse(alpha):
    inv = dict([[lettre,None] for lettre in alphabet])
    for item in alpha.items():
        inv[item[1]] = item[0]
    return inv

def composee(alphas):
    gamma = dict([[lettre,None] for lettre in alphabet])#dico
    for lettre in alphabet:
        tmp = lettre
        for i in range(len(alphas)-1,-1,-1):
            tmp = alphas[i][tmp]
        gamma[lettre] = tmp
    return gamma

def sigma(C):
    sigma_C = dict([[e,e] for e in alphabet])
    for pair in C:
        [i,j] = pair
        sigma_C[i] = j
        sigma_C[j] = i
    return sigma_C


def pivoter(alpha,decalage):
    N = len(alphabet)
    nouveau_alpha = dict([[lettre,None] for lettre in alphabet])
    for ind in range(N):
        lettre = alphabet[ind]
        nouveau_alpha[lettre] = alpha[alphabet[(ind+decalage) % N]]
    return nouveau_alpha

def rho(R):
    rotor0 = dict(zip(alphabet,rotors[0]))
    rotor1 = dict(zip(alphabet,rotors[1]))
    rotor2 = dict(zip(alphabet,rotors[2]))
    tau = dict(zip(alphabet,reflecteur))
    rotor0_R = pivoter(rotor0,alphabet.index(R[0]))
    rotor1_R = pivoter(rotor1,alphabet.index(R[1]))
    rotor2_R = pivoter(rotor2,alphabet.index(R[2]))
    rho_R = composee([inverse(rotor0_R),inverse(rotor1_R),inverse(rotor2_R),\
                     tau,rotor2_R,rotor1_R,rotor0_R])
    return rho_R

def derivatives(rotors,R,n,ring="ZZZ"):
    R = list(R)
    def lettre_suivante(rotor,lettre):
        N = len(rotor)
        ind = rotor.index(lettre)
        ind_suivant = (ind + 1) % N
        return rotor[ind_suivant]
    def deriv(R):
        R[0] = lettre_suivante(rotors[0],R[0])
        if R[0] == ring[0]:
            R[1] = lettre_suivante(rotors[1],R[1])
            if  R[1] == ring[1]:
                R[2] = lettre_suivante(rotors[2],R[2])
        return R
    Rs = []
    for i in range(n):
        R = deriv(R)
        Rs = Rs + [list(R)]
    return Rs

def chiffrer(reglages,message):
    [rotors,tau,sigma,R,ring] = reglages
    Rs = derivatives(rotors,R,len(message))
    Rs = [R] + Rs
    chiffre = ""
    for i in range(len(message)):
        Ri = Rs[i]
        rho_Ri = rho(Ri)
        alpha_i = composee([sigma,rho_Ri,sigma])
        chiffre = chiffre + alpha_i[message[i]]
    return chiffre


# Donees publiques sur la machine
reflecteur = list("YRUHQSLDPXNGOKMIEBFZCWVJAT")
rotor0 = list("EKMFLGDQVZNTOWYHXUSPAIBRCJ")
rotor1 = list("AJDKSIRUXBLHWTMCQGZNPYFVOE")
rotor2 = list("BDFHJLCPRTXVZNYEIWGAKMUSQO")
rotors = [rotor0, rotor1, rotor2]
tau = dict(zip(alphabet,reflecteur))

reglages = [rotors,tau,None,None,None]
