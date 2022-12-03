
#include <SoftwareSerial.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHT11_PIN D3
#define DHTTYPE DHT11
#define rxPin D5
#define txPin D6

String signal_condition;
String smsStatus, senderNumber, receivedDate, msg;
int SerialBaudRate = 115200;
int sms800BaudRate = 9600;

const String PHONE = "+447572785067";
int loop_delay_s = 1000;

DHT dht(DHT11_PIN, DHTTYPE);
SoftwareSerial sim800(rxPin, txPin);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




void setup()
{
  Serial.begin(SerialBaudRate);
  sim800.begin(9600);
  dht.begin();

  // clean all serial buffer
  Serial.flush();
  Serial.println("\n\n\n");
  Serial.println("---------- Start Setup ----------");
  Serial.println("Arduino serial initialize");
  Serial.println("SIM800L serial initialize");
  Serial.println("Initialize DHT11");
  Serial.println("Select message format as text mode");
  sim800.println("AT+CMGF=1"); // Select SMS Message Format
  Serial.println("Delete all outstanding SMS with AT+CMGD=1,4");
  sim800.println("AT+CMGD=1,4");
  Serial.println("---------- Debugging ------------");
  Serial.println("Phone number: " + PHONE);
  Serial.println("Loop delay: " + String(loop_delay_s) + "s");
  Serial.println("Serial monitor baud rate:" + String(SerialBaudRate));
  Serial.println("SIM800L baud rate:" + String(sms800BaudRate));
  Serial.println("Screen size: " + String(SCREEN_WIDTH) + "x" + String(SCREEN_HEIGHT));
  Serial.println("DH11 pin: " + String(DHT11_PIN) +  ", Type: " + String(DHTTYPE));
  Serial.println("SIM800x RX pin: " + String(rxPin) + ", TX pin: " + String(txPin));
  Serial.println("---------- DHT11 ------------");
  Serial.println("Waiting for DHT11 to settle...");
  delay(loop_delay_s);
  Serial.println("Temperature: " + String(get_temperature()) + " C");
  Serial.println("Humidity: " + String(get_humidity()) + " %");
  Serial.println("Heat Index: " + String(get_heat_index()) + " C");
  delay(loop_delay_s);
  Serial.println("---------- GSM ------------");
  Serial.println("Waiting for GSM to settle...");
  delay(loop_delay_s);
  Serial.println("Signal quality: " + String(get_signal_quality()));
  Serial.println("Available Network: " + String(get_available_network()));
  get_all_sms();



  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  // printToOLED("Arduino serial initialize");
  // reply(debugSend());

  Serial.println("----------- End Setup -----------");
  Serial.println("\n");
  delay(loop_delay_s);
}

void loop()
{
  while (sim800.available())
  {
    parseData(sim800.readString());
  }
  while (Serial.available())
  {
    sim800.println(Serial.readString());
  }
}


/**
 * function that takes variables and prints a text to the OLED screen
 *
 * @param text The text to be printed
 * @param color The color of the text (WHITE or BLACK)
 * @param x The x coordinate of the text
 * @param y The y coordinate of the text
 * @param size The size of the text
 */
void printToOLED(String text="default", String color="white", int x=0, int y=0, int size=1)
{
  display.clearDisplay();
  display.setTextSize(size);
  if (color == "white")
  {
    display.setTextColor(WHITE);
  }
  else if (color == "black")
  {
    display.setTextColor(BLACK);
  }
  display.setCursor(x, y);
  display.println(text);
  display.display();
}

/*
* Parse the data from input string
* @param buff The data to be parsed
*/
void parseData(String buff)
{
  Serial.println("-> parseData function called");
  Serial.println(buff);

  unsigned int len, index;

  // Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index + 2);
  buff.trim();

  if (buff != "OK")
  {
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();

    buff.remove(0, index + 2);

    if (cmd == "+CMTI")
    {
      // get newly arrived memory location and store it in temp
      index = buff.indexOf(",");
      String temp = buff.substring(index + 1, buff.length());
      temp = "AT+CMGR=" + temp + "\r";
      // get the message stored at memory location "temp"
      sim800.println(temp);
    }

    else if (cmd == "+CMGR")
    {
      extractSms(buff);
      Serial.println(msg);
      Serial.println(senderNumber);

      if (senderNumber == PHONE && msg == "get temperature")
      {
        reply("Temperature: " + String(get_temperature()) + " C");
      }
      else if (senderNumber == PHONE)
      {
        reply(getATOutput(msg));
      }
    }
  }
  else
  {
    // The result of AT Command is "OK"
  }
}

/*
/ a function that replies to the sender of the message with the message
/ @param msg The message to be sent
*/
void reply(String text)
{
  Serial.println("-> reply function called");
  if (text == "")
  {
    return;
  }

  sim800.print("AT+CMGF=1\r");
  delay(1000);
  sim800.print("AT+CMGS=\"" + PHONE + "\"\r");
  delay(1000);
  sim800.print(text);
  delay(100);
  sim800.write(0x1A); // ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1000);
  Serial.println("SMS Sent Successfully.");
  Serial.println("Delete all outstanding SMS with AT+CMGD=1,4");
  sim800.println("AT+CMGD=1,4");
}

