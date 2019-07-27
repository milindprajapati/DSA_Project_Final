@echo off
echo ===========================================
echo ==   GOOGLE PAGERANK MODEL - PART 1      ==
echo ==     By : Milind Prajapati             ==
echo ===========================================
del graph.txt
echo Program Compiling ...
g++ -o pgrk pgrk1596.cpp
g++ -o grpgen grphgen.cpp

Echo.
Echo Set All The Parameters ...
set /p n="P-1) No of Vertices : "
set /p m="P-2) No of Edges : "
set /p iter="P-3) No of Iteration : "
REM set /p init="P-3) No of Initial Value : "
set /p damp="P-4) No of Damping Factor : "
set /p err="P-5) No of Errorrate: "

echo Graph Generation in Progress Executing ...
grpgen %n% %m%

pgrk %iter% 0 %damp% %err% graph.txt
@pause
