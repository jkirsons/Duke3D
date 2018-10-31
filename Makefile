#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := Duke3D
CFLAGS += -Wno-error=char-subscripts

include $(IDF_PATH)/make/project.mk

