#include "Messages.h"

namespace aiafpb1
{
	Message& Message::operator=(const Message& m)
	{
		if (&m != this)
		{
			text = m.text;
			from_name = m.from_name;
			to_name = m.to_name;
			time = m.time;
			fresh = m.fresh;
		}
		return *this;
	}

	// вывод параметров сообщения в поток, используется для вывода списка сообщений
	std::ostream& operator<<(std::ostream& out, const Message& m)
	{
		out << std::endl << "отправлено " << m.time << " пользователем [" << m.from_name << "]";
		if (m.to_name.empty()) { out << " для всех пользователей:"; }
		else
		{
			out << " для пользователя [" << m.to_name << "]:";
			if (!m.fresh) { out << std::endl << "[сообщение прочитано получателем]"; }
		}
		out << std::endl << m.text << std::endl;
		return out;
	}

	Messages::Messages() {}
	Messages::~Messages() {}

	// добавление сообщения в массив
	void Messages::add(const Message& m) { m_mess.add_last(m); }

	// предикат (условие) для отбора общих сообщений, передается по указателю в TArray.getSelection через функцию getCommon (см. ниже)
	bool Messages::selectCommon(const Message& m, Message& c)
	{
		return (m.to_name.empty());
	}

	// предикат (условие) для отбора парных сообщений, передается по указателю в TArray.getSelection через функцию getPaired (см. ниже)
	bool Messages::selectPaired(const Message& m, Message& c)
	{
		return ((m.to_name == c.to_name && m.from_name == c.from_name) || (m.to_name == c.from_name && m.from_name == c.to_name));
	}

	// предикат (условие) для отбора непрочитанных сообщений, передается по указателю в TArray.getSelection через функцию getFresh (см. ниже)
	bool Messages::selectFresh(const Message& m, Message& c)
	{
		bool result = false;
		if (c.from_name.empty())
		{
			if (m.to_name.empty()) { result = (m.time > c.time); }
			else { result = (m.fresh && m.to_name == c.to_name); }
		}
		else { result = (m.from_name == c.from_name && m.to_name == c.to_name && m.fresh); }
		return result;
	}

	std::vector<std::reference_wrapper<Message>> Messages::getCommon()
	{
		Message c;
		return m_mess.getSelection(selectCommon, c);
	}
	
	std::vector<std::reference_wrapper<Message>> Messages::getPaired(Message& c)
	{
		return m_mess.getSelection(selectPaired, c);
	}

	std::vector<std::reference_wrapper<Message>> Messages::getFresh(Message& c)
	{
		return m_mess.getSelection(selectFresh, c);
	}
}