exe=main
cpp=Main.cpp Decoupeur.cpp Graphe.cpp Filtre.cpp
head=$(cpp:.cpp=.h)
_obj= a_Main.o a_Decoupeur.o a_Graphe.o a_Filtre.o

binDir=bin/
obj=$(subst a_, $(binDir), $(_obj)) 

comp=g++ -ansi -pedantic -Wall -std=c++11 -g -D MAP
edl=-lm

$(exe) : $(obj)
	g++ -o $(exe) $(obj) $(edl)

$(binDir)%.o : %.cpp %.h
	$(comp) -o $@ -c $<

#$(binDir)Main.o : Main.cpp Main.h

clean :
	rm $(obj)
