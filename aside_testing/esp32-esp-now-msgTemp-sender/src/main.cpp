#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h> //librería instalada
#include <math.h>

#define DHTPIN 2 //pin sensor DHT
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //mac placa destino

String success;
int nMessage;
float lastHumidity; float actualHumidity;
float lastTemperature; float actualTemperature;

typedef struct struct_message {
    char msg[50];
    float humidity;
    float temperature;
} struct_message;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nEstado del último envío del paquete:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Entrega Exitosa" : "Entrega Fallida");
  if (status==0) { success = "Entrega Exitosa :)";
  } else {success = "Entrega Fallida :(";
  }
}

//Callback cuando se reciben datos (en este caso, el único recibo es de ACKs)
void OnDataSent(const uint8_t *mac, esp_now_send_status_t status) {
  Serial.printf("ACK enviado a %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "\tEntregado" : "\tFallo al entregar");
}

void setup() {
  Serial.begin(9600);
  Serial.println("PLACA SENDER");
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
  lastHumidity = 0;
  lastTemperature = 0;
}

void loop() { //Cada segundo lee humedad y temperatura. Si son distintas a una lectura anterior, la envía junto a un mensaje numerado
  actualHumidity = roundf(dht.readHumidity()*100)/100; //humedad leída y redondeada a 2 decimales
  actualTemperature = roundf(dht.readTemperature(false)*100)/100; //lee temperatura en ºC, y redondeada a 2 decimales

  //Si ninguno de los valores es nan, y además si alguno ha cambiado
  if ((!isnan(actualHumidity) && !isnan(actualTemperature)) && (actualHumidity != lastHumidity || actualTemperature != lastTemperature)) {
    //crea el mensaje, lo rellena y lo envía
    struct_message message_to_send;
    sprintf(message_to_send.msg, "Número mensaje = %d", nMessage);
    message_to_send.humidity = actualHumidity;
    message_to_send.temperature = actualTemperature;
    esp_err_t result = esp_now_send(destBoardAddr, (uint8_t *) &message_to_send, sizeof(message_to_send));
    if (result == ESP_OK) {
      Serial.println("Enviado correctamente");
      nMessage += 1;
      lastHumidity = actualHumidity;
      lastTemperature = actualTemperature;
    } else { Serial.println("Error enviando los datos");
    }
  }
  delay(1000);
}
