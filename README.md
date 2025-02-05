# Temporizador de Um Disparo (One Shot) - Raspberry Pi Pico W

## Descrição

Este projeto foi desenvolvido para a atividade de temporização utilizando a plataforma Raspberry Pi Pico W. O sistema aciona LEDs em uma sequência, controlada pelo pressionamento de um botão (pushbutton), com um temporizador configurado para um atraso de 3 segundos entre as transições dos LEDs. A sequência de LEDs consiste em três estados:

1. Todos os LEDs acesos.
2. Dois LEDs acesos.
3. Um LED aceso.

Após a conclusão da sequência, o sistema retorna ao estado inicial e aguarda o próximo pressionamento do botão.

## Componentes

- 1x Raspberry Pi Pico W
- 3x LEDs (Azul, Vermelho e Verde)
- 3x Resistores de 330Ω
- 1x Botão (Pushbutton)

## Requisitos da Tarefa

1. **Pressionamento do Botão:** Ao pressionar o botão, os três LEDs são ligados, e a sequência de LEDs ocorre de acordo com o temporizador configurado.
2. **Temporizador de 3 segundos:** A cada 3 segundos, a sequência de LEDs muda, desligando um LED por vez.
3. **Funções Call-back:** A mudança de estado dos LEDs ocorre em funções de call-back associadas ao temporizador.
4. **Debouncing do Botão:** Implementação de software para atenuação do efeito de "bouncing" do botão.
5. **Segurança:** O botão só pode alterar o estado dos LEDs quando o último LED for desligado, evitando múltiplas mudanças de estado enquanto a sequência está em andamento.

## Funcionamento do Sistema

- **Inicialização:** Ao pressionar o botão pela primeira vez, todos os LEDs (azul, vermelho e verde) são ligados simultaneamente.
- **Sequência dos LEDs:** A cada 3 segundos, a sequência de LEDs será alterada:
  - Primeiro, todos os LEDs acesos.
  - Depois, o LED azul será desligado, deixando apenas os LEDs vermelho e verde acesos.
  - Em seguida, o LED vermelho será desligado, deixando apenas o LED verde aceso.
- **Desligamento Completo:** Após a última transição (com o LED verde apagado), a sequência é reiniciada e o sistema aguarda o próximo pressionamento do botão.

### Funcionamento do Debouncing

A função `debounce_button` é responsável por evitar que o efeito de "bouncing" do botão interfira no comportamento do sistema. Ela garante que o botão só será processado como pressionado se a mudança de estado for confirmada após um pequeno atraso.
