CUR_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PARENT_DIR := $(abspath $(CUR_DIR)/..)

DEBUG_FLAGS = -DCMAKE_BUILD_TYPE=Debug
RELEASE_FLAGS = -DCMAKE_BUILD_TYPE=Release

RELEASE_BUILD_DIR=${PARENT_DIR}/build/release
DEBUG_BUILD_DIR=${PARENT_DIR}/build/debug

debug:
	@echo "generating cmake config"
	@cmake -G "Unix Makefiles" -S ${PARENT_DIR} -B ${PARENT_DIR}/build/debug ${DEBUG_FLAGS} \
	&& make -C ${PARENT_DIR}/build/debug

release:
	@echo "generating cmake config"
	@cmake -G "Unix Makefiles" -S ${PARENT_DIR} -B ${PARENT_DIR}/build/release ${RELEASE_FLAGS} \
	&& make -C ${PARENT_DIR}/build/release
