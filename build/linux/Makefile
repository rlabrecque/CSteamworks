OBJDIR := obj
CXX := g++
CPPFLAGS := -fPIC -m32 -I"../../src" -I"../../steam" -DVERSION_SAFE_STEAM_API_INTERFACES

CPP_FILES1 := $(wildcard ../../src/*.cpp)
OBJ_FILES1 := $(patsubst ../../src/%.cpp,$(OBJDIR)/%.o,$(CPP_FILES1))
CPP_FILES2 := $(wildcard ../../wrapper/*.cpp)
OBJ_FILES2 := $(patsubst ../../wrapper/%.cpp,$(OBJDIR)/%.o,$(CPP_FILES2))

$(OBJDIR)/%.o:  ../../src/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:  ../../wrapper/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

all: $(OBJ_FILES1) $(OBJ_FILES2)
	$(CXX) $(CPPFLAGS) -Wl,--no-as-needed -L../../redistributable_bin/linux32 -lsteam_api -shared $^ -o libCSteamworks.so

clean:
	rm -rf ./$(OBJDIR)/
	rm -f libCSteamworks.so
