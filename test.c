
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
#include "/usr/include/mysql/mysql.h"

#define SERVO1 0 //bottom
#define SERVO2 1 //arm1-1
#define SERVO3 2 //arm1-2
#define SERVO4 4 //arm2-1
#define SERVO5 3 //arm2-2
#define SERVO6 5 //arm3-1
#define SERVO7 12 //arm3-2
#define SERVO8 6 //handle
#define SERVO9 13 //crain
#define SPEED 400

#define DBHOST "192.168.137.3"
#define DBUSER "pi"
#define DBPASS "raspberry"
#define DBNAME "test"

#define DELAY 1000

MYSQL *connector;
MYSQL_RES *result;
MYSQL_ROW row;

void servo_off()
{
	softPwmWrite(SERVO1, 0);
	softPwmWrite(SERVO2, 0);
	softPwmWrite(SERVO3, 0);
	softPwmWrite(SERVO4, 0);
	softPwmWrite(SERVO5, 0);
	softPwmWrite(SERVO6, 0);
	softPwmWrite(SERVO7, 0);
	softPwmWrite(SERVO8, 0);
	softPwmWrite(SERVO9, 0);
	delay(10);
}

void servo_init()
{
	softPwmWrite(SERVO2, 10);
	softPwmWrite(SERVO3, 20);
	delay(DELAY);
	softPwmWrite(SERVO4, 16);
	softPwmWrite(SERVO5, 14);
	delay(DELAY);
	softPwmWrite(SERVO1, 16);
	delay(DELAY);
	softPwmWrite(SERVO9, 12);
	delay(DELAY);
	softPwmWrite(SERVO8, 15);
	delay(DELAY);
	servo_off();
}

void movetype_a()
{
	softPwmWrite(SERVO6, 15);
	softPwmWrite(SERVO7, 15);
	delay(DELAY);
	softPwmWrite(SERVO4, 5);
	softPwmWrite(SERVO5, 25);
	delay(DELAY);
	softPwmWrite(SERVO2, 14);
	softPwmWrite(SERVO3, 16);
	delay(DELAY);
	softPwmWrite(SERVO9, 21);
	delay(DELAY);
	servo_off();
}

void movetype_b()
{
	softPwmWrite(SERVO6, 16);
	softPwmWrite(SERVO7, 14);
	delay(DELAY);
	softPwmWrite(SERVO4, 8);
	softPwmWrite(SERVO5, 22);
	delay(DELAY);
	softPwmWrite(SERVO2, 13);
	softPwmWrite(SERVO3, 17);
	delay(DELAY);
	softPwmWrite(SERVO9, 21);
	delay(DELAY);
	servo_off();
}

void movetype_c()
{
	softPwmWrite(SERVO6, 19);
	softPwmWrite(SERVO7, 11);
	delay(DELAY);
	softPwmWrite(SERVO4, 12);
	softPwmWrite(SERVO5, 18);
	delay(DELAY);
	softPwmWrite(SERVO2, 13);
	softPwmWrite(SERVO3, 17);
	delay(DELAY);
	softPwmWrite(SERVO9, 21);
	delay(DELAY);
	servo_off();
}

void movetype_d()
{
	softPwmWrite(SERVO6, 19);
	softPwmWrite(SERVO7, 11);
	delay(DELAY);
	softPwmWrite(SERVO4, 14);
	softPwmWrite(SERVO5, 16);
	delay(DELAY);
	softPwmWrite(SERVO2, 13);
	softPwmWrite(SERVO3, 17);
	delay(DELAY);
	softPwmWrite(SERVO9, 21);
	delay(DELAY);
	servo_off();
}

void movetype_e()
{
	softPwmWrite(SERVO6, 20);
	softPwmWrite(SERVO7, 10);
	delay(DELAY);
	softPwmWrite(SERVO4, 16);
	softPwmWrite(SERVO5, 14);
	delay(DELAY);
	softPwmWrite(SERVO2, 12);
	softPwmWrite(SERVO3, 18);
	delay(DELAY);
	softPwmWrite(SERVO9, 21);
	delay(DELAY);
	servo_off();
}

