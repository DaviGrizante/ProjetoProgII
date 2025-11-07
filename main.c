#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<stdbool.h>
#include<conio.h>
#include<string.h>

#define TAM 80
#define NUM_SAVES 3
#define TAM_ESCOLHA 20

typedef struct{
    char nome[TAM];
    char sexo;
    char classe;
    int pv;
    int agilidade;
    int fase;
    float defesa;
    float forca;
    bool isAlive;
}tipoPersonagem;

typedef struct{
    char nome[TAM];
    int pv;
    int agilidade;
    float forca;
    float defesa;
}tipoInimigo;

void combate(tipoInimigo inim, tipoPersonagem *p, int saveSlot){
    system("cls");
    char acao[TAM_ESCOLHA];
    float danoCausado = 0;
    float defesaAumentada = 0;
    float originalDef = p->defesa;
    bool jaAtacou = false;
    srand(time(NULL));
    puts(
"                    ______\n"
"                 .-\"      \"-.\n"
"                /            \\ \n"
"               |              |\n"
"               |,  .-.  .-.  ,|\n"
"               | )(__/  \\__)( |\n"
"               |/     /\     \|\n"
"     (@_       (_     ^^     _)\n"
"_     ) \\_______\\__|IIIIII|__/__________________________\n"
"()@8@8{}<________|-\\IIIIII/-|___________________________>\n"
"      )_/        \\          /\n"
"     (@           `--------`\n"
         );
    printf("\n\n-------------------------------------------------------COMBATE-------------------------------------------------------\n");
    while(inim.pv > 0 && p->pv > 0){
        if(p->agilidade >= inim.agilidade && jaAtacou == false){
            printf("\nVocÍ est· em combate contra %s, deseja atacar ou defender? *Veja status com \"status\"\n", inim.nome);
            fflush(stdin);
            fgets(acao, TAM_ESCOLHA, stdin);
            strlwr(acao);
            if(strncmp(acao, "atacar", 6) == 0){
                danoCausado = rand();
                danoCausado /= RAND_MAX;
                danoCausado = (p->forca*1.5) - ((inim.defesa/2) + ((1) + (inim.defesa/10) * danoCausado));
                printf("VocÍ atacou %s, causando %.2f de dano.\n", inim.nome, danoCausado);
                inim.pv -= danoCausado;
                getch();
            }
            else if(strncmp(acao,"defender",8) == 0){
                p->defesa = originalDef;
                defesaAumentada = rand();
                defesaAumentada /= RAND_MAX;
                defesaAumentada = (defesaAumentada * (p->defesa / 10)) + (1);
                printf("VocÍ defendeu, aumentando sua defesa em %.2f pontos\n", defesaAumentada);
                p->defesa += defesaAumentada;
                getch();
            }
            else if(strncmp(acao,"status", 6) == 0){
                printf("\nSeus status s„o:\n");
                printf("PV: %d\nForÁa: %.2f\nDestreza: %d\nDefesa: %.2f\n", p->pv, p->forca, p->agilidade, p->defesa);
                getch();
                continue;
            }
            else{
                printf("Comando inv·lido! Digite novamente.\n");
                sleep(1);
                continue;
            }
            if(inim.pv <= 0){
                printf("ParabÈns!!! VocÍ ganhou.\n");
                p->defesa = originalDef;
                getch();
                break;
            }
            jaAtacou = true;
        }
        else{
            danoCausado = rand();
            danoCausado /= RAND_MAX;
            danoCausado = (inim.forca*1.3) - (p->defesa + (danoCausado * ((p->defesa/10) + 1)));
            printf("%s te atacou! Causando %.2f de dano.\n", inim.nome, danoCausado);
            p->pv -= danoCausado;
            inim.agilidade = 0;
            jaAtacou = false;
            getch();
            if(p->pv <= 0){
                printf("VocÍ perdeu!\n");
                getch();
                p->isAlive = false;
                p->fase = 2;
                salvarPersonagem(*p, saveSlot, true);
            }
        }
    }
    printf("Combate encerrado. Voltando ‡ exploraÁ„o...\n");
    fflush(stdin);
    getch();
    p->defesa = originalDef;
    salvarPersonagem(*p, saveSlot, false);
}

