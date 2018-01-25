# Copyright (c) 2011 The LevelDB Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file. See the AUTHORS file for names of contributors.

#-----------------------------------------------
# Uncomment exactly one of the lines labelled 1. and 2. below
# to switch between compilation modes.
# 1. Debug Mode
OPT ?= -g
# 2. Release Mode
# OPT ?= -O2 -DNDEBUG
#-----------------------------------------------

CXX     = g++
CFLAGS  = -Wall --std=c++11
LDFLAGS = -lpthread

PRG = lightlog_test
SRC = test/$(PRG).cc

$(PRG): $(SRC) lightlog.h
	$(CXX) -o $@ $(CFLAGS) $(SRC) $(LDFLAGS) $(OPT)

.PHONY : clean
clean :
	-rm -f $(PRG)
