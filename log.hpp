
#ifndef _LOG_HEAD_ 
#define _LOG_HEAD_ 

#include "global.hpp" 

#include <iostream> 
#include <cassert> 
#include <sstream> 
#include <string> 



class Log; 

static Log* m_log = nullptr; 

class Log
{
public:
    enum class LogLevel
    {
        ALL = 0, 
        DEBUG, 
        INFO, 
        WARN, 
        ERROR, 
        NOTHING, 
    }; 

public:
    Log() {} 

    static Log* getInstance()
    {
        if(!m_log)
        {
            m_log = new (std::nothrow) Log(); 
            assert(m_log); 
            m_log->init(); 
        }
        return m_log; 
    }

    void init(void); 

    template<class... Value>
    void debug(const Value &... v)
    {
        if(log_level > LogLevel::DEBUG)
        {
            return; 
        }
        show(LogLevel::DEBUG, v...); 
    }

    template <class... Value>
    void info(const Value &... v)
    {
        if(log_level > LogLevel::INFO)
        {
            return; 
        }
        show(LogLevel::INFO, v...); 
    }

    template <class... Value>
    void warn(const Value &... v)
    {
        if(log_level > LogLevel::WARN)
        {
            return; 
        }
        show(LogLevel::WARN, v...); 
    }

    template <class... Value>
    void error(const Value &... v)
    {
        if(log_level > LogLevel::ERROR)
        {
            return; 
        }
        show(LogLevel::ERROR, v...); 
    }


private:
    template <class... Value>
    void show(LogLevel ll, const Value &... v)
    {
        std::ostringstream o; 
        BuildString(&o, v...); 
        if(has_time)
        {
            std::cout << get_cur_time(); 
        } 
        std::cout << " ";  
        std::cout  << o.str() << std::endl; 
    }
    
    template <class First, class... Rest>
    void BuildString(std::ostream *o, const First & v1, const Rest &... v2)
    {
        *o << v1; 
        BuildString(o, v2...); 
    }

    template <class Stream>
    void BuildString(Stream *o)
    {

    }

    std::string get_cur_time()
    {
        return "current time:"; 
    }


    LogLevel log_level; 
    bool has_time; 
    // static Log *m_log; 
}; 



#define glog Log::getInstance() 



#endif // _LOG_HEAD_ 