void selecionarFase(tipoPersonagem p, int saveSlot){
    switch(p.fase){
        case 0:
            introducao(p, saveSlot);
            break;
        case 1:
            fase1(p, saveSlot);
            break;
        case 2:
            menu();
            break;
    }
}

void fase1(tipoPersonagem p, int saveSlot){
    system("cls");
    bool inimigosDerrotados[3] = {false,false,false};
    bool movimentoValido = false;
    char escolhas[TAM_ESCOLHA];
    printf("-------------------------------------------------------FLORESTA PERDIDA-------------------------------------------------------\n\n");
    sleep(2);
    printf("VocÍ j· jogou jogos no estilo Adventure antes? S/N\n");
    fflush(stdin);
    scanf("%c", &escolhas[0]);
    escolhas[0] = tolower(escolhas[0]);
    if(escolhas[0] == 'n'){
        printf("\nMuito bem! Aqui vocÍ encontrar· uma explicaÁ„o breve sobre como jogar o jogo.\n");
        getch();
        printf("Jogos em estilo Adventure s„o jogos de RPG (Role-Playing Games) em formato textual, muito comum em jogos antigos de PC.\n");
        getch();
        printf("O jogo funciona com um sistema de descriÁıes, todo o cen·rio, itens, inimigos, etc. Ser„o descritos textualmente.\n");
        getch();
        printf("As descriÁıes s„o importantes para que vocÍ possa saber quais locais pode se movimentar e quando pode atacar, por exemplo.\n");
        getch();
        printf("Para se movimentar pelo mapa, digite os comandos \"norte\" para seguir em frente, \"sul\" para voltar, \"leste\" para seguir a direita e \"oeste\" para seguir a esquerda.\n");
        getch();
        printf("Digite \"status\" para ver seus status.\n");
        getch();
        printf("A qualquer momento que quiser, digite \"sair\" para sair do jogo.\n");
        getch();
        printf("Agora o jogo ir· comeÁar de verdade.\n");
        getch();
    }
    while(!movimentoValido){
        printf("\nAo adentrar a floresta, vocÍ se vÍ cercado pelo emaranhado de ·rvores a sua volta. Conforme se aprofunda na inÛspita regi„o, percebe que se torna cada vez  mais difÌcil de identificar um caminho claro para seguir.\n");
        getch();
        printf("Apenas dois caminhos parecem se fazer presentes a vocÍ no momento, um deles seguindo ao norte e outro seguindo a leste, qual deseja seguir?\n");
        fflush(stdin);
        fgets(escolhas, TAM_ESCOLHA, stdin);
        strlwr(escolhas);
        if(strncmp(escolhas, "norte", 5) == 0){
            while(!movimentoValido){
                printf("\nVocÍ adentra mais a floresta, avistando uma pequena fogueira ainda acesa no ch„o com alguns equipamentos largados prÛximos a ela, tais \n"
                       "equipamentos s„o armas, escudos e alguns alimentos. Provavelmente pertenciam a cavaleiros que tambÈm estavam em busca da princesa.\n");
                getch();
                printf("A oeste vocÍ vÍ uma trilha de sangue suave, n„o parece ter havido muita resistÍncia por parte dos cavaleiros. Ao norte a trilha segue normalmente.\n");
                getch();
                printf("Qual caminho deseja seguir?\n");
                fflush(stdin);
                fgets(escolhas, TAM_ESCOLHA, stdin);
                strlwr(escolhas);
                if(strncmp(escolhas, "oeste", 5) == 0 && inimigosDerrotados[0] == false){
                    printf("\nVocÍ segue a trilha de sangue atÈ chegar a um beco sem saÌda envolto pelas ·rvores.\n");
                    getch();
                    printf("Acima de sua cabeÁa, vocÍ nota diversos corpos de pessoas presos ao que parecem ser teias gigantes de aranha.\n");
                    getch();
                    printf("Aos poucos diversas aranhas comeÁam a descer pelas ·rvores em sua direÁ„o, as aranhas pequenas tentam te atacar, mas vocÍ consegue elimin·-las com facilidade.\n");
                    getch();
                    printf("De repente, vocÍ escuta um alto som saindo detr·s das ·rvores. Uma aranha gigante, aparantemente a m„e das aranhas, surge em sua frente berrando de dor por vocÍ estar matando suas crias.\n");
                    getch();
                    printf("N„o te resta escolha sen„o lutar!\n\n");
                    getch();
                    tipoInimigo aranha;
                    aranha.pv = 70;
                    aranha.forca = 60;
                    aranha.defesa = 80;
                    aranha.agilidade = 80;
                    strcpy(aranha.nome, "Aranha Rainha");
                    combate(aranha, &p, saveSlot);
                    inimigosDerrotados[0] = true;
                    printf("\nAo derrotar a aranha, vocÍ vÍ uma espada brilhante cair em sua frente, vinda de um dos corpos presos nas ·rvores.\n");
                    getch();
                    printf("… a espada de um cavaleiro de elite do reino, ela te concede +15 de forÁa.\n");
                    getch();
                    p.forca += 15;
                    printf("N„o h· mais nada a fazer aqui. VocÍ volta para onde estava antes.\n");
                    getch();
                    salvarPersonagem(p, saveSlot, false);
                    continue;
                }
                else if(strncmp(escolhas,"oeste",5) == 0 && inimigosDerrotados[0] == true){
                    printf("VocÍ j· derrotou a aranha que havia ali, n„o h· mais nada l· para vocÍ.\n");
                    continue;
                }
                else if(strncmp(escolhas, "norte", 5) == 0){
                    printf("Boa, vocÍ est· quase chegando amiguinho.\n");
                }
                else if(strncmp(escolhas, "sul", 3) == 0){
                    printf("Voltando...\n");
                    sleep(1);
                    break;
                }
                else if(strncmp(escolhas, "status", 6) == 0){
                    printf("\nSeus status s„o:\n");
                    printf("PV: %d\nForÁa: %.2f\nDestreza: %d\nDefesa: %.2f\n", p.pv, p.forca, p.agilidade, p.defesa);
                    getch();
                    continue;
                }
                else if(strncmp(escolhas, "sair", 4) == 0){
                    printf("Voltando ao menu...\n");
                    sleep(1);
                    p.fase = 1;
                    salvarPersonagem(p, saveSlot, false);
                    sleep(1);
                    menu();
                    break;
                }
                else{
                    printf("MovimentaÁ„o inv·lida! Digite novamente\n");
                    continue;
                }
            }
        }
        else if(strncmp(escolhas, "leste", 5) == 0 && inimigosDerrotados[1] == false){
            printf("\nSeguindo ao leste, vocÍ comeÁa a escutar baixos sons semelhantes a uma conversa, porÈm em um idioma desconhecido por vocÍ.\n");
            getch();
            printf("Seguindo ainda mais ao leste, vocÍ se depara com dois goblins sentados em meio a estrada conversando.\n");
            getch();
            printf("Caido, ao lado deles, est· um homem humano aparentemente sem vida, seu peito sangra bastante, provavelmente era um cavaleiro igual vocÍ que morreu para os goblins.\n");
            getch();
            printf("Deseja lutar contra eles ou fugir e voltar para onde estava?\n");
            fflush(stdin);
            fgets(escolhas, TAM_ESCOLHA, stdin);
            strlwr(escolhas);
            if(strncmp(escolhas, "lutar", 5) == 0){
                printf("VocÍ dispara em direÁ„o aos goblins com sua arma em punhos.\n");
                tipoInimigo goblins;
                strcpy(goblins.nome, "Goblins");
                goblins.pv = 40;
                goblins.forca = 60;
                goblins.defesa = 40;
                goblins.agilidade = 40;
                combate(goblins, &p, saveSlot);
                inimigosDerrotados[1] = true;
                printf("\nAo derrotar os goblins, vocÍ percebe que o homem carregava consigo um escudo muito melhor que o seu.\n");
                getch();
                printf("VocÍ promete resgatar a princesa pelo cavaleiro morto, e pega seu escudo para te ajudar na miss„o, aumentando sua defesa em 10 pontos.\n");
                getch();
                p.defesa += 10;
                printf("N„o h· mais nada a fazer aqui. VocÍ volta para onde estava antes.\n");
                getch();
                salvarPersonagem(p, saveSlot, false);
                continue;
            }
            else if(strncmp(escolhas, "fugir", 5) == 0){
                printf("VocÍ decide evitar a luta contra os goblins e volta furtivamente de onde veio.\n");
                getch();
                continue;
            }
            else if(strncmp(escolhas, "status", 6) == 0){
                printf("\nSeus status s„o:\n");
                printf("PV: %d\nForÁa: %.2f\nDestreza: %d\nDefesa: %.2f\n", p.pv, p.forca, p.agilidade, p.defesa);
                getch();
                continue;
            }
            else if(strncmp(escolhas, "sair", 4) == 0){
                printf("Voltando ao menu...\n");
                sleep(1);
                p.fase = 1;
                salvarPersonagem(p, saveSlot, false);
                sleep(1);
                menu();
                break;
            }
            else{
                printf("MovimentaÁ„o inv·lida! Digite novamente\n");
                continue;
            }
        }
        else if(strncmp(escolhas, "leste", 5) == 0 && inimigosDerrotados[1] == true){
            printf("J· derrotei os goblins que estavam ali, n„o h· mais nada para fazer l·.\n");
            sleep(1);
            continue;
        }
        else if(strncmp(escolhas, "status", 6) == 0){
            printf("\nSeus status s„o:\n");
            printf("PV: %d\nForÁa: %.2f\nDestreza: %d\nDefesa: %.2f\n", p.pv, p.forca, p.agilidade, p.defesa);
            getch();
            continue;
        }
        else if(strncmp(escolhas, "sair", 4) == 0){
            printf("Voltando ao menu...\n");
            sleep(1);
            p.fase = 1;
            salvarPersonagem(p, saveSlot, false);
            sleep(1);
            menu();
            break;
        }
        else{
            printf("MovimentaÁ„o inv·lida! Digite novamente\n");
            continue;
        }
    }
    printf("Fora do loop!");
    getch();
    menu();
}

