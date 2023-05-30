#include "ChatBot.h"

namespace aiafpb1
{
	ChatBot::ChatBot() { std::cout << showHelp().str() << std::endl; }	// ����� ������ ������ ��� ������� ���������
	ChatBot::~ChatBot() {}

	// ���������� ��������� ������������� ������� (�������� goon = false ������������ ��� ������ �� ����� � main)
	std::stringstream ChatBot::ApplyCommand(bool& goon, const CB_command& command)
	{
		std::stringstream result;
		goon = true;
		switch (command.type)
		{
		case CommandType::HELP:
			result = showHelp();
			break;
		case CommandType::CHAT:
			result = showChat(command.param);
			break;
		case CommandType::IN:
			result = log_in(command.param);
			break;
		case CommandType::MES:
			result = writeMessage(command.param);
			break;
		case CommandType::OUT:
			result = log_out();
			break;
		case CommandType::QUIT:
			result = quit();
			goon = false;
			break;
		case CommandType::REG:
			result = regist();
			break;
		case CommandType::SHOW:
			result = showFresh(command.param);
			break;
		case CommandType::USERS:
			result = showUsers();
			break;
		default:
			result << std::endl << "������ ������� �����������!" << std::endl;
			break;
		}
		return result;
	}

	// ����������� ������������ � �������
	std::stringstream ChatBot::regist()
	{
		m_loggedUser.clear();
		m_logged = false;
		std::string s;
		std::stringstream info;
		bool ok = false;
		bool goon = true;
		std::cout << std::endl << "��� ����������� ������� �� ������� ���� �����, ������ � ���";
		// ���� ��� ����� � �������� ������
		do
		{
			ok = input_OK("�����", m_loggedUser.log);
			ok = ok && (!m_users.logFound(m_loggedUser, m_userIndex));	// �������� �� ���������� ���������� ������ � ������� ������� ������������
			if (ok) { goon = false; }
			else
			{
				m_loggedUser.clear();
				std::cout << std::endl << "��������� ���� ����� �� ����� ���� �����������." << std::endl;
				std::cout << "�������� �� �� ���������� ����������� � ������ �������?" << std::endl;
				goon = input_OK("�� ��� Y (yes), ���� ��������", s);
				goon = goon && is_yes(s);
			}
		} while (goon);
		ok = ok && input_OK("������", m_loggedUser.pword);
		ok = ok && input_OK("���", m_loggedUser.name);
		if (ok)
		{
			std::cout << std::endl << "�� ����� ��������� ������:" << std::endl << m_loggedUser << std::endl;
			std::cout << "������������� �� �� ����������� � ������� � ����� �������?" << std::endl;
			ok = input_OK("�� ��� Y (yes), ���� �������������", s);
			ok = ok && is_yes(s);
			if (ok)
			{
				m_logged = true;
				m_userIndex = m_users.add(m_loggedUser);
				info << std::endl << m_loggedUser.name << ", �� ������� ���������������� � �������." << std::endl;
				info << "�������� ��� ��������� ���� ��������������� ������." << std::endl;
				info << "������ �� ������ ������ � ������ ��������� ��� ����� �� �������" << std::endl;
			}
			else
			{
				m_loggedUser.clear();
				info << std::endl << "����������� ��������, ������� ������� r ��� ��������� �����������" << std::endl;
			}
		}
		else
		{
			m_loggedUser.clear();
			info << std::endl << "����������� �� �������: �� ��� ������ ���� �������" << std::endl;
		}
		return info;
	}

