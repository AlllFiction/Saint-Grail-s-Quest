#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAMANHO_MAPA 12
#define TOTAL_FASES 3


typedef enum {
	CLASSE_GUERREIRO,
	CLASSE_ARQUEIRO,
	CLASSE_MAGO,
	TOTAL_CLASSES
} TipoClasse;

typedef enum {
	CASA_VAZIA,
	CASA_INIMIGO,
	CASA_TESOURO,
	CASA_ARMADILHA,
	CASA_DESCANSO,
	CASA_MISSAO,
	CASA_CHEFE
} TipoCasa;

typedef enum {
	DIFICULDADE_FACIL,
	DIFICULDADE_MEDIA,
	DIFICULDADE_ALTA,
	TOTAL_DIFICULDADES
} DificuldadeInimigo;

typedef enum {
	INIMIGO_WYRM,
	INIMIGO_NINFA,
	INIMIGO_GEMENTE,
	INIMIGO_DRAGAO,
	INIMIGO_JOTUNN,
	INIMIGO_MIMICO,
	INIMIGO_CATH_PALUG,
	INIMIGO_FADA_MORGANA,
	INIMIGO_MORDRED,
	TOTAL_INIMIGOS
} TipoInimigo;

typedef enum {
	RESULTADO_VITORIA,
	RESULTADO_DERROTA,
	RESULTADO_FUGA
} ResultadoCombate;



typedef struct {
	char nome[20];
	int vidaBase;
	int manaBase;
	int forcaBase;
	int destrezaBase;
	int constituicaoBase;
	int inteligenciaBase;
	int sabedoriaBase;
	int carismaBase;
	char armaInicial[30];
	char armaduraInicial[30];
} Classe;

typedef struct {
	char nome[20];
	TipoClasse classeId;
	int zonaAtual;
	int posicao;
	int nivel;
	int experienciaAtual;
	int experienciaProximoNivel;
	int vidaAtual;
	int vidaMaxima;
	int manaAtual;
	int manaMaxima;
	int forca;
	int destreza;
	int constituicao;
	int inteligencia;
	int sabedoria;
	int carisma;
	int ataque;
	int defesa;
	char arma[30];
	char armadura[30];
	int missaoCumprida;
} Personagem;

typedef struct {
	char nome[20];
	DificuldadeInimigo dificuldade;
	int vidaBase;
	int ataqueBase;
	int defesaBase;
	int experienciaBase;
} InimigoBase;

typedef struct {
	char nome[20];
	DificuldadeInimigo dificuldade;
	int vidaAtual;
	int vidaMaxima;
	int ataque;
	int defesa;
	int experiencia;
} Inimigo;

typedef struct {
	TipoCasa trilha[TAMANHO_MAPA];
	DificuldadeInimigo dificuldadeZona;
} Mapa;

typedef struct {
	int numero;
	char nomeRegiao[40];
	char tituloMissao[50];
	char descricaoMissao[150];
	DificuldadeInimigo dificuldade;
} Fase;



const Classe TABELA_CLASSES[TOTAL_CLASSES] = {
	[CLASSE_GUERREIRO] = { "Guerreiro", 110, 45, 20, 10, 15, 5, 10, 10, "Espada", "Armadura de Placa"},

	[CLASSE_ARQUEIRO] = {"Arqueiro", 90, 60, 10, 20, 10, 10, 12, 8, "Arco", "Traje de Couro"},

	[CLASSE_MAGO] = {"Mago", 50, 100, 5, 10, 8, 20, 12, 15, "Cajado", "Túnica Mágica"}
};

