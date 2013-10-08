include ./makefile.conf
NAME=LPC4357-Blinky
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main -DCORE_M4 -D__GNU_ARM -D_GPIO

LDSCRIPTS=-L. -L$(BASE)/ldscripts -T gcc.ld
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

all: $(NAME)-$(CORE).axf $(NAME)-$(CORE).bin

$(NAME)-$(CORE).axf: $(NAME).c lpc4300/lpc43xx_scu.c lpc4300/lpc43xx_cgu.c lpc4300/lpc43xx_gpio.c lpc4300/system_LPC43xx.c $(STARTUP)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
	
$(NAME)-$(CORE).bin:$(NAME)-$(CORE).axf
	$(OBJCOPY) -O binary $(NAME)-$(CORE).axf $(NAME)-$(CORE).bin

clean: 
	rm -f $(NAME)*.axf *.map $(NAME)*.bin
