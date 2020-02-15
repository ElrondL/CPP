.PHONY: all, clean, distclean, pack, pack-solution

all: test-ball test-ball-graphics test-springmass test-springmass-graphics
test-ball : ball.cpp ball.h test-ball.cpp
test-ball-graphics : graphics.cpp ball.cpp test-ball-graphics.cpp
test-springmass : springmass.cpp test-springmass.cpp
test-springmass-graphics : graphics.cpp springmass.cpp test-springmass-graphics.cpp

CXX=g++
CXXFLAGS=-lglut -lGL

clean:
	find . -name '*~' -delete
	rm -f b16-lab.{ncb,suo,v11.suo,sdf,opensdf}
	rm -f b16-lab.vcproj.*.user
	rm -rf Debug/
	rm -rf b16-lab/
	rm -f test-ball test-ball-graphics test-springmass test-springmass-graphics

distclean: clean
	rm -f b16-lab.zip b16-lab-solution.zip

pack-solution:
	rm -f b16-lab-solution.zip
	git archive --format zip --prefix=b16-lab-solution/ --output b16-lab-solution.zip master

pack: pack-solution
	git archive master --prefix=b16-lab/ | tar x
	echo "$$sed_command"
	cd b16-lab ; \
	for x in *.h *.cpp ; \
	do \
	  cat "$$x" | \
	  sed '/begin remove/,/end remove/c\'$$'\n'$$'\\\n''/* INCOMPLETE: TYPE YOUR CODE HERE */'$$'\\\n'$$'\\\n' \
	  > "$${x}.tmp" ; \
	  mv "$${x}.tmp" "$$x" ; \
	done
	rm -f b16-lab.zip
	zip -r b16-lab.zip b16-lab/
	rm -rf b16-lab/
