/*
* Projeto Irrigador Autônomo - Versão 5V
* Sensor de umidade no pino A0;
* Relé no pino D8;
* bomba alimentada pelo pino 5V do Arduino;
*/

// definindo pinagem
#define ANALOG_PIN A0
#define RELAY_PIN 8

void setup() {
  // pino relé como saída
  pinMode(RELAY_PIN, OUTPUT);

  // inicia o relé como DESLIGADO (LOW)
  // obs: alguns módulos relé ativam com LOW. Se a bomba
  // ligar ao invés de desligar, inverta HIGH e LOW no código
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // 1. leitura do sensor (entre 0 e 1023 -> 2^10)
  int sensor_data = analogRead(ANALOG_PIN);

  // 2. mapeia a leitura para porcentagem (0-100%)
  // obs: 1023 (seco) = 0% umidade; 0 (na água) = 100% umidade
  int moisture = map(sensor_data, 1023, 0, 0, 100);

  // 3. limiar para irrigação
  int threshold = 45; // irrigar se limiar <= 45%

  // 4. condicional
  if(moisture <= threshold){
    digitalWrite(RELAY_PIN, HIGH);
  }
  else{
    digitalWrite(RELAY_PIN, LOW);
  }

  // 5. delay de leitura
  delay(1000);
}
