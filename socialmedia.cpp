#include <iostream>
#include <string>

using namespace std;

const int MAXUSERS = 100;

class linkedList
{
    public:
        struct Node
        {
            string data;
            Node* link;
            Node(string val) : data(val), link(NULL) {}
        };

        linkedList() : start(NULL) {}

        ~linkedList()
        {
            clearData();
        }

        void add(string data)
        {
            if (hasData(data))
            {
                return;
            }
            Node* N = new Node(data);
            N->link = start;
            start = N;
        }

        void removeData(string data)
        {
            Node* ptr = start;
            Node* prev = NULL;
            while (ptr != NULL)
            {
                if (ptr->data == data)
                {
                    if (prev == NULL)
                    {
                        start = ptr->link;
                    }
                    else
                    {
                        prev->link = ptr->link;
                    }
                    delete ptr;
                    return;
                }
                prev = ptr;
                ptr = ptr->link;
            }
        }

        bool hasData(string data)
        {
            Node* ptr = start;
            while (ptr != NULL)
            {
                if (ptr->data == data)
                {
                    return true;
                }
                ptr = ptr->link;
            }
            return false;
        }

        void clearData()
        {
            Node* ptr = start;
            while (ptr != NULL)
            {
                Node* link = ptr->link;
                delete ptr;
                ptr = link;
            }
            start = NULL;
        }

        void display()
        {
            Node* ptr = start;
            while (ptr != NULL)
            {
                cout << ptr->data << " ";
                ptr = ptr->link;
            }
            cout << endl;
        }

    private:
        Node* start;
};

class Stack
{
    public:
        struct Node
        {
            string data;
            Node* link;
            Node(string val) : data(val), link(NULL) {}
        };

        Stack() : top(NULL) {}

        ~Stack()
        {
            clearData();
        }

        void push(string data)
        {
            if (hasData(data))
            {
                return;
            }
            Node* N = new Node(data);
            N->link = top;
            top = N;
        }

        string pop()
        {
            if (top == NULL)
            {
                return "";
            }
            Node* temp = top;
            string data = top->data;
            top = top->link;
            delete temp;
            return data;
        }

        bool isEmpty()
        {
            return top == NULL;
        }

        bool hasData(string data)
        {
            Node* ptr = top;
            while (ptr != NULL)
            {
                if (ptr->data == data)
                {
                    return true;
                }
                ptr = ptr->link;
            }
            return false;
        }

        void clearData()
        {
            while (!isEmpty())
            {
                pop();
            }
        }

        void display()
        {
            Node* ptr = top;
            while (ptr != NULL)
            {
                cout << ptr->data << " ";
                ptr = ptr->link;
            }
            cout << endl;
        }
    private:
        Node* top;

};

class Queue
{
    public:
        struct Node
        {
            string data;
            Node* link;
            Node(string val) : data(val), link(NULL) {}
        };

        Queue() : front(NULL), rear(NULL) {}

        ~Queue()
        {
            clearData();
        }

        void enqueue(string data)
        {
            Node* N = new Node(data);
            if (rear == NULL)
            {
                front = rear = N;
            }
            else
            {
                rear->link = N;
                rear = N;
            }
        }

        string dequeue()
        {
            if (front == NULL)
            {
                return "";
            }
            Node* temp = front;
            string data = front->data;
            front = front->link;
            if (front == NULL)
            {
                rear = NULL;
            }
            delete temp;
            return data;
        }

        bool isEmpty()
        {
            return front == NULL;
        }

        void clearData()
        {
            while (!isEmpty())
            {
                dequeue();
            }
        }

        void display()
        {
            Node* ptr = front;
            while (ptr != NULL)
            {
                cout << ptr->data << " ";
                ptr = ptr->link;
            }
            cout << endl;
        }
    private:
        Node* front;
        Node* rear;

};

class binaryTree
{
    public:
        struct Node
        {
            string data;
            Node* lchild;
            Node* rchild;
            Node(string val) : data(val), lchild(NULL), rchild(NULL) {}
        };

        binaryTree() : root(NULL) {}

        ~binaryTree()
        {
            clearData(root);
        }

        void insertDummy(string data)
        {
            root = insertCall(root, data);
        }

