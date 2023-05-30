#include "TArrayException.h"

namespace aiafpb1
{
	const std::map<etype, std::string> TArrayException::m_message
	{
		{etype::empty_array, "������ �������� ������"},
		{etype::invalid_index, "�������� �������� �������"},
		{etype::invalid_size, "������ ������� �� ����� ���� ����� ������������� ������"},
		{etype::wrong_type, "�������������� ���� ��������� �������"}
	};

	const std::string TArrayException::getInfo() const
	{
		std::stringstream ss;
		ss << "��� ���������� ������� \"" << m_source << "\"" << std::endl << "��������� ������ : " << TArrayException::m_message.at(m_error) << std::endl;
		if (!m_comment.empty()) ss << "����������� � ������: " << m_comment << std::endl;
		return ss.str();
	}

	TArrayException::TArrayException(etype error, std::string source, std::string comment) : m_error(error), m_source(source), m_comment(comment) {}

	const char* TArrayException::what() const noexcept
	{
		return (TArrayException::m_message.at(m_error)).c_str();
	}

	std::ostream& operator<<(std::ostream& out, const TArrayException& e)
	{
		out << e.getInfo();
		return out;
	}
}
