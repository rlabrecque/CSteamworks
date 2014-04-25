ifeq ($(STEAM_RUNTIME_TARGET_ARCH), i386)
	ARCH := -m32
	LINKERSEARCHPATH := ../../redistributable_bin/linux32
else
	ARCH := -m64
	LINKERSEARCHPATH := ../../redistributable_bin/linux64
endif
OBJDIR := $(STEAM_RUNTIME_TARGET_ARCH)/obj
CXX := g++
CPPFLAGS := -fPIC $(ARCH) -I"../.." -I"../../src" -I"../../steam" -DVERSION_SAFE_STEAM_API_INTERFACES -DGNUC
OUTFILE := $(STEAM_RUNTIME_TARGET_ARCH)/libCSteamworks.so

CPP_FILES1 := $(wildcard ../../src/*.cpp)
OBJ_FILES1 := $(patsubst ../../src/%.cpp,$(OBJDIR)/%.o,$(CPP_FILES1))
CPP_FILES2 := $(wildcard ../../wrapper/*.cpp)
OBJ_FILES2 := $(patsubst ../../wrapper/%.cpp,$(OBJDIR)/%.o,$(CPP_FILES2))

$(OBJDIR)/%.o:  ../../src/%.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CPPFLAGS) -c -o $@ $<
	@echo "Compiling $<"
	

$(OBJDIR)/%.o:  ../../wrapper/%.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CPPFLAGS) -c -o $@ $<
	@echo "Compiling $<"

all: $(OBJ_FILES1) $(OBJ_FILES2)
	$(CXX) $(CPPFLAGS) -Wl,--no-as-needed -L$(LINKERSEARCHPATH) -lsteam_api -shared $^ -o $(OUTFILE)

clean:
	rm -rf ./$(STEAM_RUNTIME_TARGET_ARCH)/
