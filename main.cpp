#include<bits/stdc++.h>
#include<Windows.h>
#include<io.h>
using namespace std;

int Mode, Start, Continue, Space, Speed;

char ch;
short vkCode;
int keydown, keyup;

string file_data;

HWND hwnd;

int get_Lparam(int vk, bool flag)
{
	int scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
	return flag | (scanCode << 16) | (flag << 30) | (flag << 31);
}

bool getFile()
{
	vector<_finddata_t> vec;
	string path = "config\\*.afk";
	struct _finddata_t file;
	long handle = _findfirst(path.c_str(), &file);
	if (handle == -1)
		return false;
	cout << "��⵽Ŀ¼���������ļ���" << endl << endl;
	cout << "[0]��ʹ�������ļ�" << endl;
	int num = 1;
	do
	{
		vec.push_back(file);
		cout << '[' << num++ << ']' << file.name << endl;
	} while (!_findnext(handle, &file));
	cout << endl;
	int count;
	cout << "��ѡ�������ļ���" << endl << "<< ";
	cin >> count;
	system("cls");
	if (count == 0)
		return false;
	char filename[50] = "config\\";
	strcat_s(filename, vec[count - 1].name);
	FILE* stream;
	freopen_s(&stream, filename, "r", stdin);
	cout << "ѡ��ɹ����ļ����ƣ�" << endl;
	cout << filename << endl << endl;
	return true;
}

void getWindow()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LMENU))
		{
			hwnd = GetForegroundWindow();
			if (hwnd != NULL)
			{
				char title[50];
				::GetWindowTextA(hwnd, title, sizeof(title));
				system("cls");
				cout << "����ɹ����������ƣ�" << endl;
				cout << title << endl;
			}
			else
				cout << "����ʧ�ܣ������ԣ�" << endl;
			cout << endl;
			return;
		}
		Sleep(1);
	}
}

void Get(int& a, bool flag)
{
	cin >> a;
	if (flag)
		cout << a << endl;
	else file_data += to_string(a) + '\n';
}

void Get(char& a, bool flag)
{
	cin >> a;
	if (flag)
		cout << a << endl;
	else file_data.push_back(a), file_data += '\n';
}

void Input(bool flag)
{
	cout << "[1]������� [2]�������" << endl;
	cout << "[3]�Ҽ����� [4]�Ҽ�����" << endl;
	cout << "[5]��ĸ������ [6]�ո񳤰�" << endl;
	cout << "����������ѡ�����" << endl << "<< ";
	Get(Mode, flag);
	if (Mode == 1 || Mode == 3)
	{
		cout << "�����������ٶȣ����룩" << endl << "<< ";
		Get(Speed, flag);
	}
	else if (Mode == 5)
	{
		cout << "��������ĸ��Ҳ���������֣���㣩" << endl << "<< ";
		Get(ch, flag);
	}
	else if (Mode == 6)
		ch = ' ';
	cout << "����ʱ����ʼ���������룩" << endl << "<< ";
	Get(Start, flag);
	cout << "������������ʱ�����ͣ�����룬-1Ϊ���ޣ�" << endl << "<< ";
	Get(Continue, flag);
	cout << "��ͣ��������ʱ��������������룩" << endl << "<< ";
	Get(Space, flag);
	if (Mode >= 5)
	{
		vkCode = LOBYTE(VkKeyScan(ch));
		keydown = get_Lparam(vkCode, false);
		keyup = get_Lparam(vkCode, true);
	}
}

bool sleep(int t)
{
	long now = clock();
	while (clock() - now < t)
	{
		Sleep(1);
		if (GetAsyncKeyState(VK_RCONTROL))
			return true;
	}
	return false;
}

void Do()
{
	if (sleep(Start))
		return;
	long tstart = clock();
	if (Mode == 1)
		while (true)
		{
			SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
			SendMessage(hwnd, WM_LBUTTONUP, 0, 0);
			if (sleep(Speed))
				return;
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				if (sleep(Space))
					return;
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
				return;
		}
	if (Mode == 2)
	{
		SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
		while (true)
		{
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				SendMessage(hwnd, WM_LBUTTONUP, 0, 0);
				if (sleep(Space))
					return;
				SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				SendMessage(hwnd, WM_LBUTTONUP, 0, 0);
				return;
			}
			Sleep(1);
		}
	}
	if (Mode == 3)
		while (true)
		{
			SendMessage(hwnd, WM_RBUTTONDOWN, 0, 0);
			SendMessage(hwnd, WM_RBUTTONUP, 0, 0);
			if (sleep(Speed))
				return;
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				if (sleep(Space))
					return;
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
				return;
		}
	if (Mode == 4)
	{
		SendMessage(hwnd, WM_RBUTTONDOWN, 0, 0);
		while (true)
		{
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				SendMessage(hwnd, WM_RBUTTONUP, 0, 0);
				if (sleep(Space))
					return;
				SendMessage(hwnd, WM_RBUTTONDOWN, 0, 0);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				SendMessage(hwnd, WM_RBUTTONUP, 0, 0);
				return;
			}
			Sleep(1);
		}
	}
	if (Mode >= 5)
	{
		PostMessage(hwnd, WM_KEYDOWN, vkCode, keydown);
		while (true)
		{
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				PostMessage(hwnd, WM_KEYUP, vkCode, keyup);
				if (sleep(Space))
					return;
				PostMessage(hwnd, WM_KEYDOWN, vkCode, keydown);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				PostMessage(hwnd, WM_KEYUP, vkCode, keyup);
				return;
			}
			Sleep(1);
		}
	}
}

void createFile()
{
	string filename;
	cout << "\r�����������ļ����ƣ�15�����ڣ�" << endl << "<< ";
	getchar();
	getline(cin, filename);
	filename += ".afk";
	char file[50] = "config\\";
	strcat_s(file, filename.c_str());
	system("md config");
	ofstream create(file);
	create << file_data;
	create.close();
}

int main()
{
	system("mode con cols=45 lines=25");
	system("title Minecraft-AFK By Cheny");
	bool flag = getFile();
	cout << "��ǰ��ָ�����ڰ�����Ctrl+��Alt���񴰿�" << endl;
	while (hwnd == NULL)
		getWindow();
	Input(flag);
	cout << endl << ">>>��������λ�ð�����Alt��ʼ����<<<" << endl;
	cout << ">>>����λ�ð�����Ctrl����<<<" << endl;
	if (!flag)
		cout << endl << ">>>��������F12�ɱ������õ�config<<<" << endl;
	cout << endl;
	while (true)
	{
		if (GetAsyncKeyState(VK_RMENU))
		{
			cout << "\r��ʼ����������Ctrl�ɽ�����";
			system("color 03");
			Do();
			cout << "\r��������������Alt���¿�ʼ��";
			system("color 07");
		}
		if (!flag && GetAsyncKeyState(VK_F12))
		{
			createFile();
			return 0;
		}
		Sleep(1);
	}
}