#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;

struct Node
{
	unsigned short repeatCount;
	unsigned char scanCode;
	bool extendedKey, prevKeyState, transitionState;
	operator unsigned int()
	{
		return repeatCount | (scanCode << 16) | (extendedKey << 24) | (prevKeyState << 30) | (transitionState << 31);
	}
};

int Mode, Start, Continue, Space, Speed;
char ch;
short vkCode;
HWND hwnd;
int keydown, keyup;

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
				cout << "����ɹ����������ƣ�" << endl;
				cout << title << endl;
			}
			else
				cout << "����ʧ�ܣ������ԣ�" << endl;
			cout << endl;
			return;
		}
	}
}

void Input()
{
	cout << "����������ѡ�����" << endl;
	cout << "1:������� 2:�������" << endl;
	cout << "3:�Ҽ����� 4:�Ҽ�����" << endl;
	cout << "5:��ĸ������ 6:�ո񳤰�" << endl;
	cin >> Mode;
	if (Mode == 1 || Mode == 3)
	{
		cout << "�����������ٶȣ���λ���룩��" << endl;
		cin >> Speed;
	}
	else if (Mode == 5)
	{
		cout << "��������ĸ��Сд��" << endl;
		cin >> ch;
	}
	else if (Mode == 6)
		ch = ' ';
	cout << "���������ʱ����ʼ��������λ���룩��" << endl;
	cin >> Start;
	cout << "�����������������ʱ�����ͣ����λ���룬-1Ϊ���ޣ���Ϊ0���ʾ����һ��������ͣ��" << endl;
	cin >> Continue;
	cout << "��������ͣ��������ʱ�������������λ���룩��" << endl;
	cin >> Space;
	if (Mode >= 5)
	{
		Node down = {}, up = {};
		vkCode = LOBYTE(VkKeyScan(ch));
		down.scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
		up.scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
		up.repeatCount = 1;
		up.prevKeyState = true;
		up.transitionState = true;
		keydown = down;
		keyup = up;
	}
}

void Do()
{
	Sleep(Start);
	long tstart = clock();
	if (Mode == 1)
		while (true)
		{
			SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
			SendMessage(hwnd, WM_LBUTTONUP, 0, 0);
			Sleep(Speed);
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				Sleep(Space);
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
				Sleep(Space);
				SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				SendMessage(hwnd, WM_LBUTTONUP, 0, 0);
				return;
			}
		}
	}
	if (Mode == 3)
		while (true)
		{
			SendMessage(hwnd, WM_RBUTTONDOWN, 0, 0);
			SendMessage(hwnd, WM_RBUTTONUP, 0, 0);
			Sleep(Speed);
			if (Continue != -1 && clock() - tstart >= Continue)
			{
				Sleep(Space);
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
				Sleep(Space);
				SendMessage(hwnd, WM_RBUTTONDOWN, 0, 0);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				SendMessage(hwnd, WM_RBUTTONUP, 0, 0);
				return;
			}
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
				Sleep(Space);
				PostMessage(hwnd, WM_KEYDOWN, vkCode, keydown);
				tstart = clock();
			}
			if (GetAsyncKeyState(VK_RCONTROL))
			{
				PostMessage(hwnd, WM_KEYUP, vkCode, keyup);
				return;
			}
		}
	}
}

int main()
{
	system("title Minecraft��̨�һ����� By Cheny");
	cout << "��ǰ��ָ�����ڰ�����Ctrl+��Alt���񴰿�" << endl;
	while (hwnd == NULL)
		getWindow();
	Input();
	cout << "��Ҫ��̨�һ����밴F3+Pͣ��ʧȥ�������ͣ���ٰ�Alt+tab�г�" << endl;
	cout << "�밴����Alt��ʼ������������Ctrl����" << endl;
	while (true)
	{
		if (GetAsyncKeyState(VK_RMENU))
		{
			cout << "��ʼ����" << endl;
			Do();
			cout << "��������������Alt���¿�ʼ��" << endl;
		}
	}
}