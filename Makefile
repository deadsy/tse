BUILD = build

.PHONY: all
all: .stamp_cmake build

.PHONY: build
build: .stamp_cmake
	ninja -C $(BUILD)

.PHONY: clean
clean:
	-rm -rf $(BUILD)
	-rm -rf .stamp*

.stamp_cmake:
	-rm -rf $(BUILD)
	cmake -GNinja -S src -B $(BUILD)
	touch $@
