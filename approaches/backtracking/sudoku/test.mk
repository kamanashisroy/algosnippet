VARIANT:=
VARIANT:=_optimized1

TARGET_VARIANT=${TARGET_PREFIX}${VARIANT}.bin

INPUTS=$(sort $(wildcard test_cases/input/*.txt))
OUTPUTS=$(subst input,myoutput${VARIANT},$(subst INPUT,MYOUTPUT,${INPUTS}))
LIMIT_CAT=100
AWK_LINE_COUNT=awk "{print \\$$1}"

all:test_cases/myoutput${VARIANT} ${OUTPUTS}

variant:
	#$(MAKE) ${goal}
	$(MAKE) VARIANT=_list ${goal}
	$(MAKE) VARIANT=_heap ${goal}
	
first:$(word 5,${OUTPUTS})

show:
	echo ${INPUTS}
	echo ${OUTPUTS}


test_cases/myoutput${VARIANT}:
	mkdir -p $@

test_cases/myoutput${VARIANT}/myoutput${VARIANT}%.txt:test_cases/input/input%.txt Makefile ${SOURCES}
	if [ "`wc -l $< | ${AWK_LINE_COUNT}`" -lt "${LIMIT_CAT}" ] ; then cat $<; fi
	export OUTPUT_PATH=$@;${TARGET_VARIANT} < $< > $@ 2> $@.err
	cat $@.err
	if [ "`wc -l $@ | ${AWK_LINE_COUNT}`" -lt "${LIMIT_CAT}" ] ; then cat $@; fi
	diff -u --ignore-space-change --strip-trailing-cr --ignore-blank-lines $@ $(subst input,output,$(subst INPUT,OUTPUT,$<))
	cmp $@ $(subst input,output,$(subst INPUT,OUTPUT,$<))

plot:
	python plot.py

clean:clean-test

clean-test:
	@rm ${OUTPUTS}

.PHONY:clean all variant clean-test


