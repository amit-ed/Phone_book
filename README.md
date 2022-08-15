<h1>Phonebook Project</h1>
<h3>By Amit Ein-dor</h3>

<h1>Execution</h1>
<p>1. Please compile the phonebook program using the below command (you would need gcc compiler): 
   gcc -g phonebook.c -o phonebook
</p>
<p>
2. You can run the program under valgrind to see that there are no memory leaks (you would need valgrind installed): 
	valgrind --leak-check=full --show-leak-kinds=all  --leak-resolution=high --trace-children=no --show-below-main=yes --num-callers=50 --log-file=phonebook.log ./phonebook
</p>

<h1>Description</h1>
<p>
Phonebook program that demonstrate all capabilities such as :
insert a contact, delete a contact, edit a contact, search for a contact.
And also sort all of the contacts in the list.
</p>

<h1>Data Structure</h1>
<p>
I've used a linked list for this project because it can be easily allocated in the memory without having to change all of the formation
</p>
