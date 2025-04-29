
compile:
	@meson setup build --wipe
	@meson compile -C build

run: compile
	@./build/src/bc