int d,e,f,g,n;
#define SSID        "pinkman" //改为你的Wi-Fi名称

#define PASSWORD    "fengbaba"//Wi-Fi密码

#define HOST_NAME   "api.heclouds.com"

#define DEVICEID    "503948909" //OneNet上的设备ID

#define PROJECTID   "187676" //OneNet上的产品ID

#define HOST_PORT   (80)

String apiKey="pP7sowvkaUypZyLn=CnNimSfdXA=";//与你的设备绑定的APIKey

//传感器部分================================   

#include <Wire.h>                                  //调用库  

#include <ESP8266.h>

#include <I2Cdev.h>                                //调用库  

/*******温湿度*******/

#include <Microduino_SHT2x.h>

/*******光照*******/

#define  sensorPin_1  A0

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 

                                   // received before closing the connection.  If you know the server

                                   // you're accessing is quick to respond, you can reduce this value.



//WEBSITE     

char buf[10];



#define INTERVAL_sensor 2000

unsigned long sensorlastTime = millis();



float tempOLED, humiOLED, lightnessOLED;



#define INTERVAL_OLED 1000



String mCottenData;

String jsonToSend;

int  tonepin=6;
int a =300;        //亮度值
int c=900;
int b =800;
int z=200;

//3,传感器值的设置 
#include <SoftwareSerial.h>

#define EspSerial mySerial

#define UARTSPEED  9600

SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */

ESP8266 wifi(&EspSerial);

//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象

unsigned long net_time1 = millis();                          //数据上传服务器时间

unsigned long sensor_time = millis();                        //传感器采样时间计时器



//int SensorData;                                   //用于存储传感器数据

String postString;                                //用于存储发送数据的字符串

//String jsonToSend;                                //用于存储发送的json格式参数



Tem_Hum_S2 TempMonitor;



void setup(void)     //初始化函数  

{       

   pinMode(tonepin,OUTPUT);//设置数字IO脚模式，OUTPUT为输出
  //初始化串口波特率  

    Wire.begin();

    Serial.begin(115200);

    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    Serial.print(F("setup begin\r\n"));

    delay(100);




  WifiInit(EspSerial, UARTSPEED);



  Serial.print(F("FW Version:"));

  Serial.println(wifi.getVersion().c_str());



  if (wifi.setOprToStationSoftAP()) {

    Serial.print(F("to station + softap ok\r\n"));

  } else {

    Serial.print(F("to station + softap err\r\n"));

  }



  if (wifi.joinAP(SSID, PASSWORD)) {

    Serial.print(F("Join AP success\r\n"));



    Serial.print(F("IP:"));

    Serial.println( wifi.getLocalIP().c_str());

  } else {

    Serial.print(F("Join AP failure\r\n"));

  }



  if (wifi.disableMUX()) {

    Serial.print(F("single ok\r\n"));

  } else {

    Serial.print(F("single err\r\n"));

  }



  Serial.print(F("setup end\r\n"));

    

  

}

void loop(void)     //循环函数  

{   

   int h = analogRead(A1) ;   //读取模拟口D2，获取光强
    
    Serial.println("h:");
    Serial.println(h); // 用于IDE串口观察窗

      int i = analogRead(A2) ;   //读取模拟口D2，获取光强
      Serial.println("i:");
    Serial.println(i);               // 用于IDE串口观察窗
   

          int j = analogRead(A3) ;   //读取模拟口D2，获取光强
      Serial.println("j:");
    Serial.println(j);               // 用于IDE串口观察窗


          int k = analogRead(A4) ;   //读取模拟口D2，获取光强
      Serial.println("k:");
    Serial.println(k);               // 用于IDE串口观察窗


          int l = analogRead(A5) ;   //读取模拟口D2，获取光强
      Serial.println("l:");
    Serial.println(l);               // 用于IDE串口观察窗
    
    d=e=f=g=n=1;
    if (h<= a )                         //对光强进行判断

   {
       tone(tonepin,393,300);
       d=0;
   }    
delay(50);

    if (i<= a )                         //对光强进行判断
   {
       tone(tonepin,441,300);
       e=0;
   }    
   delay(50);
    if (j<= a )                         //对光强进行判断
   {
       tone(tonepin,495,300);
       f=0;
   }    
   delay(50);
    if (k<= a )                         //对光强进行判断
   {
       tone(tonepin,624,300);
       g=0;
   }    
   delay(50);
    if (l>= b )                         //对光强进行判断
   {
       tone(tonepin,661,300);
       n=0;
   }    
   delay(50);
  if (d*e*f*g*n==0)                  
  {                
    updateSensorData();                                     //将数据上传到服务器的函数
  }
    delay(50);
  }  



  



void updateSensorData() {

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据

    Serial.print("create tcp ok\r\n");



jsonToSend="{\"do\":";
    dtostrf(d,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"re\":";
    dtostrf(e,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"mi\":";
    dtostrf(f,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
  jsonToSend+=",\"so\":";
    dtostrf(g,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
  jsonToSend+=",\"la\":";
    dtostrf(n,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+="}";







    postString="POST /devices/";

    postString+=DEVICEID;

    postString+="/datapoints?type=3 HTTP/1.1";

    postString+="\r\n";

    postString+="api-key:";

    postString+=apiKey;

    postString+="\r\n";

    postString+="Host:api.heclouds.com\r\n";

    postString+="Connection:close\r\n";

    postString+="Content-Length:";

    postString+=jsonToSend.length();

    postString+="\r\n";

    postString+="\r\n";

    postString+=jsonToSend;

    postString+="\r\n";

    postString+="\r\n";

    postString+="\r\n";



  const char *postArray = postString.c_str();                 //将str转化为char数组

  Serial.println(postArray);

  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)

  Serial.println("send success");   

     if (wifi.releaseTCP()) {                                 //释放TCP连接

        Serial.print("release tcp ok\r\n");

        } 

     else {

        Serial.print("release tcp err\r\n");

        }

      postArray = NULL;                                       //清空数组，等待下次传输数据

  

  } else {

    Serial.print("create tcp err\r\n");

  }

}


