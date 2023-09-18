#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

String success;

typedef struct struct_message {
    //String origBoardAddr;
    char msg[50];
    //float humidity;
    //float temperature;
} struct_message;

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
  Serial.println((String)"Bytes recibidos: "+len);
  //String incomingAddr = my_message.origBoardAddr;
  String incomingAddr = "nadie";
  //Serial.println((String)"Recibido de "+incomingAddr+" el mensaje: "+(String)my_message.msg);
  Serial.println(String((char *)incomingData));
  Serial.println("Mensaje: "+(String)my_message.msg+" de "+String((char *)mac));

}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_STA);
  if (esp_now_init() != ESP_OK) { //Inicializar ESP-NOW
    Serial.println("Error inicializando ESP-NOW");
    return;
  }
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  //esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
