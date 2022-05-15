from itertools import product, permutations
from enigma import machine as m
import time
from threading import Thread
from queue import Queue, Empty

#alphabet utilise
alphabet='ABCDEFGHIJKLMNOPQRSTUVWXYZ'


#recuperation du texte
fichier=open("texte_chiffre.txt",'r')
txt=fichier.read()
fichier.close()


#frequence dans une langue
fichier=open("frequence_fr.txt", 'r')
frequ_lan= {ltr : float(freq) for ltr ,freq in(line.replace("\n",'').split(";") for line in fichier)}
fichier.close()





#pretraitement du texte
def traitement(texte):
	"""
	on enleve toute la ponctuation, les accents et les espaces d'un texte donne
	"""
	alphabet_ref='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
	accent='éèêëÉÈÊËàâäÀÂÄîïÎÏôöÔÖùûüÙÛÜ'
	sans_accent='eeeeEEEEaaaAAAiiIIooOOuuuUUU'
	txt_res=''
	for car in texte :
		if car in alphabet_ref :
			txt_res+=car.upper()
		elif car in accent :
			txt_res+=sans_accent[accent.find(car)].upper()
	return(txt_res)


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


# indice de coincidence
def Coincidence(texte):
	"""
	calcul l'indice de coincidence pour un texte choisi
	frequ_lan : frequence des lettres dans la langue du texte, dico
	frequ_txt : frequence des lettres dans le texte, dico
	IC : 		indice de coincidence
	"""
	IC=0
	frequ_txt=frequence_txt(texte, alphabet)
	n=len(texte)#taille(texte)
	for i in frequ_txt:
		IC+=(frequ_txt[i]*(frequ_txt[i]-1))/(n*(n-1))
	return IC







#liste des combinaisons de rotors
def combinaisons(liste, nb):
	"""
	retourn la liste de toute les combinaison possible de position initiales des rotors
	"""
	comb = []
	#fichier=open("combinaisons_rotors.txt",'a')
	list_tuple = list(product(liste,repeat=nb)) #liste de tuple

	for tuple in list_tuple :
		comb.append(list(tuple)) #liste de liste
		#fichier.write(str(list(tuple))+'\n')

	#fichier.close()
	return comb


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
	#fichier=open("arrangement_rotors.txt",'a')

	for arr in lst_tpl_arr:
		#print(arr)
		arr_char=''
		for elt in arr:
			arr_char+=elt+' '
		lst_arr.append(arr_char[:len(arr_char)-1])
		#fichier.write(str(arr_char[:len(arr_char)-1])+'\n')

	#fichier.close()
	return(lst_arr)


#liste des paires de lettre
def liste_paire(alphabet):
	"""
	alphabet : 	alphabet d'origine
	liste :     liste de toute les paires de lettre parmutable
	"""
	liste=[]
	for lettre1 in alphabet:
		alphabet2 = alphabet[alphabet.index(lettre1)+1:]
		for lettre2 in alphabet2 :
			liste.append(lettre1+lettre2)
	return(liste)

def plausible(groupe):
	"""
	retourne si un branchement est plausible ou pas (pas de lettre branchées 2 fois ou avec elles même)
	groupe : le groupe de paire à tester
	"""
	ok=True
	car=0
	while ok and car<len(groupe) :
		if groupe[car]!=' ':
			if groupe.count(groupe[car])>1 :
				ok=False
		car += 1
	return ok


def arrangement_paire(liste, nb):
	#print('pouet')
	retour = []
	#fichier=open("paires_lettres.txt",'a')
	arr = arrangement(liste, nb)
	#print(arr)
	for groupe in arr:
		if (plausible(groupe)):
			retour.append(groupe)
			#fichier.write(str(groupe)+'\n')

	#fichier.close()

	return(retour)








# dechiffrement d'un texte
def plaintext(ciphertext, pos_rotors, ring, plugboard):
	"""
	determine un plaintext a partir d'un cifertext par enigme
	ciphertext : 	message chiffre, str
	plugboard : 	tableau de connexion, str
	plaintxt : 	message dechiffre
	rot : les rotor à utiliser
	"""
	# setup machine according to specs from a daily key sheet:
	machine = m.EnigmaMachine.from_key_sheet(
	   rotors=pos_rotors,#'II IV V',
	   reflector='B',
	   ring_settings=ring,#[1, 20, 11],
	   plugboard_settings=plugboard)#'AV BS CG')

	# set machine initial starting position
	machine.set_display('WXC')

	# decrypt the message key
	msg_key = machine.process_text('KCH')

	# decrypt the cipher text with the unencrypted message key
	machine.set_display(msg_key)

	plaintxt = machine.process_text(ciphertext)

	return plaintxt










