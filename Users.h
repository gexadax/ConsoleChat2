#pragma once
#include "TArray.h"
#include "TimeData.h"

namespace aiafpb1
{
	struct User
	{
	public:
		std::string log;
		std::string name;
		std::string pword;
		TimeData last_seen;	// ����� ���������� ��������� ������ ����

		void clear();
		std::string fullName() const;
		User& operator=(const User&);
		friend std::ostream& operator<< (std::ostream&, const User&);
	};

	class Users
	{
	private:
		// ������� ���������� ������������� ��� ������� ���������
		//TArray<User> m_users;

		// ������� ������� ������������� ��� ������� ���������
		TArray<User> m_users
		{
			{"fox", "����", "xof", TimeData()},
			{"pot", "����", "top", TimeData()},
			{"tin", "�����", "nit", TimeData()}
		};

	public:
		Users();
		~Users();

		size_t add(const User&);
		void fixTime(size_t);
		static bool selectByName(const User&, User&);
		static bool selectByLog(const User&, User&);
		bool nameFound(User&, size_t&);
		bool logFound(User&, size_t&);
		bool empty() const;
		std::stringstream showNames() const;
	};
}