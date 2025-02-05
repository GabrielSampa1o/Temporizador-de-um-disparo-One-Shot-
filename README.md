# 💡 Sequência de LEDs com Botão - Raspberry Pi Pico

## 📌 Descrição do Projeto
Este projeto permite **acender e apagar LEDs em sequência** utilizando um **botão** para ativar o ciclo. O código foi desenvolvido para a **Raspberry Pi Pico**, garantindo o controle correto por meio de **timers** e **debounce**.

## 🛠️ Componentes Utilizados
- **Raspberry Pi Pico**
- **LEDs**:
  - LED **Azul** (GPIO 12)
  - LED **Vermelho** (GPIO 13)
  - LED **Verde** (GPIO 11)
- **Botão de Acionamento** (GPIO 5)

## 📜 Estrutura do Código

### 🔹 `main.c`
- Monitora o **botão** e inicia a sequência ao ser pressionado.
- Usa **timers** para desligar os LEDs **automaticamente**.

### 🔹 Funções principais:
- **`monitor_button()`** → Detecta o pressionamento do botão.
- **`cb_start_sequence()`** → Inicia a sequência de LEDs.
- **`cb_turn_off_green()`**, **`cb_turn_off_blue()`**, **`cb_turn_off_red()`** → Apagam os LEDs após tempos programados.

## ⚡ Configuração do Hardware

| Componente | GPIO |
|------------|------|
| **LED Azul** | 12 |
| **LED Vermelho** | 13 |
| **LED Verde** | 11 |
| **Botão** | 5 |


## Como Compilar e Rodar
### **1. Instale o Raspberry Pi Pico SDK**
Siga as instruções oficiais do SDK:
https://github.com/raspberrypi/pico-sdk

### **2. Clone este repositório**
```sh
    git clone https://github.com/GabrielSampa1o/Controle-de-Interrup-es-e-LEDs-WS2812-na-Raspberry-Pi-Pico-W.git
    cd Controle-de-Interrup-es-e-LEDs-WS2812-na-Raspberry
```

### **3. Abra o VS Code** e **importe o projeto**:
   - Vá até a **Extensão Raspberry Pi Pico**.
   - Selecione **Import Project**.
   - Escolha a pasta do repositório clonado.
   - Clique em **Import**.

### **4. Compilar o código**:
   - Utilize a opção de **Build** da extensão.

### **5. Carregue o binário na Pico**
1. Pressione e segure o **botão BOOTSEL** da Raspberry Pi Pico W.
2. Conecte-a ao PC via **USB**.
3. Copie o arquivo `.uf2` gerado para a unidade montada.

## 🎮 Como Usar
1. **Pressione o botão** para ativar a sequência:
   - O LED **Verde** acende e apaga após **3s**.
   - O LED **Azul** acende e apaga após **6s**.
   - O LED **Vermelho** acende e apaga após **9s**.
2. **O botão só responde novamente após o ciclo terminar.**

## 📈 Possíveis Melhorias
- Usar **interrupções (IRQ)** para otimizar o desempenho.
- Criar **novos padrões de iluminação**.
- Adicionar **suporte a PWM** para transições suaves nos LEDs.

## 👨‍💻 Autor
- **[Gabriel Silva Sampaio]**


