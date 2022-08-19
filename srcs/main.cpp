#include "std.hpp"
#include "ChatSession.hpp"
#include "ChatServer.hpp"

int main(int argc, char* argv[])
{
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;

    plog::init(plog::verbose, &consoleAppender);


    cxxopts::Options options("RomiChatServer00", "C++ Windows Chat Server 00");
    options.add_options()
        ("h,host", "연결 대기 인터페이스 주소", cxxopts::value<std::string>()->default_value("0.0.0.0"))
        ("p,port", "연결 대기 포트", cxxopts::value<int>()->default_value("10012"))
        ("help", "도움말 출력")
    ;
    const auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        LOGI << std::endl << std::endl << options.help();
        return 0;
    }

    LOGV << "호스트 : " << result["host"].as<std::string>();
    LOGV << "포트번호: " << result["port"].as<int>();

    return 0;
}
