OBJDIR := obj
CXX = g++
CPPFLAGS = -fPIC -m32 -I"../../steam"

CPP_FILES := $(wildcard ../../wrapper/*.cpp)
OBJ_FILES := $(patsubst ../../wrapper/%.cpp,$(OBJDIR)/%.o,$(CPP_FILES))

$(OBJDIR)/%.o: ../../wrapper/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

all: $(OBJ_FILES)
	$(CXX) $(CPPFLAGS) -shared $^ -o libCSteamworks.so

$(OBJ_FILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf ./$(OBJDIR)/
	rm libCSteamworks.so