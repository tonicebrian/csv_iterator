debug: dist/Debug/Makefile
	cd dist/Debug; make

release: dist/Release/Makefile
	cd dist/Release; make

dist/Debug/Makefile: CMakeLists.txt
	mkdir -p dist/Debug; cd dist/Debug; cmake -DCMAKE_BUILD_TYPE=Debug ../..; 

dist/Release/Makefile: CMakeLists.txt
	mkdir -p dist/Release; cmake -DCMAKE_BUILD_TYPE=Release ../..

clean:
	rm -rf dist

test: debug
	dist/Debug/UnitTester
	
