#include <iostream>

#include "proto/AddressBook.pb.h"

int main(int argc, char **argv)
{
    // 声明一个地址簿对象
    address_book::AddressBook address_book;
    // repeated 标识符的字段为 0 - n 个，接口是 add_xxx(), 获取一个用于读写的指针
    auto people = address_book.add_people();
    // 使用　set_xxx() 方法填写属性
    people->set_email("locez@locez.com");
    people->set_id(0);
    people->set_name("locez");
    auto phone_number = people->add_phone();
    phone_number->set_number("123456789");
    // enum 枚举通过命名空间访问
    phone_number->set_type(address_book::Person::PhoneType::Person_PhoneType_HOME);

    std::cout << "readable: \n"
              << address_book.DebugString() << std::endl;
    auto serialized_data = address_book.SerializeAsString();

    std::cout << "binary: ===\n"
              << serialized_data << "\n===\n"
              << " length: " << serialized_data.length() << std::endl << std::endl;

    address_book::AddressBook address_book_new;
    // 反序列化
    address_book_new.ParseFromString(serialized_data);
    std::cout << "readable: \n" << address_book_new.DebugString() << std::endl;

    // repeadted 标识符的字段为 0 - n 个，访问需要遍历
    for (int i = 0; i < address_book_new.people_size(); i++)
    {
        auto people_new = address_book_new.people(i);
        std::cout << "name: " << people_new.name();
    }

    return 0;
}