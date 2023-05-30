#include "Users.h"

namespace aiafpb1
{
	// приведение параметров к начальным "нулевым" значениям
	void User::clear()
	{
		this->log.clear();
		this->pword.clear();
		this->name.clear();
		this->last_seen.clear();
	}

	// "полное" имя пользователя в формате (имя--логин) для возможности идентификации, т.к. имена пользователей могут совпадать
	std::string User::fullName() const { return (name + "--" + log); }

	User& User::operator=(const User& u)
	{
		if (&u != this)
		{
			log = u.log;
			pword = u.pword;
			name = u.name;
			last_seen = u.last_seen;
		}
		return *this;
	}

	// вывод в поток данных пользователя, используется для проверки при регистрации пользователя
	std::ostream& operator<<(std::ostream& out, const User& u)
	{
		out << " логин: " << u.log << std::endl;
		out << "пароль: " << u.pword << std::endl;
		out << "   имя: " << u.name << std::endl;
		return out;
	}

	Users::Users() {}
	Users::~Users() {}

	// добавление пользователя в массив
	size_t Users::add(const User& u)
	{
		m_users.add_last(u);
		return m_users.size() - 1;
	}

	// фиксация времени просмотра пользователем общего чата
	void Users::fixTime(size_t index) { m_users[index].last_seen.renew(); }

	// предикат для поиска пользователя по имени (через User& c), передается по указателю в TArray.tryGetOne через функцию nameFound (см. ниже)
	bool Users::selectByName(const User& u, User& c) { return (u.log == c.log || u.name == c.name); }

	// предикат для поиска пользователя по логину (через User& c), передается по указателю в TArray.tryGetOne через функцию logFound (см. ниже)
	bool Users::selectByLog(const User& u, User& c) { return (u.log == c.log); }

	bool Users::nameFound(User& c, size_t& i) { return m_users.tryGetOne(selectByName, c, i); }

	bool Users::logFound(User& c, size_t& i) { return m_users.tryGetOne(selectByLog, c, i); }

	// проверка наличия зарегистрированных пользователей
	bool Users::empty() const { return (m_users.size() == 0); }

	// вывод списка "полных" имен пользователей
	std::stringstream Users::showNames() const
	{
		std::stringstream info;
		info << std::endl << "Имена пользователей:" << std::endl;
		for (size_t i = 0; i < m_users.size(); i++) { info << m_users[i].fullName() << std::endl; }
		return info;
	}
}