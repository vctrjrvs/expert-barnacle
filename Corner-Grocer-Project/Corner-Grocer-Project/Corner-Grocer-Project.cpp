#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("StarterPythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
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
	pName = PyUnicode_FromString((char*)"StarterPythonCode");
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

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"StarterPythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
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

	return _PyLong_AsInt(presult);
}


void Grocer() {
	/*
	Print a menu that gives the user 4 options
	do/while and try/catch to ensure continuous use
	and correct inputs
	*/

	/*
	Run a loop, take the user input, and product type
	*/
	bool run = true;
	int userInput;
	string type;
	bool inputCorr;

	do {
		cout << endl;
		cout << "***************************" << endl;
		cout << "* Please Select An Option *" << endl;
		cout << "***************************" << endl;
		cout << endl;
		cout << "****************************************************" << endl;
		cout << "* 1. Print A List Of Purchased Items With Quantity *" << endl;
		cout << "*      2. Print The Total Quantity Of An Item      *" << endl;
		cout << "*                3. Print Histogram                *" << endl;
        cout << "*                  4. Exit Program                 *" << endl;
		cout << "****************************************************" << endl;
		cout << endl;


		try {
			/*Only accept choices one through four and items on list*/
			std::cin >> userInput;
			cout << "****************************************************" << endl;
			cout << endl;
			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(245, '\n');
				cout << "Error, please try again." << endl;
				cout << "Enter a number between 1 and 4" << endl;
				std::cin >> userInput;
				cout << "****************************************************" << endl;
				cout << endl;
			}
			if (userInput >= 0) {
				inputCorr = true;
			}
			else { throw (userInput); }
		}
		catch (...) {
			cout << "Enter a number between 1 and 4" << endl;
		}

		/*UI 1 looks for total products purchased list*/
		if (userInput == 1) {
			cout << endl;
			cout << "**********************************" << endl;
			cout << "* Total Products Purchased Today *" << endl;
			cout << "**********************************" << endl;
			cout << endl;

			CallProcedure("readFile");
		}
		/*UI 2 looks for specific product purchased report
		Must be on list, if not, throw error
		*/
		else if (userInput == 2) {
			string userStr;
			cout << "Enter product:";
			std::cin >> userStr;
			int total = callIntFunc("totalProducts", userStr);

			if (total == -1) {
				cout << "Item not located. Please try again." << endl;
			} else{
				cout << total << " " << userStr << " sold.";
			}
		}
		/*UI 3 runs our histogram functions and prints histogram*/
		else if (userInput == 3) {
			CallProcedure("readWriteFile");
		}
		else { run = false; }

	} while (run == true);
}

int main()
{
	CallProcedure("printsomething");
	/*cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);*/
	Grocer();

	cout << endl;
	cout << "***********" << endl;
	cout << "* Exiting *" << endl;
	cout << "***********" << endl;
	cout << endl;

	return 0;

}