void what_is_color(char *color)
{
	if (*color == 'r')
	{
		softPwmWrite(SERVO9, 21);
		delay(DELAY);
		softPwmWrite(SERVO2, 10);
		softPwmWrite(SERVO3, 20);
		delay(DELAY);
		softPwmWrite(SERVO6, 19);
		softPwmWrite(SERVO7, 11);
		delay(DELAY);
		softPwmWrite(SERVO4, 15);
		softPwmWrite(SERVO5, 15);
		delay(DELAY);
		softPwmWrite(SERVO2, 0);
		softPwmWrite(SERVO3, 0);
		delay(DELAY);
		softPwmWrite(SERVO1, 21);
		delay(DELAY);
		softPwmWrite(SERVO9, 12);
		delay(DELAY);
		servo_init();
	}
	else if (*color == 'g')
	{
		softPwmWrite(SERVO9, 21);
		delay(DELAY);
		softPwmWrite(SERVO2, 10);
		softPwmWrite(SERVO3, 20);
		delay(DELAY);
		softPwmWrite(SERVO6, 19);
		softPwmWrite(SERVO7, 11);
		delay(DELAY);
		softPwmWrite(SERVO4, 15);
		softPwmWrite(SERVO5, 15);
		delay(DELAY);
		softPwmWrite(SERVO2, 0);
		softPwmWrite(SERVO3, 0);
		delay(DELAY);
		softPwmWrite(SERVO1, 19);
		delay(DELAY);
		softPwmWrite(SERVO9, 12);
		delay(DELAY);
		servo_init();
	}
	else if (*color == 'b')
	{
		softPwmWrite(SERVO9, 21);
		delay(DELAY);
		softPwmWrite(SERVO2, 10);
		softPwmWrite(SERVO3, 20);
		delay(DELAY);
		softPwmWrite(SERVO6, 19);
		softPwmWrite(SERVO7, 11);
		delay(DELAY);
		softPwmWrite(SERVO4, 15);
		softPwmWrite(SERVO5, 15);
		delay(DELAY);
		softPwmWrite(SERVO2, 0);
		softPwmWrite(SERVO3, 0);
		delay(DELAY);
		softPwmWrite(SERVO1, 11);
		delay(DELAY);
		softPwmWrite(SERVO9, 12);
		delay(DELAY);
		servo_init();
	}
	else if (*color == 'y')
	{
		softPwmWrite(SERVO9, 21);
		delay(DELAY);
		softPwmWrite(SERVO2, 10);
		softPwmWrite(SERVO3, 20);
		delay(DELAY);
		softPwmWrite(SERVO6, 19);
		softPwmWrite(SERVO7, 11);
		delay(DELAY);
		softPwmWrite(SERVO4, 15);
		softPwmWrite(SERVO5, 15);
		delay(DELAY);
		softPwmWrite(SERVO2, 0);
		softPwmWrite(SERVO3, 0);
		delay(DELAY);
		softPwmWrite(SERVO1, 10);
		delay(DELAY);
		softPwmWrite(SERVO9, 12);
		delay(DELAY);
		servo_init();
	}
	servo_off();
}

