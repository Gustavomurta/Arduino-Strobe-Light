/*
  Arduino Nano Strobe Light - Arduino Estroboscópio
  
 CRIADO POR: GUSTAVO MURTA
 DATA: 18/04/2014
 USANDO ARDUINO NANO - IDE Versão 1.05
 E-MAIL: jgustavoam@gmail.com
 Permitido o uso público, mas devem-se manter os nomes dos autores.
 
 A tensão lida no Potenciometro é usada para ajustar a frequência do Estroboscópio.
 O valor da frequência definida é enviada via serial para o Monitor da IDE.
 
 Montagem do Circuito:
 * Conecte um potenciometro de 10K ohms no Pino Analog 0 (A0).
   O pino central deve estar ligado ao Pino A0.
   Os outros pinos do Pot devem estar ligados ao +5V e ao terra.
   Os LEDs da lanterna deven estar ligados assim:
   - fio vermelho e laranja ao +5V (Anodos dos LEDs)
   - fio marrom ao Dreno do FET
   O gate do FET deve estar ligado ao Pino Digital D12
   
 Baseado no projeto de Steve Krave:
 http://mehax.blogspot.com.br/2011/02/arduino-stroboscope.html
 
 */

// Definição da Constante

 const int pino_analog = A0;          // Pino analogico conectado o pino central do Potenciometro

// Definição das variáveis 

 float valor_sensor = 1;              // Valor lido do Potenciometro = 0 a 1023
 float pulso_strobe = 1;              // Pulso do Estroboscopio
 unsigned long micros_previo = 0;     // Variável para contagem de Tempo     
 unsigned long micros_corrente = 0;   // Também usada para contagem de Tempo 
 unsigned long millis_serial =0;      // Usada para atraso - Rotina de envio dos dados para a Serial 
 float frequencia = 1;                // Frequencia 
 int rpm = 0;                         // rpm
 
void setup()
{
  Serial.begin(115200);              // Inicializa o Monitor Serial com 115200 Baud
  pinMode(12, OUTPUT);               // Configura Pino Digital 12 como saída  
}

void loop()
{  
  valor_sensor = analogRead(pino_analog);      // Mede o valor do potenciometro = 0 a 1023
  pulso_strobe = valor_sensor*54 + 400;        // Duração do Pulso estroboscopio > Método empírico
  
  micros_corrente = micros();                  // Coleta o tempo corrente do Timer 
  
  if (micros_corrente > micros_previo + pulso_strobe)    // Definição do tempo do laço
  {      
    micros_previo = micros_previo + pulso_strobe;        // atraso do Pulso estroboscopio

    digitalWrite(12,HIGH);                     // Acende os LEDs    
    delayMicroseconds(200);                    // Duração de tempo do pulso de Luz em microsegundos, varie se desejar
    digitalWrite(12,LOW);                      // Apaga os LEDs 
    
    if(millis() > millis_serial + 500)         //  Atraso de tempo de 500 milisegundos
    { 
      millis_serial=millis();   
      
      frequencia = 1000000/pulso_strobe;       // Calculo da Frequencia   
      rpm = frequencia * 60;                   // Calculo do RPM 
        
      Serial.print("  Freq = " );              // Envia para o Monitor Serial o valor da Frequencia e do RPM                  
      Serial.print(frequencia);      
      Serial.print("  RPM = ");      
      Serial.println(rpm);  }
     }
   }
 


 
