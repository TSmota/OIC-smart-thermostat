# Termostato Inteligente
Projeto desenvolvido para a matéria de Objetos Inteligenets Conectados.

# Componentes Utilizados
- [**NodeMCU ESP8266-12 V2** ](https://www.robocore.net/loja/iot/nodemcu-esp8266-12-v2): Placa NodeMCU com módulo WiFi ESP8266 já incluso.
- [**Sensor LM-35**](https://www.robocore.net/loja/sensores/sensor-de-temperatura-lm35): Sensor utilizado para medir a temperatura com precisão.
- [**LED Emissor Infravermelhor 5mm IR333C**](https://www.robocore.net/loja/itens-eletronicos/kit-receptor-e-emissor-ir-5mm): Atuador utilizado para enviar os comandos ao ar condicionado.
- [**2 Protoboards 400 Pontos**](https://www.robocore.net/loja/protoboard/protoboard-400-pontos): Possui 2 barramentos para alimentação, 30 colunas e 10 linhas - um total de 400 pontos. Todos os pinos estão espaçados pelo padrão de 0,1". O espaçamento no meio é perfeito para componentes do tipo DIP. A protoboard aceita fios de 29AWG até 20AWG.
- [**Jumper M/M**](https://www.robocore.net/loja/cabos-conectores/jumper-premium-macho-macho-20cm): Jumpers necessários para conectar os componentes.

# Bibliotecas utilizadas
- [**ESP8266Wifi**](https://github.com/ekstrand/ESP8266wifi): Biblioteca utilizada para poder conectar a placa de desenvolvimento (NodeMCU) à rede wifi. ESP8266Wifi
- [**PubSubClient**](https://github.com/knolleary/pubsubclient): Biblioteca que permite a comunicação através do protocolo MQTT. PubSubClient
- [**IRremoteESP8266**](https://github.com/crankyoldgit/IRremoteESP8266): Biblioteca que permite o envio e recebimento de sinais infravermelhos com o ESP8266 e um led 940nm comum.

# Interfaces e protocólos
- **Desenvolvimento:** A IDE utilizada para programar e gravar o código no NodeMCU foi a **Arduino IDE**.
- **Comunicação:** Para realizar a comunicação via Internet foi utilizado o protocólo MQTT.
- **Visualização e Controle de Parâmetros:** Para visualização das informações publicadas pelo programa e alteração dos parâmetros utilizados no código foi utilizado o broker público do [Mosquitto](https://mosquitto.org/).
