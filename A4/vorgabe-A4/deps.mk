4a.o: 4a.c 4a.h firstfit.h
4b.o: 4b.c 4b.h 4a.h firstfit.h
4c.o: 4c.c 4c.h firstfit.h
firstfit.o: firstfit.c firstfit.h
test_4a.o: test_4a.c 4a.h firstfit.h
test_4b.o: test_4b.c 4b.h 4a.h firstfit.h
test_4c.o: test_4c.c 4c.h firstfit.h
