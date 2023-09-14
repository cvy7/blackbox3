TRG = blackbox3

#SRC = $(TRG).c modbus.c modbus-tcp.c  modbus-rtu.c  modbus-data.c
SRC = $(TRG).c conv_npch.c osc.c draw.c
#HD  =  config.h modbus-version.h modbus.h modbus-tcp.h modbus-tcp-private.h modbus-rtu.h modbus-rtu-private.h modbus-private.h
OBJ = $(SRC:.c=.o)
LIBS =-L ./ -lgd 

CCFLAGS = -Wall  -g -O3 

all : $(TRG)

%.o : %.c $(HD)
	gcc $(CCFLAGS) -c $< -o $@

$(TRG) : $(OBJ)
	gcc $(CCFLAGS) $(OBJ) -o $@ -L libgd.so -lgd -Wl,-rpath, libgd.so

clean:
	rm -f $(OBJ)
	#rm -f $(TRG)
