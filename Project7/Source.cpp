#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <stdlib.h>


#include <string>

using namespace std;

int userInput;
string str;
string fileLine;


void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;

    return _PyLong_AsInt(presult);
}


void UserMenu()
{
    // Simple user menu to show options
    cout << "----------------- User Menu -----------------\n";
    cout << "1: Produce a list of all items purchased with quantities \n";
    cout << "2: Display how many times a specific item was sold \n";
    cout << "3: Produce a histogram of sales data \n";
    cout << "4: Exit \n\n";
    cout << "Enter your selection as a number: 1, 2, 3, or 4. \n";
    cout << "---------------------------------------------\n\n";


    // The Menu takes user input
    cin >> userInput;

    if (userInput == 1)
    {
        // Call Item Count Function from PythonCode.py
        cout << "\n\nPrinting items and quantities sold today: \n\n";
        CallProcedure("ItemCount");
        cout << "\n\n";
        return;
    }
    else if (userInput == 2)
    {
        // Prompt user to enter item name
        cout << "\n\nPlease enter the item name: \n\n";
        cin >> str;
        cout << "\n\n";
        cout << "Printing the sales for " << str << ":\n\n";
        // Call NameItemCount Function from PythonCode.py
        cout << str << ": " << callIntFunc("NameItemCount", str) << "\n\n";
        return;
    }
    else if (userInput == 3)
    {
        // First write the appropriate counts from the input file to the output file
        cout << "\n\nWriting items and quantities sold today to a file: \n\n";
        CallProcedure("ItemCountWriter");
        cout << "\n\n";
        // Open the output file Freq. DAT  and read the data
        ifstream frequencyFile("frequency.dat");
        string item;
        int count;
        //Run thru the file line by line and print the histogram
        while (getline(frequencyFile, fileLine))
        {
            istringstream iss(fileLine);
            if (!(iss >> item >> count)) { break; } // error
            // Print the item name and match count with asterisks display 
            cout << item << " " << string(count, '*') << endl;
        }
        cout << "\n\n";
        return;
    }
    else if (userInput == 4)
    {
        // Selecting 4 = EXIT the program
        cout << "\n\nExiting program . . . \n\n";
        exit(EXIT_SUCCESS);
    }
    else
    {
        // If user does not enter a valid menu option, 
        //User returned to menu
        cout << "\n\nPlease enter a valid input . . . \n\n";
        return;
    }
}


int main()
{
    //Back to  Menu. ( EXIT = 4) or (CTRL + C)
    while (1)
    {
        UserMenu();
        
    //Nice Colors???
        system("Color 0B");
    }

    return 0;
}