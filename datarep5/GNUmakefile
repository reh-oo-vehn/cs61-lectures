PROGRAMS = opt1 opt1-noopt opt2 opt2-noopt \
	ubsignedinc ubsignedinc-noopt \
	ubsignedloop ubsignedloop-noopt \
	ubunsignedloop ubunsignedloop-noopt \
	ubsafeloop ubsafeloop-noopt \
	ubtable ubtable-noopt \
	wtf
all: $(PROGRAMS)

BASEPROGRAMS = opt1 opt2 ubsignedinc ubsignedloop ubunsignedloop ubsafeloop ubtable wtf
ALLPROGRAMS = $(PROGRAMS) accessor mb3 mb4

variants = $(1) $(addsuffix -noopt,$(1)) \
	$(addsuffix -clang,$(1)) $(addsuffix -clang-noopt,$(1)) \
	$(addsuffix -gcc,$(1)) $(addsuffix -gcc-noopt,$(1))

NEED_CXX_GCC = 1
NEED_CXX_CLANG = 1
include ../common/rules.mk


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%-clang.o: %.cc $(BUILDSTAMP)
	$(CXX_CLANG) $(CLANG_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%-gcc.o: %.cc $(BUILDSTAMP)
	$(CXX_GCC) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%-noopt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

%-clang-noopt.o: %.cc $(BUILDSTAMP)
	$(CXX_CLANG) $(CLANG_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

%-gcc-noopt.o: %.cc $(BUILDSTAMP)
	$(CXX_GCC) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<


# Rules for making executables (runnable programs) from object files

$(BASEPROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -clang,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_CLANG) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -gcc,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_GCC) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^

$(addsuffix -gcc-noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_GCC) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^

$(addsuffix -clang-noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_CLANG) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^

mb%: mb%.o mb-driver.o hexdump.o
	$(CXX) $(CXXFLAGS) -pthread $(LDFLAGS) $(O) -o $@ $^


clean:
	rm -rf $(call variants,$(ALLPROGRAMS)) *.o $(DEPSDIR)

.PHONY: all clean
.PRECIOUS: addf%.o
