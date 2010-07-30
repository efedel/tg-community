#!/bin/sh
export LD_LIBRARY_PATH=../output:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
exec ./main
