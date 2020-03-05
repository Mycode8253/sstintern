
CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)

all: libmcpu.so install

libmcpu.so: myCpu.cc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

install:
	sst-register mcpu mcpu_LIBDIR=$(CURDIR)

clean:
	rm -f *.o libmcpu.so