void introducao(tipoPersonagem p, int saveSlot){
    system("cls");
    puts(
"        ,..........   ..........,\n"
"    ,..,'          '.'          ',..,\n"
"   ,' ,'            :            ', ',\n"
"  ,' ,'             :             ', ',\n"
" ,' ,'              :              ', ',\n"
",' ,'............., : ,.............', ',\n"
",'  '............   '.'   ............'  ',\n"
"'''''''''''''''''';''';''''''''''''''''''\n"
"                   '''\n"
         );
    printf("-------------------------------------------------------INTRODUùùO-------------------------------------------------------\n\n");
    sleep(2);
    printf("H· 500 anos o reino de LusÌade n„o havia registrado nenhum ataque massivo de monstros contra o castelo do rei, entretando, h· dois dias, a situaÁ„o mudou...\n");
    getch();
    printf("Um exÈrcito de monstros de todos os tipos se juntaram e planejaram um ataque coordenado contra o castelo.\n");
    getch();
    printf("O ataque ocorreu um dia antes do maior festival do reino, o festival de comemoraÁ„o da maioridade da princesa.\n");
    getch();
    printf("Durante as duas semanas antes da festa, diversos cavaleiros importantes do reino se aventuravam em incursıes para buscar pelas iguarias mais refinadas ao redor do mundo.\n");
    getch();
    printf("Nesse momento, com os principais cavaleiros fora, os monstros se aproveitaram e atacaram o reino, raptando a princesa e a tornando refÈm deles.\n");
    getch();
    printf("VocÍ, como cavaleiro do reino, deve ir atr·s da princesa e resgat·-la das garras desses monstros vis.\n");
    getch();
    printf("Suas investigaÁıes te levaram primeiro a floresta perdida, um local dominado pelos mais terrÌveis monstros existentes.\n");
    getch();
    printf("Ser· que vocÍ conseguir· resistir a seus ataques e salvar a princesa? Seja forte e prepare-se para a jornada!!!\n");
    p.fase = 1;
    getch();
    salvarPersonagem(p,saveSlot, true);
}

