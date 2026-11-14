# Saint-Grail-s-Quest
Projeto de RPG de mesa desenvolvido em C (struct, enum e ponteiros), ambientado nas lendas do Rei Arthur e do Santo Graal.

**Aluno:** Marcos Paulo Florêncio da Silva  
**Matrícula:** 	20260015165  
**Disciplina:** DCT1106 - Programação (BSI / UFRN)
**Período Letivo:** 2026.2
**Professor:** Thommas K. S. Flores


## História

Nas terras antigas da Britânia, o nobre Rei Arthur governa a partir de sua majestosa fortaleza, **Camelot**. Embora sua coroa seja símbolo de justiça, sombras crescentes e forças sombrias rondam as fronteiras, ameaçando destruir tudo o que foi construído.

Diante da iminente guerra, o Rei reuniu seus mais leais e corajosos campeões ao redor da **Távola Redonda**, confiando a eles a mais sagrada das missões: partir pelo reino em busca do lendário **Santo Graal**. Dizem as antigas profecias que o cálice sagrado possui o poder de conceder qualquer desejo àquele que se provar digno. Com a bênção do Graal em mãos, o Rei e seus cavaleiros estarão prontos para marchar contra os inimigos poderosos que ameaçam a paz, a prosperidade e a honra do reino.


## Personagens

O jogador pode escolher entre **3 classes jogáveis**, cada uma com atributos base inspirados em RPGs de mesa, equipamentos próprios e uma habilidade especial exclusiva:

| **Guerreiro:** | HP: 110 | MP: 45 | FOR: 20 | DES: 10 | CON: 15 | INT: 5 | SAB: 10 | CAR: 10 | Espada / Armadura de Placa | **Golpe Pesado** (1.5x de dano)
| **Arqueiro:** | HP: 90 | MP: 60 | FOR: 10 | DES: 20 | CON: 10 | INT: 10 | SAB: 12 | CAR: 8 | Arco / Traje de Couro | **Tiro Triplo** (1.5x de dano)
| **Mago:** | HP: 50 | MP: 100 | FOR: 5 | DES: 10 | CON: 8 | INT: 20 | SAB: 12 | CAR: 15 | Cajado / Túnica Mágica | **Bola de Fogo** (1.5x de dano)

* **Status Derivados Iniciais:**
  * **Ataque:** $5 + (\text{Atributo Principal} \times 2)$ (Força para Guerreiro, Destreza para Arqueiro, Inteligência para Mago).
  * **Defesa:** $2 + \lfloor\text{Destreza} / 2\rfloor + \lfloor\text{Constituição} / 3\rfloor$.



## Fases e Monstros

A jornada é estruturada em **3 fases com dificuldade progressiva**, cada uma ambientada em uma região da lenda arturiana, com uma missão principal e 3 tipos de monstros distintos:

| **Fase 1** *(Fácil)* | **Reino de Logres** | **Ir à Camelot:** Atravessar a estrada perigosa e derrotar o guardião nos portões da capital. |
  • **Wyrm:** 40 HP / 15 ATK / 8 DEF / 10 XP• **Ninfa:** 25 HP / 15 ATK / 5 DEF / 10 XP• **Mímico:** 20 HP / 15 ATK / 10 DEF / 5 XP |
  
| **Fase 2** *(Média)* | **Castelo de Corbenic** | **Encontrar o Santo Graal:** Recuperar o Santo Graal na casa de missão antes de enfrentar o chefe. |
  • **Gemente:** 50 HP / 20 ATK / 15 DEF / 15 XP• **Jotunn:** 50 HP / 20 ATK / 25 DEF / 25 XP• **Dragão:** 70 HP / 30 ATK / 30 DEF / 30 XP |
  
| **Fase 3** *(Alta)* | **Planície de Salisbury** | **Vencer a guerra de Camlann:** Sobreviver ao caos e derrotar a ameaça suprema na Batalha de Camlann. |
  • **Cath Palug:** 50 HP / 40 ATK / 15 DEF / 30 XP• **Morgana:** 60 HP / 50 ATK / 25 DEF / 40 XP• **Mordred:** 80 HP / 60 ATK / 30 DEF / 50 XP |



## Dinâmica do Jogo

