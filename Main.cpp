#include "ChatBot.h"
#include <Windows.h>
#include <exception>

int main()
{
	// ����������� ������� ������� ��� �����-������ ����������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool goon = true;
	aiafpb1::ChatBot cb;
	aiafpb1::CB_command command;
	
	while (goon)
	{
		try
		{
			std::cout << std::endl << "������� �������: ";
			std::cin >> command;
			std::cout << std::endl << "�� ����� �������: " << command << std::endl;
			std::cout << cb.ApplyCommand(goon, command).str();
		}
		catch (const aiafpb1::TArrayException& e)
		{
			std::cerr << std::endl << e << std::endl;
			goon = false;
		}
		catch (const std::exception& e)
		{
			goon = false;
			std::cerr << std::endl << "���������� ����������� ����������:" << std::endl << e.what() << std::endl;
		}
		catch (...)
		{
			goon = false;
			std::cerr << std::endl << "���������� ����������� ����������" << std::endl;
		}
	}

	std::cout << std::endl << "������ ��������� ����������" << std::endl;
	std::cin.get();
	return 0;
}