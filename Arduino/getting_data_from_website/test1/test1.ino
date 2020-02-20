#include "WiFiEsp.h"


#include "SoftwareSerial.h"
SoftwareSerial esp(2, 3); // RX, TX

char ssid[] = "Inseockjjang";             // 공유기 이름 SSID
char pass[] = "029603574";        // 공유기 암호 Password

int status = WL_IDLE_STATUS;        // Status

char server[] = "www.kma.go.kr";

String data_seq = "";
String wt_hour = "";
String wt_temp = "";
String wt_state = "";
String wt_hum = "";
String wt_date = "";

unsigned long ulPreTime = 0;
bool flag_stop;

WiFiEspClient client;

void setup()
{
  Serial.begin(9600);
  esp.begin(9600);

  // 시리얼모니터가 실행될때까지 대기
//  while (!Serial);

  WiFi.init(&esp);

  // 쉴드 존재유무 확인
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true);
  }

  // 와이파이 접속여부 확인
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  // 와이파이 접속정보
  Serial.println("You're connected to the network");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println();

}

void loop()
{
  unsigned long ulCurTime = millis();

  if (ulCurTime - ulPreTime >= 10000)
  {
    ulPreTime = ulCurTime;
   
    client.flush();
   
    // 날씨서버에 연결
    if (client.connect(server, 80))
    {
      Serial.println("[Net Info] Connected! Sending HTTP request to www.kma.go.kr");
      //Serial.println("GET /data/2.5/weather?q="+location+"&mode=xml");

      // 기상청 홈페이지에서 복사한 지역날씨정보 RSS
      //      http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4719069000      // 구미 양포동
      //      http://www.kma.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=143   // 경상북도

      client.println("GET /weather/forecast/mid-term-rss3.jsp?stnId=143 HTTP/1.1");

      client.print("HOST: www.kma.go.kr\n");
      client.println("Connection: close");
      client.println();
    }
    else
    {
      Serial.println("Connect Failed!");
    }

    // 연결된 동안 데이터를 읽어옴
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
  
        // 데이터 파싱
        parsingGetData(line);

        if (flag_stop)
        {
          data_seq = "";
          flag_stop = 0;
          client.stop();

          printWeatherData();
        }
      }
    }
  }
}

void parsingGetData(String line)
{
  String tmp_str = "";

  //Check publish date & time
  int t_date = line.indexOf("</tm>");
  if (t_date >= 0)
  {
    tmp_str = "<tm>";
    wt_date = line.substring(line.indexOf(tmp_str) + tmp_str.length(), t_date);
  }

  //Check Data Sequence
  int seq = line.indexOf("<data seq=\"");
  if (seq >= 0)
  {
    tmp_str = "<data seq=\"";
    int seq_end = line.indexOf("\">");
    data_seq = line.substring(seq + tmp_str.length(), seq_end);
    // SerialUSB.println(data_seq);
  }

  if (data_seq == "0")
  {
    //시간
    int t_time = line.indexOf("</hour>");
    if (t_time >= 0)
    {
      tmp_str = "<hour>";
      wt_hour = line.substring(line.indexOf(tmp_str) + tmp_str.length(), t_time);
    }

    //온도
    int temp = line.indexOf("</temp>");
    if (temp >= 0)
    {
      tmp_str = "<temp>";
      wt_temp = line.substring(line.indexOf(tmp_str) + tmp_str.length(), temp);
    }

    //날씨 정보
    int state = line.indexOf("</wfEn>");
    if (state >= 0)
    {
      tmp_str = "<wfEn>";
      wt_state = line.substring(line.indexOf(tmp_str) + tmp_str.length(), state);
    }

    //습도
    int hum = line.indexOf("</reh>");
    if (hum >= 0)
    {
      tmp_str = "<reh>";
      wt_hum = line.substring(line.indexOf(tmp_str) + tmp_str.length(), hum);
      flag_stop = 1;
    }
  }
}


void printWeatherData(void)
{
  Serial.println("    === Weather forecast information ===");
  String t_year = wt_date.substring(0, 4);
  String t_month = wt_date.substring(4, 6);
  String t_day = wt_date.substring(6, 8);
  String t_hour = wt_date.substring(8, 10);
  //SerialUSB.println("\tDate & Time(published) : " + wt_date);
  Serial.println("\tTime&Date(published) : "  + t_hour + "h / "  + t_year + "-" + t_month + "-" + t_day);
  Serial.println("\tTime(cast)   : " + wt_hour + " h");
  Serial.println("\tTemp(cast)  : " + wt_temp + " 'C");
  Serial.println("\tState(cast) : " + wt_state);
  Serial.println("\tHumi(cast)  : " + wt_hum + " %");
}
