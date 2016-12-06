git_deploy: git_deploy.o sliza_deploy.o
	clang++-3.5 -DLINUX sliza_deploy.o git_deploy.o -o git_deploy
	rm *.o
git_deploy.o: sliza_deploy.cpp sliza_deploy.h
	clang++-3.5 -std=c++11 -c git_deploy.cpp
sliza_deploy.o: sliza_deploy.cpp sliza_deploy.h
	clang++-3.5 -std=c++11 -c sliza_deploy.cpp