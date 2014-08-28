#! /bin/sh

# Script de programmation du MSP430
#
# usage: ./upload.sh <fichier.elf>

DRIVER=rf2500
mspdebug ${DRIVER} erase
mspdebug ${DRIVER} "prog $@"

