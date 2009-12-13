#!/bin/sh
export LD_LIBRARY_PATH=../release:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
exec ./main