fichier = open("resultats.txt",'a')
thread_run = True #variable de vie des threads





def calculateur(ciphertext, plugboard):
	"""
	pos_rotors : UNE position de rotors (expl : 'I II III')
	ring : UN réglage initial (expl : [0, 0, 0])
	plugboard : une LISTE de branchements
	"""#result = 0
	#n = 0
	#dico_IC = {}
	while thread_run:
		try:
			n = queue.get(block=False) #on récupère le reglage initial à tester
			IC = 0
			stop = IC>0.06
			i = 0
			#liste_IC = [Coincidence(texte) for texte in [plaintext(ciphertext, pos_rotors, n, plug) for plug in plugboard]] #liste d'indice de conicidence
			for plug in plugboard:
				texte = plaintext(ciphertext, n[0], n[1], plug)
				IC = Coincidence(texte)
				#print(IC)
				dico_IC[IC] = (n[0], n[1], plug)
				fichier.write(str(IC)+';'+str((n[0], n[1], plug))+'\n')
				#print(dico_IC)
			#result = max(liste_IC) #max de la liste d'IC
			queue.task_done()
		except Empty:
			pass




positions = [i for i in range(0,26)]
rot = ['I', 'II', 'III', 'IV', 'V']
nb_rotors = 3
nb_paire_ech = 3
ciphertext = traitement(txt)

deb=time.time()
Arrangements = arrangement(rot, nb_rotors)
Combinaisons = combinaisons(positions, nb_rotors)
Arrangements_Paires = arrangement_paire(liste_paire(alphabet), nb_paire_ech)

#Arrangements = ['I II III', 'I II IV', 'I III II', 'I IV II']
#Combinaisons = [[1, 1, 1], [1, 2, 4], [1, 8, 6], [1, 3, 6]]
#Arrangements_Paires = ['AF BE CD', 'AG BH CI', 'AK BL CM', 'AN BO CP', 'AQ BR CS', 'AD BE CF']
fin=time.time()

print('génération : ',fin-deb)
print(len(Arrangements))
print(len(Combinaisons))
print(len(Arrangements_Paires))








thread_count = 7
queue = Queue()
#dico_calcul = {}
dico_IC = {}
thread=[]

deb=time.time()



for i in range(thread_count):
    calcul = Thread(target = calculateur, args=(ciphertext, Arrangements_Paires))
    calcul.start()
    #dico_calcul.update(dico_IC)
    thread.append(calcul)
    #print("5")

for c in Combinaisons:
    for a in Arrangements:
        queue.put([a,c]) #contient la liste des réglage initiaux des rotors à tester
queue.join()
thread_run = False



#print(dico_IC)
print(max(dico_IC),' : ', dico_IC[max(dico_IC)])
#print(thread)

fin=time.time()
print('calculs : ', fin-deb)
fichier.write(fin-deb)
fichier.close()












"""
entrée :
thread_count = 2
Arrangements = ['I II III', 'I II IV', 'I III II', 'I IV II']
Combinaisons = [[1, 1, 1], [1, 2, 4], [1, 8, 6], [1, 3, 6]]
Arrangements_Paires = ['AF BE CD', 'AG BH CI', 'AK BL CM', 'AN BO CP', 'AQ BR CS', 'AD BE CF']

sortie :
('I II IV', [1, 3, 6], 'AD BE CF')
0.7572920322418213 (0.752 avec 4 threads)





entrée :
thread_count = 4
Arrangements = arrangement(rot, nb_rotors)
Combinaisons = [[1, 1, 1], [1, 2, 4], [1, 8, 6], [1, 3, 6]]
Arrangements_Paires = ['AF BE CD', 'AG BH CI', 'AK BL CM', 'AN BO CP', 'AQ BR CS', 'AD BE CF']

sortie :
('I II IV', [1, 3, 6], 'AD BE CF')
11.415453433990479





entrée :
thread_count = 4
Arrangements = arrangement(rot, nb_rotors)
Combinaisons = combinaisons(positions, nb_rotors)
Arrangements_Paires = ['AF BE CD', 'AG BH CI', 'AK BL CM', 'AN BO CP', 'AQ BR CS', 'AD BE CF']

sortie :
...
...
"""


#for i in range(thread_count):
#	queue.put(None)
#for t in liste_calcul :
#	t.join()

#print(liste_calcul)
