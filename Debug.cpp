#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;

int Mode, Start, Continue, Space, Speed;
char ch;
short vkCode;
HWND hwnd;
int keydown, keyup;

int get_Lparam(int vk, bool flag)
{
	int scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
	return flag | (scanCode << 16) | (flag << 30) | (flag << 31);
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

void Input()
{
	cout << "[1]������� [2]�������" << endl;
	cout << "[3]�Ҽ����� [4]�Ҽ�����" << endl;
	cout << "[5]��ĸ������ [6]�ո񳤰�" << endl;
	cout << "����������ѡ�����" << endl << "<< ";
	cin >> Mode;
	if (Mode == 1 || Mode == 3)
	{
		cout << "�����������ٶȣ����룩" << endl << "<< ";
		cin >> Speed;
	}
	else if (Mode == 5)
	{
		cout << "��������ĸ" << endl << "<< ";
		cin >> ch;
	}
	else if (Mode == 6)
		ch = ' ';
	cout << "����ʱ����ʼ���������룩" << endl << "<< ";
	cin >> Start;
	cout << "������������ʱ�����ͣ�����룬-1Ϊ���ޣ�" << endl << "<< ";
	cin >> Continue;
	cout << "��ͣ��������ʱ��������������룩" << endl << "<< ";
	cin >> Space;
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

int main()
{
	system("title Minecraft-AFK By Cheny");
	system("mode con cols=45 lines=25");
	cout << "��ǰ��ָ�����ڰ�����Ctrl+��Alt���񴰿�" << endl;
	while (hwnd == NULL)
		getWindow();
	Input();
	cout << endl << ">>>��������λ�ð�����Alt��ʼ����<<<" << endl;
	cout << ">>>����λ�ð�����Ctrl����<<<" << endl << endl;
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
		Sleep(1);
	}
} 