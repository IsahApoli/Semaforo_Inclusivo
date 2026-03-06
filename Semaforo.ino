// Controle Led Carro
int carRed = 12;    
int carYellow = 11;
int carGreen = 10;

// Controle Led Pedestre
int pedRed = 9;     
int pedGreen = 8;

// Botão
int button = 2;  

// Som (buzzer)
int Som = 13;       

// Pinos CD4511
int PinoA0 = 4;     
int PinoA1 = 5;
int PinoA2 = 6;
int PinoA3 = 7;

// 15s verde automático
unsigned long changeTime = 0;
unsigned long tempoVerde = 25000;
unsigned long tempoAnterior = 0;

int estadoSemaforo = 0;

int contador = 9;                 // começa em 9
unsigned long tempoDisplay = 0;

int etapaPedestre = 0;            // controla fases internas
unsigned long tempoPisca = 0;
unsigned long tempoPiscaBlink = 0;
bool estadoPedestrePisca = HIGH  ;   // Controla o estado do LED durante o pisca

// Debounce / clique
unsigned long ultimoClique = 0;
const unsigned long debounceMs = 200;
int ultimoEstadoBotao = HIGH;     // INPUT_PULLUP: solto = HIGH, apertado = LOW

//contador extra - semaforo idosos
bool tempoExtraAdicionado = false;   // evita adicionar várias vezes
const int distanciaFaixa = 10;       // largura simulada da faixa
const int tempoExtra = 5;            // segundos extras

int trig_pin = 1;
int echo_pin = 3;
float timing = 0.0;
float distance = 0.0;

unsigned long tempoUltrassom = 0;
const unsigned long intervaloUltrassom = 100; // mede a cada 100ms

void setup() {
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);

  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);

  pinMode(Som, OUTPUT);

  pinMode(button, INPUT_PULLUP); // usando pullup interno

  pinMode(PinoA0, OUTPUT);
  pinMode(PinoA1, OUTPUT);
  pinMode(PinoA2, OUTPUT);
  pinMode(PinoA3, OUTPUT);

  changeTime = millis(); // inicia a contagem dos 15s
  
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
}

void loop() {
  unsigned long agora = millis();

  lerUltrassom();

  // ----------- LEITURA DO BOTÃO -----------
  int estadoBotao = digitalRead(button);

  bool clique = false;
  if (ultimoEstadoBotao == HIGH && estadoBotao == LOW) {
    if (agora - ultimoClique > debounceMs) {
      ultimoClique = agora;
      clique = true;
      
      // Beep de confirmação do botão
      tone(Som, 2000, 100);
    }
  }
  ultimoEstadoBotao = estadoBotao;

  // ----------- CONDIÇÕES DE TROCA -----------
  bool tempoAutomatico = (agora - changeTime >= tempoVerde);
  bool botaoPressionado = (clique && (agora - changeTime > 10000));
  bool sensorDetectou = (distance > 0 && distance < 10 && (agora - changeTime > 10000));

  if (estadoSemaforo == 0 && 
     (tempoAutomatico || botaoPressionado || sensorDetectou)) {

    estadoSemaforo = 1;
    tempoAnterior = agora;
  }

  changeLights();
}

void mostrarNumero(int numero) {
  digitalWrite(PinoA0, bitRead(numero, 0));
  digitalWrite(PinoA1, bitRead(numero, 1));
  digitalWrite(PinoA2, bitRead(numero, 2));
  digitalWrite(PinoA3, bitRead(numero, 3));
}

void lerUltrassom() {
  if (millis() - tempoUltrassom >= intervaloUltrassom) {
    tempoUltrassom = millis();

    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    timing = pulseIn(echo_pin, HIGH, 30000); // timeout 30ms
    distance = timing * 0.034 / 2.0;
  }
}

void changeLights() {
  unsigned long agora = millis();
  
  switch (estadoSemaforo) {

    case 0: // Carro verde
      digitalWrite(carGreen, HIGH);
      digitalWrite(carYellow, LOW);
      digitalWrite(carRed, LOW);

      digitalWrite(pedRed, HIGH);
      digitalWrite(pedGreen, LOW);
      break;

    case 1: // Amarelo por 3s
      digitalWrite(carGreen, LOW);
      digitalWrite(carYellow, HIGH);
      digitalWrite(carRed, LOW);

      digitalWrite(pedRed, HIGH);
      digitalWrite(pedGreen, LOW);

      if (agora - tempoAnterior >= 3000) {
        tempoAnterior = agora;
        estadoSemaforo = 2;

        contador = 9;
        mostrarNumero(contador);
        tempoDisplay = agora;

        etapaPedestre = 0;
        estadoPedestrePisca = LOW; // Garante estado inicial
      }
      break;

    case 2: // Fase pedestre
      digitalWrite(carGreen, LOW);
      digitalWrite(carYellow, LOW);
      digitalWrite(carRed, HIGH);
  
      digitalWrite(pedRed, LOW);
  
      // Display 7 segmentos 
      if (etapaPedestre == 0) {
        digitalWrite(pedGreen, HIGH);  // Verde aceso durante contagem

        if (agora - tempoDisplay >= 1000) {
          tempoDisplay = agora;

          mostrarNumero(contador);
          tone(Som, 1000, 100);

          // Diminui primeiro
          contador--;

          // Se estiver nos últimos 2 segundos
          if (contador <= 2 && !tempoExtraAdicionado) {

            // Se detectar alguém na faixa
            if (distance > 0 && distance <= distanciaFaixa) {

              contador += tempoExtra;      
              tempoExtraAdicionado = true; 
            }
          }

          if (contador < 0) {
            contador = 0;
            etapaPedestre = 1;
            tempoPisca = agora;
            tempoPiscaBlink = agora;
            estadoPedestrePisca = LOW;  // Começa com LED apagado
            
            // *** CORREÇÃO: DESLIGA O VERDE AO INICIAR O PISCA ***
            digitalWrite(pedGreen, LOW);  // <-- APAGA O VERDE
                
            noTone(Som);
          }
        }
      }

      // LED PEDESTRE PISCANDO
      if (etapaPedestre == 1) {
        // Garante que o verde continua apagado
        digitalWrite(pedGreen, LOW);
        
        // Controla o pisca-pisca a cada 200ms
        if (agora - tempoPiscaBlink >= 200) {
          tempoPiscaBlink = agora;
          
          // Inverte o estado do LED usando variável de controle
          estadoPedestrePisca = !estadoPedestrePisca;
          digitalWrite(pedRed, estadoPedestrePisca);
          
         
          if (estadoPedestrePisca == HIGH) {
            tone(Som, 2000, 50);
          }
        }

        // Após 3 segundos de pisca, volta ao normal
        if (agora - tempoPisca >= 3000) {
          digitalWrite(pedGreen, LOW);  // Garante apagado
          digitalWrite(pedRed, HIGH);   // Termina aceso

          estadoSemaforo = 0;
          changeTime = agora; // reinicia os 15s do verde
          etapaPedestre = 0;
          contador = 9;
          tempoExtraAdicionado = false;
          estadoPedestrePisca = LOW;   // Reseta para próxima vez
          noTone(Som);
        }
      }
      break;
  }
}
