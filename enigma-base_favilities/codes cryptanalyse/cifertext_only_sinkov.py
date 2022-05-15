"""
fonctionnel pour 1, 2 ou 3 paire de lettre échangées et pas plus (ne fonctionne plus)
erreur dans le papier de ref : il faut maximiser sinkov et non le minimiser
"""
from enigma import machine as m
import time

#alphabet utilise
alphabet='ABCDEFGHIJKLMNOPQRSTUVWXYZ'


#les caracteres speciaux
spec=[",", ";", ":", "!", "?", ".", "…", "/", "\n", "«", "»", "(", ")", "é", "à", "è", "ê", "ç", "ù", "î", "ô", " ", "'", "’"]
chiffre=[ "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]


#recuperation du texte
fichier=open("texte_chiffre.txt",'r')
txt=fichier.read()
fichier.close()

#frequence dans une langue
fichier=open("frequence_angl.txt", 'r')
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

	for lettre in frequ :
		frequ[lettre]=frequ[lettre]*100/len(texte) #en pourcentage
	return frequ


# statistique de Sinkov
def Sinkov(frequ_lan, frequ_txt):
	"""
	calcul la statistique de Sinkov pour un texte choisi
	frequ_lan : frequence des lettres dans la langue du texte, dico
	frequ_txt : frequence des lettres dans le texte, dico
	Sk : 		statistique de Sinkov
	"""
	Sk=0
	for i in frequ_lan:
		Sk+=frequ_lan[i]*frequ_txt[i]
	return Sk


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


# dechiffrement d'un texte
def plaintext(ciphertext, plugboard):
	"""
	determine un plaintext a partir d'un cifertext par enigme
	ciphertext : 	message chiffre, str
	plugboard : 	tableau de connexion, str
	plaintxt : 	message dechiffre
	"""
	# setup machine according to specs from a daily key sheet:
	machine = m.EnigmaMachine.from_key_sheet(
       rotors='II IV V',
       reflector='B',
       ring_settings=[1, 20, 11],
       plugboard_settings=plugboard)

	# set machine initial starting position
	machine.set_display('WXC')

	# decrypt the message key
	msg_key = machine.process_text('KCH')

	# decrypt the cipher text with the unencrypted message key
	machine.set_display(msg_key)

	plaintxt = machine.process_text(ciphertext)

	return plaintxt




#algo
gamma="" #approximation du plugboard, initialemet vide
branchement=liste_paire(alphabet) #liste de toute les permutation de lettre possible
it=0

deb=time.time()
while it < 3 :#not(stop):
	#print("debut de boucle")
	it+=1
	S_min=Sinkov(frequ_lan,frequ_lan)
	S_max=0

	for paire in branchement : #pour tous les branchement possible
		board=gamma+" "+paire #on ajoute une paire a l'approx du plugboard
		message_tmp=plaintext(txt, board) #on déchiffre le text avec le nouveau réglage
		Sk=Sinkov(frequ_lan, frequence_txt(message_tmp, alphabet)) #on clacule sinkov
		#print(paire, Sk)

		"""
		if Sk<S_min : #si plus petit que le min
			S_min=Sk #minimisation
			paire_ech=paire #sauvegarder la paire correspondante
			"""
		if Sk>S_max :#visiblement il faut bien maximiser (à préciser dans le rapport)
			S_max=Sk
			paire_ech=paire


	gamma = gamma+" "+paire_ech #approximation courante du plugboard
	message = plaintext(txt, gamma)
	suppr(paire_ech, branchement)
	#print(paire_ech, S_max)
print(message)
fin=time.time()
print(fin-deb)