        void inorderDummy()
        {
            cout << endl;
            inOrderCall(root);
        }

        Node* insertCall(Node* node, string data)
        {
            if (node == NULL)
            {
                return new Node(data);
            }

            if (data < node->data)
            {
                node->lchild = insertCall(node->lchild, data);
            }
            else
            {
                node->rchild = insertCall(node->rchild, data);
            }

            return node;
        }

        void inOrderCall(Node* node)
        {
            if (node == NULL)
            {
                return;
            }

            inOrderCall(node->lchild);
            cout << node->data << endl;
            inOrderCall(node->rchild);
        }

        void clearData(Node* node)
        {
            if (node)
            {
                clearData(node->lchild);
                clearData(node->rchild);
                delete node;
            }
        }
    private:
        Node* root;
};

class SocialMedia
{
    public:
        SocialMedia()
        {
            for (int i = 0; i < MAXUSERS; i++)
            {
                followers[i] = new linkedList();
                following[i] = new linkedList();
                postTree[i] = new binaryTree();
                notifications[i] = new Queue();
                searchedUsers[i] = new Stack();
                profileViewers[i] = new Stack();
            }
            linkUserID = 0;
        }

        ~SocialMedia()
        {
            for (int i = 0; i < MAXUSERS; i++)
            {
                delete followers[i];
                delete following[i];
                delete postTree[i];
                delete notifications[i];
                delete searchedUsers[i];
                delete profileViewers[i];

            }
        }

        void addUser(string username)
        {
            userNames[linkUserID] = username;
            linkUserID++;
        }

        void addFollower(string username, string follower)
        {
            int userIndex = getUserIndex(username);
            int followerIndex = getUserIndex(follower);

            if (userIndex == -1 || followerIndex == -1)
            {
                cout << "User or follower not found." << endl;
                return;
            }

            followers[userIndex]->add(follower);
            following[followerIndex]->add(username);

            searchProfile(follower, username);


            string notification = "\nYou have a new follower: " + follower;
            notifications[userIndex]->enqueue(notification);
        }

        void removeFollower(string username, string follower)
        {
            int userIndex = getUserIndex(username);
            int followerIndex = getUserIndex(follower);

            if (userIndex == -1 || followerIndex == -1)
            {
                cout << "User or follower not found." << endl;
                return;
            }

            followers[userIndex]->removeData(follower);
            following[followerIndex]->removeData(username);
        }

        void postMessage(string username, string message)
        {
            int userIndex = getUserIndex(username);
            if (userIndex == -1)
            {
                cout << "User not found." << endl;
                return;
            }
            postTree[userIndex]->insertDummy(message);
        }

        void sendNotification(string username, string notification)
        {
            int userIndex = getUserIndex(username);
            if (userIndex == -1)
            {
                cout << "User not found." << endl;
                return;
            }
            notifications[userIndex]->enqueue(notification);
        }

        void searchProfile(string visitor, string profile)
        {
            int visitorIndex = getUserIndex(visitor);
            int profileIndex = getUserIndex(profile);

            if (visitorIndex == -1 || profileIndex == -1)
            {
                cout << "Visitor or profile not found." << endl;
                return;
            }

            searchedUsers[visitorIndex]->push(profile);
            profileViewers[profileIndex]->push(visitor);
        }


        int getUserIndex(string username)
        {
            for (int i = 0; i < linkUserID; i++)
            {
                if (userNames[i] == username)
                {
                    return i;
                }
            }
            return -1;
        }