void criarSaveFiles(){
    FILE *arq = fopen("saveFiles.adv", "wb");
    if(arq == NULL){
        printf("N„o foi possÌvel criar o arquivo!");
    }
    else{
        tipoPersonagem vazio = {0};

        for(int i = 0; i < NUM_SAVES; i++){
            fwrite(&vazio, sizeof(tipoPersonagem), 1, arq);
        }
        fclose(arq);
    }
}

void salvarPersonagem(tipoPersonagem p,int saveSlot, bool selecionaFase){
    FILE *arq = fopen("saveFiles.adv", "r+b");
    if(arq == NULL){
        printf("Ocorreu um problema ao abrir o arquivo de save! Criando novo arquivo...");
        sleep(1);
        criarSaveFiles();
        arq = fopen("saveFiles.adv", "r+b");
    }

    if(saveSlot < 1 || saveSlot > NUM_SAVES){
        printf("Valor de arquivo de salvamento errado! Voltando para o menu...");
        fclose(arq);
        sleep(1);
        menu();
    }
    fseek(arq, (saveSlot - 1) * sizeof(tipoPersonagem), SEEK_SET);
    fwrite(&p, sizeof(tipoPersonagem), 1, arq);
    fclose(arq);
    printf("\nPersonagem salvo com sucesso! Retornando ao jogo...\n");
    sleep(2);
    if(selecionaFase = true){
        selecionarFase(p, saveSlot);
    }
}

