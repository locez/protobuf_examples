#include <iostream>

#include <google/protobuf/util/json_util.h>

#include "proto/JsonPerson.pb.h"

void print(const std::string &title, const std::string &option, const std::string &content)
{
    std::cout << title << "  (" << option << "):\n"
              << content << "\n\n";
}

int main(int argc, char **argv)
{
    json_person::Person person;
    person.set_name("locez");
    person.set_email("locez@locez.com");
    person.mutable_phone()->set_type(json_person::Person::PhoneType::Person_PhoneType_MOBILE);
    person.mutable_phone()->set_number("1000000");
    std::string result;
    // 使用默认选项序列化成 json， 会忽略默认的值，如果带有 json_name 则会按照 json_name 定义的名字序列化该字段
    google::protobuf::util::MessageToJsonString(person, &result);
    print("serailize1", "default option", result);

    google::protobuf::util::JsonOptions serial_options;
    // 在 field 中指定了 json_name 的选项，但是序列化时，保留原有的字段名字
    serial_options.preserve_proto_field_names = true;
    result = "";
    google::protobuf::util::MessageToJsonString(person, &result, serial_options);
    print("serialize2", "perserve proto field names = true", result);

    serial_options = google::protobuf::util::JsonOptions();
    // add whitespace 选项会使得序列化后的 json 更加美观可读
    serial_options.add_whitespace = true;
    result = "";
    google::protobuf::util::MessageToJsonString(person, &result, serial_options);
    print("serialize3", "add whitespace = true", result);

    serial_options = google::protobuf::util::JsonOptions();
    // 默认值的字段也序列化
    serial_options.always_print_primitive_fields = true;
    result = "";
    google::protobuf::util::MessageToJsonString(person, &result, serial_options);
    print("serialize4", "always_print_primitive_fields = true", result);

    serial_options = google::protobuf::util::JsonOptions();
    serial_options.always_print_primitive_fields = true;
    // 枚举序列化成对应的 int 型数字，而不是对应的字面量字符串
    serial_options.always_print_enums_as_ints = true;
    result = "";
    google::protobuf::util::MessageToJsonString(person, &result, serial_options);
    print("serialize5", "always_print_enums_as_ints = true", result);

    // 这个 json 字符串多了一个 unknown_field 的字段，该字段没有在 proto 文件里面定义
    std::string json_string = R"({"name":"locez","id":0,"email":"locez@locez.com","phone":{"phone_number":"1000000","phone_type":0,"unknown_field":0}})";
    json_person::Person p;
    auto status = google::protobuf::util::JsonStringToMessage(json_string, &p);
    if (status.ok())
    {
        print("deserialize1", "default option", p.DebugString());
    }
    else
    {
        print("deserialize1 failed", "default option", status.error_message().ToString());
    }

    google::protobuf::util::JsonParseOptions deserialize_options;
    // 忽略不存在的字段，只解析存在的可以解析的字段
    deserialize_options.ignore_unknown_fields = true;
    status = google::protobuf::util::JsonStringToMessage(json_string, &p, deserialize_options);
    if (status.ok())
    {
        print("deserialize2", "ignore_unknown_fields = true", p.DebugString());
    }
    else
    {
        print("deserialize1 failed", "ignore_unknown_fields = true", status.error_message().ToString());
    }
    return 0;
}