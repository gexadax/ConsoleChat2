#pragma once
#include "TArray.h"
#include "TimeData.h"

namespace aiafpb1
{
	struct Message
	{
	public:
		std::string text;		// ����� ���������
		std::string from_name;	// "������" ��� �����������
		std::string to_name;	// "������" ��� ����������
		TimeData time;			// ����� �������� ���������
		bool fresh = true;		// true, ���� ��������� �� ��������� �����������

		Message& operator=(const Message&);
		friend std::ostream& operator<< (std::ostream&, const Message&);
	};

	class Messages
	{
	private:
		// ������� ���������� ��������� ��� ������� ���������
		//TArray<Message> m_mess;

		// ������� ������� ��������� ��� ������� ��������� - ������ ��� ��������� ������������� � Users!
		TArray<Message> m_mess
		{
			{"���� ������! ���� ����� ����", "����--fox", "", TimeData(), true},
			{"������ ����, � ����", "����--pot", "", TimeData(), true},
			{"���� ������ �� ������!", "�����--tin", "", TimeData(), true},
			{"��� ���� ��� � ���� ����?", "�����--tin", "����--fox", TimeData(), true},
			{"��, �� ��� ������ ��� ������������ ��", "����--fox", "�����--tin", TimeData(), true},
			{"� ��� �������� ���� �����?", "����--fox", "����--pot", TimeData(), true},
			{"��� � ���� ������ � ����������������", "����--pot", "����--fox", TimeData(), true},
			{"��� � ������� - ��� ����� �������", "����--pot", "�����--tin", TimeData(), true},
			{"��������, ������ � ������� ;)", "�����--tin", "����--pot", TimeData(), true}
		};

	public:
		Messages();
		~Messages();

		void add(const Message&);
		static bool selectCommon(const Message&, Message&);
		static bool selectPaired(const Message&, Message&);
		static bool selectFresh(const Message&, Message&);
		std::vector<std::reference_wrapper<Message>> getCommon();
		std::vector<std::reference_wrapper<Message>> getPaired(Message&);
		std::vector<std::reference_wrapper<Message>> getFresh(Message&);
	};
}