const InimigoBase TABELA_INIMIGOS[TOTAL_INIMIGOS] = {
	[INIMIGO_WYRM] = {"Wyrm", DIFICULDADE_FACIL, 40, 15, 8, 10},
    [INIMIGO_NINFA] = {"Ninfa", DIFICULDADE_FACIL, 25, 15, 5, 10},
    [INIMIGO_MIMICO] = {"Mimico", DIFICULDADE_FACIL, 20, 15, 10, 5},
    [INIMIGO_GEMENTE] = {"Gemente", DIFICULDADE_MEDIA, 50, 20, 15, 15},
    [INIMIGO_JOTUNN] = {"Jotunn", DIFICULDADE_MEDIA, 50, 20, 25, 25},
    [INIMIGO_DRAGAO] = {"Dragao", DIFICULDADE_MEDIA, 70, 30, 30, 30},
    [INIMIGO_CATH_PALUG] = {"Cath Palug", DIFICULDADE_ALTA, 50, 40, 15, 30},
    [INIMIGO_FADA_MORGANA] = {"Morgana", DIFICULDADE_ALTA, 60, 50, 25, 40},
    [INIMIGO_MORDRED] = {"Mordred", DIFICULDADE_ALTA, 80, 60, 30, 50}
};

const Fase TABELA_FASES[TOTAL_FASES] = {
	[0] = {1, "Reino de Logres", "Ir à Camelot", "Atravesse a estrada perigosa e alcance os portões da capital Camelot.", DIFICULDADE_FACIL},
	[1] = {2, "Castelo de Corbenic", "Encontrar o Santo Graal", "Explore o castelo, recupere o Santo Graal e enfrente seu guardião.", DIFICULDADE_MEDIA},
	[2] = {3, "Planície de Salisbury", "Vencer a guerra de Camlann", "Sobreviva ao caos da guerra e derrote a ameaça suprema na Batalha de Camlann.", DIFICULDADE_ALTA}
};



