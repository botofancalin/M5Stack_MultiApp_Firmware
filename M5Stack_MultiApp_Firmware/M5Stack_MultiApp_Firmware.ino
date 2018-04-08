#include "apps.h"

void setup()
{
	M5.begin();
	Wire.begin();
	dacWrite(25, 0); // Speaker OFF

	if (!EEPROM.begin(EEPROM_SIZE))
	{
		M5.powerOFF();
	}
	else
	{
		M5.lcd.setBrightness(byte(EEPROM.read(0)));
	}

	MyMenu.addMenuItem(0, "APPLICATIONS", "<", "OK", ">", 1, "/Data/Apps.jpg", appReturn);
	MyMenu.addMenuItem(0, "SYSTEM", "<", "OK", ">", 2, "/Data/System.jpg", appReturn);
	MyMenu.addMenuItem(0, "ABOUT", "<", "OK", ">", -1, "/Data/About.jpg", appAbout);

	MyMenu.addMenuItem(1, "OSCILOSCOPE", "<", "OK", ">", -1, "/Data/Oscilloscope.jpg", appOsciloscope);
	MyMenu.addMenuItem(1, "STOPWATCH", "<", "OK", ">", -1, "/Data/Stopwatch.jpg", appStopWatch);
	MyMenu.addMenuItem(1, "TOOLS", "<", "OK", ">", -1, "/Data/Tools.jpg", appListTools);
	MyMenu.addMenuItem(1, "GAMES", "<", "OK", ">", -1, "/Data/Games.jpg", appListGames);
	MyMenu.addMenuItem(1, "RETURN", "<", "OK", ">", 0, "/Data/Return.jpg", appReturn);

	MyMenu.addMenuItem(2, "SYSTEM INFORMATIONS", "<", "OK", ">", -1, "/Data/SysInfo.jpg", appSysInfo);
	MyMenu.addMenuItem(2, "DISPLAY BACKLIGHT", "<", "OK", ">", -1, "/Data/BackLight.jpg", appCfgBrigthness);
	MyMenu.addMenuItem(2, "SLEEP/CHARGING", "<", "OK", ">", -1, "/Data/Sleep.jpg", appSleep);
	MyMenu.addMenuItem(2, "RETURN", "<", "OK", ">", 0, "/Data/Return.jpg", appReturn);

	MyMenu.show();
}

void loop()
{
	if (WiFi.isConnected())
	{
		if (!OtaRunning)
		{
			appOta();
			OtaRunning = true;
		}
		ArduinoOTA.handle();
	}
	M5.update();
	if (M5.BtnC.wasPressed())
	{
		MyMenu.up();
	}
	if (M5.BtnA.wasPressed())
	{
		MyMenu.down();
	}
	if (M5.BtnB.wasPressed())
	{
		MyMenu.execute();
	}
}
