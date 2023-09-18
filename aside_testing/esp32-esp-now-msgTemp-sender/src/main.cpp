#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h> //library installed

#define DHTPIN 2 //pin sensor DHT
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC DE LA PLACA DESTINO

String success;
int nMessage;

typedef struct struct_message {
    //String origBoardAddr;
    char msg[50];
    //float humidity;
    //float temperature;
} struct_message;

// Callback when data is sent
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
  String incomingMsg = my_message.msg;
  Serial.println("Mensaje: "+incomingMsg+" de "+String((char *)mac));
  //Serial.println((String)"Recibido de "+incomingAddr+" el mensaje: "+incomingMsg);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_STA);
  if (esp_now_init() != ESP_OK) { //Inicializar ESP-NOW
    Serial.println("Error inicializando ESP-NOW");
    return;
  }
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  esp_now_register_send_cb(OnDataSent);
  //esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, destBoardAddr, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Error añadiendo el peer");
    return;
  }
  nMessage = 0;

}

void loop() {
  struct_message message_to_send;
  sprintf(message_to_send.msg, "Número mensaje = %d", nMessage);
  Serial.println((String)message_to_send.msg);
  //message_to_send.origBoardAddr = (String)WiFi.macAddress();
  //message_to_send.origBoardAddr = "C0:49:EF:CA:2B:74";

  //message_to_send.humidity = dht.readHumidity();
  //message_to_send.temperature = dht.readTemperature(false); //lee temperatura en ºC
  //añadir un control para no mandarlo si la temperatura/humedad no cambia

  esp_err_t result = esp_now_send(destBoardAddr, (uint8_t *) &message_to_send, sizeof(message_to_send));
  if (result == ESP_OK) { Serial.println("Enviado correctamente");
  } else { Serial.println("Error enviando los datos");
  }

  nMessage += 1;
  delay(1000);
}
