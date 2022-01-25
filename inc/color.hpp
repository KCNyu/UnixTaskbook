#ifndef COLOR_HPP
#define COLOR_HPP

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BROWN "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

#define LOG_ERROR(format, ...)                  \
	{                                       \
		fprintf(stdout, "%s" format "", \
			RED, ##__VA_ARGS__);    \
		fprintf(stdout, "\n%s", RESET); \
		exit(1);                        \
	}
#define LOG_INFO(format, ...)                   \
	{                                       \
		fprintf(stdout, "%s" format "", \
			RED, ##__VA_ARGS__);    \
		fprintf(stdout, "\n%s", RESET); \
	}
#define LOG_WARN(format, ...)                    \
	{                                        \
		fprintf(stdout, "%s" format "",  \
			MAGENTA, ##__VA_ARGS__); \
		fprintf(stdout, "\n%s", RESET);  \
	}
#define LOG_SUCCESS(format, ...)                \
	{                                       \
		fprintf(stdout, "%s" format "", \
			GREEN, ##__VA_ARGS__);  \
		fprintf(stdout, "\n%s", RESET); \
	}
#define LOG_FILE(format, ...)                \
	{                                       \
		fprintf(stdout, "%s" format "", \
			CYAN, ##__VA_ARGS__);  \
		fprintf(stdout, "\n%s", RESET); \
	}
#define LOG_MARK(format, ...)                \
	{                                       \
		fprintf(stdout, "%s" format "", \
			BROWN, ##__VA_ARGS__);  \
		fprintf(stdout, "\n%s", RESET); \
	}

#endif /* COLOR_HPP */