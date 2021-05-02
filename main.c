#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
char player_name[30];
int people = 50, court = 50, treasury = 50;
char *file_names[20][20];
//global variables done
//===================================================

struct problem{
    char problem_set[200];
    char choice_1[200];
    int effect_1_people , effect_1_court, effect_1_treasury;
    char choice_2[200];
    int effect_2_people , effect_2_court, effect_2_treasury;
    int chance;
    int index;
};

struct node{
    struct problem  problem;
    struct node *next;
};

struct save_information{
    char name[30];
    int situation;//--------> if game was over or not. 0 means:it was in the mid 1 means:it was over
    int lines;
    int problem_chance[30];
    int ppl;
    int cour;
    int treas;
};

void delay_clear(void)
{
    for(int i = 0 ; i < 20000; i++)
        for(int j = 0; j < 25000; j++);
    system("cls");
}

void loading(void)
{
    printf("LOADING ...\n10%%\n");
    delay_clear();
    printf("LOADING\n28%%\n");
    delay_clear();
    printf("LOADING .\n35%%\n");
    delay_clear();
    printf("LOADING ..\n42%%\n");
    delay_clear();
    printf("LOADING ...\n57%%\n");
    delay_clear();
    printf("LOADING\n69%%\n");
    delay_clear();
    printf("LOADING .\n78%%\n");
    delay_clear();
    printf("LOADING ..\n90%%\n");
    delay_clear();
    printf("LOADING ...\n98%%\n");
    delay_clear();
    printf("LOADING\n99%%\n");
    delay_clear();
    printf("LOADING .\n100%%\n");
    delay_clear();
    printf("LOADING COMPELETED\n");
}

void saving(void)
{
    printf("SAVING ...\n10%%\n");
    delay_clear();
    printf("SAVING\n20%%\n");
    delay_clear();
    printf("SAVING .\n35%%\n");
    delay_clear();
    printf("SAVING ..\n41%%\n");
    delay_clear();
    printf("SAVING ...\n50%%\n");
    delay_clear();
    printf("SAVING\n63%%\n");
    delay_clear();
    printf("SAVING .\n70%%\n");
    delay_clear();
    printf("SAVING ..\n88%%\n");
    delay_clear();
    printf("LOADING ...\n97%%\n");
    delay_clear();
    printf("LOADING\n99%%\n");
    delay_clear();
    printf("LOADING .\n100%%\n");
    delay_clear();
    printf("SAVING COMPELETED\n");
}

void add_end(struct node *list, struct problem temperory)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    struct node *current;
    for(current = list; current -> next != NULL; current = current -> next);
    current -> next = new_node;
    new_node -> problem = temperory;
    new_node -> next = NULL;
}

void delete_node(struct node **plist, struct node *del)
{
    if(*plist == del)
    {
        (*plist) = del -> next;
        free(del);
        return;
    }
    struct node *current = *plist;
    while(current -> next != del)
    {
        current = current -> next;
    }
        current -> next = del -> next;
        free(del);
}

struct node * create_node(struct problem temperory)
{
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    head -> next = NULL;
    strcpy(head -> problem.problem_set, temperory.problem_set);
    strcpy(head -> problem.choice_1, temperory.choice_1);
    strcpy(head-> problem.choice_2, temperory.choice_2);
    head -> problem.effect_1_court = temperory.effect_1_court;
    head -> problem.effect_1_people = temperory.effect_1_people;
    head -> problem.effect_1_treasury = temperory.effect_1_treasury;
    head -> problem.effect_2_court = temperory.effect_2_court;
    head -> problem.effect_2_people = temperory.effect_2_people;
    head -> problem.effect_2_treasury = temperory.effect_2_treasury;
    head -> problem.chance = temperory.chance;
    head -> problem.index = temperory.index;
    return head;
}

void print_list(struct node *list)
{
    struct node *curret;
    for(curret = list; curret != NULL; curret = curret -> next)
    {
        printf("%s", curret -> problem.problem_set);
        printf("%s", curret -> problem.choice_1);
        printf("%d\n", curret -> problem.effect_1_people);
        printf("%d\n", curret -> problem.effect_1_court);
        printf("%d\n", curret -> problem.effect_1_treasury);
        printf("%s", curret -> problem.choice_2);
        printf("%d\n", curret -> problem.effect_2_people);
        printf("%d\n", curret -> problem.effect_2_court);
        printf("%d\n", curret -> problem.effect_2_treasury);
        printf("%d\n", curret -> problem.chance);
        printf("%d\n", curret -> problem.index);
    }
}

