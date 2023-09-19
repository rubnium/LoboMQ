#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

String success;
const char* ssid = "MiFibra-8696";
const char* password = "7ahKvT57";
const char* ntpServer = "hora.roa.es";
const long  gmtOffset_sec = 2L * 60L * 60L; //España GMT (+2 horas)

typedef struct struct_message {
    char msg[50];
    float humidity;
    float temperature;
} struct_message;

String getLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Error al obtener el tiempo");
    return "(unknown time)";
  }
  char localTime[20];
  sprintf(localTime, "%d %b %Y %H:%M:%S", &timeinfo); //TODO: no funciona
  return String(localTime);
}

// Callback when data is sent NOT USED
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nEstado del último envío del paquete:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Entrega Exitosa" : "Entrega Fallida");
  if (status==0) { success = "Entrega Exitosa :)";
  } else {success = "Entrega Fallida :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  struct_message my_message;
  memcpy(&my_message, incomingData, sizeof(my_message));
  Serial.printf("Mensaje recibido a las %s de y con tamaño de %d bytes:\n", getLocalTime(), len);
  Serial.println("\t msg: "+(String)my_message.msg);
  Serial.printf("\t humidity: %f\n", my_message.humidity);
  Serial.printf("\t temperature: %f\n",my_message.temperature);
}

void setup() {
  Serial.begin(9600);
    Serial.println("PLACA RECEPTOR");
  WiFi.mode(WIFI_AP_STA);
  
  Serial.println("Conectando a "+String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(750);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  if (esp_now_init() != ESP_OK) { //Inicializar ESP-NOW
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  configTime(gmtOffset_sec, 3600, ntpServer);

  //esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.println(getLocalTime()); //DEBUG
}
