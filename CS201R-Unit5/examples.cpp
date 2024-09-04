#include "examples.h"

void example1() {
    //Demonstration of File I/O

    // create a variable for the input & output files
    ifstream inFile;
    ofstream outFile;

    // open the files & assign the input and output files to the variables
    inFile.open("input1.txt");
    outFile.open("output1.txt");

    // check the input file is valid
    if (!inFile.good() || !outFile.good()) {
        cout << "Unable to open file(s)/n";
        return;
    }

    // input values from the input file
    // add to the sum 
    // output the sum of the values
    // 
    // ADD LOGIC TO VERIFY INPUT IS NUMERIC
    // ADD LOGIC TO STORE VALUES IN VECTOR
    int next, sum = 0;
 
    while (inFile >> next) {
        sum += next;
        outFile << next << " ";
    }

    // write the average of the odd values to the output file
    outFile << "\nThe sum is: " << sum << endl;

    // close the input & output files
    outFile.close();
    inFile.close();
}


void example2() {
    //Demonstration of stringstream, vector of struct types

    struct Person {
        string last;
        string first;
        int age;
    };

    // name the input & output streams
    ifstream inFile;
    ofstream outFile;

    // open both files  
    inFile.open("input2.txt");
    outFile.open("output2.txt");

    // ADD LOGIC TO VERIFY FILES ARE GOOD

    //reading a CSV file
    string inLine, last, first, age;

    vector<Person> people;
    Person temp;

    while (getline(inFile, inLine)) {     // read each line of input
        istringstream inSS(inLine);

        // separate data (separated by white space)
        // these are all strings
        inSS >> last;
        inSS >> first;
        inSS >> age;

        //UPDATE LOGIC TO STORE VALUES IN VECTOR  
 

        outFile << first << " " << last << " : " << age << endl;
    }

    //UPDATE LOGIC TO PRINT VECTOR
  
    outFile.close();
    inFile.close();
}

 
void example3() {
    //Demonstration of File I/O & CSV file input using string stream & output formatting

    // name the input & output streams
    ifstream inFile;
    ofstream outFile;

    // open both files using the variable name for the input & output streams
    inFile.open("input3.txt");
    outFile.open("output3.txt");

    // check that the input file opened
    if (!inFile.good() || !outFile.good()) {
        cout << "Unable to open file(s)/n";
        return;
    }

    //reading a CSV file
    string inLine, token;
    vector<string> tokens;               // vector of strings to hold each
    
    // read in line, break up by commas
    while (getline(inFile, inLine)) {     // read each line of input
        stringstream inSS(inLine);        //copy input line to stringstream
        tokens.clear();                   //clear vector of previous data
        while (getline(inSS, token, ',')) {  //as long as there are commas
            tokens.push_back(token);         //add string(token)to vector of tokens
        }
        outFile << tokens[0] << "  "
            << setw(20) << left << tokens[1]
            << right << setw(10);  //print id and name
        int sum = stoi(tokens[2]) + stoi(tokens[3]) + stoi(tokens[4]);  //add 3 values 
        outFile << setprecision(2) << fixed << static_cast<double>(sum) / 3 << endl;
    }
    outFile.close();
    inFile.close();
}

void example4() {
    //Demonstration of File I/O & CSV file input using string stream & output formatting
    //store values in a vector of 'struct' types containing the id, name, and 3 scores

    struct studentInfo {          //using a struct for related student data
        char id;
        string name;
        int score1;
        int score2;
        int score3;
    };

    // name the input & output streams
    ifstream inFile;
    ofstream outFile;

    // open both files using the variable name for the input & output streams
    inFile.open("input3.txt");
    outFile.open("output4.txt");

    // check that the input file opened
    if (!inFile.good() || !outFile.good()) {
        cout << "Unable to open file(s)/n";
        return;
    }

    vector<studentInfo> studentData;             // create a vector to hold student data
    studentInfo tempData;                        // create a struct to hold 1 student's data
    string inLine, token;
    vector<string> tokens;                    // vector of strings to hold each 
    // string between the commas
    int sum;
    while (getline(inFile, inLine)) {          // read a line of input from the input file
        stringstream inSS(inLine);             //copy input line to stringstream
        tokens.clear();                       //clear vector of previous data
        sum = 0;

        while (getline(inSS, token, ',')) {
            tokens.push_back(token);              //as long as there are commas 
            // push each value onto row
        }
        //store data from row in temp data structure
        tempData.id = tokens[0][0];              //row[0] is a string - take 0th character
        tempData.name = tokens[1];
        tempData.score1 = stoi(tokens[2]);
        tempData.score2 = stoi(tokens[3]);
        tempData.score3 = stoi(tokens[4]);

        studentData.push_back(tempData);       // push student onto the vector
    }

    //print id, name, scores & average
    for (int i = 0; i < studentData.size(); i++) {
        sum = studentData[i].score1 + studentData[i].score2 + studentData[i].score3;
        double avg = static_cast<double>(sum) / 3;

        outFile << studentData[i].id << "  "
            << setw(20) << left
            << studentData[i].name << right << setw(10)
            << setprecision(2) << fixed << avg << endl;
    }

    //close data file
    outFile.close();
    inFile.close();
}

