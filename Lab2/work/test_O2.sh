rm data_O2_power2.txt

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768
do
  echo "N = "$N
    ./lab2 $N $(($N+1)) >> data_O2_power2.txt
done
