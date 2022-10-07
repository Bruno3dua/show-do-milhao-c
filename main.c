// ACADÊMICO: BRUNO EDUARDO MARQUES GOMES //
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pergunta          //
{                        //
    char nivel;          //
    char descricao[200]; // ORGANIZA O ARQUIVO BINÁRIO
    char alt[4][30];     //
    char alt_correta;    //
};                       //

struct playerState
{
    int difficult;                // LEVEL DE DIFICULDADE
    int money;                    // DINHEIRO ATUAL
    int skipCount;                // PULAR RESTANTES
    int audienceAssistancesCount; // AJUDAS DA PLATEIA RESTANTES
    int studentsAssistancesCount; // AJUDAS DE ACADEMICOS RESTANTES
    int cardsAssistancesCount;    // AJUDAS DE CARTAS RESTANTES
    int qNum;                     // QUESTÃO ATUAL NO JOGO
    int currQ;                    // QUESTÃO ATUAL NO ARQUIVO BINÁRIO
};

char op, nQ1, nQ2, nQ3; // ARMAZENA A QUESTÃO CERTA E AS ALTERNATIVAS ERRADAS
char alt[4];            // ARMAZENA AS OPÇÕES

void printQuestion(struct pergunta q[70], struct playerState *state, int sameQuestion); //
int randomNum(int low, int high);                                                       //
int selectRandomQuestion(struct playerState *state);                                    //
void printCards();                                                                      // FUNÇÕES (PROTOTYPES)
void cardAux(struct pergunta q[70], struct playerState state);                          //
char rightQ(struct pergunta q[70], struct playerState state);                           //

int main()
{
    struct pergunta q[70];
    struct playerState state = {1, 0, 3, 3, 3, 3, 1, 0};
    srand(time(NULL));

    // ABERTURA DO ARQUIVO //
    FILE *questions;
    questions = fopen("perguntas.dat", "rb");
    if (questions == NULL)
        printf("\nNao foi possivel abrir o arquivo\n");
    else
    {
        int sameQuestion;
        sameQuestion = 0;
        fread(&q[0].nivel, sizeof(struct pergunta), 70, questions);    //
        fread(&q[0].descricao, sizeof(q->nivel), 70, questions);       //
        for (int i = 0; i < 70; i++)                                   //
        {                                                              //
            for (int j = 0; j < 4; j++)                                //  LÊ E GUARDA AS QUESTÕES
            {                                                          //
                fread(&q[i].alt[j], sizeof(q->alt), 70, questions);    //
            }                                                          //
        }                                                              //
        fread(&q[0].alt_correta, sizeof(q->descricao), 70, questions); //

        while (1)
        {
            system("cls");
            printQuestion(q, &state, sameQuestion);
            sameQuestion = 0;
            switch (op)
            {
                int exitop, n, card;
                char yn, ans;

            case 'a': //
            case 'b': // OPTIONS
            case 'c': //
            case 'd': //
                if (op == q[state.currQ].alt_correta)
                {
                    // SISTEMA MONETÁRIO //
                    if (state.qNum < 5)
                        state.money += 1000;
                    else if (state.qNum == 5)
                        state.money = 10000;
                    else if (state.qNum > 5 && state.qNum < 10)
                        state.money += 10000;
                    else if (state.qNum == 10)
                        state.money = 100000;
                    else if (state.qNum > 10 && state.qNum <= 15)
                        state.money += 100000;
                    else if (state.qNum == 16)
                    {
                        state.money = 1000000;
                        system("cls");
                        printf("\n############################################\n");
                        printf("#                                          #\n");
                        printf("#                                          #\n");
                        printf("#       VOCE GANHOU R$ 1.000.000,00        #\n");
                        printf("#                                          #\n");
                        printf("#                                          #\n");
                        printf("############################################\n");
                        exit(1);
                    }

                    printf("\nVoce acertou!\n");
                    printf("\nIr para proxima pergunta?\n[1] - Sim \n[0] - Nao\n");
                    scanf("%d%*c", &exitop);
                    state.qNum += 1;

                    if (exitop == 0)
                    {
                        printf("Finalizando o jogo...");
                        exit(1);
                    }
                    break;
                }
                else
                {
                    printf("Voce perdeu");
                    exit(1);
                }
                break;

            // AJUDAS //
            // PULAR //
            case '1':
                if (state.skipCount == 0)
                    sameQuestion = 1;
                else
                    state.skipCount -= 1;
                break;
            // AJUDA DA PLATÉIA //
            case '2':
                if (state.audienceAssistancesCount == 0)
                    sameQuestion = 1;
                else
                {
                    for (int i = 1; i <= 30; i++)
                    {
                        ans = rightQ(q, state);
                        n = randomNum(1, 10);
                        if (n <= 4)
                            printf("[%c] ", ans);
                        else if (n == 5 || n == 6)
                            printf("[%c] ", nQ1);
                        else if (n == 7 || n == 8)
                            printf("[%c] ", nQ2);
                        else if (n == 9 || n == 10)
                            printf("[%c] ", nQ3);
                        if (i % 10 == 0)
                            printf("\n");
                    }
                    state.audienceAssistancesCount -= 1;
                    printf("\nResponder? (y/n)\n");
                    scanf("%c%*c", &yn);
                    if (yn == 'y' || yn == 'Y')
                        sameQuestion = 1;
                    else
                        exit(1);
                }
                break;
            // AJUDA DOS UNIVERSITÁRIOS //
            case '3':
                if (state.studentsAssistancesCount == 0)
                    sameQuestion = 1;
                else
                {
                    ans = rightQ(q, state);
                    for (int i = 0; i < 3; i++)
                    {
                        n = randomNum(1, 10);
                        if (n <= 7)
                            printf("( %c ) ", ans);
                        else if (n == 8)
                            printf("( %c ) ", nQ1);
                        else if (n == 9)
                            printf("( %c ) ", nQ2);
                        else if (n == 10)
                            printf("( %c ) ", nQ3);
                    }
                    state.studentsAssistancesCount -= 1;
                    printf("\nResponder? (y/n)\n");
                    scanf("%c%*c", &yn);
                    if (yn == 'y' || yn == 'Y')
                        sameQuestion = 1;
                    else
                        exit(1);
                }
                break;
            // AJUDA DAS CARTAS //
            case '4':
                if (state.cardsAssistancesCount == 0)
                    sameQuestion = 1;
                else
                {
                    printCards();
                    cardAux(q, state);
                    state.cardsAssistancesCount -= 1;
                }
                printf("\nResponder? (y/n)\n");
                scanf("%c%*c", &yn);
                if (yn == 'n' || yn == 'N')
                    exit(1);
                else
                    sameQuestion = 1;
                break;
            // SAIR //
            case '5':
                printf("\nDeseja mesmo desistir? \n[1] - Sim\n[0] - Nao\n");
                scanf("%d%*c", &exitop);
                if (exitop == 1)
                {
                    printf("Finalizando o jogo...");
                    exit(1);
                }
                else
                    sameQuestion = 1;
                break;

            default:
                sameQuestion = 1;
                break;
            }
        }
    }
    fclose(questions);
    return 0;
}
// FUNÇÕES
int selectRandomQuestion(struct playerState *state)
{
    if (state->difficult == 1)
        return randomNum(0, 19);
    else if (state->difficult == 2)
        return randomNum(20, 39);
    else if (state->difficult == 3)
        return randomNum(40, 59);
    else if (state->difficult == 4)
        return randomNum(60, 69);
}

