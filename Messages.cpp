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

	// ����� ���������� ��������� � �����, ������������ ��� ������ ������ ���������
	std::ostream& operator<<(std::ostream& out, const Message& m)
	{
		out << std::endl << "���������� " << m.time << " ������������� [" << m.from_name << "]";
		if (m.to_name.empty()) { out << " ��� ���� �������������:"; }
		else
		{
			out << " ��� ������������ [" << m.to_name << "]:";
			if (!m.fresh) { out << std::endl << "[��������� ��������� �����������]"; }
		}
		out << std::endl << m.text << std::endl;
		return out;
	}

	Messages::Messages() {}
	Messages::~Messages() {}

	// ���������� ��������� � ������
	void Messages::add(const Message& m) { m_mess.add_last(m); }

	// �������� (�������) ��� ������ ����� ���������, ���������� �� ��������� � TArray.getSelection ����� ������� getCommon (��. ����)
	bool Messages::selectCommon(const Message& m, Message& c)
	{
		return (m.to_name.empty());
	}

	// �������� (�������) ��� ������ ������ ���������, ���������� �� ��������� � TArray.getSelection ����� ������� getPaired (��. ����)
	bool Messages::selectPaired(const Message& m, Message& c)
	{
		return ((m.to_name == c.to_name && m.from_name == c.from_name) || (m.to_name == c.from_name && m.from_name == c.to_name));
	}

	// �������� (�������) ��� ������ ������������� ���������, ���������� �� ��������� � TArray.getSelection ����� ������� getFresh (��. ����)
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