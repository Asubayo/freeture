#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <functional>
#include <sstream>
#include <iostream>

class CArgParser
{
	class IOption
	{
	public:
		IOption(const std::string longOptName, const std::string shortOptName, const std::string description) :
			longName(longOptName), shortName(shortOptName), desc(description)
		{
			hasCallback = false;
		}

		bool isNameMatch(const std::string& name) const
		{
			if (name.size() == 1)
			{
				return shortName == name;
			}

			return longName == name;
		}

		virtual void parse_value(const std::string& strvalue) = 0;

		std::function<void()> callback;
		bool hasCallback;
		std::string longName;
		std::string shortName;
		std::string desc;	
	};

	template <typename T>
	class COption final : public IOption
	{
	public:
		COption(const std::string longOptName, const std::string shortOptName, const std::string description, T dfltValue) :
			value(dfltValue), IOption(longOptName, shortOptName, description)
		{

		}

		void parse_value(const std::string& strvalue)
		{
			value = parse(strvalue, value);
		}

		bool parse(const std::string& value, const bool&)
		{
			return value == "true" || value == "1" ? true : false;
		}

		int parse(const std::string& value, const int&)
		{
			return std::stoi(value);
		}

		unsigned int parse(const std::string& value, const unsigned int&)
		{
			return static_cast<unsigned int>(std::stoul(value));
		}

		std::string parse(const std::string& value, const std::string&)
		{
			return value;
		}

		double parse(const std::string& value, const double&)
		{
			return std::stod(value);
		}

		float parse(const std::string& value, const float&)
		{
			return std::stof(value);
		}

		T value;
	};

	enum E_ARG_TYPE
	{
		EAT_LONGNAME,
		EAT_SHORTNAME,
		EAT_VALUE,
	};

public:
	explicit CArgParser(const int& argc, const char** argv) :
		argCount(argc)
	{
		for (int i = 1; i < argc; ++i)
		{
			args.push_back(argv[i]);
		}
	}

	template<typename T>
	CArgParser& operator ()(
		const std::string& longOptName, 
		const std::string& shortOptName, 
		const std::string& description,
		T defaultValue = T())
	{
		IOption* opt = new COption<T>(longOptName, shortOptName, description, defaultValue);
		opts.push_back(std::unique_ptr<IOption>(std::move(opt)));
		return *this;
	}

	template<typename T>
	CArgParser& operator ()(
		const std::string& longOptName,
		const std::string& description,
		T defaultValue = T())
	{
		IOption* opt = new COption<T>(longOptName, "", description, defaultValue);
		opts.push_back(std::unique_ptr<IOption>(std::move(opt)));
		return *this;
	}

	template<typename T>
	T& get(std::string name) 
	{
		if (name.size() > 0)
		{
			for (auto &i : opts)
			{
				if (i.get()->isNameMatch(name))
				{
					return dynamic_cast<COption<T>*>(i.get())->value;
				}
			}
		}

		throw std::runtime_error("The option " + name + " could not be found.");
	}

	int find_option_by_name(const std::string& name)
	{
		for (unsigned int i = 0; i < opts.size(); ++i)
		{
			if (opts[i].get()->isNameMatch(name))
			{
				if (opts[i].get()->hasCallback)
					opts[i].get()->callback();
				return i;
			}
		}

		return -1;
	}

	void run()
	{
		generateHelpOption();

		int optIndex = -1;

		for (auto& i : args)
		{
			auto cnt = std::count(i.begin(), i.end(), '-');
			E_ARG_TYPE argtype = cnt >= 2 ? EAT_LONGNAME : cnt == 1 ? EAT_SHORTNAME : EAT_VALUE;

			switch (argtype)
			{
			case EAT_LONGNAME:
			case EAT_SHORTNAME:
				{
					auto name = i.substr(cnt);
					optIndex = find_option_by_name(name);
					if (optIndex != -1) optDefined.push_back(optIndex);
				}
				break;
			case EAT_VALUE:
				{
					if (optIndex != -1)
					{
						opts[optIndex]->parse_value(i);
						optIndex = -1;
					}
				}
				break;
			}

		}
	}

private:

	void generateHelpOption()
	{
		IOption* opt = new COption<bool>("help", "h", "show available program options", true);

		opt->hasCallback = true;
		opt->callback = [&]()
		{
			int max = 0;
			for (auto& i : opts)
			{
				if (i.get()->longName.size() > max)
				{
					max = i.get()->longName.size();
				}
			}

			std::stringstream ss;
			ss << "Program options : \n\n";

			for (auto& i : opts)
			{				
				int size = i.get()->longName.size();
				ss << "-> full_name(--" << i.get()->longName << ")";

				for (int r = 0 ; r < (max - size + 1); r++)
				{
					ss << " ";
				}

				if (i.get()->shortName.empty())
				{
					ss << "short_name(??)\t";
				}
				else
				{
					ss << "short_name(-" << i.get()->shortName << ")\t";
				}

				ss << " " << i.get()->desc << "\n\n";
				
			}

			std::cout << ss.str() << std::endl;
		};

		opts.push_back(std::unique_ptr<IOption>(std::move(opt)));
	}

	std::vector<std::string> args;	
	std::vector<std::unique_ptr<IOption>> opts;
	std::vector<unsigned int> optDefined;
	unsigned int argCount;
};