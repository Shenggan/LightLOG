#ifndef _LIGHT_LOG_H
#define _LIGHT_LOG_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <memory>
#include <mutex>

namespace llog {

enum LOG_LEVEL {
    LOG_LEVEL_INFO,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING
};

#define COLOR_ERR 31 //31
#define COLOR_MSG 37 //37
#define COLOR_WRN 33 //33
#define COLOR_FILE 35 //35
#define COLOR_LINE 32 //32
#define COLOR_FUNC 36 //36
#define DELIMITER " "

class Message {
private:
    std::string msg;
    std::string colorStr(int color, int bold, const std::string & delimiter, const std::string & t) {
        std::stringstream ss;
        ss << "\033[" << bold << ";" << color << "m";
        ss << t;
        ss << "\033[0m";
        ss << delimiter;
		return ss.str();
    }
    
    std::string logHeader(int level, std::string file, std::string function, int linenumber) {
        std::stringstream ss;
        std::stringstream st;
        int color = 39;
        if (level==2) { color = COLOR_ERR; st << "[ERRO]"; }
		if (level==0) { color = COLOR_MSG; st << "[INFO]"; }
		if (level==1) { color = COLOR_WRN; st << "[WARN]"; }

        ss << colorStr(color,1,DELIMITER,st.str());

        time_t rawtime;
		struct tm * timeinfo;
		char timeBuffer[30];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timeBuffer, 30, "%Y/%m/%d-%H:%M:%S", timeinfo); 
		ss << colorStr(color, 0, DELIMITER, timeBuffer);

        int pPos = 0;
		for (int i = file.length()-1; i > 0; i--)
			if (file.substr(i,1)==std::string("/"))
			{ pPos = i+1; break; }
		file = file.substr(pPos,file.length()-pPos);
		ss << colorStr(COLOR_FILE, 0, ":", file); //35
		ss << colorStr(COLOR_LINE, 1, ":", std::to_string(linenumber)); //32
		ss << colorStr(COLOR_FUNC, 0, DELIMITER, function); //36

        return ss.str();
    }
public:
    Message(const int level = 0, std::string file = nullptr, std::string function = nullptr, const int linenumber = 0) {
        msg += logHeader(level, file, function, linenumber);
    }
    template <typename T> Message& operator<<(const T & t) {
        std::stringstream ss;
        ss << t;
        msg += ss.str();
        return *this;
    }
    std::string get_string() const {
        return msg;
    }
};

// Singleton Class
class Logger {
private:
    static std::unique_ptr<Logger>          m_instance_;
    LOG_LEVEL                               m_level_;
    static std::mutex                       mtx_;
    Logger(){};
public:
    static Logger* get_instance() {
        if (m_instance_ == nullptr) {
            mtx_.lock();
            if (m_instance_ == nullptr) {
                m_instance_.reset(new Logger);
            }
            mtx_.unlock();
        }
        return m_instance_.get();
    }
    
    void set_level(int level) {
        m_level_ = LOG_LEVEL(level);
    }
    int get_level() const {
        return m_level_;
    }

    void operator+=(const Message& m)
    {
        std::cout << m.get_string() + '\n';
    }

};

std::unique_ptr<Logger> Logger::m_instance_ = nullptr;
std::mutex Logger::mtx_;

# define LLOG(level) (*llog::Logger::get_instance()) += llog::Message(level, __FILE__, __FUNCTION__, __LINE__)


} //namespace llog

#endif // _LIGHT_LOG_H