int main(int argc, char* argv[])
{
	int state = 0;

	connector = mysql_init(NULL);
	if (!mysql_real_connect(connector, DBHOST, DBUSER, DBPASS, DBNAME, 3306, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(connector));
		return 0;
	}

	char query[1024];

	sprintf(query, "select * from sample");
	state = mysql_query(connector, query);
	if (state)
	{
		fprintf(stderr, "%s\n", mysql_error(connector));
		printf("Write DB error\n");
	}
	result = mysql_store_result(connector);
	row = mysql_fetch_row(result);
	int x = atoi(row[0]);
	int y = atoi(row[1]);
	char *color = row[2];

	int data;

	if (wiringPiSetup() == -1) return 1;

	pinMode(SERVO1, OUTPUT);
	softPwmCreate(SERVO1, 0, SPEED);
	pinMode(SERVO2, OUTPUT);
	softPwmCreate(SERVO2, 0, SPEED);
	pinMode(SERVO3, OUTPUT);
	softPwmCreate(SERVO3, 0, SPEED);
	pinMode(SERVO4, OUTPUT);
	softPwmCreate(SERVO4, 0, SPEED);
	pinMode(SERVO5, OUTPUT);
	softPwmCreate(SERVO5, 0, SPEED);
	pinMode(SERVO6, OUTPUT);
	softPwmCreate(SERVO6, 0, SPEED);
	pinMode(SERVO7, OUTPUT);
	softPwmCreate(SERVO7, 0, SPEED);
	pinMode(SERVO8, OUTPUT);
	softPwmCreate(SERVO8, 0, SPEED);
	pinMode(SERVO9, OUTPUT);
	softPwmCreate(SERVO9, 0, SPEED);
	if (argc == 1)
	{
		fputs("There is no input option.", stderr);
		return 1;
	}
	else
		data = (int)argv[1][0];

	if (data == 'a')
	{
		servo_init();
	}

	else if (data == 'b')
	{
		if (y >= 800)
		{
			if (x<448)
			{
				softPwmWrite(SERVO1, 17);
				softPwmWrite(SERVO8, 16);
				delay(DELAY);
				movetype_a();
			}
			else if (x >= 448 && x<740)
			{
				softPwmWrite(SERVO1, 16);
				softPwmWrite(SERVO8, 15);
				delay(DELAY);
				movetype_a();
			}
			else if (x >= 740)
			{
				softPwmWrite(SERVO1, 15);
				softPwmWrite(SERVO8, 14);
				delay(DELAY);
				movetype_a();
			}
		}

		else if (y >= 755 && y<800)
		{
			if (x<640)
			{
				softPwmWrite(SERVO1, 16);
				softPwmWrite(SERVO8, 15);
				delay(DELAY);
				movetype_b();
			}
			else if (x >= 640 && x<800)
			{
				softPwmWrite(SERVO1, 15);
				softPwmWrite(SERVO8, 14);
				delay(DELAY);
				movetype_b();
			}
			else if (x >= 800)
			{
				softPwmWrite(SERVO1, 14);
				softPwmWrite(SERVO8, 13);
				delay(DELAY);
				movetype_a();
			}
		}

		else if (y >= 650 && y<755)
		{
			if (x<320)
			{
				softPwmWrite(SERVO1, 18);
				softPwmWrite(SERVO8, 17);
				delay(DELAY);
				movetype_a();
			}
			else if (x >= 320 && x<512)
			{
				softPwmWrite(SERVO1, 17);
				softPwmWrite(SERVO8, 16);
				delay(DELAY);
				movetype_b();
			}
			else if (x >= 512 && x<704)
			{
				softPwmWrite(SERVO1, 16);
				softPwmWrite(SERVO8, 15);
				delay(DELAY);
				movetype_c();
			}
			else if (x >= 704 && x<832)
			{
				softPwmWrite(SERVO1, 15);
				softPwmWrite(SERVO8, 14);
				delay(DELAY);
				movetype_c();
			}
			else if (x >= 832)
			{
				softPwmWrite(SERVO1, 14);
				softPwmWrite(SERVO8, 13);
				delay(DELAY);
				movetype_b();
			}
		}

		else if (y >= 550 && y<650)
		{
			if (x<384)
			{
				softPwmWrite(SERVO1, 18);
				softPwmWrite(SERVO8, 17);
				delay(DELAY);
				movetype_b();
			}
			else if (x >= 384 && x<512)
			{
				softPwmWrite(SERVO1, 17);
				softPwmWrite(SERVO8, 16);
				delay(DELAY);
				movetype_c();
			}
			else if (x >= 512 && x<704)
			{
				softPwmWrite(SERVO1, 16);
				softPwmWrite(SERVO8, 15);
				delay(DELAY);
				movetype_d();
			}
			else if (x >= 704 && x<832)
			{
				softPwmWrite(SERVO1, 15);
				softPwmWrite(SERVO8, 14);
				delay(DELAY);
				movetype_d();
			}
			else if (x >= 832)
			{
				softPwmWrite(SERVO1, 14);
				softPwmWrite(SERVO8, 13);
				delay(DELAY);
				movetype_c();
			}
		}

		else if (y >= 528 && y<550)
		{
			if (x<448)
			{
				softPwmWrite(SERVO1, 18);
				softPwmWrite(SERVO8, 17);
				delay(DELAY);
				movetype_c();
			}
			else if (x >= 448 && x<640)
			{
				softPwmWrite(SERVO1, 17);
				softPwmWrite(SERVO8, 16);
				delay(DELAY);
				movetype_d();
			}
			else if (x >= 640 && x<960)
			{
				softPwmWrite(SERVO1, 14);
				softPwmWrite(SERVO8, 13);
				delay(DELAY);
				movetype_d();
			}
			else if (x >= 960)
			{
				softPwmWrite(SERVO1, 13);
				softPwmWrite(SERVO8, 12);
				delay(DELAY);
				movetype_b();
			}
		}

		else if (y >= 480 && y<528)
		{
			if (x<512)
			{
				softPwmWrite(SERVO1, 18);
				softPwmWrite(SERVO8, 17);
				delay(DELAY);
				movetype_d();
			}
			else if (x >= 512 && x<640)
			{
				softPwmWrite(SERVO1, 16);
				softPwmWrite(SERVO8, 15);
				delay(DELAY);
				movetype_e();
			}
			else if (x >= 640 && x<832)
			{
				softPwmWrite(SERVO1, 15);
				softPwmWrite(SERVO8, 14);
				delay(DELAY);
				movetype_e();
			}
			else if (x >= 832)
			{
				softPwmWrite(SERVO1, 13);
				softPwmWrite(SERVO8, 12);
				delay(DELAY);
				movetype_c();
			}
		}

		else if (y >= 432 && y<480)
		{
			if (x<320)
			{
				softPwmWrite(SERVO1, 19);
				softPwmWrite(SERVO8, 18);
				delay(DELAY);
				movetype_c();
			}
			else if (x >= 320 && x<640)
			{
				softPwmWrite(SERVO1, 17);
				softPwmWrite(SERVO8, 16);
				delay(DELAY);
				movetype_e();
			}
			else if (x >= 640 && x<832)
			{
				softPwmWrite(SERVO1, 14);
				softPwmWrite(SERVO8, 13);
				delay(DELAY);
				movetype_e();
			}
			else if (x >= 832)
			{
				softPwmWrite(SERVO1, 13);
				softPwmWrite(SERVO8, 12);
				delay(DELAY);
				movetype_d();
			}
		}
		what_is_color(color);
		}
		return 0;
}