void criarPersonagem(int saveSlot){
    tipoPersonagem novo;
    while(true){
        system("cls");
        printf("-------------------------------------------------------CRIA«√O DE PERSONAGEM-------------------------------------------------------\n\n");
        printf("Qual ser· o sexo do seu personagem? M/F\n");
        fflush(stdin);
        scanf("%c", &novo.sexo);
        novo.sexo = tolower(novo.sexo);
        if(novo.sexo == 'm'){
            printf("Seu personagem È do sexo masculino!\n");
        }
        else if(novo.sexo == 'f'){
            printf("Seu personagem È do sexo feminino!\n");
        }
        else{
            printf("Caracter inv·lido, digite novamente!\n");
            sleep(1);
            continue;
        }
        printf("\nQual ser· o nome do seu personagem?\n");
        fflush(stdin);
        fgets(novo.nome, TAM, stdin);
        do{
            char retry;
            printf("\nQual ser· a classe do seu personagem? G/L/B\n");
            printf("*Caso n„o conheÁa as classes, digite \'h\' no console.\n");
            fflush(stdin);
            scanf("%c", &novo.classe);
            novo.classe = tolower(novo.classe);
            if(novo.classe == 'h'){
                printf("\nO caracter \'g\' corresponde ao guerreiro, focado em defesa alta, ataque mediano e destreza baixa.\n"
                    "\nO caracter \'l\' corresponde ao ladr„o, focado em destreza alta, defesa mediana e ataque baixo.\n"
                    "\nO caracter \'b\' corresponde ao b·rbaro, focado em ataque alto, destreza mediana e defesa baixa.\n"
                );
                printf("\nQual dessas classes vocÍ prefere?\n");
                fflush(stdin);
                scanf("%c", &novo.classe);
                novo.classe = tolower(novo.classe);
            }
            if(novo.classe == 'g'){
                printf("\nSeu personagem È GUERREIRO! Seus status s„o:\n"
                       "PV: 60.\n"
                       "ForÁa: 40.\n"
                       "Destreza: 25\n"
                       "Defesa: 60\n"
                       );
                novo.pv = 60;
                novo.forca = 40;
                novo.agilidade = 25;
                novo.defesa = 60;
            }
            else if(novo.classe == 'l'){
                printf("\nSeu personagem È LADR√O! Seus status s„o:\n"
                        "PV: 50\n"
                        "ForÁa: 25\n"
                        "Destreza: 60\n"
                        "Defesa: 40\n"
                    );
                novo.pv = 50;
                novo.forca = 25;
                novo.agilidade = 60;
                novo.defesa = 40;
            }
            else if(novo.classe == 'b'){
                printf("\nSeu personagem È B¡RBARO! Seus status s„o:\n"
                        "PV: 45\n"
                        "ForÁa: 60\n"
                        "Destreza: 40\n"
                        "Defesa: 25\n"
                    );
                novo.pv = 45;
                novo.forca = 60;
                novo.agilidade = 40;
                novo.defesa = 25;
            }
            else{
                printf("\nCaracter inv·lido, digite novamente!\n");
                novo.classe = 'x';
                continue;
            }
            printf("VocÍ deseja jogar com essa classe? S/N\n");
            fflush(stdin);
            scanf("%c", &retry);
            retry = tolower(retry);
            if(retry == 's'){
                printf("Classe Selecionada com sucesso!\nHora de iniciar sua aventura!!!");
                novo.isAlive = true;
                novo.fase = 0;
                sleep(2);
                salvarPersonagem(novo,saveSlot, true);
            }
            else{
                printf("Voltando a seleÁ„o de classe...");
                sleep(2);
                novo.classe = 'x';
            }
        }while(novo.classe == 'x');
    break;
    }
}

void verificarSave(int saveSlot, bool newGame){
    FILE *arq = fopen("saveFiles.adv", "rb");
    char startNewGame;
    if(arq == NULL){
        printf("Ocorreu um problema ao carregar o arquivo, criando arquivo...");
        criarSaveFiles();
        arq = fopen("saveFiles.adv", "rb");
    }
    tipoPersonagem p;
    fseek(arq, (saveSlot - 1) * sizeof(tipoPersonagem), SEEK_SET);
    fread(&p, sizeof(tipoPersonagem), 1, arq);
    if(p.isAlive == false && newGame == true){
        printf("Redirecionando para a criaÁ„o de personagem...\n");
        sleep(1);
        criarPersonagem(saveSlot);
    }
    else if(newGame == true){
        printf("Tem certeza que deseja sobrescrever os dados salvos? S/N\n");
        fflush(stdin);
        scanf("%c", &startNewGame);
        startNewGame = tolower(startNewGame);
        if(startNewGame == 's'){
            printf("Redirecionando para a criaÁ„o de personagem...\n");
            sleep(1);
            criarPersonagem(saveSlot);
        }
        else{
            printf("Voltando para o menu...\n");
            sleep(1);
            menu();
        }
    }
    else if(p.isAlive == true && newGame == false){
        printf("Carregando arquivo de salvamento...");
        sleep(1);
        selecionarFase(p,saveSlot);
    }
    else{
        printf("ImpossÌvel carregar save, escolha um arquivo de salvamento com um personagem disponÌvel para carregar o jogo.\n");
        sleep(3);
        menu();
    }
}

void selecaoSave(bool newGame){
    FILE *arq;
    int saveFile = 0;
    system("cls");
    printf("Qual arquivo de salvamento vocÍ vai utilizar?\n");

    arq = fopen("saveFiles.adv", "rb");

    if(arq == NULL){
        criarSaveFiles();
        arq = fopen("saveFiles.adv", "rb");
        if(arq == NULL){
            printf("Ocorreu um erro ao abrir o arquivo! Retornando ao menu...\n");
            sleep(1);
            menu();
        }
    }
    tipoPersonagem personagem;
    for(int i = 0; i < NUM_SAVES; i++){
        fread(&personagem, sizeof(tipoPersonagem), 1, arq);
        if(ferror(arq)){
            printf("Ocorreu um erro ao ler o arquivo! Voltando ao menu...\n");
            sleep(1);
            menu();
        }
        printf("\n\n-------------------------------------------------------ARQUIVO %d-------------------------------------------------------\n\n", i+1);
        if(personagem.isAlive){
            printf("Nome: %sSexo: %c\nClasse: %c\nPV: %d\nForÁa: %.2f\nDestreza: %d\nDefesa: %.2f\n", personagem.nome, personagem.sexo, personagem.classe, personagem.pv, personagem.forca, personagem.agilidade, personagem.defesa);
        }
        else{
            printf("Vazio\n");
        }
        if(feof(arq) && i==NUM_SAVES-1){
            break;
        }
    }
    fclose(arq);
    printf("\n\nEscolha 1, 2 ou 3! Caso queira cancelar, aperte qualquer tecla, exceto as 3 mencionadas:\n");
    fflush(stdin);
    scanf("%d", &saveFile);
    if(saveFile < 1 || saveFile > NUM_SAVES){
        printf("Voltando ao menu...");
        sleep(1);
        menu();
    }
    else{
        printf("Verificando arquivo de salvamento...\n");
        sleep(1);
        verificarSave(saveFile, newGame);
    }
}