	// ���� ������������ � �������
	std::stringstream ChatBot::log_in(std::string log)
	{
		m_loggedUser.clear();
		std::string s;
		std::stringstream info;
		bool ok = true;
		if(log.empty()) { ok = input_OK("�����", m_loggedUser.log); }
		else { m_loggedUser.log = log; }
		ok = ok && m_users.logFound(m_loggedUser, m_userIndex);
		ok = ok && input_OK("������", s);
		ok = ok && (s == m_loggedUser.pword);
		if (ok)
		{
			m_logged = true;
			info << std::endl << m_loggedUser.name << ", �� ����� � ������� � ������ ������ � ������������� ���������" << std::endl;
		}
		else
		{
			m_logged = false;
			m_loggedUser.clear();
			info << std::endl << "���� � ������� �� ������: ������������ ������� ������" << std::endl;
		}
		return info;
	}

	// ����� ������������ �� �������
	std::stringstream ChatBot::log_out()
	{
		std::stringstream info;
		if (m_logged)
		{
			info << std::endl << m_loggedUser.name << ", �� ����� �� �������" << std::endl;
			m_logged = false;
			m_loggedUser.clear();
		}
		else { info << std::endl << "����� �� ������� �������� ������ ����� ����� � ���" << std::endl; }
		return info;
	}

	// ����� ������ ������
	std::stringstream ChatBot::showHelp() const
	{
		std::stringstream help;
		help << std::endl << " ������ ������ (�������� ������ ������� � ����� ������ �������� ��� �������������):" << std::endl;
		help << " q - ����������� ������ � ����������" << std::endl;
		help << " r - ����������� ������ ������������" << std::endl;
		help << " i - ���� ������������ � ������� ����, �������� - �����" << std::endl;
		help << " o - ����� �� ������� ����" << std::endl;
		help << " c - ����� ���� � ������ �������������, �������� - ����� ��� ��� �������" << std::endl;
		help << "     ������������ (��� ���������� ��������� - ����� ������ ����), �������� � �������" << std::endl;
		help << "     ����� �������� ���� ��������� ������� ������������ (��� ����, ���� ����� ���)," << std::endl;
		help << "     ����� ���� ���������� ������� � ����� ����� ������" << std::endl;
		help << " m - �������� ��������� ������������, �������� - ����� ��� ��� ����������" << std::endl;
		help << "     (��� ���������� ��������� ��������� ���������� ����)" << std::endl;
		help << " s - ����� ������������� ���������, �������� - ����� ��� ��� �����������" << std::endl;
		help << "     (��� ���������� ��������� ��������� ��� ����� ���������)" << std::endl;
		help << " u - ����� ������ �������������" << std::endl;
		help << " ? - ����� ������� ������ ������" << std::endl;
		return help;
	}

	// ����� ������������������ �������������
	std::stringstream ChatBot::showUsers() const
	{
		std::stringstream info;
		if (m_users.empty()) { info << "���� ��� ������������������ �������������" << std::endl; }
		else { info << m_users.showNames().str(); }
		return info;
	}

	// ����� �� ���������
	std::stringstream ChatBot::quit() const
	{
		std::stringstream info;
		info << std::endl << "�������� ������ �� ����������� ������ ���������" << std::endl;
		return info;
	}

	// ����� ��������� ���� � �������� ��������� � ���� ���
	std::stringstream ChatBot::showChat(std::string from_name)
	{
		std::stringstream info;
		if (m_logged)
		{
			std::string to_name;
			bool name_ok = from_name.empty();
			Message comparer;	// �������� ��� ������ ��������� �� ������ ��������� � ��������� ����������
			if (name_ok)
			{
				// ������� � ����� ���������, ������������ ���� (����� ���)
				std::vector<std::reference_wrapper<Message>> selection(m_messages.getCommon());
				for (Message& m : selection) { info << m << std::endl; }
				m_loggedUser.last_seen.renew();	// �������� ������� ��������� ��������� ������ ����
				m_users.fixTime(m_userIndex);
			}
			else
			{
				User sender{ from_name, from_name };
				// ����� ������������ �� ���������� � ��� ������� ��� ������ �, ���� �� ������, �������� ��� ������ � sender (�����������)
				name_ok = name_OK(sender);
				if (name_ok)
				{
					comparer.to_name = m_loggedUser.fullName();
					to_name = sender.fullName();
					comparer.from_name = to_name;
					// ������� � ����� ��������� ���� ����� ������� (loggedUser) � ������ �������������
					std::vector<std::reference_wrapper<Message>> selection(m_messages.getPaired(comparer));
					for (Message& m : selection)
					{
						info << m << std::endl;
						if (m.to_name == comparer.to_name) { m.fresh = false; }	// ������� ��������� ��� ������������
					}
				}
			}
			if (name_ok)
			{
				std::cout << info.str();
				info.str(std::string());	// ������� info
				info << makeMessage(m_loggedUser.fullName(), to_name).str();
			}
			else { info << std::endl << "��������� ���� ������������ �� ������ (������� u - ����� ������)" << std::endl; }
		}
		else { info << std::endl << "��� ������ � ������ ���������� ����� � ������� (������� i)" << std::endl; }
		return info;
	}

