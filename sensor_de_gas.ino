// Definição dos pinos no ESP8266
#define GAS_SENSOR_PIN A0 // Pino A0 para o sensor de gás
#define BUZZER_PIN D5     // Pino D5 para o buzzer
#define RED_LED_PIN D6    // Pino D6 para o LED vermelho
#define GREEN_LED_PIN D7  // Pino D7 para o LED verde

#define BLYNK_TEMPLATE_ID "TMPL2pU_EoXnf"
#define BLYNK_TEMPLATE_NAME "Sensor de Gás "
#define BLYNK_AUTH_TOKEN "7q80GGkifjXvIeY3AvEgRFdjt0CoRe1V"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Informações da rede Wi-Fi
char ssid[] = "333333"; // Nome da rede Wi-Fi
char password[] = "3333";   // Senha da rede Wi-Fi

void setup()
{
  pinMode(GAS_SENSOR_PIN, INPUT);   // Configura o pino do sensor de gás como entrada
  Serial.begin(9600);               // Inicia a comunicação serial
  pinMode(BUZZER_PIN, OUTPUT);      // Configura o pino do buzzer como saída
  pinMode(RED_LED_PIN, OUTPUT);     // Configura o pino do LED vermelho como saída
  pinMode(GREEN_LED_PIN, OUTPUT);   // Configura o pino do LED verde como saída

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicializa o Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop()
{
  Blynk.run(); // Chama a função Blynk

  int sensorValue = analogRead(GAS_SENSOR_PIN);  // Leitura do valor do sensor de gás
  Serial.print("Valor do Gás: ");                // Imprime o valor no monitor serial
  Serial.println(sensorValue);

  // Ajuste o limite do gás para 512 (equivalente ao valor analógico)
  if (sensorValue >= 5) {  
    // Aciona o LED vermelho e o buzzer quando o limite for ultrapassado
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    // Piscar o LED vermelho e buzzer
    delay(1000);  // Espera 1 segundo
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW); 
    delay(1000);  // Espera mais 1 segundo
  } 
  else {
    // Aciona o LED verde quando o nível estiver normal
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  // Aguarda 500 ms antes da próxima leitura
}
