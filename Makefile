.PHONY: all
all: format test build

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make
	
.PHONY: format
format:
	clang-format src/* include/* -i


.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build