	// ����� ������������� ���������
	std::stringstream ChatBot::showFresh(std::string from_name)
	{
		std::stringstream info;
		if (m_logged)
		{
			bool name_ok = from_name.empty();
			bool no_fresh;
			Message comparer;	// �������� ��� ������ ��������� �� ������ ��������� � ��������� ����������
			comparer.to_name = m_loggedUser.fullName();
			comparer.time = m_loggedUser.last_seen;
			if (name_ok)
			{
				m_loggedUser.last_seen.renew();	// �������� ������� ��������� ��������� ������ ����
				m_users.fixTime(m_userIndex);
				comparer.from_name = from_name;
				std::stringstream m_c;	// �������� ��� ������ ������������� ���������, ������������ ����
				std::stringstream m_p;	// �������� ��� ������ ������������� ���������, ������������ �������� ������������
				// ������� ���������, ������������� ������� �������������
				std::vector<std::reference_wrapper<Message>> selection(m_messages.getFresh(comparer));
				no_fresh = (selection.size() == 0);
				if (!no_fresh)
				{
					for (Message& m : selection)
					{
						if (m.to_name.empty()) { m_c << m << std::endl; }
						else
						{
							m_p << m << std::endl;
							m.fresh = false;	// ������� ��������� ��� ������������
						}
					}
					if (!m_c.str().empty()) { info << std::endl << "����� ���������, ������������ ����:" << std::endl << m_c.str(); }
					if (!m_p.str().empty()) { info << std::endl << "����� ���������, ������������ ���:" << std::endl << m_p.str(); }
				}
			}
			else
			{
				User sender{ from_name, from_name };
				// ����� ������������ �� ���������� � ��� ������� ��� ������ �, ���� �� ������, �������� ��� ������ � sender (�����������)
				name_ok = name_OK(sender);
				if (name_ok)
				{
					comparer.to_name = m_loggedUser.fullName();
					comparer.from_name = sender.fullName();
					// ������� ������������� ��������� �� ����������� ������������
					std::vector<std::reference_wrapper<Message>> selection(m_messages.getFresh(comparer));
					no_fresh = (selection.size() == 0);
					if (!no_fresh)
					{
						for (Message& m : selection)
						{
							info << m << std::endl;
							m.fresh = false;
						}
					}
				}
			}
			if (name_ok) { if (no_fresh) { info << std::endl << "������������� ���� ��������� ���" << std::endl; } }
			else { info << std::endl << "��������� ���� ����������� �� ������ (������� u - ����� ������)" << std::endl; }
		}
		else { info << std::endl << "��� ������ � ������ ���������� ����� � ������� (������� i)" << std::endl; }
		return info;
	}

