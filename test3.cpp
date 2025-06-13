#include <cstdio>
#include <unistd.h>
// situation
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------

// move chars
void *memmove(void *dest, const void *src, size_t count) {
  if (dest == nullptr || src == nullptr || count == 0) {
    return dest;
  }

  unsigned char *d = static_cast<unsigned char *>(dest);
  const unsigned char *s = static_cast<const unsigned char *>(src);

  if (d < s) {
    // Copy forward if dest is before src
    for (size_t i = 0; i < count; ++i) {
      d[i] = s[i];
    }
    } else if (d > s) {
    // Copy backward if dest is after src
    for (size_t i = count; i > 0; --i) {
      d[i - 1] = s[i - 1];
    }
  }
  return dest;
}
// strlen chars
size_t strlen(const char *s) {
  size_t i = 0;
  const char *p = s;
  while (*p != '\0') {
    p++;
    i++;
  }
  return i;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// print
void print_arg(const char *arg) {
  if (arg != nullptr) {
    write(STDOUT_FILENO, arg, strlen(arg));
  }
}
// print
void print_arg(int arg) {
  char buffer[32];
  int len = snprintf(buffer, sizeof(buffer), "%d", arg);
  write(STDOUT_FILENO, buffer, len);
}
// print
void print_arg(double arg) {
  char buffer[64];
  int len = snprintf(buffer, sizeof(buffer), "%g", arg);
  write(STDOUT_FILENO, buffer, len);
}
// print
void print_arg(float arg) {
  char buffer[64];
  int len = snprintf(buffer, sizeof(buffer), "%f", arg);
  write(STDOUT_FILENO, buffer, len);
}
// print
template <typename... Args>
void outLog(const Args &...args) {
  (print_arg(args), ...);
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
//  1  r   Searches file. If the file is opened successfully fopen() loads it into memory and sets up a pointer that points to the first character in it. If the file cannot be opened fopen( ) returns NULL.
//  2  rb  Open for reading in binary mode. If the file does not exist, fopen( ) returns NULL.
//  3  w   Open for writing in text mode. If the file exists, its contents are overwritten. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open the file. 
//  4  wb  Open for writing in binary mode. If the file exists, its contents are overwritten. If the file does not exist, it will be created. 
//  5  a   Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the last character in it. It opens only in the append mode. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open the file. 
//  6  ab  Open for append in binary mode. Data is added to the end of the file. If the file does not exist, it will be created. 
//  7  r+  Searches file. It is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the first character in it. Returns NULL, if unable to open the file. 
//  8  rb+ Open for both reading and writing in binary mode. If the file does not exist, fopen( ) returns NULL. 
//  9  w+  Searches file. If the file exists, its contents are overwritten. If the file doesn’t exist a new file is created. Returns NULL, if unable to open the file. 
//  10 wb+ Open for both reading and writing in binary mode. If the file exists, its contents are overwritten. If the file does not exist, it will be created. 
//  11 a+  Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the last character in it. It opens the file in both reading and append mode. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open  the file. 
//  12 ab+ Open for both reading and appending in binary mode. If the file does not exist, it will be created.
template <typename T = int>
struct IOps {
  T id;
  T location;
  FILE *file;
};
// open
template <typename T>
void open(IOps<T> **op, const char *file, const char *mode) {
  (*op) = new IOps<T>();
  (*op)->file = fopen(file, mode);
}
// close
template <typename T>
void close(IOps<T> **op) {
  fclose((*op)->file); // close file
  delete (*op);
  (*op) = nullptr;
}
// getsize
template <typename T>
size_t sizeOfFile(IOps<T> **op) {
  fseek((*op)->file, 0, SEEK_END); // Move to the end of the file
  return ftell((*op)->file);       // Get the current position (size)
}
// move to the start
template <typename T>
void start(IOps<T> **op) {
  fseek((*op)->file, 0, SEEK_SET); // Move to the start of the file
  (*op)->location = 0;
}
// move to the end
template <typename T>
void end(IOps<T> **op) {
  fseek((*op)->file, 0, SEEK_END); // Move to the end of the file
  // op->location=0;
}
// relative from current pos
template <typename T>
void setPosIOp(IOps<T> **op, int p) {
  fseek((*op)->file, p, SEEK_CUR); // move to pos from cur relative prev pos=cur
  (*op)->location = p;
}
// move to start
template <typename T>
void unwind(IOps<T> **op) {
  rewind((*op)->file); // to the start pos in file
  op->location = 0;
}
// readlines
template <typename T>
void readline(IOps<T> **op) {
  char tempB[1024];
  while (fscanf((*op)->file, "%[^\n]\n", tempB) == 1) {

    outLog(tempB, "\n");
  }
}

//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// array
template <typename T>
struct DArray {
  T *data;
  size_t size;
  size_t cap;
};
// create array
template <typename T>
void createArr(DArray<T> **arr) {
  *arr = new DArray<T>();

  (*arr)->data = new T[10];
  (*arr)->cap = 10;
  (*arr)->size = 0;
}
// push to the back side
template <typename T>
void push_back(DArray<T> **arr, T data) {
  if ((*arr)->size == (*arr)->cap) {
    // Resize the array if full
    (*arr)->cap *= 2;
    T *newData = new int[(*arr)->cap];
    for (int i = 0; i < (*arr)->size; ++i) {
      newData[i] = (*arr)->data[i];
    }
    delete[] (*arr)->data;
    (*arr)->data = newData;
  }
  // Add new element
  (*arr)->data[(*arr)->size++] = data;
  ;
}
// pop from the back side
template <typename T>
T pop_back(DArray<T> **arr) {
  if ((*arr)->size > 0) {
    (*arr)->size--;
  }
  return (*arr)->data[(*arr)->size];
}
// print array
template <typename T>
void printer(DArray<T> **arr) {
  size_t count = 0;
  if (*arr != nullptr) {
    while (count != (*arr)->size) {
      outLog((*arr)->data[count++], "\n");
    }
  }
}
// delete array
template <typename T>
void cleaner(DArray<T> **arr) {
  delete[] (*arr)->data;
  (*arr)->data = nullptr;
  delete *arr;
  *arr = nullptr;
  // return nullptr;//delete *arr;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// stack
template <typename T>
struct Stack {
  T *data;
  size_t cap;
  size_t top = 0;
};
// create stack
template <typename T>
void createStack(Stack<T> **st, size_t s) {
  *st = new Stack<T>();
  (*st)->data = new T[s];
  (*st)->cap = s;
}
// push to the stack
template <typename T>
void push(Stack<T> **st, int el) {
  if ((*st)->top == (*st)->cap - 1) {
    outLog("Stack Overflow\n");
    return;
  }
  (*st)->data[++(*st)->top] = el;
}
// pop from stack
template <typename T>
int pop(Stack<T> **st) {
  if ((*st)->top == -1) {
    outLog("Stack Underflow\n");
    return -1;
  }
  return (*st)->data[(*st)->top--];
}
// peek
template <typename T>
int peek(Stack<T> **st) {
  if ((*st) != nullptr) {
    if ((*st)->top == -1) {
      outLog("Stack is Empty\n");
      return -1;
    }
    return (*st)->data[(*st)->top];
  }
  return 0;
}
// chech if isempty
template <typename T>
bool isEmpty(Stack<T> **st) { return (*st)->top == -1; }
// delete list
template <typename T>
void cleaner(Stack<T> **st) {
  delete[] (*st)->data;
  (*st)->data = nullptr;
  delete *st;
  (*st) = nullptr;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// char unsigned char?
template <typename T = char>
struct String {
  T *data;
  size_t size;
  size_t cap;
};
//?
template <typename T>
void createStr(String<T> **str) {
  *str = new String<T>();
  (*str)->data = new char[10];
  (*str)->cap = 10;
  (*str)->size = 0;
}
//?
template <typename T>
void push_back(String<T> **str, T data) {
  if ((*str)->size == (*str)->cap) {
    // Resize the array if full
    (*str)->cap *= 2;
    T *newData = new T[(*str)->cap];
    for (int i = 0; i < (*str)->size; ++i) {
      newData[i] = (*str)->data[i];
    }
    delete[] (*str)->data;
    (*str)->data = newData;
  }
  // Add new element
  (*str)->data[(*str)->size++] = data;
  (*str)->data[(*str)->size] = '\0';
  ;
}
//?
template <typename T>
void push_back(String<char> **str, T *data) {
  size_t s = strlen(data);
  size_t oldsize = (*str)->size;
  size_t newsize = (*str)->size + s;
  if (oldsize < newsize) {
    // Resize the array if full
    (*str)->cap = newsize;

    char *newData = new char[newsize];
    for (int i = 0; i < (*str)->size; ++i) {
      newData[i] = (*str)->data[i];
    }
    delete[] (*str)->data;
    (*str)->data = newData;
    (*str)->size = newsize;
  }
  // Add new element
  memmove((*str)->data + oldsize, &data[0], strlen(data)); // this is custom
}
//?
template <typename T> 
T pop_back(String<T> **str) {
  if ((*str)->size > 0) {
    (*str)->size--;
  }
  return (*str)->data[(*str)->size];
}
// print string
template <typename T>
void printer(String<T> **str) {
  if ((*str) != nullptr)
  outLog((*str)->data, "\n");
}
// delete string
template <typename T>
void cleaner(String<T> **str) {
  delete[] (*str)->data;
  (*str)->data = nullptr;
  delete (*str);
  (*str) = nullptr;
}

// readlines
template <typename T>
void readline(IOps<T> **op, String<char> **dst) {
  char tempB[1024];
  while (fscanf((*op)->file, "%[^\n]\n", tempB) == 1) {

    push_back(&(*dst), tempB);
  }
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// singly linked list representation
template <typename T>
struct List {
  T data;
  List *next;
};
// function add item to the single linked list
template <typename T>
void push_back(List<T> **item, T data) {
  List<T> *tempList = new List<T>();
  tempList->data = data;
  tempList->next = NULL;
  if (*item == nullptr) {
    *item = tempList;
    return;
  }
  List<T> *curr = *item;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = tempList;
}
// Function to insert a node at the beginning of the list
template <typename T>
void push_front(List<T> **item, T data) {
  List<T> *newNode = new List<T>();
  newNode->data = data;
  newNode->next = *item;
  *item = newNode;
}
// function print single linked list
template <typename T>
void printer(List<T> *item) {
  List<T> *curr = item;
  while (curr != NULL) {
    outLog(curr->data, "\n");
    curr = curr->next;
  }
}
// Function to delete the single linked list
template <typename T>
void cleaner(List<T> **head) {
  List<T> *current = *head;
  List<T> *next = nullptr;
  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }
  *head = nullptr;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// double linked list
template <typename T>
struct DList {
  T data;
  DList *next;
  DList *prev;
};
// function add item to the single linked list
template <typename T>
void push_back(DList<T> **item, T data) {
  DList<T> *tempList = new DList<T>();
  tempList->data = data;
  tempList->next = NULL;
  tempList->prev = NULL;
  if (*item == nullptr) {
    *item = tempList;
    return;
  }
  DList<T> *curr = *item;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = tempList;
  tempList->prev = curr;
}
// Function to insert a node at the beginning of the list
template <typename T>
void push_front(DList<T> **item, T data) {
  DList<T> *newNode = new DList<T>();
  newNode->data = data;
  newNode->next = *item;
  *item = newNode;
}
// function print single linked list
template <typename T>
void printer(DList<T> *item) {
  DList<T> *curr = item;
  while (curr != NULL) {
    outLog(curr->data, "\n");
    curr = curr->next;
  }
}
// delete double list
template <typename T>
void cleaner(DList<T> **head) {
  DList<T> *current = *head;
  DList<T> *next = nullptr;
  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }
  *head = nullptr;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
//queue
template <typename T>
struct Queue{
  T data;
  
};
// btree
template <typename T>
struct BTree {
  T data;
  BTree *left;
  BTree *right;
};
//?
template<typename T>
void createBT(){}
template<typename T>
void insertB(BTree<T> **bt,T d){
  BTree<T> *temp=new BTree<T>();
  temp->left=nullptr;
  temp->right=nullptr;
  temp->data=d;
  if(*bt==nullptr){
    *bt=temp;
    return;
  }
  
}
template<typename T>
void deleteB(){}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
int main() {
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  List<int> *head = nullptr;
  push_back(&head, 1);
  push_back(&head, 2);
  push_front(&head, 0);
  push_back(&head, 3);
  outLog("Linked List: \n");
  printer(head);
  cleaner(&head);
  outLog("Linked List after deletion: \n");
  printer(head);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  DList<int> *head1 = nullptr;
  push_back(&head1, 1);
  push_back(&head1, 2);
  push_back(&head1, 3);
  push_back(&head1, 4);
  outLog("DLinked List: \n");
  printer(head1);
  cleaner(&head1);
  outLog("DLinked List after deletion: \n");
  printer(head1);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  DArray<int> *arr = nullptr;
  createArr(&arr);
  push_back(&arr, 1);
  push_back(&arr, 2);
  push_back(&arr, 3);
  push_back(&arr, 4);
  push_back(&arr, 4);
  push_back(&arr, 4);
  push_back(&arr, 3);
  push_back(&arr, 4);
  push_back(&arr, 4);
  push_back(&arr, 4);
  pop_back(&arr);
  pop_back(&arr);
  pop_back(&arr);
  outLog("DArray Arr: \n");
  printer(&arr);
  outLog("DArray Arr after deletion: \n");
  cleaner(&arr);
  printer(&arr);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  Stack<int> *s = nullptr;
  createStack(&s, 5);
  push(&s, 10);
  push(&s, 20);
  outLog("Stack: \n");
  outLog("Top element is ", peek(&s), "\n");
  pop(&s);
  outLog("Top element after pop is ", peek(&s), "\n");
  cleaner(&s);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  String<char> *string = nullptr;
  createStr(&string);
  push_back(&string, '"');
  push_back(&string, '"');
  push_back(&string, "ddasdasdsadasdasdasdasdasda5435345345435435");
  outLog("String: \n");
  printer(&string);
  cleaner(&string);
  printer(&string);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  //---------------------------------------------------------
  String<char> *string1 = nullptr;
  IOps<int> *test;
  open(&test, "test1.cpp", "rb");

  createStr(&string1);
  outLog("String1: \n");

  readline(&test, &string1);
  outLog((int)sizeOfFile(&test), "\n");
  printer(&string1);
  cleaner(&string1);
  close(&test);
  //---------------------------------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //--ABSOLUTLYNOWARRANTLY-----------------------------------
  //---------------------------------------------------------
  return 0;
}
//---------------------------------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//--ABSOLUTLYNOWARRANTLY-----------------------------------
//---------------------------------------------------------
// situation
// #include <new>
// void* ptr = ::operator new(1024,(void*)32);
//::operator delete(ptr,(void*)32
