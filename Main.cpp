#include "ChatBot.h"
#include <Windows.h>
#include <exception>

int main()
{
	// подключение кодовых страниц для ввода-вывода кириллицей
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool goon = true;
	aiafpb1::ChatBot cb;
	aiafpb1::CB_command command;
	
	while (goon)
	{
		try
		{
			std::cout << std::endl << "Введите команду: ";
			std::cin >> command;
			std::cout << std::endl << "Вы ввели команду: " << command << std::endl;
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
			std::cerr << std::endl << "Обработано стандартное исключение:" << std::endl << e.what() << std::endl;
		}
		catch (...)
		{
			goon = false;
			std::cerr << std::endl << "Обработано неизвестное исключение" << std::endl;
		}
	}

	std::cout << std::endl << "Работа программы прекращена" << std::endl;
	std::cin.get();
	return 0;
}