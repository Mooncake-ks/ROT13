#include <iostream>
#include <string>
#include <algorithm>

//Алфавит
enum TYPE_ALFH
{
    EN,
    RU,
};

class ROT13
{
public:

    //Шифрование
    std::string encrypt(const std::string& mes, const TYPE_ALFH& type_alfh = EN);
    //Дешифрование
    std::string decrypt(const std::string& mes, const TYPE_ALFH& type_alfh = EN);

    
private:
    const int m_k = 13;
    std::string m_alfh;

    void set_alfh(const TYPE_ALFH& type_alfh);
    //Проверка на регистр
    bool check_register(const char& ch, const TYPE_ALFH& type_alft);

};

int main()
{
    setlocale(LC_ALL, "Ru");

    ROT13 m_test;
    std::cout << "Testing RU ROT13:" << std::endl;
    std::cout << "Привет, мир! ->\t" << m_test.encrypt("Привет, мир!", TYPE_ALFH::RU) << std::endl;
    std::cout << "Ьэхося, щхэ! ->\t" << m_test.decrypt("Ьэхося, щхэ!", TYPE_ALFH::RU) << std::endl;

    std::cout << "\nTesting EN ROT13:" << std::endl;
    std::cout << "Hello, world! -> " << m_test.encrypt("Hello, world!") << std::endl;
    std::cout << "Uryyb, jbeyq! -> " << m_test.decrypt("Uryyb, jbeyq!", TYPE_ALFH::RU) << std::endl;

    /*
    //В верхний регистр 
    std::transform(n.cbegin(), n.cend(), n.begin(), [](unsigned char c) { return std::toupper(c); });
    std::cout << n << std::endl;
    // В нижний регистр
    std::transform(n.cbegin(), n.cend(), n.begin(), [](unsigned char c) { return std::tolower(c); });
    std::cout << n << std::endl;/*

    /*std::cout << encrypt("HELLO",TYPE_ALFH::EN) << std::endl;
    std::cout << decrypt("URYYB", TYPE_ALFH::EN) << std::endl;

    std::cout << encrypt("ПРИВЕТ",TYPE_ALFH::RU) << std::endl;
    std::cout << decrypt("ЬЭХОСЯ", TYPE_ALFH::RU) << std::endl;*/


    return 0;
}

std::string ROT13::encrypt(const std::string& mes, const TYPE_ALFH& type_alfh)
{
    set_alfh(type_alfh);

    std::string result;

    for (auto el : mes)
    {
        int position = static_cast<int>(m_alfh.find(el));

        if (position == -1)
        {
            if (check_register(el,type_alfh))
            {
                position = static_cast<int>(m_alfh.find(el));
                position += m_k;
                result += m_alfh[position];
            }
            else
            {
                result += el;

            }
        }
        else
        {
            position += m_k;
            result += m_alfh[position];
        }


    }
    return result;
}

std::string ROT13::decrypt(const std::string& mes, const TYPE_ALFH& type_alfh)
{
    set_alfh(type_alfh);
    int pos_alf=m_alfh.size()/2;

    

    std::string result;

    for (auto el : mes)
    {
        int position = static_cast<int>(m_alfh.find(el, pos_alf));
        if (position == -1)
        {
            if (check_register(el,type_alfh))
            {
                position = static_cast<int>(m_alfh.find(el, pos_alf));
                position -= m_k;
                result += m_alfh[position];
            }
            else
            {
                result += el;
            }
        }
        else
        {
            position -= m_k;
            result += m_alfh[position];
        }
    }

    return result;
}

void ROT13::set_alfh(const TYPE_ALFH& type_alfh)
{
    if (type_alfh == RU)
    {
        m_alfh = { "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" };
    }
    else if (type_alfh == EN)
    {
        m_alfh = { "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    }
}

bool ROT13::check_register(const char& ch, const TYPE_ALFH& type_alfh)
{
    bool is_lower, is_upper;
    if (type_alfh == RU)
    {
        is_upper = (ch >= 'А' and ch <= 'Я') || ch == 'Ё';
        is_lower = (ch >= 'а' and ch <= 'я') || ch == 'ё';
    }
    else
    {
        is_upper = isupper(ch);
        is_lower = islower(ch);
    }

    if (is_upper)
    {
        std::transform(m_alfh.cbegin(), m_alfh.cend(), m_alfh.begin(), [](unsigned char c) { return std::toupper(c); });
        return true;
    }
    else if (is_lower)
    {
        std::transform(m_alfh.cbegin(), m_alfh.cend(), m_alfh.begin(), [](unsigned char c) { return std::tolower(c); });
        return true;
    }

    return false;
}
