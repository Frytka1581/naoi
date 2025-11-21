for I in {1..10000}; do
    ./gen > in
    ./wzor < in > out
    ./brut < in > out2
    diff -bew out out2 || break
    echo "${I} [OK]"
done