void print_random_node(struct node *list, int rand)
{
    struct node *current = list;
    if(rand == current -> problem.index)
    {
        printf("%s\n", current -> problem.problem_set);
        printf("1. %s",current -> problem.choice_1);
        printf("2. %s", current -> problem.choice_2);
        current -> problem.chance--;
    }
    else
    {
        while(1)
        {
            current = current -> next;
            if(rand == current -> problem.index)
            {
                printf("%s", current -> problem.problem_set);
                printf("1. %s",current -> problem.choice_1);
                printf("2. %s", current -> problem.choice_2);
                current -> problem.chance--;
                break;
            }
        }
    }
}

int node_counter(struct node *list)
{
    int ctr = 0;
    struct node *current;
    for(current = list; current != NULL; current = current -> next)
        ctr++;
    return ctr;
}

int random_number(int i)
{
    time_t t = time(NULL);
    srand(t);
    int r;
    r = rand() % i;
    return r;
}

struct node * find_rand(struct node *list, int index)
{
    struct node *current;
    for(current = list; current != NULL; current = current -> next)
    {
        if(index == current -> problem.index)
            return current;
    }
}

int file_line_counter(void)
{
    FILE *f;
    f = fopen("CHOICES.txt", "r");
    if(f == NULL)
    {
        printf("ERROR");
        exit(-1);
    }
    char buff[100];
    int ctr = 0;
    while(1)
    {
        fgets(buff, 50, f);
        ctr++;
        if(feof(f))
            break;
    }
    return ctr;
}

void file_fixer(int lines)
{
    FILE *f;
    f = fopen("CHOICES.txt", "r");
    if(f == NULL)
    {
        printf("ERROR\n");
        exit(-1);
    }
    for(int i = 0; i < lines; i++)
        fscanf(f, "%s", file_names[i]);
}

int node_index_initializer(struct node *list)
{
    struct node *current;
    int i = 0;
    for(current = list; current != NULL; current = current -> next)
    {
        current -> problem.index = i;
        i++;
    }
    return i;
}

struct node * make_node(int lines)
{
    struct node *list;
    char temp[200];
    FILE *F;
    struct problem temperory;
    int flag = 0;
    int ctr = 0;
    for(int i = 0; i < lines; i++)
    {
        F = fopen(file_names[i], "r");
        fgets(temp, 200, F);
        strcpy(temperory.problem_set, temp);
        fgets(temp, 200, F);
        strcpy(temperory.choice_1, temp);
        fscanf(F, "%d", &temperory.effect_1_people);
        fgetc(F);
        fscanf(F, "%d", &temperory.effect_1_court);
        fgetc(F);
        fscanf(F, "%d", &temperory.effect_1_treasury);
        fgetc(F);
        fgets(temp, 200, F);
        strcpy(temperory.choice_2, temp);
        fscanf(F, "%d", &temperory.effect_2_people);
        fgetc(F);
        fscanf(F, "%d", &temperory.effect_2_court);
        fgetc(F);
        fscanf(F, "%d", &temperory.effect_2_treasury);
        fgetc(F);
        temperory.chance = 3;
        temperory.index = i;
        if(flag == 0)
        {
            flag = 1;
            list = create_node(temperory);
        }
        else
            add_end(list, temperory);
    }
    return list;
}