void creditos(){
    system("cls");
    puts(
"                   _ _ _\n"
"                  | (_) |\n"
"  ___ _ __ ___  __| |_| |_ ___\n"
" / __| '__/ _ \\/ _` | | __/ __|\n"
"| (__| | |  __/ (_| | | |_\\__ \\ \n"
" \\___|_|  \\___|\\__,_|_|\\__|___/\n"
    );
    sleep(2);
    printf("-------------------------------------------------------INTEGRANTES DO GRUPO-------------------------------------------------------\n\n");
    sleep(2);
    printf("Davi de S· Grizante\n");
    sleep(2);
    printf("Kelwin Regis Esechiel\n");
    sleep(2);
    printf("\n-------------------------------------------------------CR…DITOS DAS ARTES ASCII-------------------------------------------------------\n\n");
    sleep(2);
    printf("ASCII ART ARCHIVE: https://www.asciiart.eu/#google_vignette\n");
    sleep(2);
    printf("ASCII.co.uk: https://ascii.co.uk/art/credits\n");
    sleep(2);
    printf("\n-------------------------------------------------------INFORMA«’ES DO PROJETO-------------------------------------------------------\n\n");
    sleep(2);
    printf("MatÈria: ProgramaÁ„oII\n");
    sleep(2);
    printf("Professora: Daniele Junqueira Frosoni\n");
    sleep(2);
    printf("Curso: Jogos Digitais 2∞ Semestre\n");
    sleep(2);
    printf("Fatec Americana 2025\n");
    sleep(2);
    printf("\n-------------------------------------------------------OBRIGADO POR JOGAR!!!-------------------------------------------------------\n");
    printf("\n*Digite algo para sair!");
    fflush(stdin);
    getch();
}

void menu(){
    int opcoes = 0;
    fflush(stdin);

    while(opcoes != 4){
        system("cls");
        puts(
"\n                                 |>>>\n"
"                                 |\n"
"                   |>>>      _  _|_  _         |>>>\n"
"                   |        |;| |;| |;|        |\n"
"               _  _|_  _    \\.    .  //    _  _|_   _\n"
"              |;|_|;|_|;|    \\:. ,  //    |;|_|;|__|;|\n"
"              \\..      /     ||;   . |    \\\\.    .  /\n"
"               \\.  ,  /      ||:  .  |     \\\\:  .  /\n"
"                ||:   |_  _  ||_ . _ |_   _||:     |\n"
"                ||:  .||_|;|_|;|_|;|_|;|_|;||:.    |\n"
"                ||:   |.    .     .      . ||:  .  |\n"
"                ||: . | .     . .   .  ,   ||:     |       \\,/\n"
"                ||:   |:  ,  _______   .   ||: ,   |            /`\\ \n"
"                ||:   | .   /+++++++\\   .  ||:     |\n"
"                ||:   |.    |+++++++| .    ||: .   |\n"
"             __ ||: . |: ,  |+++++++|.  . _||_     |\n"
"   ____--`~    '--~~__|.    |+++++++|----~    ~`---,             ___\n"
"-~--~                   ~---__|,--~'                  ~~----_____-~'   `~----~~\n"
);
    printf("-------------------------------------------------------MENU PRINCIPAL-------------------------------------------------------\n");
    printf("[1]Novo Jogo.\n");
    printf("[2]Carregar Jogo.\n");
    printf("[3]CrÈditos.\n");
    printf("[4]Sair.\n");

    printf("Escolha uma das opÁıes acima com o n˙mero correspondente: \n");
    fflush(stdin);
    scanf("%d", &opcoes);

    switch(opcoes){
        case 1:
            selecaoSave(true);
            break;
        case 2:
            selecaoSave(false);
            break;
        case 3:
            creditos();
            break;
        case 4:
            printf("Saindo do jogo...");
            exit(0);
        default:
            printf("Comando n„o detectado! Tente novamente.\n");
            sleep(2);
            continue;
        }
    }
}

int main(){
    setlocale(LC_ALL, "portuguese");

    menu();

    return 0;
}
