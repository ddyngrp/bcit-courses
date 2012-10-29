rm a3tests/data
rm a3tests/data2
cp a3tests/data2_org a3tests/data2

echo "===================== * Runs * ======================"
echo "======================= Run 1 ======================="
./a3 a3tests/data < a3tests/in1 > a3tests/out1_2
echo "======================= Run 2 ======================="
./a3 a3tests/data < a3tests/in2 > a3tests/out2_2
echo "======================= Run 3 ======================="
./a3 a3tests/data < a3tests/in3 > a3tests/out3_2
echo "======================= Run 4 ======================="
./a3 a3tests/data2 < a3tests/in4 > a3tests/out4_2

cd a3tests
echo
echo "===================== * DIFF * ======================"
echo "======================= Test 1 ======================="
diff out1 out1_2
echo "======================= Test 2 ======================="
diff out2 out2_2
echo "======================= Test 3 ======================="
diff out3 out3_2
echo "======================= Test 4 ======================="
diff out4 out4_2

echo
echo "====================== * CMP * ======================="
echo "Test 1: "; cmp out1 out1_2 && echo "\tPASS" || "\tFAIL"
echo "Test 2: "; cmp out2 out2_2 && echo "\tPASS" || "\tFAIL"
echo "Test 3: "; cmp out3 out3_2 && echo "\tPASS" || "\tFAIL"
echo "Test 4: "; cmp out4 out4_2 && echo "\tPASS" || "\tFAIL"
cd ..
