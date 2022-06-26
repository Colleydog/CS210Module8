#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

void printMenu();
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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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


int main()
{
	int input;
	
	printMenu();
	cin >> input;
	std::system("cls");

	//loops till option 4 is selected from menu
	while (input != 4) {

		//make a lsit of all items purchased in a given day along with the number of times each item was purchased
		if (input == 1){
			CallProcedure("determineInventory");
		}
		//makes number represeting how many ties a specidic item was purchased in a day
		else if (input == 2) {
			cout << "Enter in the item you would like to look for: " << endl;
			string item;
			
			cin >> item;
			//makes first char in string to upper case
			item[0] = toupper(item[0]);
			
			int num = callIntFunc("determineFrequency", item);
				//If num is less then 
				if (num < 1) {
					cout << "No item quantity" << endl;
				}else
					cout << item << "  " << callIntFunc("determineFrequency", item) << endl;
		}
		//makes a histogram listing all items purchased in a given day, with a symbol of all times the item was purchased
		else if (input == 3) {
			string item;
			cout << "Type in a single character to represent the histogram" << endl;

			cin >> item;
			callIntFunc("histogram", item);
		}
		else {
			cout << "invalid input" << endl;
			
		}

		std::system("pause");
		//if 4 was never selected; will ask for new input
		if (input != 4) {
			std::system("cls");
			printMenu();
			
			cin >> input;
		}
		
	}


	std::system("pause");
	return 0;
}

void printMenu() {
	cout << "Select an option below " << endl;
	cout << "1. Show list of all items purchased" << endl;
	cout << "2. Show number of times a given items was purchased" << endl;
	cout << "3. text-based histogram for all items purchased in a given day" << endl;
	cout << "4. to exit" << endl;
}

void numberItemsAppear() {
	CallProcedure("getInventory");

}
