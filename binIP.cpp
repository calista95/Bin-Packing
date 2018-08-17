#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//converts a string to int
int stringToInt(string s)
{
        int x=0;
        stringstream geek(s);
        geek >> x;
        return x;
}


//writes items into LP format
void writeFile(int round, float cap, int numItems, vector<int>weight)
{
	//convert round integer into a string in order to use for file naming
	stringstream ss;
	ss << round;
	
        ofstream outfile;
        string s = ss.str();
        s += "_testcase.txt";
        outfile.open(s.c_str());

        int i, j, k;
        //write data into the file

        //cout << "number of items: " << numItems << endl;
        //objective function
        outfile << "min ";
        for (i=1; i<numItems; i++)
        {
                outfile << "y" << i << "+" ;
        }
        outfile << "y" << numItems << endl;
        outfile << "ST" << endl;

        for (i=1; i<numItems; i++)
        {
                outfile << "y" << i << "+ ";
        }
        outfile << "y" << numItems << ">=1" << endl;
        outfile << endl;
        //first set of constraints
        for (i=1; i<=numItems; i++)
        {
                for (j=1; j<=numItems-1; j++)
                {
                        outfile << "x" << i << j << "+" ;
                }
                outfile << "x" << i << numItems ;
                outfile << "=1 " << endl;
        }
        outfile << endl;

        //second set of constraints
        for (j=1; j<=numItems; j++)
        {
                for (i=0; i<numItems-1; i++)
                {
                        outfile << weight[i] << "x" << i+1 << j << "+";
                }
                outfile << weight[numItems-1] << "x" << numItems << j << "-" << cap << "y" << j << "<= 0" << endl;
        }
        outfile << endl;

        outfile << "END" << endl;

        for (i=1; i<=numItems; i++)
        {
                outfile << "INT y" << i << endl;
        }
        for (i=1; i<=numItems; i++)
        {
                for (int j=1; j<=numItems; j++)
                {
                        outfile << "INT x" << i << j << endl;
                }
        }
  outfile.close();
}


int main()
{
        ifstream infile;
        infile.open("binEC.txt");
        if (!infile)
        {
                cout << "File not found." << endl;
        }


        int numTest; //number of test cases
        //vector <int> testCases; //stores the test cases
        float cap=0.0;
        int numItems=0;
        vector <int> weights; //stores a list of the weights we will use

        string myString;
        int x=0;
        int iteration=0;
        int round=1;
        while (infile >> myString) //parse file information
                {
                        if (iteration ==0)
                                {
                                        numTest = stringToInt(myString);
                                }
                        else if (iteration==1) //store cap
                                {
                                        cap=stringToInt(myString);
                                }
                        else if (iteration ==2) //store number of items
                                {
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
                                                }
                                }


                                //write data into file
                                writeFile(round, cap, numItems, weights);


                                //set up for next round
                                iteration = 0;
                                weights.clear();
                                //we need to store cap for next round here
                                cap = stringToInt(myString);
                                numItems = 0;
                                //increment the round
                                round++;

                        }
                        iteration++;
                }


        infile.close();


        return 0;
}
