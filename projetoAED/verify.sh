#!/bin/bash

echo "enunciado"
./istravel exemplos/enunciado.cli exemplos/enunciado.map
verISTravel exemplos/enunciado.map exemplos/enunciado.cli exemplos/enunciado.sol
echo $?

echo "rnd500"
./istravel exemplos/rnd500.cli exemplos/rnd500.map
verISTravel exemplos/rnd500.map exemplos/rnd500.cli exemplos/rnd500.sol
echo $?

echo "sm2"
./istravel exemplos/sm2.cli exemplos/sm2.map
verISTravel exemplos/sm2.map exemplos/sm2.cli exemplos/sm2.sol
echo $?

echo "swtno"
./istravel exemplos/swtno.cli exemplos/swtno.map
verISTravel exemplos/swtno.map exemplos/swtno.cli exemplos/swtno.sol
echo $?

echo "tx1"
./istravel exemplos/tx1.cli exemplos/tx1.map
verISTravel exemplos/tx1.map exemplos/tx1.cli exemplos/tx1.sol
echo $?

echo "w12"
./istravel exemplos/w12.cli exemplos/w12.map
verISTravel exemplos/w12.map exemplos/w12.cli exemplos/w12.sol
echo $?

echo "w25"
./istravel exemplos/w25.cli exemplos/w25.map
verISTravel exemplos/w25.map exemplos/w25.cli exemplos/w25.sol
echo $?

echo "w50"
./istravel exemplos/w50.cli exemplos/w50.map
verISTravel exemplos/w50.map exemplos/w50.cli exemplos/w50.sol
echo $?
