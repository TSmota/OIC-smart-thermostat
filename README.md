# Termostato Inteligente
Projeto desenvolvido para auxiliar pessoas com deficiência de locomoção e/ou deficiência de funções motoras que estejam internados em hospitais ou até mesmo em casa no controle do ar-condicionado.  
O sensor LM35 é o responsável por verificar a temperatura ambiente, a partir dessa informação o NodeMCU envia um comando para o ar-condicionado utilizando o LED emissor de infravermelho. O comando que será enviado irá depender da temperatura ambiente atual e das configurações feitas no broker MQTT.

# Componentes Utilizados
- [**NodeMCU ESP8266-12 V2** ](https://www.robocore.net/loja/iot/nodemcu-esp8266-12-v2): Placa NodeMCU com módulo WiFi ESP8266 já incluso.
- [**Sensor LM-35**](https://www.robocore.net/loja/sensores/sensor-de-temperatura-lm35): Sensor utilizado para medir a temperatura com precisão.
- [**LED Emissor Infravermelhor 5mm IR333C**](https://www.robocore.net/loja/itens-eletronicos/kit-receptor-e-emissor-ir-5mm): Atuador utilizado para enviar os comandos ao ar condicionado.
- [**Protoboard 400 Pontos**](https://www.robocore.net/loja/protoboard/protoboard-400-pontos): Possui 2 barramentos para alimentação, 30 colunas e 10 linhas - um total de 400 pontos. Todos os pinos estão espaçados pelo padrão de 0,1". O espaçamento no meio é perfeito para componentes do tipo DIP. A protoboard aceita fios de 29AWG até 20AWG.
- [**7 Jumpers M/M**](https://www.robocore.net/loja/cabos-conectores/jumper-premium-macho-macho-20cm): Jumpers necessários para conectar os componentes.

# Bibliotecas utilizadas
- [**ESP8266Wifi**](https://github.com/ekstrand/ESP8266wifi): Biblioteca utilizada para poder conectar a placa de desenvolvimento (NodeMCU) à rede wifi.
- [**PubSubClient**](https://github.com/knolleary/pubsubclient): Biblioteca que permite a comunicação através do protocolo MQTT.
- [**IRremoteESP8266**](https://github.com/crankyoldgit/IRremoteESP8266): Biblioteca que permite o envio e recebimento de sinais infravermelhos com o ESP8266 e um led 940nm comum.

# Interfaces e protocólos
- **Desenvolvimento:** A IDE utilizada para programar e gravar o código no NodeMCU foi a **Arduino IDE**.
- **Comunicação:** Para realizar a comunicação via Internet foi utilizado o protocólo MQTT.
- **Visualização e Controle de Parâmetros:** Para visualização das informações publicadas pelo programa e alteração dos parâmetros utilizados no código foi utilizado o broker público do [Mosquitto](https://mosquitto.org/).

# Diagrama do circuito
![Diagrama do circuito do termostato inteligente](https://github.com/TSmota/OIC-smart-thermostat/blob/master/diagrama.png)

# Como fazer
- Siga o tutorial encontrado [neste link](https://randomnerdtutorials.com/esp8266-and-node-red-with-mqtt/) para a configuração inicial do seu projeto (não é necessário um raspberri pi. o mosquitto pode ser instalando em sua máquina windows, clicando [aqui](https://mosquitto.org/));
- Baixe o arquivo "flows.json" e importe no node-red;
- Monte o seu circuito com base em nosso diagrama, utilizando os materiais informados;
- Baixe o arquivo "ac_temp_control.ino" e configure as credenciais de acesso ao wifi e o objeto de controle de ar condicioado, caso haja necessidade;
- Caso ocorram dúvidas sobre o código, [este vídeo](https://youtu.be/LxmnRRdBWjY) tem uma explicação do funcionamento de cada parte do código.

