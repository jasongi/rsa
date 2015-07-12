make clean
set -v
make
PUBLIC=4485239
PRIVATE=3536567
N=32432863
./rsa -e testfile_SDES.txt testfile_SDES_en.txt $PUBLIC $N
./rsa -d testfile_SDES_en.txt testfile_SDES_de.txt $PRIVATE $N
diff -s testfile_SDES.txt testfile_SDES_de.txt
