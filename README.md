# Gator-ammarly
To get started compile test.cpp, BKTree.cpp, and Interface.cpp to c++17
The menu consists of 4 options, the 4th being the exit
1. Load the trees
2. Single word spell check
3. Text file spell check

To load the trees, download the csv file for the data and copy get the path to the file
The UI will prompt you to enter the path, doing so will then train the trees for further use in the other 2 options.

The 2nd option is a single word spell check. The UI will prompt you to type in a single word and press enter.
If the word is spelled incorrectly (which should be the intention when using) you will be given word suggestions 
from both the BKTree and the Trie, as well as the amount of time lookup took to get these suggestions from
both trees. You will then be prompted to continue until you enter '123' to which you will be brought back to the main menu.

The 3rd option requires you to have a text document in the same folder as the executable. The UI will prompt you to type in
the name of the text file (.txt including), to which the program will go line by line word by word giving you suggestions to 
words which are thought to be spelled incorrectly, which of course will give suggestions from both Trees as well as the lookup times.
Additionally, if the word is spelled correctly the user has the option to do nothing at all. After the program goes through every line, 
a new txt file is created in the same folder as the executable, with the edits that the user chose to make.
