SIZE="-DSIZE=100000"
rm -R obj
mkdir obj
gcc -Wall -O2 -c -m32 -Iinc/ src/Concurrent.c -o obj/Concurrent.o
ar rcs libconcurrent.a obj/Concurrent.o 
gcc -Wall -O2 -m32 $SIZE -Iinc/ Test.c -o TestIterative
gcc -Wall -O2 -m32 $SIZE -DCONCURRENT -Iinc/ Test.c -o TestConcurrent -L./ -lconcurrent -lpthread