/*
* Extract SMS from the response string
* @param buff The response string
*/
void extractSms(String buff)
{
  Serial.println("-> extractSms function called");
  unsigned int index;

  index = buff.indexOf(",");
  smsStatus = buff.substring(1, index - 1);
  buff.remove(0, index + 2);

  senderNumber = buff.substring(0, 13);
  buff.remove(0, 19);

  receivedDate = buff.substring(0, 20);
  buff.remove(0, buff.indexOf("\r"));
  buff.trim();

  index = buff.indexOf("\n\r");
  buff = buff.substring(0, index);
  buff.trim();
  msg = buff;
  buff = "";
  msg.toLowerCase();
}

/*
* Function that returns the temperature from the DHT11 sensor
* @param  none
* @return temperature
*/
String get_temperature()
{
  Serial.println("-> get_temperature function called");
  float t = dht.readTemperature();
  if (isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  String str_temperature = String(t);
  return str_temperature;
}

/*
* Function that returns the humidity from the DHT11 sensor
* @param  none
* @return humidity
*/
String get_humidity()
{
  Serial.println("-> get_humidity function called");
  float h = dht.readHumidity();
  if (isnan(h) || h > 100 || h < 0)
  {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  String str_humidity = String(h);
  return str_humidity;
}

/*
* Function that returns the Heat Index from the DHT11 sensor
* @param  none
* @return heat index
*/
String get_heat_index()
{
  Serial.println("-> get_heat_index function called");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  float hi = dht.computeHeatIndex(t, h, false);
  String str_heat_index = String(hi);
  return str_heat_index;
}

/*
* Function that returns the temperature, humidity and Heat Index from the DHT11 sensor
* @param  none
* @return temperature, humidity and Heat Index
*/
String get_DHT11_data()
{
  Serial.println("-> get_DHT11_data function called");
  String str_temperature = get_temperature();
  String str_humidity = get_humidity();
  String str_heat_index = get_heat_index();

  String humidity = "Humidity: " + str_humidity + "%";
  String temperature = "Temperature: " + str_temperature + "C";
  String heat_index = "Heat index: " + str_heat_index + "C";

  return humidity + "\n" + temperature + "\n" + heat_index;
}

/*
* Function that returns the signal strength
* @param  none
* @return signal strength
*/
String get_signal_quality()
{
  Serial.println("-> get_signal_quality function called");
  sim800.println("AT+CSQ");
  delay(1000);
  String signal = sim800.readString();
  int start = signal.indexOf(":");
  int end = signal.indexOf(",");
  signal = signal.substring(start + 1, end);
  // check if the signal strength is over 25 dBm
  if (signal.toInt() >2)
  {
    return signal;
  }
  else
  {
    return "0";
  }


}

/*
* Use AT commands to get all available networks
* @param  none
* @return All available networks
*/
String get_available_network()
{
  Serial.println("-> get_available_network function called (execution_time>10sec)");
  sim800.println("AT+COPS=?");
  delay(10000);
  String networks = sim800.readString();
  int start = networks.indexOf("(");
  int end = networks.indexOf(")");
  networks = networks.substring(start + 1, end);
  // Serial.println("Networks: " + networks);
  return networks;
}


/**
 * a funtion that returns the output of the AT command
 *
 * @param ATcommand The AT command to be executed
 * @return The output of the AT command
 */
String getATOutput(String ATcommand)
{
  Serial.println("-> getATOutput function called");
  sim800.println(ATcommand);
  delay(5000);
  String ATresponse = sim800.readString();
  return ATresponse;
}


// // a function that will be executed at th begginging and send debuging data to the phone with Reply function
// String debugSend()
// {
//   Serial.println("-> debugSend function called");

//   String debug_message = "";
//   debug_message =  "Debugging data:";
//   // debug_message += "\nSignal Strength: " + get_signal_quality();
//   debug_message += "\nSignal Condition: " + getSignalCondition(get_signal_quality());
//   debug_message += "\nNetworks: " + get_available_network();

//   // append to the debug message the output of the AT commands


//   Serial.println("--------------------");
//   Serial.println(debug_message);
//   Serial.println("--------------------");

//   return debug_message;
// }

// // a function that converts the signal strength to a condition
// String getSignalCondition(String signal)
// {
//   // convert signal into an integer
//   String signal = signal.toInt();
//   Serial.println("-> getSignalCondition function called");
//   if (signal >= 0 && signal <= 5)
//   {
//     return "No Signal";
//   }
//   else if (signal >= 6 && signal <= 10)
//   {
//     return "Very Weak";
//   }
//   else if (signal >= 11 && signal <= 15)
//   {
//     return "Weak";
//   }
//   else if (signal >= 16 && signal <= 20)
//   {
//     return "Good";
//   }
//   else if (signal >= 21)
//   {
//     return "Excellent";
//   }
//   else
//   {
//     return "Unknown";
//   }
// }


//   mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled