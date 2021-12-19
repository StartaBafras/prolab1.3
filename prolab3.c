//Beyhan KARADAĞ 190201012 Alperen KOLAT 200201006
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue //kuyruk yapisi
{
    int priority_id;
    int plane_id;
    int order_Landing_Time;
    struct Queue *next;
} Queue;

Queue *landing(Queue *P_Queue, int time);

int out_Put_add(Queue *P_Queue,int plane_landing_time);

int print_Queue(Queue *P_Queue);

int controller(Queue *P_Queue);

Queue* add(Queue *P_Queue,int priority,int plane_id, int d_time);

int rotar(Queue *P_Queue, int time);



int main()
{

    Queue *Queue_list = NULL;
    controller(Queue_list);

    free(Queue_list);
    return 0;
}


Queue *landing(Queue *P_Queue, int time)
{

    FILE *file_output;
    if ((file_output = fopen("output.txt", "a")) == NULL)
    {
        printf("dosya acma hatasi!");
        return 1;
    }

    fprintf(file_output, "%d %d %d \n", P_Queue->priority_id, P_Queue->plane_id,time + 1);//inis saatini bi saat

    fclose(file_output);

    Queue *temp = P_Queue;
    P_Queue = P_Queue->next;
    printf("\n%d Kuyruk numarali ucak inis yaptı.",temp->plane_id);
    free(temp);

    return P_Queue;
}


int print_Queue(Queue *P_Queue) //kuyrugu bastırılır
{

    while (P_Queue != NULL)
    {

        printf("Oncelik ->%2d \tucak id ->%2d \torder_Landing_Time ->%2d \n", P_Queue->priority_id, P_Queue->plane_id, P_Queue->order_Landing_Time);
        P_Queue = P_Queue->next;
    }

    return 1;
}

int controller(Queue *P_Queue)
{
    int temp1;
    int temp2;
    int temp3;
    int Landing_Time = 1;
    FILE *file1;
    if ((file1 = fopen("input.txt", "r")) == NULL)
    {
        printf("dosya acma hatasi!");
        return 1;
    }

    while (Landing_Time != 25) //24 saaatlik dilimi kontrol
    {

        while (!feof(file1))
        {
            fscanf(file1, "%d %d %d", &temp1, &temp2, &temp3);

            if (temp3 == Landing_Time) //saat göre o saat iniş yapıcak uçakları  kuyruga ekler
            {
                P_Queue = add(P_Queue,temp1,temp2,temp3);
            }
        }

        printf("\n");
        printf(" \t \t SAAt %d:00  \n\n", Landing_Time);


        print_Queue(P_Queue); //kuyruk her saat ekranda gösterilir

        rotar(P_Queue,Landing_Time);

        if(P_Queue != NULL) P_Queue = landing(P_Queue,Landing_Time); //kuyruktan inis yapan ucak silinir

       

        Landing_Time++; //saat ilerletilir

        rewind(file1);
    }

    fclose(file1);
    return 1;
}


Queue* add(Queue *P_Queue,int priority,int plane_id, int d_time)
{
    if(P_Queue == NULL)
    {
        Queue *new = malloc(sizeof(Queue));
        new->order_Landing_Time = d_time;
        new->plane_id = plane_id;
        new->priority_id = priority;
        return new;
    }
    if( P_Queue->next != NULL)
    {
        if(P_Queue->priority_id <= priority && P_Queue->next->priority_id <= priority )
        {
            add(P_Queue->next,priority,plane_id,d_time);
            return P_Queue;
        }
        
    }
        Queue *new = malloc(sizeof(Queue));

        new->next = NULL;
        new->order_Landing_Time = d_time;
        new->plane_id = plane_id;
        new->priority_id = priority;

        if(P_Queue->priority_id > priority)
        {
            new->next = P_Queue;
            return new;
        }
        else
        {
            if(P_Queue->next != NULL) new->next = P_Queue->next;
            P_Queue->next = new;
        }

    
    return P_Queue;
}

int rotar(Queue *P_Queue, int time)
{
    if(P_Queue != NULL)
    {
        while (P_Queue->next != NULL)
        {

            if (time - P_Queue->next->order_Landing_Time == 3)
            {
                printf("\n sabihaya gönderildi\n\n");
                printf("priority ->%2d \tplane id ->%2d \torder_Landing_Time ->%2d \n\n", P_Queue->next->priority_id, P_Queue->next->plane_id, P_Queue->next->order_Landing_Time);

                Queue *tmp = P_Queue->next;
                P_Queue->next = P_Queue->next->next;
                free(tmp);
                P_Queue = P_Queue->next;

            }
            else P_Queue = P_Queue->next;
            
        }
    }

}

