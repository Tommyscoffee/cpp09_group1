ARGS=$(gshuf -i 1-100000 -n $1)

# ./PmergeMe -1 0 22 3 4
# ./PmergeMe  0 22 3 4
# ./PmergeMe  0 22 3 4
# ./PmergeMe  22 03 4
# ./PmergeMe  22 3 4
# ./PmergeMe  2 1
# ./PmergeMe  1 2
# ./PmergeMe  
echo ${ARGS}
./PmergeMe ${ARGS}
