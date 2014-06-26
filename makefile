#Edit this to select source files
Sources=main.cpp encryptor.cpp
#This determines the executable name
Executable=encryptor.exe
#Change these to change compiler settings
CFlags=-c -Wall -std=c++11
LDFlags=
CC=g++
#Change these to select where you store your files. Place a period for the root folder
ObjectDir=obj
SourceDir=src
BinDir=.

#Leave everything below here alone!!
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir)/,$(Sources))
CObjects=$(addprefix $(ObjectDir)/,$(Objects))
CExecutable=$(addprefix $(BinDir)/,$(Executable))

all:$(CSources) $(CExecutable)

$(CExecutable): $(CObjects) | $(BinDir)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(CObjects): | $(ObjectDir)

$(ObjectDir):
	mkdir -p $@

$(ObjectDir)/%.o: $(SourceDir)/%.cpp
	$(CC) $(CFlags) $< -o $@

$(BinDir):
	mkdir -p $(BinDir)

clean:
	rm -rf $(ObjectDir)/*.o $(CExecutable)