#include <ctelebot/ct_api.h>
#include <ctelebot/ct_common.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>
#include <string.h>

#define TELEGRAM_TOKEN ""

static void log_func(int priority, const char *format, ... )
{
	static const char *CONSOLE_COLOR_RED = "\033[31;1m";
	static const char *CONSOLE_COLOR_GREEN = "\033[32;1m";
	static const char *CONSOLE_COLOR_YELLOW = "\033[33;1m";
	static const char *CONSOLE_COLOR_BLUE = "\033[34;1m";
	static const char *CONSOLE_COLOR_CYAN = "\033[36;1m";
	static const char *CONSOLE_COLOR_WHITE = "\033[37;1m";
	static const char *CONSOLE_COLOR_DEFAULT = "\033[39;0m";

	char logbuff[1024];
	va_list args;
	va_start (args, format);
	vsnprintf (logbuff, sizeof(logbuff), format, args);
	va_end (args);

	switch (priority) {
		case LOG_DEBUG:
			printf("%s[Debug]%s %s", CONSOLE_COLOR_BLUE, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		case LOG_INFO:
			printf("%s[Info]%s %s", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		case LOG_NOTICE:
			printf("%s[Notice]%s %s", CONSOLE_COLOR_CYAN, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		case LOG_WARNING:
			printf("%s[Warning]%s %s", CONSOLE_COLOR_YELLOW, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		case LOG_ERR:
			printf("%s[Error]%s %s", CONSOLE_COLOR_RED, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		case LOG_CRIT:
			printf("%s[Crit]%s %s", CONSOLE_COLOR_WHITE, CONSOLE_COLOR_DEFAULT, logbuff);
			break;

		default:
			break;
	}
}

int main()
{
	ct_set_log_print_function(log_func);

	if (strlen(TELEGRAM_TOKEN) == 0) {
		ct_log_crit("Telegram bot token is not set! Get the token from the @BotFather and set TELEGRAM_TOKEN");
		return -1;
	}

	ct_log_info("Run telegram bot");

	ct_api_t *tlgrm = ct_api_create();
	ct_api_set_token(tlgrm, TELEGRAM_TOKEN);

	bool run = true;

	while (run) {
		ct_api_update(tlgrm);

		while (true) {
			ct_message_t *recv_msg = ct_api_recv_message(tlgrm);

			if (!recv_msg) {
				break;
			}

			const char *text = ct_message_get_text(recv_msg);
			time_t unixtime =  ct_message_get_date(recv_msg);
			ssize_t chat_id = ct_message_get_chat_id(recv_msg);

			struct tm *local = localtime(&unixtime);

			char send_text[1024];
			snprintf(send_text, sizeof(send_text), "Receive message:\n'%s'\n%s", text, asctime(local));
			ct_api_send_text(tlgrm, chat_id, send_text);

			ct_message_free(recv_msg);
		}

		sleep(4);
	}

	ct_api_free(tlgrm);

	return 0;
}

