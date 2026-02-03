# Irrigação Autônoma

Este projeto, desenvolvido em colaboração com os alunos da 1ª série do Ensino Médio da Escola Parque, visa trazer uma alternativa sustentável à irrigação de plantas, baseando-se nos níveis de umidade do solo em que a planta se encontra. Foi desenvolvido para a plataforma **Arduino Uno**.

[Anexar foto]

## Configurações de Hardware

O sistema utiliza um sensor de umidade analógico para monitoramento e um módulo relé para o controle da bomba d'água.

| Componente | Pino Arduino | Descrição Técnica |
| :--- | :--- | :--- |
| **Sensor de Umidade** | A0 | Entrada analógica (Sinal de 0 a 1023) |
| **Módulo Relé** | D8 | Saída digital para controle de acionamento |
| **Alimentação Bomba** | 5V | Alimentação via barramento de corrente contínua |

---

## Funcionamento do Código

### Setup

* `Serial.begin(9600);`
    Estabelece a taxa de transmissão de dados para o monitoramento via terminal.
* `pinMode(RELAY_PIN, OUTPUT);`
    Configura o pino digital 8 como uma saída de sinal.
* `digitalWrite(RELAY_PIN, LOW);`
    Garante que o relé (e a bomba) inicie em estado desligado.

### Loop

* `analogRead(ANALOG_PIN);`
    Lê a tensão no pino A0 e converte em um valor numérico entre 0 e 1023.
* `map(sensor_data, 1023, 0, 0, 100);`
    Converte a leitura bruta em uma escala percentual, onde 1023 representa solo seco (0%) e 0 representa solo saturado (100%).
* `if(moisture <= threshold)`
    Compara a umidade atual com o limite de 45%. Se for menor ou igual, o pino do relé é alterado para `HIGH` (ligado). Caso contrário, permanece em `LOW` (desligado).
* `delay(5000);`
    Interrompe a execução por 5 segundos antes de iniciar a próxima leitura.

---

## Nota sobre Visualização de Dados

Atualmente, o sistema envia dados brutos via porta serial. **Ainda é necessário desenvolver uma forma de visualizar melhor as informações no terminal.** A implementação atual utiliza concatenações que podem apresentar falhas de legibilidade ou erros na IDE do Arduino. Recomenda-se a revisão de `Serial.print()` para garantir que cada informação seja mostrada de forma sequencial e clara, para evitar sobreposição de caracteres ou símbolos ilegíveis.

---

## Otimizações Futuras

Para a evolução do projeto, pode-se implementar o seguinte:

1.  **Histerese:** Implementar uma margem de segurança no limiar (ex: ligar em 45% e desligar apenas em 55%) para evitar o acionamento intermitente da bomba (*chattering*).
2.  **Média:** Realizar múltiplas leituras do sensor e calcular a média aritmética para filtrar ruídos elétricos.
3.  **Interface LCD:** Adicionar um display I2C para visualização local sem necessidade de computador.
4.  **Economia de Bateria:** Implementar modos de economia de energia caso o sistema venha a operar por baterias.
5.  **Calibração de Solo:** Criar uma rotina de calibração para definir os limites reais de "seco" e "úmido" baseados no solo específico.
