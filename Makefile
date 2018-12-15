#-------------prekladac-------------#
CC=gcc
CPPC=g++

#-------------flagy-------------#
CFLAGS= -std=c99 -pedantic -Wall
CPPFLAGS= -std=c++11 -Wall -pedantic

#-------------soubory-------------#
JMENA=tail tail2 wordcount wordcount-dynamic

#-------------objektove soubory pro knihovny-------------#
KNIHOVNI=htab_clear.o htab_init.o htab_lookup_add.o htab_free.o htab_foreach.o htab_remove.o htab_find.o htab_size.o htab_bucket_count.o htab_hash_function.o

all: $(JMENA)

tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

tail2: tail2.cc
	$(CPPC) $(CPPFLAGS) -o tail2 tail2.cc

#-------------staticka verze-------------#
wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount -static io.o wordcount.o libhtab.a

#-------------dynamicka verze-------------#
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o libhtab.so

#-------------staticka knihovna-------------#
libhtab.a: $(KNIHOVNI)
	ar crs libhtab.a $(KNIHOVNI)

#-------------dynamicka knihovna-------------#
libhtab.so: $(KNIHOVNI)
	$(CC) $(CFLAGS) -shared -fPIC $(KNIHOVNI) -o libhtab.so

#-------------Objektove soubory-------------#
wordcount.o: wordcount.c htab.h
	$(CC) $(FLAGS) -c wordcount.c -o wordcount.o
io.o:
	$(CC) $(CFLAGS) -c io.c -o io.o
hash_function.o: hash_function.c hash_function.h
	$(CC) $(CFLAGS) -fPIC -c hash_function.c
htab_clear.o: htab_clear.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o
htab_init.o: htab_init.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o
htab_lookup_add.o: htab_lookup_add.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o
htab_free.o: htab_free.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o
htab_foreach.o: htab_foreach.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_foreach.c -o htab_foreach.o
htab_remove.o: htab_remove.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c -o htab_remove.o
htab_find.o: htab_find.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o
htab_size.o: htab_size.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o
htab_bucket_count.o: htab_bucket_count.c htab.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o
#-------------Clean-------------#
clean:
	rm -f *.o $(JMENA) libhtab.so libhtab.a
#-------------ZIP-------------#
zip:
	zip xdorda00.zip *.c *.cc *.h Makefile
