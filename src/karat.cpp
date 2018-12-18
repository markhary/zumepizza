#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

/*
Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique integer identifier.

For example, in this diagram, 3 is a child of 1 and 2, and 5 is a child of 4:
            
1   2   4
 \ /   / \
  3   5   8
   \ / \   \
    6   7   10


Write a function that, for two given individuals in our dataset, returns true if and only if they share at least one ancestor.

Sample input and output:
parentChildPairs, 3, 8 => false
parentChildPairs, 5, 8 => true
parentChildPairs, 6, 8 => true
*/

// Use with std::map, this is a nice and clean tree structure
// Assuming fixed two nodes max
// Note that C++11 automatically initializes these to 0
struct PersonStruct {
    int parent1;
    int parent2;
};

// Used to make a clean answer for the first question
struct ParentsStruct {
  vector<int> zeroParents;
  vector<int> oneParents;
};

// Space complexity O(N)
// Time complexity worst-case O(N*log(N)) because of std::map 
ParentsStruct countParents(vector<pair<int, int>> parent_child_pairs) {
    ParentsStruct parents;
    
    // Key = unique identifier for child
    // Value = number of parents
    // O(N*log(N))
    std::map<int, int> person;
    
    // O(N)
    // iterate through parent_child_pairs
    // put key/value into list and increment value
    for (const auto &pcp: parent_child_pairs) {
        person[pcp.first];
        person[pcp.second]++;
    }
    
    // iterate keys and make my arrays
    // O(N)
    for (const auto &p: person) {
        if (p.second == 1) {
            parents.oneParents.push_back(p.first);
        } else if (!p.second) {
            parents.zeroParents.push_back(p.first);
        } else {
            // Two parents    
        }
    }
  
    return parents;
}

//
// Traverse a tree structure and get a list of all ancestors.  
// Not sure what to make of the complexity, have to traverse
// all nodes to get information, but we only have to go
// one way.  This this is at worst O(N), but average O(log(N)).
// Space complexity is O(N)
//
vector<int> getAncestors(map<int, PersonStruct> &persons, 
                         int person) {
    vector<int> ancestors;
    
    // Start with a person, get the parent, push it to the list,
    // and then recursively call self to get ancestors of that
    // person
    
    if ( persons[person].parent1 != 0 ) {
        ancestors.push_back(persons[person].parent1);
        vector<int> tmpAncestors = getAncestors(persons, 
                                         persons[person].parent1);
        ancestors.insert(ancestors.end(), tmpAncestors.begin(),
                         tmpAncestors.end());
    }
    if ( persons[person].parent2 != 0 ) {
        ancestors.push_back(persons[person].parent2);
        vector<int> tmpAncestors = getAncestors(persons, 
                                         persons[person].parent2);
        ancestors.insert(ancestors.end(), tmpAncestors.begin(),
                         tmpAncestors.end());
    }
    
    return ancestors;
}

// 1. Create the tree structure
// 2. Traverse the tree structure for person 1
//   -- push parents to array
//   -- Have to recursively check each parent and add their
//      parents to the array
// 3. Do the same for person 2
// 4. Check if any of the ancestors in person 1 are in person 2.
//    Only have to check one (see note below).  
// Edge case: Have to share ancestors because person N cannot 
//            be their own ancestor
// I think this is space complexity O(N), and time complexity
// O(N*(log(N))) because I am using std::map
//
bool compareAncestors(vector<pair<int, int>> parent_child_pairs, 
                      const int &person1, const int &person2) {
    
    // Key = unique identifier for person
    // Person will have two parents, as noted by the value of
    // parent.  0 means no parent
    std::map<int, PersonStruct> persons;
    
    // O(N)
    // iterate through parent_child_pairs
    // put key/value into list
    for (const auto &pcp: parent_child_pairs) {
        // Create an entry in my map for the parent
        persons[pcp.first];
        
        // Now I have a map of of children and parents
        if ( persons[pcp.second].parent1 == 0 ) {
            persons[pcp.second].parent1 = pcp.first;
        } else if ( persons[pcp.second].parent2 == 0 ) {
            persons[pcp.second].parent2 = pcp.first;
        } else {
            cout << "Error - more than two parents" << endl;
        }
    }
    
    // Now go through and get a list of the ancestors for person 1
    vector<int> ancestors1 = getAncestors(persons, person1);
    vector<int> ancestors2 = getAncestors(persons, person2);
    
    // print out ancestors for person 1
    cout << "Ancestors person " << person1 << ": [";
    for (const auto &a: ancestors1) {
        cout << a << " ";
    }
    cout << "]" << endl;
    
    // print out ancestors for person 2
    cout << "Ancestors person " << person2 << ": [";
    for (const auto &a: ancestors2) {
        cout << a << " ";
    }
    cout << "]" << endl;
    
    // Now check if any ancestors from 1 are in 2
    // Let A = A0, A1... An and
    //     B = B0, B1, Bm
    //  We are lookging for any x that is in A or B.
    //  So it is sufficient to loop through all elements of A
    //    and see if they are in B.  Do not have to do this twice
    //  Also, can exit quickly if either list is empty
    if ( ancestors1.size() && ancestors2.size() ) {
        for (const auto &a: ancestors1) {
            if (std::find(ancestors2.begin(), ancestors2.end(), 
                          a) != ancestors2.end()) {
                return true;
            }
        }
    }
    
    return false;
}

int main() {

  
    // list of unique individuals
    // iterate through list and track count parents
    // don't care about individuals with two parents
    
    // std::pair. first->parent, second->child
    cout << "-- Exercise One --" << endl;
  
    vector<pair<int, int>> parent_child_pairs = {
        std::make_pair(1, 3),
        std::make_pair(2, 3),
        std::make_pair(3, 6),
        std::make_pair(5, 6),
        std::make_pair(5, 7),
        std::make_pair(4, 5),
        std::make_pair(4, 8),
        std::make_pair(8, 10)
    };
  
    ParentsStruct parents = countParents(parent_child_pairs);
    cout << "[" << endl;
    cout << " [";
    for (const auto &z: parents.zeroParents) {
        cout << z << ", ";
    }
    cout << " ]" << endl;
    cout << " [";
    for (const auto &o: parents.oneParents) {
        cout << o << ", ";
    }
    cout << " ]" << endl;
    cout << "]" << endl;
    
    cout << "-- Exercise Two --" << endl;
      
    bool answer;
    
    //parentChildPairs, 3, 8 => false
    answer = compareAncestors(parent_child_pairs, 3, 8); 
    cout << "parentChildPairs, 3, 8 => " 
        << (answer? "true": "false") << endl;
            
    //parentChildPairs, 5, 8 => true
    answer = compareAncestors(parent_child_pairs, 5, 8); 
    cout << "parentChildPairs, 3, 8 => " 
        << (answer? "true": "false") << endl;
            
    //parentChildPairs, 6, 8 => true
    answer = compareAncestors(parent_child_pairs, 6, 8); 
    cout << "parentChildPairs, 3, 8 => " 
        << (answer? "true": "false") << endl;
    
    // Added in another pair to check
    // parentChildPairs, 1, 8 => false
    // Because no self ancestors
    answer = compareAncestors(parent_child_pairs, 1, 6); 
    cout << "parentChildPairs, 1, 6 => " 
        << (answer? "true": "false") << endl;
      
    return 0  ;
}


