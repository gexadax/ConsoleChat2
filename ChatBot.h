#pragma once
#include "Users.h"
#include "Messages.h"

namespace aiafpb1
{
	enum class CommandType
	{
		HELP = '?',	// ����� ������ ������
		CHAT = 'c',	// �������� ��� � �������������, �������� - ����� ��� ��� ������������ (��� ���������� - ����� ���)
		IN = 'i',	// ����� � �������, �������� - �����
		MES = 'm',	// �������� ��������� ������������, �������� - ����� ��� ��� ������������ (��� ���������� - � ����� ���)
		OUT = 'o',	// ����� �� �������
		QUIT = 'q',	// ����� �� ���������
		REG = 'r',	// ����������� � �������
		SHOW = 's', // �������� ������������� ���������, �������� - ����� ��� ��� ����������� (��� ���������� - ��� ����� ���������)
		USERS = 'u'	// ����� ������ ������������������ �������������
	};

	// ��������� ��� ������ ������������ ��� ������ � ������� ChatBot
	struct CB_command
	{
	private:
		CommandType type = CommandType::HELP;
		std::string param;
	public:
		friend std::istream& operator>> (std::istream&, CB_command&);
		friend std::ostream& operator<< (std::ostream&, const CB_command&);
		friend class ChatBot;
	};

	// �������� ����� ��� ������ � ������
	class ChatBot
	{
	private:
		Users m_users;			// ������ ������������������ �������������
		Messages m_messages;	// ������ ���������
		bool m_logged = false;	// true, ���� ������������ ����� � �������
		User m_loggedUser;		// ������������, ������� ����� � �������
		size_t m_userIndex;		// ������ �������� ������������ � ������� ������������������ �������������

		std::stringstream log_in(std::string);
		std::stringstream log_out();
		std::stringstream quit() const;
		std::stringstream regist();
		std::stringstream showChat(std::string);
		std::stringstream showFresh(std::string);
		std::stringstream showHelp() const;
		std::stringstream showUsers() const;
		std::stringstream writeMessage(std::string);
		std::stringstream makeMessage(std::string, std::string);
		bool is_yes(std::string);
		bool name_OK(User&);
		bool input_OK(std::string, std::string&);

	public:
		ChatBot();
		~ChatBot();
		std::stringstream ApplyCommand(bool&, const CB_command&);
	};
}