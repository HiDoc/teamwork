make fclean
make push_swap
cd _visualizer/c
echo "<!> compiling random unique number generator"
gcc rnd_int.c -o rnd_int.exe
echo "<!> compiling json list generator"
gcc list_jsonifier.c -o list_jsonifier.exe
cat ../static_test/${1:-20}.txt > ../unsorted_list.txt 
./list_jsonifier.exe "unsorted_list" "$(cat ../unsorted_list.txt)" "0" > ../unsorted_list.json 
cd ../..
echo "<!> running push_swap on generated list ..."
./push_swap $(cat _visualizer/unsorted_list.txt) > _visualizer/commands.txt
cd _visualizer/c
cat ../commands.txt
echo "<!> building json from output ..."
./list_jsonifier.exe "commands" "$(cat ../commands.txt)" "1" > ../commands.json
cd ..
echo "<!> injecting json data to html hidden container"
sed '/<p id="commands">/ r commands.json' html/index_tpl.html > html/tmp.html
sed '/<p id="int_list">/ r unsorted_list.json' html/tmp.html > html/index.html

open html/index.html