Use 'make' to compile all the neccessary files.
---
After compiling there will be 3 executable files: 'main.out', 'gen.out' and 'conv.out'.
---
MAIN.OUT:
    The program takes one (.txt) or (.bin) file as a parameter. After launch it is recommended that you type 'help' in order to see the list of commands:
        {result - display the result.}
        {add [(Surname),(Number of CPUs),(CPUs {use '|' to split them}),(RAM size),(GPU),(Number of HDDs),(HDD sizes {use '|' to split them}),(number of peripherals),(OS)] - add a student.}
        {remove [surname] - remove a student.}
        {info [surname] - information about a student.}
        {table - display information about all students.}
        {q - quit the program.}
    The result shows the best PC in the collection of students who have multiple PCs.
    Adding command takes only one parameter which is represented in CSV format (!).
---
GEN.OUT: 
    The program takes any number of parameters which represent wishlist of files to be randomly generated. The passed files must have a (.txt) extension or no extension at all. Created files store data in CSV format. 
    Example of use: 
        'gen.out new_data.txt data.txt another_file ...'  
---
CONV.OUT: 
    The program takes any number of parameters which represent files to be converted into binary format (.bin).
    Example of use: 
        'conv.out data.txt old_data existing_data.txt ...'
    Created files will have a (.bin) extension.
---