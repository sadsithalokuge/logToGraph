exe=main
cpp=Main.cpp
head=$(cpp:.cpp=.h)
_obj= a_Main.o

binDir=bin/
obj=$(subst a_, $(binDir), $(_obj)) 

comp=g++ -ansi -pedantic -Wall -std=c++11 -g #-D MAP
edl=-lm

$(exe) : $(obj)
	g++ -o $(exe) $(obj) $(edl)

$(binDir)%.o : %.cpp %.h
	$(comp) -o $@ -c $<

#$(binDir)Main.o : Main.cpp Main.h

clean :
	rm $(obj)