### Movimentação e Tabuleiro
* O tabuleiro de cada fase é representado por um vetor de **12 casas** (`0` a `11`).
* A cada turno de exploração, o jogador pressiona `ENTER` para lançar um dado de 6 faces (**d6**), avançando de 1 a 6 casas.
* Os limites do tabuleiro são tratados automaticamente: caso a soma ultrapasse o final da trilha, o herói para exatamente na casa `11` (`[C]`).

### Eventos nas Casas
Ao parar em uma casa, um dos seguintes eventos é disparado:
* **Casa Vazia (`CASA_VAZIA`):** Caminho tranquilo, nenhum evento ocorre.
* **Combate (`CASA_INIMIGO`):** Um monstro compatível com a dificuldade da fase é sorteado para batalhar.
* **Tesouro (`CASA_TESOURO`):** Concede imediatamente um bônus aleatório permanente de atributo.
* **Descanso (`CASA_DESCANSO`):** Restaura 100% da Vida (`vidaAtual`) e da Mana (`manaAtual`) do herói.
* **Missão (`CASA_MISSAO`):** Posicionada na metade do tabuleiro da Fase 2; permite coletar o **Santo Graal**, requisito obrigatório para liberar o duelo contra o chefe da segunda fase.
* **Chefe (`CASA_CHEFE`):** Localizada na última casa (`11`); derrotar o chefe conclui a missão e avança para a próxima fase (ou encerra o jogo na Fase 3).

### Sistema de Combate por Turnos e Fórmulas
O combate alterna entre o **Turno do Jogador** e o **Turno do Monstro** até que a vida de um dos combatentes chegue a zero ou ocorra fuga:
1. **Atacar:** Aplica dano calculado pela fórmula $\text{Dano} = \max(1, \text{Ataque} - \lfloor\text{Defesa} / 2\rfloor)$.
2. **Defender:** O herói assume postura defensiva, reduzindo o dano do próximo ataque do monstro pela metade ($\text{Dano} / 2$).
3. **Usar Habilidade Especial:** Consome Mana para desferir um golpe especial com multiplicador de `1.5x` sobre o ataque.
4. **Tentar Fugir:** Rola um **d20** somado a $\lfloor\text{Destreza} / 3\rfloor$. Se o resultado for **$\ge 12$**, o jogador escapa do combate sem receber recompensas.

### Recompensas, Evolução e Condições de Fim de Jogo
* **Bônus de Vitória:** Ao vencer um inimigo comum ou abrir um baú, o jogador recebe um bônus aleatório (+1 em Força, Destreza, Inteligência ou +5 em HP Máximo).
* **Subida de Nível (Level Up):** A meta inicial é de `25 XP` (aumentando em `1.5x` a cada nível). Ao subir de nível, o herói recebe **+12 pontos distribuídos** entre seus atributos conforme a classe, recalcula ataque e defesa, e restaura toda a vida e mana.
* **Vitória:** Cumprir as missões das 3 fases e derrotar o chefe final na Batalha de Camlann.
* **Derrota (Game Over):** Ocorre quando a vida do herói (`vidaAtual`) chega a `0`.



## Estrutura do Código

O projeto foi implementado em **Linguagem C (padrão C99)** utilizando exclusivamente bibliotecas padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h` e `math.h`):

* **Enumerações (`enum`):** `TipoClasse`, `TipoCasa`, `DificuldadeInimigo`, `TipoInimigo` e `ResultadoCombate` garantem legibilidade e eliminam "números mágicos".
* **Estruturas (`struct`):** `Classe`, `Personagem`, `InimigoBase`, `Inimigo`, `Mapa` e `Fase` modelam as entidades e regras do jogo.
* **Uso de Ponteiros:** Funções como `atribuirClasse`, `aplicarBonusClasse`, `aplicarBonusAleatorio`, `ganharExperiencia`, `moverJogador`, `avancarMapa`, `eventoCasa` e `iniciarCombate` recebem ponteiros para as estruturas (`Personagem *p`, `Inimigo *m`, `Mapa *m`), atualizando os dados diretamente na memória.



## Como Compilar e Jogar

### Pré-requisitos
* Compilador **GCC** instalado.

### Linux / macOS
1. Abra o terminal na pasta raiz do projeto.
2. Compile o código-fonte:
   ```bash
   gcc -Wall -Wextra src/rpg_3.c -o jogo -lm

### Windows (MinGW / PowerShell / CMD)
1. Compile o código-fonte:
   ``gcc -Wall -Wextra src/rpg_3.c -o jogo.exe -lm``
2. Execute o jogo:
   ``jogo.exe``
