echo "./a.out -abc https://www.eurosport.de"
./a.out -abc https://www.eurosport.de

echo "

"

echo "too many positional arguments"

echo "./a.out -a 5 https://www.eurosport.de --b hello -c"
./a.out -a 5 https://www.eurosport.de --b hello -c
