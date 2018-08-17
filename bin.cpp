/* Program: bin.cpp
 * Name: Calista Wong
 * Description: This program reads from a file, then uses first fit and first fit decreasing to determine how many containers are needed to fill a vector of weights with a capacity restriction.
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//struct for every bin that is created and its corresponding capacity
struct bin
{
        int capacity;
};

//converts a string to int
int stringToInt(string s)
{
        int x=0;
        stringstream geek(s);
        geek >> x;
        return x;
}

//void insertSort(int myArray[], int size)
void insertSort(vector<int>myVector)
{
        for (int i=1; i<myVector.size(); i++)
        {
                int key = myVector[i]; //key is the value that we are looking at, initialize it to the second value of the array
                int j= i-1; //j is the value we are comparing key to, initialize it to one less than key

                while (j>=0 && myVector[j] >key) //if the value of myArray[j] is greater than the key and is a valid array value
                                {
                                        myVector[j+1] = myVector[j];      //move it one position ahead of its current position
                                        j=j-1; //decreemnt it to look at the one below
                                }
                myVector[j+1]=key;
        }

        //results from within function
        cout << "after sort in function " << endl;
        for (int i=0; i<myVector.size(); i++)
        {
                cout << myVector[i] << " ";
        }
        cout << endl;
}


//first fit
int firstFit(int cap, int numItems, vector<int> weights)
{
        bin *myBin;
        vector<bin*>binCollection;
        //initialize a starting bin and add it to the bin collection
        myBin = new bin;
        myBin->capacity=cap;
        binCollection.push_back(myBin);

        bool fit=false; //flag to indicate if our item fit into a container successfully
        for (int i=0; i<numItems; i++)
                {
                        int current = weights[i];
                        //cout << "current weight: " << current << endl;
                        //cout << "size of bin collection: " << binCollection.size() << endl;
                        while (fit == false)
                                {
                                        for (int j=0; j<binCollection.size(); j++)
                                                {

                                                        //cout << "current bin capacity: " << binCollection[j]->capacity << endl;
                                                        if (binCollection[j]->capacity - current >=0)//there is enough space
                                                                {
                                                                        //cout << "there is enough space " << endl;
                                                                        binCollection[j]->capacity = binCollection[j]->capacity-current;
                                                                        //cout << "new bin space: " << binCollection[j]->capacity << endl;
   									fit = true;
                                                                        break;
                                                                }

                                                        else //not enough space in the current bin
                                                                {
                                                                        //cout << "not enough space: " << endl;
                                                                        //cout << "j value: " << j << endl;
                                                                        //cout << "bincollection value: " << binCollection.size() << endl;

                                                                        if (j==binCollection.size()-1) //it is the last avail bin so we need to make a new one
                                                                                {
                                                                                        //cout << "we need to create a new bin" << endl;
                                                                                        //create a new bin
                                                                                        myBin=new bin;
                                                                                        //cout << "new bin created " << endl;
                                                                                        //initialize capacity by subtracting from current item's weight
                                                                                        myBin->capacity = cap-current;
                                                                                        binCollection.push_back(myBin);
                                                                                        //cout << "new bin space:" << myBin->capacity << endl;
                                                                                        fit = true;
                                                                                        break;
                                                                                }

                                                                }
                                                }

                                }
                        fit = false;
                        //cout << endl;
                }
        return binCollection.size();
}


//first fit decreasing
int firstFitDec(int cap, int numItems, vector<int> myVector)
{
        //sort the vector
        for (int i=1; i<myVector.size(); i++)
        {
                int key = myVector[i]; //key is the value that we are looking at, initialize it to the second value of the array
                int j= i-1; //j is the value we are comparing key to, initialize it to one less than key

                while (j>=0 && myVector[j] <key) //if the value of myArray[j] is greater than the key and is a valid array value
                                {
                                        myVector[j+1] = myVector[j];      //move it one position ahead of its current position
                                        j=j-1; //decreemnt it to look at the one below
                                }
                myVector[j+1]=key;
        }
        /*
        for (int i=0; i<myVector.size(); i++)
        {
                cout << myVector[i] << " ";
        }
        cout << endl;
        */
        //send to firstFit and return result
        return firstFit(cap, numItems, myVector);
}

int main()
{

        ifstream infile;
        infile.open("bin.txt");
        if (!infile)
        {
                cout << "File not found." << endl;
        }

        int numTest; //number of test cases
        //vector <int> testCases; //stores the test cases
        int cap=0;
        int numItems=0;
        vector <int> weights; //stores a list of the weights we will use

        string myString;
        int x=0;
 	int iteration=0;
        while (infile >> myString) //parse file information
                {
                        //cout << "iteration: " << iteration << endl;
                        if (iteration ==0)
                                {
                                        numTest = stringToInt(myString);
                                        //cout << "number of tests: " << numTest << endl;
                                }
                        else if (iteration==1) //store cap
                                {
                                        //cout << "store cap: " << myString << endl;
                                        cap=stringToInt(myString);
                                }
                        else if (iteration ==2) //store number of items
                                {
                                        //cout << "store num items: " << myString << endl;
                                        numItems = stringToInt(myString);
                                }
                        else if (iteration == 3)//store the list of weights
                        {
                                //cout << "store weights: " << endl;
                                //first member of line
                                weights.push_back(stringToInt(myString));

                                //remaining members
                                if (getline(infile, myString))
                                {
                                        istringstream is(myString); //store first
                                        int n;
                                        while (is >> n) //store remaining
                                                {
                                                        weights.push_back(n);
                                                        //cout << n;
                                                }
                                }


                                //send to function
                                cout << "First fit: " << firstFit(cap, numItems, weights) << endl;
                                cout << "First fit decreasing: " << firstFitDec(cap, numItems, weights) << endl;
                                /*
                                cout << "Summary: " << endl;
                                cout << "cap: " << cap << endl;
                                cout << "numItems: " << numItems << endl;
                                cout << "weights: " << endl;
                                for (int i=0; i<weights.size(); i++)
                                {
                                        cout << weights[i] << " ";
                                }
                                cout << endl;
                                */
                                //set up for next round
                                iteration = 0;
                                weights.clear();
                                //we need to store cap for next round here
                                cap = stringToInt(myString);
                                numItems = 0;

                        }
                        iteration++;
                        //cout << endl;
                }


        infile.close();

        return 0;
}