void example5() {
    //Demonstration of File I/O & CSV file input using string stream & vector manipulation
    ifstream inFile;
    ofstream outFile;

    inFile.open("input5.txt");
    outFile.open("output5.txt");

    if (!inFile.good()) {
        cout << "Unable to open input file/n";
        return;
    }

    //find average for each student
    stringstream inSS;
    string inLine, token;
    vector<string> tokens, names;
    vector<string>::iterator it;

    int sum;
    while (getline(inFile, inLine)) {
        stringstream inSS(inLine);             //copy input line to stringstream
        tokens.clear();                        //clear vector of previous information
        sum = 0;
        while (getline(inSS, token, ',')) {    //loop as long as there are commas 
            tokens.push_back(token);           //push onto tokens          
        }
        if (tokens[0] == "a")
            names.push_back(tokens[1]);
        else if (tokens[0] == "d") {
            it = find(names.begin(), names.end(), tokens[1]);
            if (it != names.end())
                names.erase(it);
        }
        else if (tokens[0] == "r") {
            //replace is found in algorithms
            replace(names.begin(), names.end(), tokens[1], tokens[2]);

            //this is another way to replace the data in the vector
            //it = find(names.begin(), names.end(), row[1]);
            //if (it != names.end()) {
                //names.erase(it);
                //names.push_back(row[2]);
            //}
        }
    }
    for (int i = 0; i < names.size(); i++)
        outFile << names.at(i) << endl;

    outFile.close();
    inFile.close();
}
bool isDigits(string str1) {
    return str1.find_first_not_of("0123456789") == string::npos;
}

bool isDigits2(string str1) {
    for (int i = 0; i < str1.size(); i++)
        if (!isdigit(str1[i]))
            return false;
    return true;
}

void example6() {
    cout << "EXAMPLE 6: HANDLING FILE I/O\n";
    //Demonstration of File I/O

    // create a variable for the input & output files
    ifstream inFile;
    ofstream outFile;

    // open the files & assign the input and output files to the variables
    inFile.open("input6.txt");
    outFile.open("output6.txt");

    // check the input file is valid
    if (!inFile.good()) {
        cout << "Unable to open input file/n";
        return;
    }

    // input values from the input file
    // if numeric, convert the value and add to the sum 
    // output the sum of the values
    // isDigits or isDigits2 would both work
    string next;
    int numb, sum = 0;
    while (inFile >> next) {
        if (!isDigits(next))
            continue;
        sum += stoi(next);
        outFile << next << " ";
    }


    // write the average of the odd values to the output file
    outFile << "\nThe sum is: " << sum << endl;

    // close the input & output files
    outFile.close();
    inFile.close();
}

void example7() {
    cout << "EXAMPLE 7: HANDLING INVALID INPUT\n";
    int x, y;
    string clearStr;
    try {
        cout << "Enter the nominator: \n";
        cin >> x;
        cout << "Enter the dominator: \n";
        cin >> y;

        if (y == 0)
            throw runtime_error(to_string(x)
                + "can't be divided by 0.");

        cout << "The result of the division is ";
        cout << x / y << endl;
    }
    catch (runtime_error e) {
        cout << e.what() << endl;
    }
    getline(cin, clearStr);
}
void example8() {
    //Demonstration of stringstream
    cout << "EXAMPLE 8: USING STRINGSTREAM\n";
    // name the input & output streams
    ifstream inFile;
    ofstream outFile;

    // open both files  
    inFile.open("input8.txt");
    outFile.open("output8.txt");

    // check that the input file opened
    if (!inFile.good()) {
        cout << "Error in input file/n";
        return;
    }

    //reading an input file (values separated spaces)
    string inLine, tempValue;
    int intValue, count, sum;
    bool errorFound;

    while (getline(inFile, inLine)) {     // read each line of input
        istringstream inSS(inLine);
        count = 0;
        sum = 0;
        errorFound = false;
        // separate data (separated by white space)
        while (inSS >> tempValue) {
            try {
                intValue = stoi(tempValue);
                count++;
                sum += intValue;
            }
            catch (invalid_argument) {
                errorFound = true;
                break;
            }
        }
        try {
            if (count == 0)
                throw runtime_error("No valid values in input line: ");
            if (errorFound)
                throw ("Error in input line: ");
            outFile << "The average of the values is: "
                << sum / static_cast<double>(count) << endl;
        }
        catch (runtime_error e) {
            outFile << e.what() << inLine << endl;
        }
        catch (...) {
            outFile << "ERROR: " << inLine << endl;
        }
    }

    outFile.close();
    inFile.close();
}


void example9() {
    cout << "EXAMPLE 9: FAIL BITS\n";
    int speed;
    string x_string;
    stringstream x_value;
    cout << "Enter an integer:\n";
    cin >> x_string;
    try {
        x_value.exceptions(ios::failbit);
        x_value << x_string;
        x_value >> speed;
        cout << "Speed is " << speed << endl;
    }
    catch (const ios::failure& failure) {
        cout << "Could not convert " << x_value.str()
            << " to an int" << endl;
        cout << failure.what() << endl;
        cout << failure.code() << endl;
    }
}

double division(double a, double b)
{
    if (b == 0) {
        throw runtime_error("Cannot divide by 0");
    }
    return (a / b);
}

void example10() {
    cout << "EXAMPLE 10: TRY/CATCH WITH FUNCTIONS\n";

    double x, y;
    cout << "Enter two numbers: \n";
    cin >> x >> y;
    double z;

    try {
        z = division(x, y);
        cout << "The result= " << z << endl;
    }
    catch (runtime_error e) {
        cout << e.what() << endl;
    }

}


