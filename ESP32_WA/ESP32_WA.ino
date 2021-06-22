#include <WiFi.h>
#include <HTTPClient.h>

#define SERVER_IP "http://wa.ismaillowkey.my.id"
#define PHONENO "6282210388811" // NO wa yang ingin dikirim pesan

//Provide your own WiFi credentials
//const char* ssid = "YOUR_WIFI";
//const char* pass = "YOUR_WIFI_PASSWORD";
const char* ssid = "TOHO";
const char* pass = "toho123456";

void setup() {
  Serial.begin(9600);

  Serial.print("Menghubungkan ke : ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    // buat random anga
    String randNumber = String(random(300));
    // kirim message ke wa tujuan
    SimpleSendMessage("send from ismaillowkey : " + randNumber);
  }
}

void loop() 
{
}

void SimpleSendMessage(String message)
{
  WiFiClient client;
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(client, SERVER_IP "/chat/sendmessage/" PHONENO);
  http.addHeader("Content-Type", "application/json");

  Serial.print("[HTTP] POST...\n");
  // start connection and send HTTP header and body
  int httpCode = http.POST("{\"message\":\"" + message + "\"}");

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}