void printQuestion(struct pergunta q[70], struct playerState *state, int sameQuestion)
{
    if (sameQuestion == 0)
    {
        alt[0] = 'a';
        alt[1] = 'b';
        alt[2] = 'c';
        alt[3] = 'd';
        if (state->qNum >= 1 && state->qNum <= 5)
            state->difficult = 1;
        else if (state->qNum >= 6 && state->qNum <= 10)
            state->difficult = 2;
        else if (state->qNum >= 11 && state->qNum <= 15)
            state->difficult = 3;
        else if (state->qNum >= 16)
            state->difficult = 4;
        state->currQ = selectRandomQuestion(state);
    }
    printf("\n################  SHOW DO MILHAO  ################\n");
    printf("\nPERGUNTA %d          Total acumulado: [R$ %d.00]\n", state->qNum, state->money);
    printf("\n%s\n", q[state->currQ].descricao);
    printf("\n(%c) %s\n", alt[0], q[state->currQ].alt[0]);
    printf("(%c) %s\n", alt[1], q[state->currQ].alt[1]);
    printf("(%c) %s\n", alt[2], q[state->currQ].alt[2]);
    printf("(%c) %s\n", alt[3], q[state->currQ].alt[3]);
    printf("\n---------------------- AJUDA ----------------------\n");
    printf("\n[1] Pular pergunta ............................(%dx)\n", state->skipCount);
    printf("[2] Pedir ajuda a plateia .....................(%dx)\n", state->audienceAssistancesCount);
    printf("[3] Pedir ajuda aos universitarios ............(%dx)\n", state->studentsAssistancesCount);
    printf("[4] Pedir ajuda as cartas .....................(%dx)\n", state->cardsAssistancesCount);
    printf("[5] Parar\n");
    printf("\n###################################################\n");
    scanf("%c%*c", &op);
}

int randomNum(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

void printCards()
{
    int selectedCard;
    printf("\nEscolha uma carta: \n");
    printf(" _________    _________    _________    _________\n");
    printf("|   [1]   |  |   [2]   |  |   [3]   |  |   [4]   |\n");
    printf("|   ___   |  |   ___   |  |   ___   |  |   ___   |\n");
    printf("|  |   |  |  |  |   |  |  |  |   |  |  |  |   |  |\n");
    printf("|  | X |  |  |  | X |  |  |  | X |  |  |  | X |  |\n");
    printf("|  |___|  |  |  |___|  |  |  |___|  |  |  |___|  |\n");
    printf("|_________|  |_________|  |_________|  |_________|\n");

    scanf("%d%*c", &selectedCard);
}

char rightQ(struct pergunta q[70], struct playerState state)
{
    char ans;

    if (q[state.currQ].alt_correta == 'a')
    {
        ans = 'a';
        nQ1 = 'b';
        nQ2 = 'c';
        nQ3 = 'd';
    }
    if (q[state.currQ].alt_correta == 'b')
    {
        ans = 'b';
        nQ1 = 'a';
        nQ2 = 'c';
        nQ3 = 'd';
    }
    if (q[state.currQ].alt_correta == 'c')
    {
        ans = 'c';
        nQ1 = 'b';
        nQ2 = 'a';
        nQ3 = 'd';
    }
    if (q[state.currQ].alt_correta == 'd')
    {
        ans = 'd';
        nQ1 = 'b';
        nQ2 = 'c';
        nQ3 = 'a';
    }

    return ans;
}

void cardAux(struct pergunta q[70], struct playerState state)
{
    int card = randomNum(0, 3);
    printf("\n[Com essa carta voce elimina %d Questoes (ao)]\n", card);
    for (int i = 0; i < card; i++)
    {
        if (alt[i] != rightQ(q, state))
        {
            alt[i] = 'x';
        }
        else
        {
            card++;
        }
    }
}