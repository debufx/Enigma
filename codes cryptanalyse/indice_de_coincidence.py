"""
grand texte, p paires échangées
On part du principe qu'on connait les câblages des rotors.
On cherche donc le positionnement, le réglage des rotors et les fiches.
Le but va être de calculer l’IC du texte pour toutes les positions de rotors et de prendre la plus haute valeur.
"""
from enigma import machine as m
from itertools import permutations

#alphabet utilise
alphabet='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

#liste des rotors
Rot=['I', 'II', 'III', 'IV', 'V']


#les caracteres speciaux
spec=[",", ";", ":", "!", "?", ".", "…", "/", "\n", "«", "»", "(", ")", "é", "à", "è", "ê", "ç", "ù", "î", "ô", " ", "'", "’", "-", "–", "_"]
chiffre=[ "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]


#recuperation du texte
fichier=open("texte_chiffre.txt",'r')
txt=fichier.read()
fichier.close()

#frequence dans une langue
fichier=open("frequence_fr.txt", 'r')
frequ_lan= {ltr : float(freq) for ltr ,freq in(line.replace("\n",'').split(";") for line in fichier)}
fichier.close()


# frequence dans le texte choisi
def frequence_txt(texte, alphabet):
	"""
	determine la frequence des lettres dans le texte donne en argument
	texte : 	texte etudie, str
	alphabet : 	l'alphabet utilise pour le texte, str
	frequ : 	frequences, dico
	"""
	frequ={char : 0 for char in alphabet}

	for char in texte :
		if char.upper() in frequ :
			frequ[char.upper()]+=1 #combien de chaque lettre ?
	"""
	for lettre in frequ :
		frequ[lettre]=frequ[lettre]*100/len(texte) #en pourcentage
	"""
	return frequ

# taille du texte étudié (sans les caractères spéciaux)
def taille(texte):
	"""
	compte le nombre de lettre dans le texte donné
	(sans les espace, passage à la ligne et caractère spéciaux)
	"""
	length=0
	for char in texte :
		if char not in spec+chiffre :
			length+=1
	return length


# indice de coincidence
def Coincidence(texte): #arp, il y a un problme de l'ordre de 10**3...
	"""
	calcul l'indice de coincidence' pour un texte choisi
	frequ_lan : frequence des lettres dans la langue du texte, dico
	frequ_txt : frequence des lettres dans le texte, dico
	Sk : 		statistique de Sinkov
	"""
	IC=0
	frequ_txt=frequence_txt(txt, alphabet)
	n=taille(texte)
	#n=len(texte)
	for i in frequ_txt:
		IC+=(frequ_txt[i]*(frequ_txt[i]-1))/(n*(n-1))
	return IC






#liste des paire de lettre
def liste_paire(alphabet):
	"""
	alphabet : 	alphabet sans parmutation
	liste :     liste de toute les paires de lettre parmutable
	"""
	liste=[]
	for lettre1 in alphabet:
		alphabet2 = alphabet[alphabet.index(lettre1)+1:]
		for lettre2 in alphabet2 :
			liste.append(lettre1+lettre2)
	return(liste)


#liste des arrangement possible des rotors
def arrangement(liste, nb):
	"""
	retourn la liste de tous les arrangement possible de nb rotor parmis la liste de rotors donnée
	liste : liste de rotors
	nb : monbre de rotor à garder
	lst_tpl_arr : liste de tuple d'arrangement
	lst_arr : liste de chaine de caractère d'arrangement (expl : 'I II III')
	"""
	lst_tpl_arr=list(permutations(liste,nb))
	lst_arr=[]
	for arr in lst_tpl_arr:
		#print(arr)
		arr_char=''
		for elt in arr:
			arr_char+=elt+' '
		lst_arr.append(arr_char[:len(arr_char)-1])
	return(lst_arr)



# dechiffrement d'un texte
def plaintext(ciphertext,rot, plugboard):
	"""
	determine un plaintext a partir d'un cifertext par enigme
	ciphertext : 	message chiffre, str
	plugboard : 	tableau de connexion, str
	plaintxt : 	message dechiffre
	rot : les rotor à utiliser
	"""
	# setup machine according to specs from a daily key sheet:
	machine = m.EnigmaMachine.from_key_sheet(
       rotors=rot,#'II IV V',
       reflector='B',
       ring_settings=[1, 20, 11],
       plugboard_settings=plugboard)#'AV BS CG')

	# set machine initial starting position
	machine.set_display('WXC')

	# decrypt the message key
	msg_key = machine.process_text('KCH')

	# decrypt the cipher text with the unencrypted message key
	machine.set_display(msg_key)

	plaintxt = machine.process_text(ciphertext)

	return plaintxt



#suppression
def suppr(paire, branchement):
	"""
	suppression d'une paire et de toute les paire qui utilise une des deux lettre de la paire
	paire : paire étudiée
	branchement : liste des permutations
	"""
	branchement.pop(branchement.index(paire))
	a_suppr=[]
	for var in branchement :
		if (paire[0] in var or paire[1] in var) :
			a_suppr.append(var)
			#print(a_suppr)
	for i in a_suppr :
		branchement.pop(branchement.index(i))

#algo
gamma="" #approximation du plugboard, initialemet vide
branchement=liste_paire(alphabet) #liste de toute les permutation de lettre possible
it=0

it=0
"""
S_min_prec=0
S_min=Sinkov(frequ_lan,frequ_lan)
stop=abs(S_min_prec - S_min)<1
"""

"""
#ça doit pas être comme ça qu'on l'utilise...
while it<3 :#not(stop):
	print("debut de boucle")
	it+=1
	IC_M=0

	for paire in branchement :
		board=gamma+" "+paire
		message_tmp=plaintext(txt, board)
		IC=Coincidence(txt)

		if IC>IC_M :#visiblement il faut bien maximiser (à préciser dans le rapport)
			IC_M=IC
			paire_ech=paire


	gamma = gamma+" "+paire_ech#approximation courante du plugboard
	message = plaintext(txt, gamma)
	suppr(paire_ech, branchement)
	print(paire_ech, IC_M)
print(message)
"""

#algo2
Rot_util=['II', 'IV', 'V']
liste_arr=arrangement(Rot_util,len(Rot_util))
print(liste_arr)
ICM=0
#print(ICM)

for arr in liste_arr:
	message_tmp=plaintext(txt, arr, 'AV BS CG')
	IC=Coincidence(message_tmp)
	print(arr)
	print(IC)
	if IC>ICM :
		ICM=IC
		arr_best=arr

print(arr_best)
print(ICM)
message=plaintext(txt, arr_best, 'AV BS CG')
#print(message)
