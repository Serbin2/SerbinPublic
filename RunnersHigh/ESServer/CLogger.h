#pragma once


#include "ILogger.h"
#include "Clock.h"


class ConsoleLogger : public ILog
{
public:
	ConsoleLogger() = default;
	virtual ~ConsoleLogger() {}


protected:
	virtual void Error(const char* pText) override
	{
		Clock::GetInstance()->CheckTime();
		std::string text = Clock::GetInstance()->Now_Mul();
		text = (text.c_str() - 1);
		std::cout << "[ERROR] " << "[ " << text.c_str() + 1 << "] " << pText << std::endl;
	}

	virtual void Warn(const char* pText) override
	{
		Clock::GetInstance()->CheckTime();
		std::string text = Clock::GetInstance()->Now_Mul();
		text = (text.c_str() - 1);
		std::cout << "[WARN] " << "[ " << text.c_str() + 1 << " ] " << pText << std::endl;
	}

	virtual void Debug(const char* pText) override
	{
		Clock::GetInstance()->CheckTime();
		std::string text = Clock::GetInstance()->Now_Mul();
		text = (text.c_str() - 1);
		std::cout << "[DEBUG] " << "[ " << text.c_str() + 1 << " ] " << pText << std::endl;

	}

	virtual void Trace(const char* pText) override
	{
		Clock::GetInstance()->CheckTime();
		std::string text = Clock::GetInstance()->Now_Mul();
		text = (text.c_str() - 1);
		std::cout << "[TRACE] " << "[ " << text.c_str() + 1 << " ] " << pText << std::endl;

	}

	virtual void Info(const char* pText) override
	{
		Clock::GetInstance()->CheckTime();
		std::string text = Clock::GetInstance()->Now_Mul();
		text = (text.c_str() - 1);
		std::cout << "[INFO]  " << "[ " << text.c_str() + 1 << " ] " << pText << std::endl;
	}
};