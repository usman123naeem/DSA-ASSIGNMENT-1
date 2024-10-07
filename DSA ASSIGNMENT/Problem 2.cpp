#include <iostream>
#include <random>
#include <string>
#include <cmath>

using namespace std;
// Node class : This class is used to make nodes that contain data(64 bits number) and pointing toward the next node
class Node {
public:
    u_int64_t num;
    Node* next;
    Node(u_int64_t num)  // Constructor of Node class
    {
        this->num = num;
        this->next = NULL;
    }
};
// Linked lisst
class LinkedList {
public:
    Node* start;
    int length;

    LinkedList() {
        start = NULL;
        length = 0;
    }
// Checks whether the linked list is empty or not
    bool isEmpty() {
        return start == NULL;
    }
// It inserts nodes in the linked list
    void insert(u_int64_t data) {
        Node* newNode = new Node(data);
        if (isEmpty()) // if the linked list is empty then the start node will be the new_node
        {
            start = newNode;
        } else // if the linked list have nodes then insert the node at the last and point its next instance to NULL
        {
            Node* temp = start;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        length++;
    }
// Function to convert the entire linked list into a string representation of the 1024-bit number
    string toString() {
        string result = "";
        Node* temp = start;
        while (temp->next != NULL) {
            result += to_string(temp->num);
            temp = temp->next;
        }
        result += to_string(temp->num);
        return result;
    }
// it will print the whole linked list
    void print() {
        if (isEmpty()) {
            cout << "The list is empty\n";
        } else {
            Node* temp = start;
            while (temp != NULL) {
                cout << temp->num << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

// Function to generate 1024-bit number and insert all 64-bit numbers into linked list
string generate_1024_bit_number(LinkedList& LL) {
    random_device rd;
    /*random_device can provide non-deterministic random numbers.
    It is commonly used to seed pseudo-random number generators (like mt19937 or other random engines)
    to improve the randomness of the numbers they produce. */
    mt19937_64 gen(rd());
    /*mt19937_64 is a class in the C++ Standard Library, specifically found in the <random> header,
    that implements the Mersenne Twister algorithm for generating pseudo-random numbers.*/
    uniform_int_distribution<uint64_t> dis(0, UINT64_MAX - 1);
    /*uniform_int_distribution ensures that all integers within the specified range are equally likely to be generated.
    uint64_t specifies the type of integers that the distribution will generate.
    '0' is the minimum value of the distribution.
    'UINT64_MAX' is the maximum value of the distribution.*/
    string _1024_bit_number = ""; // we do not have any data type in which we can store 1024 bit number so we use string concatenation to store 1024 bit number

    for (int i = 0; i < 16; i++) {
        uint64_t random_number = dis(gen);// generating the random 64 bit numbers
        LL.insert(random_number); // insert the 64 bit number in the seperate nodes of linked list
        _1024_bit_number += to_string(random_number); // sting concatenation
    }

    return _1024_bit_number;// returning the 1024 bit number in the form of string
}

// Miller-Rabin Primality Test
/*The Miller-Rabin Primality Test is a probabilistic algorithm used to determine whether a number is a prime.
Unlike deterministic primality tests, which can be computationally expensive for large numbers,
the Miller-Rabin test can quickly indicate whether a number is composite (not prime) or probably prime.*/
bool isPrime(string numStr) {
    // check if the input is "2" or "3", which are prime numbers
    if (numStr == "2" || numStr == "3") return true;

    // check for empty string or if the number is "0" or "1", which are not prime
    if (numStr.empty() || (numStr[0] == '0' || numStr[0] == '1')) return false;

    // convert the input string to an unsigned long long integer
    unsigned long long num = stoull(numStr);

    // check if the number is even; if so, it is not prime (except for 2)
    if (num % 2 == 0) return false;

    // Prepare for the Miller-Rabin test
    int k = 0; // This will count how many times we can divide by 2
    unsigned long long m = num - 1; // Start with m = num - 1

    // factor out powers of 2 from m
    while (m % 2 == 0) {
        m /= 2; // Divide m by 2
        k++; // Increment k for each division
    }

    // pErform the Miller-Rabin test with a few small bases (2, 3, 5, 7)
    for (unsigned long long a : {2, 3, 5, 7}) {
        // skip the base if it is greater than or equal to num
        if (a >= num) continue;

        // compute x = a^m - 1
        unsigned long long x = pow(a, m) - 1;

        // check if x is congruent to 0 mod num (indicating num is likely prime)
        if (x % num == 0) continue;

        // initialize isComposite to true; we will prove it false if we find evidence otherwise
        bool isComposite = true;

        // check if x can be squared to reach num - 1
        for (int j = 0; j < k; j++) {
            // If x becomes congruent to num - 1, num is probably prime
            if (x % num == num - 1) {
                isComposite = false; // Found evidence num is likely prime
                break; // Exit the loop early
            }
            // Square x and take mod num
            x = (x * x) % num;
        }

        // If no evidence was found for primality, return false
        if (isComposite) return false; // num is composite
    }

    // if all tests pass, return true; num is likely prime
    return true;
}


int main() {
    LinkedList L1;
    cout << "Randomly generated 1024-bit number: ";
    string generatedNumber = generate_1024_bit_number(L1);
    cout << generatedNumber << endl;

    // Check for primality of the entire number represented in the linked list
    cout << "Is the number prime? " << (isPrime(L1.toString()) ? "Yes" : "No") << endl;

    return 0;
}