void aguardarEnter(const char *mensagem) {
	printf("%s", mensagem);
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void exibirHistoriaIntroducao() {
    printf("\n====================================================================\n");
    printf("                  A LENDA DO SANTO GRAAL E CAMELOT                  \n");
    printf("====================================================================\n\n");

    printf("Nas terras antigas da Britânia, o nobre Rei Arthur governa a partir\n");
    printf("de sua majestosa fortaleza, Camelot. Embora sua coroa seja símbolo\n");
    printf("de justiça, sombras crescentes e forças sombrias rondam as fronteiras,\n");
    printf("ameaçando destruir tudo o que foi construído.\n");
    
    aguardarEnter("\n[Pressione ENTER para continuar...]");

    printf("\nDiante da iminente guerra, o Rei reuniu seus mais leais e corajosos\n");
    printf("campeões ao redor da Távola Redonda. A eles, confiou a mais sagrada\n");
    printf("das missões: partir pelo reino em busca do lendário Santo Graal.\n");
    printf("Dizem as antigas profecias que o cálice sagrado possui o poder de\n");
    printf("conceder qualquer desejo àquele que se provar digno.\n");

    aguardarEnter("\n[Pressione ENTER para continuar...]");

    printf("\nO desejo do Rei Arthur é claro e nobre: que Camelot se erga como\n");
    printf("um reino eterno de paz, prosperidade, poder e honra. Com a bênção\n");
    printf("do Graal em mãos, o Rei e seus cavaleiros estarão prontos para\n");
    printf("marchar contra os inimigos poderosos que ameaçam a paz do reino.\n\n");
    printf("Sua jornada como um dos escolhidos da Távola Redonda começa agora...\n");
    printf("====================================================================\n");

    aguardarEnter("\n[Pressione ENTER para criar seu herói...]");
}

int rolarDados(int lados) {
	return (rand() % lados) + 1;
}

void aplicarBonusAleatorio(Personagem *p) {
	int atributo = rand() % 5;
	printf("Bônus de vitória: ");
	switch(atributo) {
		case 1: p->forca++; printf("+1 de Força!\n"); break;
		case 2: p->destreza++; printf("+1 de Destreza!\n"); break;
		case 3: p->inteligencia++; printf("+1 de Inteligência!\n"); break;
		case 4: p->vidaMaxima += 5; p->vidaAtual += 5; printf("+5 de HP máximo!\n"); break;
		default: printf("Nada! Sem sorte dessa vez!\n"); break;
	}
}

int usarHabilidadeEspecial(Personagem *p) {
	if (p->manaAtual < 10) {
		printf("Mana insuficiente! Habilidade falhou!\n");
		return 0;
	}

	p->manaAtual -= 10;
	int dano = 0;

	switch(p->classeId) {
		case CLASSE_GUERREIRO:
			dano = (int)(p->ataque * 1.5);
			printf("%s usou [Golpe Pesado] causando %d de dano!\n", p->nome, dano);
			p->manaAtual -= 10;
			break;
		
		case CLASSE_ARQUEIRO:
			dano = (int)(p->ataque * 1.5);
			printf("%s disparou [Tiro Triplo] causando %d de dano!\n", p->nome, dano);
			p->manaAtual -= 10;
			break;
		
		case CLASSE_MAGO:
			dano = (int)(p->ataque * 1.5);
			printf("%s lançou [Bola de Fogo] causando %d de dano\n", p->nome, dano);
			p->manaAtual -= 10;
			break;
		
		default:
			break;
	}
	return dano;
}

void atribuirClasse(Personagem *p, TipoClasse tipo) {
	p->classeId = tipo;

	Classe dadosClasse = TABELA_CLASSES[tipo];

	p->vidaAtual = dadosClasse.vidaBase;
	p->vidaMaxima = dadosClasse.vidaBase;
	p->manaAtual = dadosClasse.manaBase;
	p->manaMaxima = dadosClasse.manaBase;
	p->forca = dadosClasse.forcaBase;
	p->destreza = dadosClasse.destrezaBase;
	p->constituicao = dadosClasse.constituicaoBase;
	p->inteligencia = dadosClasse.inteligenciaBase;
	p->sabedoria = dadosClasse.sabedoriaBase;
	p->carisma = dadosClasse.carismaBase;

	snprintf(p->arma, sizeof(p->arma), "%s", dadosClasse.armaInicial);
	snprintf(p->armadura, sizeof(p->armadura), "%s", dadosClasse.armaduraInicial);

	switch (tipo) {
		case CLASSE_GUERREIRO:
			p->ataque = 5 + (p->forca * 2);
			break;
		case CLASSE_ARQUEIRO:
			p->ataque = 5 + (p->destreza * 2);
			break;
		case CLASSE_MAGO:
			p->ataque = 5 + (p->inteligencia * 2);
			break;
		default:
			p->ataque = 5 + p->forca;
			break;
	}
	p->defesa = 2 + (p->destreza/2) + (p->constituicao/3);
}

Inimigo criarInimigo(DificuldadeInimigo dif) {
	TipoInimigo candidatos[TOTAL_INIMIGOS];
	int total = 0;
	for (int i = 0; i < TOTAL_INIMIGOS; i++) {
		if (TABELA_INIMIGOS[i].dificuldade == dif) {
			candidatos[total++] = (TipoInimigo)i;
		}
	}
	TipoInimigo sorteado = candidatos[rand() % total];
	InimigoBase base = TABELA_INIMIGOS[sorteado];

	Inimigo  monstro;

	snprintf(monstro.nome, sizeof(monstro.nome), "%s", base.nome);
	monstro.dificuldade = base.dificuldade;
	monstro.vidaAtual = base.vidaBase;
	monstro.vidaMaxima = base.vidaBase;
	monstro.ataque = base.ataqueBase;
	monstro.defesa = base.defesaBase;
	monstro.experiencia = base.experienciaBase;

	return monstro;
}

int calcularDano(int ataque, int defesa) {
	int dano = ataque - (defesa/2);
	return (dano > 1) ? dano : 1;
}

ResultadoCombate iniciarCombate(Personagem *p, Inimigo *m) {
	int emCombate = 1;
	ResultadoCombate resultado = RESULTADO_DERROTA;
	

	printf("\n==================================================\n");
    printf(" ⚔️ COMBATE INICIADO: %s VS %s!\n", p->nome, m->nome);
    printf("==================================================\n");

	while (emCombate && p->vidaAtual > 0 && m->vidaAtual > 0) {
		printf("\n--- SEU TURNO ---\n");
        printf("%s | HP: %d/%d | MP: %d/%d\n", p->nome, p->vidaAtual, p->vidaMaxima, p->manaAtual, p->manaMaxima);
        printf("%s | HP: %d/%d\n", m->nome, m->vidaAtual, m->vidaMaxima);
        printf("----------------------------------\n");
        printf("1. Atacar\n2. Defender\n3. Usar Habilidade Especial (10 MP)\n4. Tentar Fugir\n");
        printf("Escolha sua ação: ");

		int danoCausado = calcularDano(p->ataque, m->defesa);
		int posturaDefensiva = 0;
		int escolha;
		scanf("%d", &escolha);


		switch(escolha) {

			case 1:
				m->vidaAtual -= danoCausado;
				if (m->vidaAtual < 0) m->vidaAtual = 0;

				printf("Você atacou o %s e deu %d de dano!\n", m->nome, danoCausado);
				break;
			
			case 2:
				printf("Você assumiu uma postura deffensiva! Dano reduzido no próximo turno!\n");
				posturaDefensiva = 1;
				break;

			case 3:
				int danoEsp = usarHabilidadeEspecial(p);
				m->vidaAtual -= danoEsp;
				if (m->vidaAtual < 0) m->vidaAtual = 0;
				break;
			
			case 4:
				int testeFuga = rolarDados(20) + (p->destreza / 3);

				if (testeFuga >= 12) {
					printf("Fuga bem sucedida! Você escapou do combate!\n");
					return RESULTADO_FUGA;
				} printf("Falha na fuga! %s bloqueou seu caminho!", m->nome);
				break;

			default:
				printf("\nOpção inválida! Você perde seu turno!\n");
				break;
		}

		if (m->vidaAtual <= 0) {
			printf("\nVocê derrotou o %s!\n", m->nome);
			return RESULTADO_VITORIA;
		}

		printf("\n--- TURNO DO MONSTRO ---\n");
		int danoMonstro = calcularDano(m->ataque, p->defesa);
		if (posturaDefensiva) danoMonstro /= 2;

		p->vidaAtual -= danoMonstro;
		if (p->vidaAtual < 0) p->vidaAtual = 0;

		printf("O %s te atacou e deu %d de dano!\n", m->nome, danoMonstro);

		if (p->vidaAtual <= 0) {
			printf("\nVocê caiu em combate! Foi derrotado pelo %s...\n", m->nome);
			return RESULTADO_DERROTA;
		}
	}

	return resultado;

}

void aplicarBonusClasse(Personagem *p) {
	switch (p->classeId) {
		case CLASSE_GUERREIRO:
			p->forca += 4;
			p->destreza += 2;
			p->constituicao += 3;
			p->inteligencia += 1;
			p->sabedoria += 1;
			p->carisma += 1;
			break;

		case CLASSE_ARQUEIRO:
			p->forca += 2;
			p->destreza += 4;
			p->constituicao += 2;
			p->inteligencia += 1;
			p->sabedoria += 2;
			p->carisma += 1;
			break;
		
		case CLASSE_MAGO:
			p->forca += 1;
			p->destreza += 1;
			p->constituicao += 2;
			p->inteligencia += 5;
			p->sabedoria += 2;
			p->carisma += 1;
			break;

		default:
			break;
	}

	p->vidaMaxima += (p->constituicao * 2);
	p->manaMaxima += (p->inteligencia * 2) + p->sabedoria;

	if (p->classeId == CLASSE_GUERREIRO) {
		p->ataque += (p->forca * 2);
	} else if (p->classeId == CLASSE_ARQUEIRO) {
		p->ataque += (p->destreza * 2);
	} else if (p->classeId == CLASSE_MAGO) {
		p->ataque += (p->inteligencia * 2);
	}

	p->defesa += (p->destreza / 2) + (p->constituicao / 2);

	p->vidaAtual = p->vidaMaxima;
	p->manaAtual = p->manaMaxima;

}

void ganharExperiencia(Personagem *p, int experienciaGanha) {
	p->experienciaAtual += experienciaGanha;
	printf("\nvocê ganhou %d de Experiência!\n", experienciaGanha);

	while (p->experienciaAtual >= p->experienciaProximoNivel) {
		p->experienciaAtual -= p->experienciaProximoNivel;
		p->nivel++;
		p->experienciaProximoNivel = (int)(p->experienciaProximoNivel * 1.5);

		printf("\n====================================\n");
        printf("       LEVEL UP! NÍVEL %d!          \n", p->nivel);
        printf("====================================\n");

        aplicarBonusClasse(p);

        printf("Atributos aumentados (+12 pontos totais)!\n");
        printf("FOR: %d | DES: %d | CON: %d\n", p->forca, p->destreza, p->constituicao);
        printf("INT: %d | SAB: %d | CAR: %d\n", p->inteligencia, p->sabedoria, p->carisma);
        printf("------------------------------------\n");
        printf("HP Máximo: %d | MP Máximo: %d\n", p->vidaMaxima, p->manaMaxima);
        printf("Ataque: %d | Defesa: %d\n", p->ataque, p->defesa);
        printf("Próximo Nível exige: %d XP (XP Atual: %d)\n", p->experienciaProximoNivel, p->experienciaAtual);
        printf("====================================\n\n");
	}
}

Personagem criarPersonagem() {
	Personagem novoHeroi;

	novoHeroi.zonaAtual = 1;
	novoHeroi.posicao = 0;
	novoHeroi.nivel = 1;
	novoHeroi.experienciaAtual = 0;
	novoHeroi.experienciaProximoNivel = 25;
	novoHeroi.missaoCumprida = 0;

	printf("====================================\n");
    printf("       CRIAÇÃO DE PERSONAGEM        \n");
    printf("====================================\n");
	printf("Digite o nome do seu personagem: ");
	scanf("%29s", novoHeroi.nome);

	int opcao;
	printf("\nEscolha sua classe: \n");
	for(int i = 0; i < TOTAL_CLASSES; i++) {
		printf("%d. %s\n (HP: %d | Mana: %d)\n For: %d | Dex: %d | Con: %d| Int: %d | Sab: %d | Car: %d\n\n", i + 1, TABELA_CLASSES[i].nome, TABELA_CLASSES[i].vidaBase, TABELA_CLASSES[i].manaBase, TABELA_CLASSES[i].forcaBase, TABELA_CLASSES[i].destrezaBase, TABELA_CLASSES[i].constituicaoBase, TABELA_CLASSES[i].inteligenciaBase, TABELA_CLASSES[i].sabedoriaBase, TABELA_CLASSES[i].carismaBase);

	}

	do {
		printf("Opção (1-%d): ", TOTAL_CLASSES);
		scanf("%d", &opcao);
	} while (opcao < 1 || opcao > TOTAL_CLASSES);


	TipoClasse classeEscolhida = (TipoClasse)(opcao - 1);
	atribuirClasse(&novoHeroi, classeEscolhida);

	return novoHeroi;
}

void exibirFichaPersonagem(const Personagem *p) {
    printf("\n====================================\n");
    printf(" FICHA DE PERSONAGEM: %s\n", p->nome);
    printf(" Classe: %s | Nível: %d\n", TABELA_CLASSES[p->classeId].nome, p->nivel);
	printf(" Equipamentos: [%s] / [%s]\n", p->arma, p->armadura);
    printf(" XP: %d / %d\n", p->experienciaAtual, p->experienciaProximoNivel);
    printf("------------------------------------\n");
    printf(" [ATRIBUTOS PRINCIPAIS]\n");
    printf(" FOR: %2d | DES: %2d | CON: %2d\n", p->forca, p->destreza, p->constituicao);
    printf(" INT: %2d | SAB: %2d | CAR: %2d\n", p->inteligencia, p->sabedoria, p->carisma);
    printf("------------------------------------\n");
    printf(" [STATUS DE COMBATE]\n");
    printf(" HP: %d/%d | MP: %d/%d\n", p->vidaAtual, p->vidaMaxima, p->manaAtual, p->manaMaxima);
    printf(" ATK: %d | DEF: %d\n", p->ataque, p->defesa);
    printf("====================================\n\n");
}

Mapa gerarMapaPorFase(int numeroFase) {
	Mapa m;
	m.dificuldadeZona = TABELA_FASES[numeroFase - 1].dificuldade;

	m.trilha[0] = CASA_VAZIA;

	for (int i = 1; i < TAMANHO_MAPA - 1; i++) {
		if (i == TAMANHO_MAPA / 2 && numeroFase == 2) {
			m.trilha[i] = CASA_MISSAO;
			continue;
		}

		int r = rand() % 100;
		if (r <= 35) m.trilha[i] = CASA_VAZIA;
		else if (r > 35 && r <= 65) m.trilha[i] = CASA_INIMIGO;
		else if (r > 65 && r <= 80) m.trilha[i] = CASA_TESOURO;
		else if (r > 80 && r <= 90) m.trilha[i] = CASA_ARMADILHA;
		else m.trilha[i] = CASA_DESCANSO;
	}

	m.trilha[TAMANHO_MAPA - 1] = CASA_CHEFE;
	return m;
}

int apresentarInicioFase(int numeroFase) {
	Fase f = TABELA_FASES[numeroFase - 1];
	printf("\n======================================================\n");
    printf(" 🏰 FASE %d: %s\n", f.numero, f.nomeRegiao);
    printf(" 📜 MISSÃO PRINCIPAL: %s\n", f.tituloMissao);
    printf(" 📜 OBJETIVO: %s\n", f.descricaoMissao);
    printf("======================================================\n");
}

int avancarMapa(Personagem *p, Mapa *m) {
	if (p->zonaAtual >= TOTAL_FASES) return 0;
	p->zonaAtual++;
	p->posicao = 0;
	p->missaoCumprida = 0;

	printf("\n==================================================\n");
    printf("   🏆 ZONA %d CONCLUÍDA! AVANÇANDO PARA A ZONA %d   \n", p->zonaAtual - 1, p->zonaAtual);
    printf("==================================================\n");

	p->vidaAtual = p->vidaMaxima;
	p->manaAtual = p->manaMaxima;
	printf("Você descansou entre as regiões e recuperou sua vida e mana (%d/%d HP) || (%d/%d MP)\n", p->vidaAtual, p->vidaMaxima, p->manaAtual, p->manaMaxima);

	apresentarInicioFase(p->zonaAtual);
	*m = gerarMapaPorFase(p->zonaAtual);
	return 1;
}

void desenharMapa(int posicaoJogador, int zona) {
	printf("[FASE %d]: ", zona);
	for (int i = 0; i < TAMANHO_MAPA; i++) {
		if (i == posicaoJogador) printf("[P] ");
		else if (i == TAMANHO_MAPA - 1) printf("[C] ");
		else printf("[.] ");
	}
	printf("\n");
}

int moverJogador (Personagem *p, int tamanhoMapa) {
	int passos = rolarDados(6);
	p->posicao += passos;

	if (p->posicao >= tamanhoMapa) {
		p->posicao = tamanhoMapa - 1;
	}

	printf("Dado: %d! Você avançou para a casa: %d\n", passos, p->posicao);
	return passos;
}

void encontroInimigo(Personagem *p, DificuldadeInimigo dificuldade) {
	Inimigo monstro = criarInimigo(dificuldade);

	ResultadoCombate resultado = iniciarCombate(p, &monstro);

	switch(resultado) {
		case RESULTADO_VITORIA:
			ganharExperiencia(p, monstro.experiencia);
			break;
		
		case RESULTADO_FUGA:
			printf("Você recuou em segurança e continua na mesma casa do mapa.\n");
			break;

		case RESULTADO_DERROTA:
			printf("\n--- GAME OVER ---\n");
            printf("Sua jornada chegou ao fim. Deseja recarregar o jogo?\n");
			break;
	}
}

void eventoCasa(TipoCasa evento, Personagem *p, Mapa *m) {
	switch(evento) {
		case CASA_INIMIGO:
			printf("Um inimigo apareceu!\n");
			Inimigo monstro = criarInimigo(m->dificuldadeZona);
			ResultadoCombate resultado = iniciarCombate(p, &monstro);
			if (resultado == RESULTADO_VITORIA) {
				ganharExperiencia(p, monstro.experiencia);
				aplicarBonusAleatorio(p);
			}
			break;
		
		case CASA_MISSAO:
			if (p->zonaAtual == 2) {
				printf("LOCAL DA MISSÃO! Você encontrou o lendário Santo Graal\n");
				p->missaoCumprida = 1;
				printf("Item da missão [Santo Graal] coletado com sucesso!\n");
			}
			break;

		case CASA_CHEFE: {
			printf("\nPortão do chefe da fase %d!\n", p->zonaAtual);

			if (p->zonaAtual == 2 && !p->missaoCumprida) {
				printf("Só o Santo Graal pode conceder a força para superá-lo! Procure-o primeiro!\n");
				break;
			}

			Inimigo chefe = criarInimigo(m->dificuldadeZona);
			printf("O chefe [%s] avança para o duelo final!\n", chefe.nome);

			ResultadoCombate  resultado = iniciarCombate(p, &chefe);
			if (resultado == RESULTADO_VITORIA) {
				ganharExperiencia(p, chefe.experiencia * 2);
				printf("Missão Cumprida: %s\n", TABELA_FASES[p->zonaAtual - 1]);

				if (p->zonaAtual < TOTAL_FASES) {
					avancarMapa(p, m);
				} else {
					p->zonaAtual++;
					printf("VITÓRIA SUPREMA! VOCÊ VENCEU A BATALHA DE CAMLANN E CONCLUIU O JOGO!");
				}
			}

			break;
		}

		case CASA_TESOURO:
			printf("Você encontrou um tesouro!\n");
			aplicarBonusAleatorio(p);
			break;

		case CASA_DESCANSO:
			printf("Você encontrou um lugar onde pode descansar! Vida e Mana recuperados!\n");
			p->vidaAtual = p->vidaMaxima;
			p->manaAtual = p->manaMaxima;
			break;
			
		default:
			printf("Você não encontrou nada! Gire o dado novamente para prosseguir!\n");
			break;
	}
}



int main() {
	srand((unsigned int) time(NULL));

	exibirHistoriaIntroducao();

	Personagem jogador = criarPersonagem();
	exibirFichaPersonagem(&jogador);

	Mapa mapaAtual = gerarMapaPorFase(jogador.zonaAtual);
	apresentarInicioFase(jogador.zonaAtual);

	while (jogador.vidaAtual > 0 && jogador.zonaAtual <= TOTAL_FASES) {
		desenharMapa(jogador.posicao, jogador.zonaAtual);

		aguardarEnter("\nPressione o ENTER para rolar o d6 e se mover...");
		moverJogador(&jogador, TAMANHO_MAPA);

		TipoCasa evento = mapaAtual.trilha[jogador.posicao];
		eventoCasa(evento, &jogador, &mapaAtual);
	}

	if (jogador.vidaAtual <= 0) {
		printf("\nGAME OVER! Seu herói caiu em batalha na fase: %d.\n", jogador.zonaAtual);
	}

	return 0;
}
