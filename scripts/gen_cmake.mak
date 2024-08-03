CUR_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PARENT_DIR := $(abspath $(CUR_DIR)/..)

default:
	@echo "generating cmake config"
	cmake -G "Unix Makefiles" -S ${PARENT_DIR} -B ${PARENT_DIR}/build/
