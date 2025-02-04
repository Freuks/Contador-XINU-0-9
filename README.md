# Contador XINU 0.9 🚀  

Este projeto implementa um **contador utilizando Xinu e um LED Matrix em um Arduino Uno**. O código aproveita os recursos do **Xinu OS**, como **processos concorrentes, semáforos e gerenciamento de tempo**, garantindo um funcionamento otimizado e estruturado.  

## 📌 Funcionalidades  
✅ Exibição de números de **0 a 9** no **LED Matrix**  
✅ Utilização de **processos** para exibição independente dos números  
✅ **Sincronização com semáforos** para evitar conflitos na execução  
✅ Uso do **sleep()** do Xinu para um melhor gerenciamento de tempo  
✅ Manipulação de **GPIO** utilizando a biblioteca `avr_gpio.h`  
✅ Alternância do estado de um **LED indicador** durante a contagem  

## 🛠️ Tecnologias Utilizadas  
- **Xinu OS**  
- **Arduino Uno**  
- **Linguagem C**  
- **Biblioteca avr_gpio.h**  
- **Simulação com PicSimLab**  

## 🖥️ Simulação com PicSimLab  
Para testar e validar o funcionamento do código, utilizei o **[PicSimLab](https://github.com/lcgamboa/picsimlab)**, um **simulador de microcontroladores** desenvolvido por **Gamboa**. Esse simulador permite testar projetos **Arduino**, **PIC**, entre outros, sem a necessidade de um hardware físico. 
