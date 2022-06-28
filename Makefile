COMPILER = g++
COMPILER_FLAGS = -g -c

SOURCEDIR = src/main
BUILDDIR = build

SOURCES = $(wildcard src/main/**/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

default: create_build_dir $(OBJECTS)

# builds every source file into objects file
$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCES)
	@mkdir -p $$(dirname $@)
	@echo Folder for object file created
	$(CC) $(FLAGS) $< -o $@
	@echo Object file compiled: $@

create_build_dir:
	@mkdir -p $(BUILDDIR)
	@echo Build folder created

# build_src:
# 	set -e; \
# 	for i in $(SOURCES); do \
# 		echo '==== Making:' $$i; \
# 		$(CC) $(FLAGS) $$i; \
# 	done

# $(OBJECTS): $(BUILDDIR)/%.o : $(SOURCES)
#     $(CC) $(FLAGS) $< -o $@

all222:
	set -e; \
	for i in */Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) -j; \
	done

# Don't 'set -e' because some of these tests are expected to fail
runtests:
	for i in */Makefile; do \
		echo '==== Running:' $$(dirname $$i); \
		$$(dirname $$i)/$$(dirname $$i).out; \
	done

clean:
	set -e; \
	for i in */Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) clean; \
	done
	rm -f $(BUILDDIR)/*o

compile_main:
	set -e; \
	for i in ../crazyclock/*.cpp; do \
		echo '==== Making:' $$(dirname $$i); \
	done
