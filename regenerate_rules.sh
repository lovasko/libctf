#!/usr/local/bin/bash

# (re)create files
echo "Initialisation"
echo '' > link_rule.ninja
echo '' > compile_rules.ninja

echo "Compilation rules"
# create compile rules
for source in `find src/ -name '*.c'`
do
	object=${source/src/obj}
	object=${object/.c/.o}
	echo "build $object: compile $source" >> compile_rules.ninja
done

# create link rule
echo "Link rule"
objects=`find src/ -name '*.c' | tr "\n" " " | sed 's/\.c/\.o/g'`
echo "build bin/libbsdctf.so: link ${objects//src/obj}" >> link_rule.ninja

