# Impledge-Assignment
C++ code for the given assignment

# How To Run Code
1) Install extensions on VS Code - Code Runner, C/C++ 
2) Setup MinGw on your desktop and add it to the environment variables
3) Add the code files and the input files into the same folder and open the code in the VS Code
4) Run the code in the terminal and you will get the following output
![image](https://github.com/PulkitChikara/Impledge-Assignment/assets/81486998/3ecea141-0e06-473c-a2cf-318f2deaf371)

# The Program Overview
The program is designed to find the longest and second-longest compounded words from a list of words stored in a file. The approach involves using a Trie data structure to efficiently store and search for words, enabling fast lookup during the compound word detection process.

The 'insertWord' function inserts each word into the Trie, while the 'isWordInTrie' function checks if a given word exists in the Trie. The 'isCompoundWord' function recursively checks if a word is a compounded word by iterating through its prefixes and suffixes and checking their presence in the Trie. This approach helps avoid redundant checks and improves performance.

The main function reads the words from the input file, inserts them into the Trie, and then identifies the compounded words using the 'isCompoundWord' function. It stores the compounded words in a set and maps them to their respective lengths. Finally, it sorts the compounded words based on their lengths and outputs the longest and second longest compounded words along with the time taken to process the file.

Overall, the program leverages Trie data structure and dynamic programming techniques to efficiently identify compounded words and provide accurate results promptly.
