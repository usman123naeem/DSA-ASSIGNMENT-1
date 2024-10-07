
#include <iostream>
#include <string>
using namespace std;
int cycle = 0;
class Process
{
public:
    string Process_id;
    int execution_time;
    int remaining_time;
    Process()
    {
    }
    Process(string id, int time)
    {
        this->Process_id = id;
        this->remaining_time = time;
        this->execution_time = 0;
    }
    void print()
    {
        if (remaining_time>0){
        cout << " [ " << Process_id << " , " << remaining_time << " ] ";
    }
    else{
        cout<< " [ " << Process_id << " , (Completed) ]" ;
    }
    }
};

class Node
{
public:
    Process data;
    Node *next;
    Node()
    {
    }
    Node(Process data)
    {
        this->data = data;
        this->next = NULL;
    }
};
class Circular_linked_list
{
public:
    Node *start;
    int length;
    Circular_linked_list()
    {
        start = NULL;
        length = 0;
    }
    bool isEmpty()
    {
        return start == NULL;
    }
    void insert(Process data)
    {
        Node *node = new Node(data);
        if (isEmpty())
        {
            start = node;
            node->next = start;
            length++;
        }
        else
        {
            Node *temp = start;
            while (temp->next != start)
            {

                temp = temp->next;
            }
            node->next = start;
            temp->next = node;
            length++;
        }
    }
    void del(string process_id)
    {
        if (isEmpty())
        {
            cout << "The list is empty\n";
            return;
        }
        if (start->data.Process_id == process_id)
        {

            if (start->next == start)
            {

                delete start;

                start = NULL;

                return;
            }

            Node *temp = start;

            while (temp->next != start)
            {

                temp = temp->next;
            }

            temp->next = start->next;

            delete start;

            start = temp->next;

            return;
        }
        Node *temp = start;
        Node *prev = NULL;
        while (temp->next != start)
        {
            prev = temp;
            temp = temp->next;
            if (temp->data.Process_id == process_id)
            {
                break;
            }
        }
        if (temp->data.Process_id != process_id)
        {
            cout << "This process is not present in this Circular linked list\n";
        }
        else
        {

            prev->next = temp->next;
            free(temp);
        }
    }

    void print()
    {
        if (isEmpty())
        {
            cout << "The list is empty\n";
        }
        else
        {
            Node *temp = start;
            do
            {
                Process P_temp = temp->data;
                P_temp.print();

                temp = temp->next;
            } while (temp->next != start->next);
            cout << endl;
        }
    }
};
void Cycles(Circular_linked_list list, int Time)
{
    cycle++;

    if (list.isEmpty())
    {
        cout << "The list is empty\n";
    }
    else
    {
        Node *temp = list.start;
        Node *prev = NULL;
        while (temp->next != list.start)
        {
            temp->data.remaining_time = temp->data.remaining_time - 3;
            temp->data.execution_time = temp->data.execution_time + 3;
            temp->data.print();
            prev = temp;
            temp = temp->next;
            if (prev->data.remaining_time <= 0)
            {

                list.del(prev->data.Process_id);
            }
        }
        temp->data.remaining_time = temp->data.remaining_time - 3;
        temp->data.execution_time = temp->data.execution_time + 3;
        temp->data.print();
        if (temp->data.remaining_time <= 0)
        {

            list.del(temp->data.Process_id);
        }
        cout<<endl;
    }
}
int main()
{
    Circular_linked_list L1;
    Process P1("P 1", 10), P2("P 2", 5), P3("P 3", 8);
    L1.insert(P1);
    L1.insert(P2);
    L1.insert(P3);
    cout << "Initial Processes: ";
    L1.print();
    int CPU_TIME;
    cout << "CPU Time per Process per Cycle: ";
    cin >> CPU_TIME;
    cout << "Cycle 1 :";
    Cycles(L1, CPU_TIME);
    cout << "Cycle 2 :";
    Cycles(L1, CPU_TIME);
    Process P4("P 4", 9);
    cout << "New process arrives: ('P 4',9)\n";
    L1.insert(P4);
    cout << "Cycle 3 :";
    Cycles(L1, CPU_TIME);
    return 0;
}