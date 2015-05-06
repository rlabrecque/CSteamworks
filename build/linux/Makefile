STEAM_RUNTIME_TARGET_ARCH := $(shell uname -m)
ifeq ($(STEAM_RUNTIME_TARGET_ARCH), i686)
	ARCH := -m32
	LINKERSEARCHPATH := ../../redistributable_bin/linux32
else
	ARCH := -m64
	LINKERSEARCHPATH := ../../redistributable_bin/linux64
endif
CXX := g++
INCLUDES := -I"../../src" -I"../../steam" -I"../../wrapper"
CPPFLAGS := -fPIC $(ARCH) $(INCLUDES) -DVERSION_SAFE_STEAM_API_INTERFACES -DGNUC -Wall
OBJDIR := $(STEAM_RUNTIME_TARGET_ARCH)/obj
OUTFILE := $(STEAM_RUNTIME_TARGET_ARCH)/libCSteamworks.so

CPP_FILES := ../../src/steam_api.cpp
OBJ_FILES := $(OBJDIR)/steam_api.o

$(OBJDIR)/%.o:  $(CPP_FILES)
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CPPFLAGS) -c -o $@ $<
	@echo "Compiling $<"

all: $(OBJ_FILES)
	$(CXX) $(CPPFLAGS) -Wl,-z,origin '-Wl,-rpath,$$ORIGIN' -L$(LINKERSEARCHPATH) -lsteam_api -shared $^ -o $(OUTFILE)

clean:
	rm -rf ./$(STEAM_RUNTIME_TARGET_ARCH)/
