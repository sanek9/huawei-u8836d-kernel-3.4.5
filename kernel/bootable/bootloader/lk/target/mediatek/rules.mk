LOCAL_DIR := $(GET_LOCAL_DIR)

PLATFORM := mediatek

MODULES += \
        dev/keys \
    lib/ptable

include custom/out/$(FULL_PROJECT)/lk/rules_platform.mk

