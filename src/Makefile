# https://github.com/bxparks/EpoxyDuino#managing-multiple-makefiles

runtests: make_all
	@set -e; \
	for i in */Makefile; do \
		echo '==== Running:' $$(dirname $$i); \
		$$(dirname $$i)/$$(dirname $$i)Test.out; \
	done

make_all:
	@set -e; \
	for i in */Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) -j; \
	done

clean:
	@set -e; \
	for i in */Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) clean; \
	done