	// ���������� � �������� ���������
	std::stringstream ChatBot::writeMessage(std::string name)
	{
		std::stringstream info;
		if (m_logged)
		{
			std::string to_name = name;
			bool name_ok = name.empty();
			if (!name_ok)
			{
				User recipient{ name, name };
				// ����� ������������ �� ���������� � ��� ������� ��� ������ �, ���� �� ������, �������� ��� ������ � recipient (����������)
				name_ok = name_OK(recipient);
				to_name = recipient.fullName();
			}
			if(name_ok) { info << makeMessage(m_loggedUser.fullName(), to_name).str(); }
			else { info << std::endl << "��������� ���� ���������� �� ������ (������� u - ����� ������)" << std::endl; }
		}
		else { info << std::endl << "����� �������� ��������� ���������� ����� � ������� (������� i)" << std::endl; }
		return info;
	}

	// ���� � �������� ���������
	std::stringstream ChatBot::makeMessage(std::string from_name, std::string to_name)
	{
		std::stringstream info;
		std::string text;
		std::string name{ to_name.empty() ? "����" : "������������ [" + to_name + "]" };
		std::cout << std::endl << "������� ����� ��������� ��� " << name << ":" << std::endl;
		std::getline(std::cin, text);
		if (!text.empty())
		{
			TimeData time;	// �������� ������� �������� ���������
			Message m{ text, from_name, to_name, time, true };
			m_messages.add(m);
			info << std::endl << std::endl << "�� ��������� ���������:" << std::endl << m << std::endl;
		}
		else { info << std::endl << "��������� �� ������������" << std::endl; }
		return info;
	}

	// ����� ������������ �� ���������� � ��� ������� ��� ������ �, ���� �� ������, �������� ��� ������ � u
	bool ChatBot::name_OK(User& u)
	{
		size_t i;
		return m_users.nameFound(u, i);
	}

	// ��������� ����� ������������ � �������� ���������� � param
	bool ChatBot::input_OK(std::string param_name, std::string& param)
	{
		bool result = false;
		std::string input;
		std::string word;
		std::cout << std::endl << "������� " << param_name << ": ";
		std::getline(std::cin, input);
		input += " ";
		for (const char c : input)
		{
			if (c == ' ') { if (!word.empty()) break; }
			else { word += c; }
		}
		if (!word.empty())
		{
			param = word;
			result = true;
		}
		return result;
	}

	inline bool ChatBot::is_yes(std::string s)
	{
		return (s == "y" || s == "Y" || s == "yes" || s == "Yes" || s == "YES" || s == "��" || s == "��" || s == "��");
	}

	// ��������� ����� ������������ � ������������ �� ���� ������� � ������������� �������
	std::istream& operator>>(std::istream& in, CB_command& command)
	{
		std::string input;
		std::string p;
		std::getline(in, input);
		input += " ";
		command.type = CommandType::HELP;
		command.param.clear();
		bool gettype = true;
		for (const char c : input)
		{
			if (gettype)
			{
				if (c == '?') break;
				if (c == 'C' || c == 'c')
				{
					command.type = CommandType::CHAT;
					gettype = false;
				}
				if (c == 'I' || c == 'i')
				{
					command.type = CommandType::IN;
					gettype = false;
				}
				if (c == 'M' || c == 'm')
				{
					command.type = CommandType::MES;
					gettype = false;
				}
				if (c == 'O' || c == 'o')
				{
					command.type = CommandType::OUT;
					break;
				}
				if (c == 'Q' || c == 'q')
				{
					command.type = CommandType::QUIT;
					break;
				}
				if (c == 'R' || c == 'r')
				{
					command.type = CommandType::REG;
					break;
				}
				if (c == 'S' || c == 's')
				{
					command.type = CommandType::SHOW;
					gettype = false;
				}
				if (c == 'U' || c == 'u')
				{
					command.type = CommandType::USERS;
					break;
				}
			}
			else
			{
				if (c == ' ') { if (!p.empty()) break; }
				else { p += c; }
			}
		}
		if (!p.empty()) { command.param = p; }
		in.clear();
		return in;
	}

	// ����� ������� � ������������� �������
	std::ostream& operator<<(std::ostream& out, const CB_command& command)
	{
		out << static_cast<char>(command.type);
		if (!command.param.empty()) { out << " " << command.param; }
		return out;
	}
}