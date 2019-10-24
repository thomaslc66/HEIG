#!/usr/bin/env python2
# encoding: utf-8
from pwn import *
import argparse

parser = argparse.ArgumentParser("Template d'exploitation SLO level3")
parser.add_argument('--file', '-f', type=str, default="./cha1", help="name of the binary to exploit")
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


#on affiche un partie de la mémoire avec %x
payload = 'Z' + "%x" * 99
payload = "materialistically"
#payload = "6553796d746572637373615064726f77"
r.sendlineafter('Login : ', payload)

r.interactive()
r.close()

