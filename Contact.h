#define NAME_LEN 31
#define PHONE_LEN 15

//------------------------------------------
//A struct that contain the Contact's data
struct Contact {
    char fname[NAME_LEN];
    char lname[NAME_LEN];
    char telep[PHONE_LEN];
    char cellp[PHONE_LEN];
};

//A struct that contain a node of contact.
//Contact node holds a pointer to one contact and a pointer to the next node
struct Contact_Node {
    struct Contact* data;
    struct Contact_Node* next;
};