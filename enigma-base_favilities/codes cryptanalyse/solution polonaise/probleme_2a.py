"""
objectif = trouver la position initiale des rotors en ne connaissanant que eps_(j+3) pour eps_j
"""
from infos_publiques import *
import time


def deduire(messages_interceptes):
	"""
	deduit des messages interceptes les permutations qui definissent beta1 (lettres 0 et 3), beta2 (1,4) et beta3 (2,5)
	message_interceptes : 	liste de chaines de characteress de longeurs 6 et representant les chiffres des repete des 3 lettres de debut de message
	beta : 			liste de dictionnaire
	beta_i :		dictionnaire contenant les lettres et leur permutation deduite des messages interceptes
	"""

	betas = []
	for i in range(3):
		beta_i = dict([[e,e] for e in alphabet])
		for message in messages_interceptes:
			beta_i[message[i]] = message[i+3]
		betas = betas + [beta_i]
	return betas



def motif_de_decomposition(alpha):
	"""
	determine le motif de decomposation d'un schema de permutation donne
	alpha : dictionnaire contenant les lettres et leur permutation
	vu : liste de booleen
	total_fait : entier
	motif : motif de decomposition du dictionnaire etudie i.e. liste des longueurs des orbites triees par ordre croissant
	"""
	N = len(alphabet)
	vu = [False for i in range(N)]
	total_fait = 0
	motif = []
	while total_fait < N:
		ind = vu.index(False) 			#recupere l'indice du premier false
		vu[ind] = True 				#le met a true
		lettre = alphabet[ind] 			#recupere la lettre correspondant a cet indice
		lettre_debut = lettre 			#la marque comme debut d'un cycle
		longueur_cycle = 1 			#initialise la longueur de ce cycle
		lettre = alpha[lettre] 			#recupere la lettre correspondant a la permutation de la lettre du debut
		vu[alphabet.index(lettre)] = True 	#signale que cette lettre a ete vu
		total_fait += 1				#incremente le nombre de lettre observee
		while lettre != lettre_debut:  #tq on est pas retourne au depart du cycle
			lettre = alpha[lettre]
			vu[alphabet.index(lettre)] = True
			total_fait += 1
			longueur_cycle += 1
		motif = motif + [longueur_cycle]
	motif.sort()
	return motif



def debug_deduire(rotors,reflecteur,betas,sigma,R):
	tau = dict(zip(alphabet,reflecteur))
	R1,R2,R3,R4,R5 = derivatives(rotors,list(R),5)

	beta_R = composee([sigma,rho(R3),inverse(rho(R)),sigma])
	beta_R1 = composee([sigma,rho(R4),inverse(rho(R1)),sigma])
	beta_R2 = composee([sigma,rho(R5),inverse(rho(R2)),sigma])


	if beta_R != betas[0]:
		print ("beta0",alpha_R,betas[0])
	if beta_R1 != betas[1]:
		print ("beta1",beta_R1,betas[1])
	if beta_R2 != betas[2]:
		print ("beta2",beta_R2,betas[2])



def resout_probleme_2a(rotors,reflecteur,motifs_but):
	solutions = []
	for R in ensemble_puissance(alphabet,repeat=3):
		tau = dict(zip(alphabet,reflecteur))
		R1,R2,R3,R4,R5 = derivatives(rotors,list(R),5)

		alpha_R = composee([rho(R3),inverse(rho(R))])
		alpha_R1 = composee([rho(R4),inverse(rho(R1))])
		alpha_R2 = composee([rho(R5),inverse(rho(R2))])

		motif0 = motif_de_decomposition(alpha_R)
		motif1 = motif_de_decomposition(alpha_R1)
		motif2 = motif_de_decomposition(alpha_R2)

		motifs = [motif0,motif1,motif2]
		#print motifs
		if motifs == motifs_but:
			solutions = solutions + [R]
	return solutions


# donnees du probleme
messages_interceptes = \
['RWMRHQ', 'VNFDRF', 'DXWIVI', 'CESBZN', 'XDIHPM', 'SLBZQB', 'QKULTR', 'OSKEAU', 'NRECLC', 'LZNVOT', 'TGHYSZ', 'JFVGIY', 'WQAQWE', 'IBJOXD', 'HVXNJX', 'UUTUES', 'GMRMFA', 'AIQABG', 'FHDTKP', 'KYPSGJ', 'PPGPYH', 'BOLJCW', 'MACXMV', 'ECOWNO', 'ZTZKUL', 'YJYFDK']# a solidifier... beaucoup trop fragile

# calcul principal :
[rotors,reflecteur,_,_,_] = reglages
betas =  deduire(messages_interceptes)
print (betas)
motifs_but = [motif_de_decomposition(beta) for beta in betas]
deb=time.time()
solutions = resout_probleme_2a(rotors,reflecteur,motifs_but)
fin=time.time()
print ("Les positions possibles des rotors sont",solutions)
print(fin-deb)


""" debug
sigma_C = sigma(["CR","YP","TO","GA","PH","ES"])
sigma_C = sigma([])
R = ("B","O","B")
debug_deduire(rotors,reflecteur,betas,sigma_C,R)
"""
