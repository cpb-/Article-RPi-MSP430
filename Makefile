CC=      msp430-gcc
CFLAGS=  -Wall -mmcu=msp430g2553
LDFLAGS= -mmcu=msp430g2553

ELF_FILES=                 \
	msp430-spi-1.elf   \
	msp430-spi-2.elf   \
	msp430-spi-3.elf   \
	msp430-spi-4.elf   \
	msp430-spi-5.elf   \

.PHONY: all
all: $(ELF_FILES)


%.elf: %.c
	$(CC) $(CFLAGS) -o $@  $<

.PHONY: clean
clean:
	rm -f *.elf *~ 
