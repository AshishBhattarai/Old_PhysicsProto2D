#!/bin/sh

mkdir -p build && cd build && cmake ../ -DUSE_SHARED_ASIO=off -DUSE_SHARED_GLM=off && make && cp compile_commands.json .. && cd ..
if [[ "$1" == "r" ]]; then
	cd bin && ./phy-proto && cd ..
fi