        void displayNetwork()
        {
            for (int i = 0; i < linkUserID; i++)
            {
                cout << "User: " << userNames[i] << endl;
                cout << endl << "Followers: ";
                followers[i]->display();
                cout << "Following: ";
                following[i]->display();
                cout << endl << "Posts: ";
                postTree[i]->inorderDummy();
                cout << endl;
                cout << "Notifications: ";
                notifications[i]->display();
                cout << endl << "Searched Profiles: ";
                searchedUsers[i]->display();
                cout << "Profile Viewers: ";
                profileViewers[i]->display();
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }

    private:
        linkedList* followers[MAXUSERS];
        linkedList* following[MAXUSERS];
        binaryTree* postTree[MAXUSERS];
        Queue* notifications[MAXUSERS];
        Stack* searchedUsers[MAXUSERS];
        Stack* profileViewers[MAXUSERS];
        string userNames[MAXUSERS];
        int linkUserID;
};

int main()
{
    system("color 03");
    SocialMedia linkedIN;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                                                       LinkedIN LITE                                                                        " ;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

    int userCount = 22;
    string users[userCount] = {"Aakash", "Kabilan", "Jitesh", "Harshil", "Kavin Raj", "Haritha", "Vaishnavi", "Kaniska","Prathish", "Jovisha", "Raksha", "Sanchitha", "Sangamithra", "Santhosh", "Sri Vinay", "Rheya","Vithaha", "Shivashree", "Kavya", "Kaviya", "Devanand", "Anirutha"};

    for (int i = 0; i < userCount; i++)
    {
        linkedIN.addUser(users[i]);
    }

    linkedIN.addFollower("Aakash", "Kabilan");
    linkedIN.addFollower("Aakash", "Jitesh");
    linkedIN.addFollower("Aakash", "Kavin Raj");
    linkedIN.addFollower("Aakash", "Vaishnavi");

    linkedIN.addFollower("Kabilan", "Aakash");
    linkedIN.addFollower("Kabilan", "Jitesh");
    linkedIN.addFollower("Kabilan", "Haritha");
    linkedIN.addFollower("Kabilan", "Kaniska");

    linkedIN.addFollower("Jitesh", "Aakash");
    linkedIN.addFollower("Jitesh", "Kabilan");
    linkedIN.addFollower("Jitesh", "Vaishnavi");
    linkedIN.addFollower("Jitesh", "Prathish");

    linkedIN.addFollower("Harshil", "Kavin Raj");
    linkedIN.addFollower("Harshil", "Vaishnavi");
    linkedIN.addFollower("Harshil", "Haritha");
    linkedIN.addFollower("Harshil", "Kaniska");

    linkedIN.addFollower("Kavin Raj", "Harshil");
    linkedIN.addFollower("Kavin Raj", "Jitesh");
    linkedIN.addFollower("Kavin Raj", "Haritha");
    linkedIN.addFollower("Kavin Raj", "Vaishnavi");

    linkedIN.addFollower("Haritha", "Aakash");
    linkedIN.addFollower("Haritha", "Kabilan");
    linkedIN.addFollower("Haritha", "Vaishnavi");
    linkedIN.addFollower("Haritha", "Kavin Raj");

    linkedIN.addFollower("Vaishnavi", "Aakash");
    linkedIN.addFollower("Vaishnavi", "Jitesh");
    linkedIN.addFollower("Vaishnavi", "Kavin Raj");
    linkedIN.addFollower("Vaishnavi", "Haritha");

    linkedIN.addFollower("Kaniska", "Kabilan");
    linkedIN.addFollower("Kaniska", "Vaishnavi");
    linkedIN.addFollower("Kaniska", "Jovisha");
    linkedIN.addFollower("Kaniska", "Raksha");

    linkedIN.addFollower("Prathish", "Jitesh");
    linkedIN.addFollower("Prathish", "Vaishnavi");
    linkedIN.addFollower("Prathish", "Kaviya");
    linkedIN.addFollower("Prathish", "Devanand");

    linkedIN.addFollower("Jovisha", "Kaniska");
    linkedIN.addFollower("Jovisha", "Raksha");
    linkedIN.addFollower("Jovisha", "Sanchitha");
    linkedIN.addFollower("Jovisha", "Sangamithra");

    linkedIN.addFollower("Raksha", "Jovisha");
    linkedIN.addFollower("Raksha", "Sanchitha");
    linkedIN.addFollower("Raksha", "Kaviya");
    linkedIN.addFollower("Raksha", "Rheya");

    linkedIN.addFollower("Sanchitha", "Kaniska");
    linkedIN.addFollower("Sanchitha", "Raksha");
    linkedIN.addFollower("Sanchitha", "Jovisha");
    linkedIN.addFollower("Sanchitha", "Santhosh");

    linkedIN.addFollower("Sangamithra", "Kaviya");
    linkedIN.addFollower("Sangamithra", "Sanchitha");
    linkedIN.addFollower("Sangamithra", "Santhosh");
    linkedIN.addFollower("Sangamithra", "Sri Vinay");

    linkedIN.addFollower("Santhosh", "Sangamithra");
    linkedIN.addFollower("Santhosh", "Sanchitha");
    linkedIN.addFollower("Santhosh", "Sri Vinay");
    linkedIN.addFollower("Santhosh", "Vithaha");

    linkedIN.addFollower("Sri Vinay", "Santhosh");
    linkedIN.addFollower("Sri Vinay", "Rheya");
    linkedIN.addFollower("Sri Vinay", "Vithaha");
    linkedIN.addFollower("Sri Vinay", "Shivashree");

    linkedIN.addFollower("Rheya", "Sri Vinay");
    linkedIN.addFollower("Rheya", "Raksha");
    linkedIN.addFollower("Rheya", "Vithaha");
    linkedIN.addFollower("Rheya", "Shivashree");

    linkedIN.addFollower("Vithaha", "Santhosh");
    linkedIN.addFollower("Vithaha", "Sri Vinay");
    linkedIN.addFollower("Vithaha", "Rheya");
    linkedIN.addFollower("Vithaha", "Kaviya");

    linkedIN.addFollower("Shivashree", "Sri Vinay");
    linkedIN.addFollower("Shivashree", "Rheya");
    linkedIN.addFollower("Shivashree", "Kaviya");
    linkedIN.addFollower("Shivashree", "Devanand");

    linkedIN.addFollower("Kavya", "Vithaha");
    linkedIN.addFollower("Kavya", "Shivashree");
    linkedIN.addFollower("Kavya", "Rheya");
    linkedIN.addFollower("Kavya", "Anirutha");

    linkedIN.addFollower("Kaviya", "Rheya");
    linkedIN.addFollower("Kaviya", "Devanand");
    linkedIN.addFollower("Kaviya", "Anirutha");
    linkedIN.addFollower("Kaviya", "Prathish");

    linkedIN.addFollower("Devanand", "Anirutha");
    linkedIN.addFollower("Devanand", "Kaviya");
    linkedIN.addFollower("Devanand", "Shivashree");
    linkedIN.addFollower("Devanand", "Prathish");

    linkedIN.addFollower("Anirutha", "Devanand");
    linkedIN.addFollower("Anirutha", "Kaviya");
    linkedIN.addFollower("Anirutha", "Kavya");
    linkedIN.addFollower("Anirutha", "Vithaha");

    linkedIN.postMessage("Aakash", "Welcome to LinkedIN Lite!");
    linkedIN.postMessage("Kabilan", "Good morning!");
    linkedIN.postMessage("Jitesh", "Movie Binge");
    linkedIN.postMessage("Harshil", "It's a beautiful day!");
    linkedIN.postMessage("Kavin Raj", "Just finished my morning run.");
    linkedIN.postMessage("Haritha", "Excited for the weekend!");
    linkedIN.postMessage("Vaishnavi", "Time to relax!");
    linkedIN.postMessage("Kaniska", "College's going well today.");
    linkedIN.postMessage("Prathish", "Great workout session!");
    linkedIN.postMessage("Jovisha", "Planning a trip!");
    linkedIN.postMessage("Raksha", "Enjoying the sunny weather!");
    linkedIN.postMessage("Sanchitha", "Relaxing with family.");
    linkedIN.postMessage("Sangamithra", "Cooking something new today!");
    linkedIN.postMessage("Santhosh", "Looking forward to dinner.");
    linkedIN.postMessage("Sri Vinay", "Learning a new skill.");
    linkedIN.postMessage("Rheya", "Loving the new movie I watched!");
    linkedIN.postMessage("Vithaha", "Exploring the city.");
    linkedIN.postMessage("Shivashree", "Meditating in the morning.");
    linkedIN.postMessage("Kavya", "Trying a new recipe!");
    linkedIN.postMessage("Kaviya", "Starting a new project.");
    linkedIN.postMessage("Devanand", "Finished a challenging task.");
    linkedIN.postMessage("Anirutha", "Reading a good book.");

    linkedIN.displayNetwork();
}
