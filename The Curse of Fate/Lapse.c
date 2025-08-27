#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include<time.h>
#include<stdbool.h>
#define SCENARIO_COUNT 20
#define MAX_LEN 512

int ekonomi  = 50;
int guvenlik = 50;
int doga     = 50;
int halk     = 50;

struct Change {
    int ekonomi;
    int guvenlik;
    int doga;
    int halk;
};

struct Change rightChange[SCENARIO_COUNT] = {
    {+30, 0, -25, 0},
    {-15, +30, 0, 0},
    {-30, 0, +30, +10},
    {+20, 0, 0, -30},
    {+20, -20, 0, 0},
    {+30, +20, -30, 0},
    {-20, 0, 0, +30},
    {-25, +30, 0, +10},
    {+30, 0, -30, 0},
    {-20, 0, 0, +20},
    {0, +30, 0, 0},
    {+40, 0, -30, 0},
    {-30, 0, 0, +30},
    {0, +20, 0, -30},
    {+30, 0, 0, +20},
    {-10, +30, 0, 0},
    {-25, 0, +30, +10},
    {+30, 0, 0, -20},
    {0, +20, 0, -30},
    {-20, 0, 0, +20}
};

struct Change leftChange[SCENARIO_COUNT] = {
    {-20, 0, +20, 0},
    {+20, -20, 0, 0},
    {-40, 0, -20, -20},
    {-20, 0, 0, +20},
    {+20, +20, 0, -20},
    {-20, 0, +20, -20},
    {+20, 0, 0, -20},
    {0, -30, 0, -20},
    {-20, 0, +20, 0},
    {+10, 0, 0, -10},
    {0, -30, 0, 0},
    {-25, 0, +30, 0},
    {+20, 0, 0, -20},
    {0, +20, 0, +20},
    {-20, 0, 0, -20},
    {-20, -30, 0, 0},
    {+20, 0, -20, -10},
    {-20, 0, 0, +10},
    {0, -20, 0, +20},
    {+10, 0, 0, -10}
};

char makeDecission(){
    char secim='a';
        printf("Seciminizi yapiniz(R/L): ");
        while(secim!='r' && secim!='R' && secim!='l' && secim!='L'){
            scanf("%c",&secim);
        }
    return secim;
}

void PrintSlow(char *word){
    int count=0;

    for(int i=0;i<strlen(word);i++){
        if(count>50 && word[i]==' '){
            printf("\n");
            count=0;
        }
        else{
            printf("%c",word[i]);
            count++;
        }
        fflush(stdout);
        Sleep(5);
    }
    printf("\n");
}


void showStats(){

    if(ekonomi > 100) ekonomi = 100;
    if(guvenlik > 100) guvenlik = 100;
    if(doga > 100) doga = 100;
    if(halk > 100) halk = 100;

    if(ekonomi<=0 || guvenlik<=0 || doga<=0 || halk<=0){
        PrintSlow("Oyun Sona Erdi Kaybettiniz!\n");
        exit(0);
    }

    char buffer[100];

    sprintf(buffer, "\nEkonomi: %d/100", ekonomi);
    PrintSlow(buffer);

    sprintf(buffer, "Guvenlik: %d/100", guvenlik);
    PrintSlow(buffer);

    sprintf(buffer, "Doga: %d/100", doga);
    PrintSlow(buffer);

    sprintf(buffer, "Halk: %d/100\n", halk);
    PrintSlow(buffer);
}


char *scenarios[SCENARIO_COUNT];
int scenarioCount = 0;

void loadScenarios() {
    FILE *fp = fopen("Olaylar.txt", "r");
    if (!fp) {
        printf("Senaryo dosyasi acilamadi!\n");
        exit(1);
    }

    char buffer[MAX_LEN];

while (fgets(buffer, sizeof(buffer), fp)) {
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }


    scenarios[scenarioCount] = strdup(buffer);
    scenarioCount++;

    if (scenarioCount >= SCENARIO_COUNT) {
        break;
    }
}

    fclose(fp);
}


void randomSituationGenarator(){

    loadScenarios();

    int coolDown[SCENARIO_COUNT];
    for (int i = 0; i < SCENARIO_COUNT; i++) {
        coolDown[i] = 0;
    }

    for(int i=0;i<SCENARIO_COUNT;i++){
        int randomScene;
        while(true){
            randomScene= rand() % SCENARIO_COUNT;
            if(coolDown[randomScene]==0){
                break;
            }
        }
        printf("Tur: %d\n",i+1);
        PrintSlow(scenarios[randomScene]);

        coolDown[randomScene]=1;

        showStats();

        char secim = makeDecission();

        if(secim == 'r' || secim== 'R'){
            ekonomi   += rightChange[randomScene].ekonomi;
            guvenlik  += rightChange[randomScene].guvenlik;
            doga      += rightChange[randomScene].doga;
            halk      += rightChange[randomScene].halk;
        }
        else {
            ekonomi   += leftChange[randomScene].ekonomi;
            guvenlik  += leftChange[randomScene].guvenlik;
            doga      += leftChange[randomScene].doga;
            halk      += leftChange[randomScene].halk;
        }

        showStats();

        if(i==(SCENARIO_COUNT-1)){
            PrintSlow("Tebrikler Kazandiniz!\n");
            exit(0);
        }
    }

}

int main(){
    srand(time(NULL));
    PrintSlow("Oyun icerisindeki secimlerinize gore birtakim degerler degismektedir R ya da r olayi onayladiginizi , l ya da L reddettiginizi gostermektedir.\n");
    showStats();
    randomSituationGenarator();
}
