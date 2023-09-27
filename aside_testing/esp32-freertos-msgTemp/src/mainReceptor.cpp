// PLACA RECEPTOR

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

String success;

typedef struct struct_message {
    char msg[50];
    float humidity;
    float temperature;
} struct_message;

//Callback cuando se envían datos (en este caso, el único envío es de ACKs)
void OnDataSent(const uint8_t *mac, esp_now_send_status_t status) {
  Serial.printf("ACK enviado a %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "\tEntregado" : "\tFallo al entregar");
}

//Callback cuando se reciben datos (lo único que va a recibir son mensajes con formato struct_message)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  struct_message my_message;
  memcpy(&my_message, incomingData, sizeof(my_message));
  Serial.printf("Mensaje recibido de %02x:%02x:%02x:%02x:%02x:%02x y con tamaño de %d bytes:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], len);
  Serial.println("\t msg: "+(String)my_message.msg);
  Serial.printf("\t humidity: %f\n", my_message.humidity);
  Serial.printf("\t temperature: %f\n",my_message.temperature);
}

//TODO: Sincroniza el RTC de la placa con el servidor NTP
void setRTC() {
  return NULL;
}

void setup() {
  Serial.begin(9600);
  Serial.println("PLACA RECEPTOR");
  WiFi.mode(WIFI_STA);
  
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  if (esp_now_init() != ESP_OK) { //Inicializar ESP-NOW
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}

