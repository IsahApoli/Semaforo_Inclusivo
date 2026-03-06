# Semaforo_Inclusivo
🚦 Sistema de Semáforo Inteligente com Acessibilidade
📌 Sobre o Projeto

Este projeto tem como objetivo desenvolver um semáforo inteligente para pedestres e veículos, utilizando a plataforma Arduino, com foco em acessibilidade, segurança e adaptação ao fluxo de pessoas.

A proposta vai além de um semáforo convencional: o sistema é capaz de detectar a presença de pedestres por meio de um sensor ultrassônico e ajustar automaticamente o tempo de travessia, garantindo mais segurança, especialmente para idosos e pessoas com mobilidade reduzida. Além disso, conta com um buzzer que emite sinais sonoros durante a travessia, auxiliando pessoas com deficiência visual a identificarem o momento seguro para atravessar.

🎯 Propósito do Trabalho

O principal propósito deste trabalho é:

✔ Desenvolver um sistema embarcado funcional
✔ Aplicar conceitos de programação com controle de tempo usando millis()
✔ Implementar máquina de estados (controle por fases)
✔ Tornar o sistema adaptativo e inclusivo
✔ Integrar sensores e atuadores em um único projeto

Além do aprendizado técnico, o projeto propõe uma solução tecnológica com impacto social, promovendo maior segurança na travessia de pedestres.

⚙️ Funcionamento do Sistema

O semáforo opera em três estados principais:
🚗 1. Carro Verde
Veículos podem trafegar
Pedestres aguardam
O sistema pode mudar automaticamente após 15 segundos, por acionamento do botão ou detecção do sensor

🚦 2. Carro Amarelo
Indica atenção
Dura 2 segundos antes de fechar para veículos

🚶 3. Fase do Pedestre
Veículos param (vermelho)
Pedestres atravessam (verde)
Display de 7 segmentos realiza contagem regressiva
Buzzer emite sinal sonoro

💡 Diferencial Inteligente:
Se o sensor detectar que ainda há alguém na faixa nos últimos segundos da contagem, o sistema adiciona automaticamente tempo extra para que a travessia seja concluída com segurança.

Após isso, o sistema reinicia o ciclo normalmente.

🧩 Componentes Utilizados

1 Arduino Uno R3
2 LEDs Vermelhos
1 LED Amarelo
2 LEDs Verdes
1 Botão
6 Resistores de 500 Ω
1 Resistor de 1 kΩ
1 Buzzer (Piezo)
1 Display de 7 segmentos (cátodo comum)
1 Decodificador CD4511 (para controle do display)
1 Sensor de distância ultrassônico (4 pinos)

🧠 Conceitos Aplicados

Programação em C++ para Arduino
Controle de tempo com millis()
Máquina de estados
Debounce para botão
Leitura de sensor ultrassônico
Lógica condicional adaptativa
Controle de display com decodificador

👩‍💻👨‍💻 Participantes

Cauã Oliveira
Giovanna Bruna
Giovanna Franguelli
Isabella Apolinario
Julia Pereira

🌟 Conclusão

O projeto demonstra a aplicação prática de sistemas embarcados na solução de problemas reais.

Além de integrar múltiplos componentes eletrônicos e lógica de programação, o sistema promove acessibilidade e segurança urbana, mostrando como a tecnologia pode ser utilizada para criar ambientes mais inclusivos e inteligentes.
