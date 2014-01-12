CC = g++
CFLAGS = -Wall -o3

INCS = -I ./
SRCS = dm.cc nj.cc pt.cc
OBJS = $(SRCS:.cc=.o)
OUTDIR = ../Bin/

#project name
MAIN = ../Bin/LAB

all:	$(MAIN)

$(MAIN): $(OBJS)
	test -d $(OUTDIR) || mkdir $(OUTDIR)
	$(CC) $(CFLAGS) $(INCS) -o $(MAIN) $(OBJS) main.cc

.cc.o:
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 

clean:
	rm -rf $(MAIN) *.o