int main()
{
    int lines = file_line_counter();
    file_fixer(lines);
    printf("Welcome to the game \n\n");
    printf("Enter your name :\n");
    scanf("%s", player_name);
    printf("Welcome LORD %s\n", player_name);
    printf("1.Resume game\n2.New game\n");
    int tmp;
    struct node *list;
    scanf("%d", &tmp);
    struct save_information save;
    if(tmp == 1)
    {
        FILE *fl;
        fl = fopen("SAVED GAMES\\S.bin", "rb");
        if(fl == NULL)
        {
            printf("There Is No Saved Game!");
            exit(-1);
        }
        fseek(fl, 30, SEEK_SET);
        int situation;
        fread(&situation, sizeof(int), 1, fl);
        int temp_chance[30];
        if(situation == 0)
        {
            rewind(fl);
            fread(&player_name, sizeof(char), 30 ,fl);
            fseek(fl, sizeof(int), SEEK_CUR);
            fread(&lines, sizeof(int), 1, fl);
            fread(&people, sizeof(int), 1, fl);
            fread(&court, sizeof(int), 1, fl);
            fread(&treasury, sizeof(int), 1, fl);
            for(int i = 0; i < lines; i++)
                fread(&temp_chance[i], sizeof(int), 1, fl);
            loading();
        }
        if(situation == 1)
        {
            strcpy(save.name, player_name);
            save.situation = 1;
            save.lines = lines;
            for(int i = 0; i < lines; i++)
                save.problem_chance[i] = 3;
            save.ppl = 50;
            save.cour = 50;
            save.treas = 50;
            loading();
        }
    }
    if(tmp == 2)
    {
        printf("Welcome To The Game.\nGood Luck:)\n\n\n\n");
    }
    list = make_node(lines);
    struct node *tempe;
    int tmp1, tmp2[100] = {100};
    printf("Press 0 IF You Want To Quit.\n");
    //delay(3000);
    system("cls");
    int j = 0;
    tempe = list;
    int new_index;
    int i = node_index_initializer(list);
    int tmp3 = 0;//for save or not
    struct node *curr;//for save
    while(1)
    {
        if(i == 0)
        {
            //list = make_node(lines);
            //i = node_index_initializer(list);
            printf("YOU WON 1 ROUND!");
        }
        tmp = random_number(i);
        printf("people: %d  court: %d  treasury: %d\n", people, court, treasury);
        print_random_node(list, tmp);
        tempe = find_rand(list, tmp);
        scanf("%d", &tmp1);
        if(tmp1 == 0)
        {
            printf("Do You Want To Save The Game???\n\n1.YES\n2.NO\n");
            scanf("%d", &tmp3);
            if(tmp3 == 1)
            {
                int i = 0;
                strcpy(save.name, player_name);
                save.situation = 0;
                save.lines = node_counter(list);
                for(curr = list; curr != NULL; curr = curr -> next)
                {
                    save.problem_chance[i] = curr -> problem.chance;
                    i++;
                }
                //delay(3000);
                save.ppl = people;
                save.cour = court;
                save.treas = treasury;
                FILE *fs1;//save
                fs1 = fopen("SAVED GAMES\\S.bin", "wb");
                if(fs1 == NULL)
                {
                    printf("ERROR");
                    exit(-1);
                }
                saving();
                fwrite(save.name, sizeof(char), 30, fs1);
                fwrite(&save.situation, sizeof(int), 1, fs1);
                fwrite(&save.lines, sizeof(int), 1, fs1);
                fwrite(&save.ppl, sizeof(int), 1, fs1);
                fwrite(&save.cour, sizeof(int), 1, fs1);
                fwrite(&save.treas, sizeof(int), 1, fs1);
                for(int j = 0; j < i; j++)
                    fwrite(&save.problem_chance[j], sizeof(int), 1, fs1);
                printf("GOOD LUCK ;)\n");
                return 0;
            }
            if(tmp3 == 2)
            {
                printf("GOOD LUCK ;)\n");
                return 0;
            }
        }
        if(tmp1 == 1)
        {
            people += tempe -> problem.effect_1_people;
            court += tempe -> problem.effect_1_court;
            treasury += tempe -> problem.effect_1_treasury;
            if(people > 100)
                people = 100;
            if(court > 100)
                court = 100;
            if(treasury > 100)
                treasury = 100;
        }
        if(tmp1 == 2)
        {
            people += tempe -> problem.effect_2_people;
            court += tempe -> problem.effect_2_court;
            treasury += tempe -> problem.effect_2_treasury;
            if(people > 100)
                people = 100;
            if(court > 100)
                court = 100;
            if(treasury > 100)
                treasury = 100;
        }
        system("cls");
        if(tempe -> problem.chance == 0)
        {
            delete_node(&list, tempe);
            i = node_index_initializer(list);
        }
        if(people <= 0 || court <= 0 || treasury <= 0 || ((people + court + treasury) / 3) < 10)
        {
            printf("Game Over:(\nDo You Want To Save The Game???\n\n1.YES\n2.NO\n");
            scanf("%d", &tmp);
            if(tmp == 1)
            {
                FILE *fs;
                fs = fopen("SAVED GAMES\\S.bin", "wb");
                if(fs == NULL)
                {
                    printf("ERROR\n");
                    exit(-1);
                }
                saving();
                strcpy(save.name, player_name);
                save.situation = 1;
                save.lines = lines;
                for(curr = list; curr != NULL; curr = curr -> next)
                {
                    save.problem_chance[i] = tempe -> problem.chance;
                    i++;
                }
                save.ppl = people;
                save.cour = court;
                save.treas = treasury;
                fwrite(save.name, sizeof(char), 30, fs);
                fwrite(&save.situation, sizeof(int), 1, fs);
                fwrite(&save.lines, sizeof(int), 1, fs);
                for(int j = 0; j < i; j++)
                    fwrite(&save.problem_chance[i], sizeof(int), 1, fs);
                fwrite(&save.ppl, sizeof(int), 1, fs);
                fwrite(&save.cour, sizeof(int), 1, fs);
                fwrite(&save.treas, sizeof(int), 1, fs);
                printf("Good Luck ;)\n");
                return 0;
            }
            if(tmp == 2)
            {
                printf("Good Luck ;)\n");
                return 0;
            }
        }
    }
    return 0;
}
