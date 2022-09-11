#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MergeSort.h"
#include "Contact.h"
//------------------------------------------
extern struct Contact;
extern struct Contact_Node;
extern void MergeSort(struct Contact_Node** headRef, char compare_by);
#define TOTAL_CONTACTS 5
#define NAME_LEN 31
#define PHONE_LEN 15
//------------------------------------------
struct Contact A[TOTAL_CONTACTS];
struct Contact_Node* head;
struct Contact_Node* tail;
int last;
//------------------------------------------
void clrscr(void);
void gotoxy(int x, int y);
void insert(void);
void delete(void);
void edit(void);
void search(void);
void searchf(void);
void searchl(void);
void searchp(void);
void searchc(void);
void list(void);
void list2(void);
void sort(void);
void sortf(void);
void sortl(void);
void sortp(void);
void sortc(void);
void help(void);
size_t get_input(char* dest, size_t max_size);
void insert_node(struct Contact* data);
void print_contact(struct Contact* cont, int index);
//----------------------------------------------------------------------------------------
int main()
{
	char n;
	while (1) {
		clrscr();
		printf("\n|Phone Book12<::>Home|\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("Welcome to PHONE BOOK2022!\nYou have inserted ( %d ) contacts.\n\n", last);
		printf("\t[1] |--> Insert\n");
		printf("\t[2] |--> Delete\n");
		printf("\t[3] |--> Edit\n");
		printf("\t[4] |--> Search\n");
		printf("\t[5] |--> Show All\n");
		printf("\t[6] |--> Sort\n");
		printf("\t[7] |--> Help\n");
		printf("\t[8] |--> Exit\n");
		printf("\n\tPlease Enter Your Choice (1-8): ");
		n = getc(stdin);
		getc(stdin);
		switch (n) {
		case '1':
			insert();
			break;
		case '2':
			delete();
			break;
		case '3':
			edit();
			break;
		case '4':
			search();
			break;
		case '5':
			list();
			break;
		case '6':
			sort();
			break;
		case '7':
			help();
			break;
		case '8':
			exit(1);
			break;
		default:
			printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-8!\nPress any key to continue...", n);
			getc(stdin);
			break;
		}//End of swicth
	}
	return 0;
}//End of main function!
//----------------------------------------------------------------------------------------
//Generic function for user input
//Get a pointer to the destination buffer and int - how many is the maximum bytes to read
size_t get_input(char* dest, size_t max_size)
{
	size_t len = max_size;
	size_t len_size = 0;
	char* input = NULL;
	input = (char*)malloc(len * sizeof(char));
	len_size = getline(&input, &len, stdin);
	if (input[len_size - 1] == '\n') {
		input[len_size - 1] = '\0';     //replace endline with null
		len_size--;
	}
	if (len_size >= max_size) {
		input[max_size - 1] = '\0'; //make the string null terminated
	}
	strcpy(dest, input);
	free(input);
}
//----------------------------------------------------------------------------------------

void print_contact(struct Contact* cont, int index)
{
	printf("\n\nCantact %2.2d{", index);
	printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }", cont->fname, cont->lname, cont->telep, cont->cellp);
}
//----------------------------------------------------------------------------------------
void insert(void)
{
	char ans = 'y';
	//char *string = (char *)malloc(31);
	size_t len_size = 0;
	clrscr();
	printf("\nPhone Book12<::>Insert Contacts");
	printf("\n--------------------------------------------------------------------------------");

	while (ans == 'y') {
		if (last == TOTAL_CONTACTS) //if we got to the maximum contact amount
			last = 0;   //start to override from the first contact
		else {
			struct Contact* cont = malloc(sizeof(struct Contact));
			printf("\n\nData of Contact %2.2d{\n", last + 1);
			printf("\n\t  1-F.Name: ");
			len_size = get_input(cont->fname, 31);

			printf("\t  2-L.Name: ");
			len_size = get_input(cont->lname, 31);

			printf("\t  3-Tele.P: ");
			len_size = get_input(cont->telep, 15);

			printf("\t  4-Cell.P: ");
			len_size = get_input(cont->cellp, 15);

			insert_node(cont);
			printf("\n|-->Data Recorded!}");
			printf("\n\t\t\tNext Contact?(y/n) Answer:");
			ans = getc(stdin);
			getc(stdin);
			last++;
		}
	}
	printf("\n\nYou have inserted ( %d ) contact!\nPress a key to return main page & continue program|-->", last);
	getc(stdin);
}
//----------------------------------------------------------------------------------------
void delete(void)
{
	char dfname_string[NAME_LEN], dlname_string[NAME_LEN];
	size_t len_size = 0;
	register int i, j, find = 0;
	char ch;
	clrscr();
	printf("\nPhone Book12<::>Delete Contacts");
	printf("\n--------------------------------------------------------------------------------");
	printf("\n::Enter data of the contact that you want delete it,please:");
	printf("\n\n  ::Enter first name: ");
	len_size = get_input(dfname_string, 31);

	printf("\n  ::Enter last name: ");
	len_size = get_input(dlname_string, 31);

	struct Contact_Node* cont = head;
	struct Contact_Node* prev = cont;
	while (cont != NULL)
	{
		printf("%s\n", cont->data->fname);
		if (strcmp(dfname_string, cont->data->fname) == 0 && strcmp(dlname_string, cont->data->lname) == 0)
		{
			printf("\nContact was found! Details:");
			print_contact(cont->data, i + 1);
			printf("\n\nAre you sure you want to delete this contact?(y/n)");
			ch = getc(stdin);
			getc(stdin);
			if (ch == 'y')
			{
				find = 1;
				if (prev == head)
				{
					head = NULL;
					break;
				}
				prev->next = cont->next;
				free(cont->data);
				free(cont);
				break;
			}
		}
		i++;
		prev = cont;
		cont = cont->next;
	}

	if (find == 0)
		printf("\t\t\n<<This contact does not exist in this list or program can not delete it.>>");
	else
		printf("\t\t\n<<Target contact was successfully deleted from list!>>");
	printf("\n\n\nPress a key to return main page & continue program|-->");
	getc(stdin);
}
//----------------------------------------------------------------------------------------
void edit()
{
	char dfname[31], dlname[31], ch;
	size_t len_size;
	register int i, find = 0;
	clrscr();
	printf("\nPhone Book12<::>Edit Contacts");
	printf("\n--------------------------------------------------------------------------------");
	printf("\n::Enter data of the contact that you want edit it,please:");

	printf("\n\n  ::Enter first name: ");
	len_size = get_input(dfname, 31);
	printf("\n  ::Enter last name: ");
	len_size = get_input(dlname, 31);

	struct Contact_Node* cont = head;
	while (cont != NULL)
	{
		if (strcmp(dfname, cont->data->fname) == 0 && strcmp(dlname, cont->data->lname) == 0)
		{
			printf("\nContact found! Details:");
			print_contact(cont->data, i + 1);
			printf("\n\nDo you want edit it?(y/n) ");
			ch = getc(stdin);
			if (ch == 'y')
			{
				printf("\n::Enter NEW data for this contact...");
				printf("\n >|Enter new first name: ");
				get_input(cont->data->fname, 31);

				printf(" >|Enter new last name: ");
				get_input(cont->data->lname, 31);

				printf(" >|Enter new telephone number: ");
				get_input(cont->data->telep, 15);

				printf(" >|Enter new cellphone number: ");
				get_input(cont->data->cellp, 15);

				find = 1;
				break;
			}
		}
		i++;
		cont = cont->next;
	}

	if (find == 0)
		printf("\t\t\n<<This contact does not exist or you chose not to Edit it.>>");
	else
		printf("\t\t\n<<Target contact was successfully updated!>>");
	printf("\n\n\n   ::Press a key to return main page & continue program|-->");
	getc(stdin);
}
//----------------------------------------------------------------------------------------
//A function to search for a specific contact/s using a filter
//Find the Contacts and print their details
void search(void)
{
	char ch;
	clrscr();
	printf("\nPhone Book12<::>$earch Contacts");
	printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose search type,please:\n\n");
	printf("\t[1] |--> Search by first name\n");
	printf("\t[2] |--> Search by last name\n");
	printf("\t[3] |--> Search by phone number\n");
	printf("\t[4] |--> Search by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
	switch (ch) {
	case '1':
		searchf();
		break;
	case '2':
		searchl();
		break;
	case '3':
		searchp();
		break;
	case '4':
		searchc();
		break;
	case '5':
	default:
		return;
	}
}
//----------------------------------------------------------------------------------------
//Find the needed contact by first name
//The user will provide a first name
void searchf(void)
{
	char fname[NAME_LEN];
	int i = 0, find = 0;
	printf("Enter a first name to search:");
	get_input(fname, NAME_LEN);

	struct Contact_Node* cont = head;
	while (cont != NULL) {
		if (strcmp(fname, cont->data->fname) == 0) {
			find = 1;
			break;
		}
		i++;
		cont = cont->next;
	}

	if (find == 0)
		printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
	else {
		printf("\t\n<<Target contact found! Details:>>");
		print_contact(cont->data, i + 1);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
}
//----------------------------------------------------------------------------------------
//Find the needed contact by last name
//The user will provide a last name
void searchl(void)
{
	char lname[NAME_LEN];
	int i, find = 0;
	printf("\n::Enter a last name to search:");
	get_input(lname, NAME_LEN);
	struct Contact_Node* cont = head;
	while (cont != NULL) {
		if (strcmp(lname, cont->data->lname) == 0) {
			find = 1;
			break;
		}
		i++;
		cont = cont->next;
	}

	if (find == 0)
		printf("\t\n<<Not Find!There is not contact with tish name in phone book.>>");
	else {
		printf("\t\n<<Target contact found! Details:>>");
		print_contact(cont->data, i + 1);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
}
//----------------------------------------------------------------------------------------
//Find the needed contact by phone number
//The user will provide a phone number
void searchp(void)
{
	char phone[PHONE_LEN];
	int i, find = 0;
	printf("\n::Enter a phone number to search:");
	get_input(phone, PHONE_LEN);

	struct Contact_Node* cont = head;
	while (cont != NULL) {
		if (strcmp(phone, cont->data->telep) == 0) {
			find = 1;
			break;
		}
		i++;
		cont = cont->next;
	}
	if (find == 0)
		printf("\t\n<<Not Found!There is not contact with tish phone number  in phone book.>>");
	else {
		printf("\t\n<<Target contact found! Details:>>");
		print_contact(cont->data, i + 1);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
}
//----------------------------------------------------------------------------------------
//Find the needed contact by cellphone number
//The user will provide a cellphone number
void searchc(void)
{
	char phone[PHONE_LEN];
	int i, find = 0;
	printf("\n::Enter a cellphone number to search:");
	get_input(phone, PHONE_LEN);

	struct Contact_Node* cont = head;
	while (cont != NULL) {
		if (strcmp(phone, cont->data->cellp) == 0) {
			find = 1;
			break;
		}
		i++;
		cont = cont->next;
	}
	if (find == 0)
		printf("\t\n<<Not Find!There is not contact with tish cellphone number in phone book.>>");
	else {
		printf("\t\n<<Target contact found! Details:>>");
		print_contact(cont->data, i + 1);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
}
//----------------------------------------------------------------------------------------
void sort(void)
{
	char ch;
	clrscr();
	printf("\nPhone Book12<::>search Contacts");
	printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose sort type,please:\n\n");
	printf("\t[1] |--> Sort by first name\n");
	printf("\t[2] |--> Sort by last name\n");
	printf("\t[3] |--> Sort by phone number\n");
	printf("\t[4] |--> Sort by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
	MergeSort(&head, ch);
}
//----------------------------------------------------------------------------------------
void list()
{
	register int i;
	clrscr();
	printf("\nPhone Book12<::>All Contacts List");
	printf("\n--------------------------------------------------------------------------------");
	gotoxy(1, 4);
	printf("Row");
	gotoxy(9, 4);
	printf("First Name");
	gotoxy(27, 4);
	printf("Last Name");
	gotoxy(44, 4);
	printf("Telephone");
	gotoxy(60, 4);
	printf("Cellphone");
	printf("\n--------------------------------------------------------------------------------");

	struct Contact_Node* cont = head;
	i = 0;
	//last node's next address will be NULL.
	while (cont != NULL)
	{
		gotoxy(1, i + 6);
		printf("%3.3d", i + 1);
		gotoxy(9, i + 6);
		printf("%s", cont->data->fname);
		gotoxy(28, i + 6);
		printf("%s", cont->data->lname);
		gotoxy(44, i + 6);
		printf("%s", cont->data->telep);
		gotoxy(60, i + 6);
		printf("%s", cont->data->cellp);

		cont = cont->next;
		i++;
	}

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t    **********End Of list!**********");
	printf("\n\n\n   ::Press a key to return main page & continue program.|-->");
	getc(stdin);
}
//----------------------------------------------------------------------------------------
void help(void)
{
	clrscr();
	gotoxy(26, 1);
	printf("--------------------------");
	gotoxy(26, 2);
	printf("|Welcome To Phone Book12!|");
	gotoxy(26, 3);
	printf("--------------------------");
	gotoxy(1, 5);
	printf("PhoneBook12>>[Help & Instructions] \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\nAbout Phonebook12\n *Version: 2.5\n *Valence: 50 Contacts(MAX)\n  *By: Morteza Zakeri (2011-12)");
	printf("\n\nThis program allows you to have a list of your contacts.\nIt also allows you to have your listing added or deleted from your list.\nOther features of this program include:\nSearch,edit,sort & list.\n\n   ::Press a key to return main page & continue program.|-->");
	getc(stdin);
}
//----------------------------------------------------------------------------------------
//just a better name for clear screen
void clrscr()
{
	system("clear");
}
//----------------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}
//----------------------------------------------------------------------------------------
void insert_node(struct Contact* data)
{
	struct Contact_Node* new_contact_node = malloc(sizeof(struct Contact_Node));
	new_contact_node->data = data;
	new_contact_node->next = NULL;
	if (head == NULL)
	{
		head = new_contact_node;
	}
	else
	{
		new_contact_node->next = head->next;
		head->next = new_contact_node;
	}
}