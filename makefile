git_deploy: git_deploy.o
	clang++-3.5 -DLINUX git_deploy.o -o git_deploy
	rm git_deploy.o
git_deploy.o:
	clang++-3.5 -std=c++11 -c git_deploy.cpp