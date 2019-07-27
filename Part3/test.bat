@echo off
del performance.csv
g++ -o test pgrk1596.cpp
test
@pause