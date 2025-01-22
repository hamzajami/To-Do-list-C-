#include <iostream>
#include <string>

using namespace std;

struct Node {
    string task;
    int priority;
    Node* next;

    Node(string t, int p) {
        task = t;
        priority = p;
        next = nullptr;
    }
};

struct QueueNode {
    string task;
    QueueNode* next;

    QueueNode(string t) {
        task = t;
        next = nullptr;
    }
};

struct StackNode {
    string action;
    StackNode* next;

    StackNode(string a) {
        action = a;
        next = nullptr;
    }
};

// BST Node Structure
struct BSTNode {
    int id;
    string task;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int taskId, string taskName) {
        id = taskId;
        task = taskName;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree for Task Management
class TaskBST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int id, string task) {
        if (node == nullptr) {
            return new BSTNode(id, task);
        }
        if (id < node->id) {
            node->left = insert(node->left, id, task);
        } else if (id > node->id) {
            node->right = insert(node->right, id, task);
        }
        return node;
    }

    void inOrderTraversal(BSTNode* node) {
        if (node == nullptr) return;
        inOrderTraversal(node->left);
        cout << "ID: " << node->id << " - Task: " << node->task << endl;
        inOrderTraversal(node->right);
    }

    BSTNode* search(BSTNode* node, int id) {
        if (node == nullptr || node->id == id) {
            return node;
        }
        if (id < node->id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

public:
    TaskBST() {
        root = nullptr;
    }

    void addTask(int id, string task) {
        root = insert(root, id, task);
        cout << "Task added to BST: ID = " << id << endl;
    }

    void displayTasks() {
        if (root == nullptr) {
            cout << "No tasks in BST." << endl;
        } else {
            cout << "Tasks in BST (sorted by ID):" << endl;
            inOrderTraversal(root);
        }
    }

    void searchTask(int id) {
        BSTNode* result = search(root, id);
        if (result == nullptr) {
            cout << "Task with ID " << id << " not found in BST." << endl;
        } else {
            cout << "Found Task: ID = " << id << ", Task = " << result->task << endl;
        }
    }
};

class TaskQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    TaskQueue() {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(string task) {
        QueueNode* newNode = new QueueNode(task);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Task added to queue: " << task << endl;
    }

    string dequeue() {
        if (front == nullptr) {
            cout << "No tasks to remove!" << endl;
            return "";
        }
        string task = front->task;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return task;
    }

    void display() {
        if (front == nullptr) {
            cout << "No tasks in the queue!" << endl;
            return;
        }
        QueueNode* temp = front;
        cout << "Tasks in the queue:" << endl;
        while (temp != nullptr) {
            cout << "- " << temp->task << endl;
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

class TaskStack {
private:
    StackNode* top;

public:
    TaskStack() {
        top = nullptr;
    }

    void push(string action) {
        StackNode* newNode = new StackNode(action);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (top == nullptr) {
            cout << "No actions to undo!" << endl;
            return "";
        }
        string action = top->action;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return action;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

void addPriorityTask(Node*& head, string task, int priority) {
    Node* newNode = new Node(task, priority);
    if (head == nullptr || head->priority > priority) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    cout << "Priority task added: " << task << " (Priority: " << priority << ")" << endl;
}

void displayPriorityTasks(Node* head) {
    if (head == nullptr) {
        cout << "No priority tasks!" << endl;
        return;
    }
    cout << "Priority tasks:" << endl;
    while (head != nullptr) {
        cout << "- " << head->task << " (Priority: " << head->priority << ")" << endl;
        head = head->next;
    }
}

bool login() {
    string usernames[] = {"admin1", "admin2", "admin3", "admin4", "admin5"};
    string passwords[] = {"admin123", "admin234", "admin345", "admin456", "admin567"};
    int totalUsers = 5;

    string username, password;
    int attempts = 3;

    cout << "=== Login Page ===" << endl;

    while (attempts > 0) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        bool loginSuccessful = false;
        for (int i = 0; i < totalUsers; i++) {
            if (username == usernames[i] && password == passwords[i]) {
                loginSuccessful = true;
                break;
            }
        }

        if (loginSuccessful) {
            cout << "Login successful! Welcome, " << username << "!\n" << endl;
            return true;
        } else {
            attempts--;
            cout << "Invalid credentials. Attempts remaining: " << attempts << endl;
        }
    }

    cout << "Too many failed attempts. Exiting program." << endl;
    return false;
}

int main() {
    if (!login()) {
        
    }

    TaskQueue taskQueue;
    TaskStack undoStack;
    Node* priorityHead = nullptr;
    TaskBST taskBST;

    int choice;
    do {
        cout << "\n=== To-Do List Menu ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove/Mark Task as Done" << endl;
        cout << "3. Add Priority Task" << endl;
        cout << "4. Display Tasks" << endl;
        cout << "5. Display Priority Tasks" << endl;
        cout << "6. Undo Delete or Complete" << endl;
        cout << "7. Add Task to BST" << endl;
        cout << "8. Display Tasks in BST" << endl;
        cout << "9. Search Task in BST" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {
        case 1: {
            string task;
            cout << "Enter task: ";
            getline(cin, task);
            taskQueue.enqueue(task);
            undoStack.push("Add: " + task);
            break;
        }
        case 2: {
            string task = taskQueue.dequeue();
            if (!task.empty()) {
                cout << "Task marked as done: " << task << endl;
                undoStack.push("Remove: " + task);
            }
            break;
        }
        case 3: {
            string task;
            int priority;
            cout << "Enter task: ";
            getline(cin, task);
            cout << "Enter priority (1-High, 2-Medium, 3-Low): ";
            cin >> priority;
            addPriorityTask(priorityHead, task, priority);
            break;
        }
        case 4:
            taskQueue.display();
            break;
        case 5:
            displayPriorityTasks(priorityHead);
            break;
        case 6: {
            string action = undoStack.pop();
            if (!action.empty()) {
                cout << "Undoing: " << action << endl;
            }
            break;
        }
        case 7: {
            int id;
            string task;
            cout << "Enter task ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter task: ";
            getline(cin, task);
            taskBST.addTask(id, task);
            break;
        }
        case 8:
            taskBST.displayTasks();
            break;
        case 9: {
            int id;
            cout << "Enter task ID to search: ";
            cin >> id;
            taskBST.searchTask(id);
            break;
        }
        case 10:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    } while (choice != 10);

    return 0;
}