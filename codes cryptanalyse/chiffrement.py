#from enigma.machine import EnigmaMachine
from enigma import machine as m

#recuperation du texte
fichier=open("Ruy_Blas.txt",'r')
txt=fichier.read()
fichier.close()

#pretraitement du texte
def traitement(texte):
    alphabet_ref='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    accent='éèêëÉÈÊËàâäÀÂÄîïÎÏôöÔÖùûüÙÛÜ'
    sans_accent='eeeeEEEEaaaAAAiiIIooOOuuuUUU'
    txt=''
    for car in texte :
        if car in alphabet_ref :
            txt+=car
        elif car in accent :
            txt+=sans_accent[accent.find(car)]
    return(txt)


# setup machine according to specs from a daily key sheet:
def chiffrement(ciphertext):
    machine = m.EnigmaMachine.from_key_sheet(
           rotors='I II IV',
           reflector='B',
           ring_settings=[1, 3, 6],
           plugboard_settings='AD BE CF')

    # set machine initial starting position
    machine.set_display('WXC')

    # decrypt the message key
    msg_key = machine.process_text('KCH')

    # decrypt the cipher text with the unencrypted message key
    machine.set_display(msg_key)

    plaintext = machine.process_text(ciphertext)

    return(plaintext)

#txt="Dans l’art de perdre il n’est pas dur de passer maitre ;tant de choses semblent si pleines d’envie d’etre perdues que leur perte n’est pas un desastre."

#écriture du résultat
fichier=open("texte_chiffre.txt",'w')
txt_traite=traitement(txt)
plaintext=chiffrement(txt_traite)
fichier.write(plaintext)
fichier.close()
#print(plaintext)


"""
fichier=open("alphabet.txt",'r')
for line in fichier :
    ciphertext=line[:10]
    plaintext = machine.process_text(ciphertext)
    print(plaintext)
fichier.close()
"""

#print(traitement(txt))
