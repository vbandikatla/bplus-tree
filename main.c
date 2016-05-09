#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max_child 4     //number of children
#define min_keys 1      //number of keys
#define level_one 2     //first level keys

typedef struct datatag
{
    int anum;
    char book[15];
    char author[15];
    int isbn;
    char publisher;
    int price;
} data_type;

typedef struct data_tag
{
    data_type data[max_child];
    struct node_tag *next;
    struct node_tag *prev;
    int active;
    int key_num;

} dnode;

typedef struct i_tag
{
    int key[max_child];
    struct node_tag *x[max_child];
} inode;

typedef struct node_tag
{
    int type;
    union {
        dnode d_node;
        inode i_node;
    };
    struct node_tag *parent;
} node;

//****************ALL FUNCTIONS ***********************************
node *make_node(int i);
node *insert(node *root, node **lptr, data_type data);
void print_database(node *lptr);
int insert_into_array(data_type a[], data_type data, int mode);
node *insert_inode(int key, node *parent, node *q, node *temp, node *root);
node *adjust_link_list(node *p, node **lptr);
node *delete (node *root, int anum, node **lptr);
node *merge_inode(node *q, node *parent, node *root);

int main()
{
    node *root = NULL, *lptr = NULL;
    data_type data, d[level_one];
    int k;
    char option[10];

    while (true)
    {
        system("cls");
        printf("YOUR OPTIONS:\n");
        printf("1) INSERT YOUR DATA \n");
        printf("7) PRINT THE DATABASE \n");
        printf("8) EXIT THE PROGRAM \n");
        printf("*********************************\n");
        printf("YOUR OPTION:");
        scanf("%s", option);
        if (strcmp(option, "2") == 0)
        {
            system("cls");
            printf("GIVE THE ACCESS NUMBER OF THE RECORD TO DELETE\n");
            scanf("%d", &data.anum);
            root = delete (root, data.anum, &lptr);
        }
        else if (strcmp(option, "8") == 0)
        {
            break;
        }
        else if (strcmp(option, "1") == 0)
        {
            system("cls");
            printf("ENTER THE DETAILS :\n \n \n");
            printf("\nENTER THE ACCESS NUMBER OF THE BOOK :");
            scanf("%d", &data.anum);
            printf("\nENTER THE NAME OF THE BOOK :");
            scanf("%s", data.book);
            printf("\nENTER THE AUTHOR OF THE BOOK :");
			scanf("%s",data.author);
			printf("\nENTER THE ISBN NUMBER :");
			scanf("%d",&data.isbn);
			printf("\nENTER THE PUBLISHER :");
			scanf("%s",data.publisher);
			printf("\nENTER THE PRICE OF THE BOOK:");
			scanf("%d",&data.price);
            printf("\n******************************************\n");
            root = insert(root, &lptr, data);
        }
        else if (strcmp(option, "7") == 0)
        {

            print_database(lptr);
        }
    }

    return 0;
}

node *make_node(int i)
{
    node *p;
    int j;
    p = (node *)malloc(sizeof(node));
    p->type = i;
    if (i == 1)
    {
        p->parent = NULL;
        for (j = 0; j < max_child; j++)
        {
            ((p->d_node).data[j]).anum = -1;
            (p->d_node).next = NULL;
            (p->d_node).prev = NULL;
            (p->d_node).active = 0;
        }
    }
    else if (i == 0)
    {
        p->parent = NULL;
        for (j = 0; j <= max_child - 1; j++)
        {
            (p->i_node).key[j] = -1;
            (p->i_node).x[j] = NULL;
        }
        (p->i_node).x[max_child - 1] = NULL;
    }
    else
    {
        printf("ERROR IN MAKING THE NEW NODE \n INVALID NODE TYPE IS GIVEN\n");
        getch();
    }
    return p;
}

node *insert(node *root, node **lptr, data_type data)
{
    node *p = root, *q, *temp, *tempo;
    int u, v = 0;
    node *n1, *n2;
    int anum = data.anum, j, k, min_keysi, median, flag2 = 1;
    data_type data2, d[level_one];
    if (p == NULL)
    {
        n1 = make_node(1);
        n2 = make_node(0);
        n1->parent = n2;
        (n2->i_node).x[0] = n1;
        (n2->i_node).key[0] = anum + 1;
        (n1->d_node).data[0] = data;
        (n1->d_node).active = 1;
        (n1->d_node).key_num = 1;
        root = n2;
        *lptr = n1;
    }
    else
    {
        while (p->type == 0)
        {
            k = -1;
            //printf("the anum is %d\n",anum);
            for (j = 0; j < max_child - 1; j++)
            {
                if ((p->i_node).key[j] <= anum && (p->i_node).key[j] != -1)
                {

                    if (1)
                    {
                        printf("checking for cousin\n");
                        printf("the key is %d\n", (p->i_node).key[j]);
                        //	printf("the active elemnts is %d\n",(p->i_node).active);
                        getch();
                    }

                    k = j;
                }
                if ((p->i_node).key[j] == -1)
                {
                    j = max_child;
                }
            }
            k++; //IMPORTANT CHECK HERE IF ERROR COMES
            if (1)
            {
                printf("%d is k value\n", k);
                getch();
            }

            if (k < 0)
            {
                printf("ERROR IN INSERT BECAUSE KEY VALUE IS GOING LESS THAN min_keys\n");
                getch();
            }
            q = p;
            p = (p->i_node).x[k];
            if (p != NULL)
            {
                /*	if(anum>=37)
			{
				printf("the active elemnts is %d\n",(p->d_node).active);
				printf("the type of node is %d\n",(p->type));
				getch();
			}*/
            }

            if (p == NULL)
            {
                /*	if(anum>=22)
				{
					printf("p IS NULL so now while is going to break\n");
				getch();
				}*/

                break;
            }
        }
        printf("completed while loop\n");
        getch();
        flag2 = 1;
        if ((q->i_node).x[0] != NULL)
        {

            if (k == 1 && (((q->i_node).x[0])->d_node).active <= max_child && min_keysi != -1 && p == NULL)
            {
                printf("the 1st node not filled\n");
                getch();
                if ((((q->i_node).x[0])->d_node).active == max_child)
                {
                    temp = make_node(1);
                    (temp->d_node).data[0] = (((q->i_node).x[0])->d_node).data[max_child - 1];
                    ((((q->i_node).x[0])->d_node).data[max_child - 1]).anum = -1;
                    (((q->i_node).x[0])->d_node).active = max_child - 1;
                    min_keysi = insert_into_array((temp->d_node).data, data, 1);
                    (temp->d_node).active = 2;
                }
                if ((((q->i_node).x[0])->d_node).active < max_child)
                {
                    (q->i_node).key[0] = anum + 1;
                    min_keysi = insert_into_array((((q->i_node).x[0])->d_node).data, data, 1);
                    ((((q->i_node).x[0])->d_node).active)++;
                    //((p->d_node).data[1]).anum=-1;
                    //(p->d_node).data[0]=data;
                    //(p->d_node).active=1;
                    min_keysi = -1;
                    flag2 = 0;
                }
            }
        }
        else
        {
            printf("initial error\n");
            getch();
            flag2 = 0;
        }

        if (p != NULL && flag2 == 1)
        {

            //printf("checking data already exists or not\n");
            //getch();
            min_keysi = insert_into_array((p->d_node).data, data, 0);
            /*	if(anum==15)
		{
			printf("the data which is going to insert is %d\n",data.anum);
			printf("after while loop value of min_keysi is %d\n",min_keysi);
			printf("the k value is %d",k);
			getch();}*/

            if ((p->d_node).active < max_child && min_keysi != -1)
            {
                min_keysi = insert_into_array((p->d_node).data, data, 1);
                ((p->d_node).active)++;
            }
            else if (min_keysi != -1)
            {
                if ((p->d_node).active == max_child)
                {

                    if (p == (q->i_node).x[max_child - 1])
                    {
                        /*if(anum==37)
							{
								printf("LETS SEE THIS CASE \n");
								getch();
							}*/

                        printf("last node case\n");
                        getch();

                        if (anum < ((p->d_node).data[level_one + 1]).anum)
                        {
                            data2 = (p->d_node).data[max_child - 1];
                            ((p->d_node).data[max_child - 1]).anum = -1;
                            min_keysi = insert_into_array((p->d_node).data, data, 1);
                            data = data2;
                            anum = ((p->d_node).data[level_one + 1]).anum;
                        }

                        v = 0;
                        for (u = level_one + 1; u <= max_child - 1; u++)
                        {
                            d[v] = (p->d_node).data[level_one + v + 1];
                            ((p->d_node).data[level_one + v + 1]).anum = -1;
                            ((p->d_node).active)--;
                            v++;
                        }
                        d[v] = data;

                        (q->i_node).key[max_child - 1] = d[0].anum;
                        printf("the key sent up is %d\n", (q->i_node).key[max_child - 1]);
                        getch();
                        if (max_child % 2 == 0)
                        {
                            median = (max_child / 2);
                        }
                        else
                        {
                            median = (max_child - 1) / 2;
                        }
                        int n, m;
                        m = 0;
                        temp = make_node(0);
                        temp->parent = q->parent;
                        for (n = median + 1; n < max_child; n++) //check here n<max_child or n<max_child-1
                        {
                            (temp->i_node).key[m] = (q->i_node).key[n];
                            (q->i_node).key[n] = -1;
                            (temp->i_node).x[m] = (q->i_node).x[n];
                            (q->i_node).x[n] = NULL;
                            m++;
                        }
                        (temp->i_node).x[m] = NULL;
                        //if(q->parent!=NULL)
                        //printf("the key in array at last is %d\n",((q->parent)->i_node).key[max_child-1]);
                        /*if(data.anum>=44)//check here
							{
								printf("%d  is made as median\n",(q->i_node).key[median]);
								getch();
							}*/
                        //	printf("key 0 before insertion %d \n",(root->i_node).key[0]);
                        printf("%d  is made as median\n", (q->i_node).key[median]);
                        getch();

                        root = insert_inode((q->i_node).key[median], q->parent, q, temp, root);
                        printf("the previous value at median poition is %d\n", (q->i_node).key[median]);
                        (q->i_node).key[median] = -1;
                        printf("the present value at median poition is %d\n", (q->i_node).key[median]);
                        //	printf("key 0 after insertion %d \n",(root->i_node).key[0]);
                        //	printf("key 0 after insertion %d \n",(root->i_node).key[1]);
                        //	printf("anum of data is %d\n",data.anum);
                        getch();
                        printf("the data going to insert is %d \n", d[0].anum);
                        printf("the data going to insert is %d \n", d[1].anum);
                        getch();
                        for (u = 0; u <= min_keys; u++)
                        {
                            data = d[u];

                            root = insert(root, lptr, data);
                        }

                        //	root=insert(root,lptr,data);
                    }
                    else if (anum > ((p->d_node).data[level_one + 1]).anum)
                    {
                        (q->i_node).key[k] = ((p->d_node).data[level_one + 1]).anum;
                        printf("the updated key is %d\n", (q->i_node).key[k]);
                        printf("the k is %d\n", k);
                        getch();

                        v = 0;
                        for (u = level_one + 1; u <= max_child - 1; u++)
                        {
                            d[v] = (p->d_node).data[level_one + v + 1];
                            printf(" %d data is saving into array of datas\n", v);
                            printf("the data saved is %d \n", d[v].anum);

                            ((p->d_node).data[level_one + v + 1]).anum = -1;
                            ((p->d_node).active)--;
                            v++;
                        }
                        d[v] = data;
                        printf("the data saved is %d \n", d[v].anum);
                        printf(" %d data is saving into array of datas\n", v);
                        printf("----------------\n");
                        getch();
                        /*	if(anum>=18)
							{
								printf("3rd key is updated\n");
								getch();
							}*/

                        for (u = 0; u <= min_keys; u++)
                        {
                            data = d[u];
                            printf("(397)now the data going to be inserted is %d\n", data.anum);
                            getch();
                            root = insert(root, lptr, data);
                        }
                    }
                    else
                    {

                        data2 = (p->d_node).data[max_child - 1];
                        ((p->d_node).data[max_child - 1]).anum = -1;
                        //(p->d_node).data[max_child]=data;
                        min_keysi = insert_into_array((p->d_node).data, data, 1);
                        (q->i_node).key[k] = ((p->d_node).data[level_one + 1]).anum;
                        printf("the updated key is %d in 2nd else \n", (q->i_node).key[k]);
                        getch();
                        v = 0;
                        for (u = level_one + 1; u <= max_child - 1; u++)
                        {
                            d[v] = (p->d_node).data[level_one + v + 1];
                            ((p->d_node).data[level_one + v + 1]).anum = -1;
                            ((p->d_node).active)--;
                            v++;
                        }
                        d[v] = data2;
                        for (u = 0; u <= min_keys; u++)
                        {
                            data = d[u];
                            root = insert(root, lptr, data);
                        }
                    }
                }
            }
        }
        else if (flag2 == 1)
        {
            /*if(anum>=18)
			{
				printf("p is null so it entered into else part\n");
				getch();
			}*/
            temp = make_node(1);
            (q->i_node).x[k] = temp;
            p = temp;
            p->parent = q;
            (p->d_node).key_num = k;
            min_keysi = insert_into_array((p->d_node).data, data, 1);
            (p->d_node).active = 1;
            //	printf("IT REACHED HERE \n");
            //	getch();
            if (k < ((*lptr)->d_node).key_num && p->parent == (*lptr)->parent)
            {
                //	printf("it enterd into if 1\n");
                //getch();
                (temp->d_node).next = *lptr;
                (temp->d_node).prev = NULL;
                ((*lptr)->d_node).prev = temp;

                *lptr = temp;
                //printf("lptr is changed\n");
                //getch();
            }
            else
            {
                //printf("it enterd into if 2\n");
                //getch();
                if ((((*lptr)->d_node).data[0]).anum > anum)
                {
                    //printf("it enterd into if 3\n");
                    //getch();
                    (temp->d_node).next = *lptr;
                    (temp->d_node).prev = NULL;
                    ((*lptr)->d_node).prev = temp;

                    *lptr = temp;
                }
                else
                {
                    //	printf("it enterd into if 4\n");
                    //	getch();
                    node *head = *lptr;
                    node *before;
                    while (((head->d_node).data[0]).anum < anum)
                    {
                        //printf("IT ENTERD INTO WHILE LOOP\n");
                        //getch();
                        before = head;
                        head = (head->d_node).next;
                        if (head == NULL)
                        {
                            break;
                        }
                    }

                    if (head == NULL)
                    {
                        //	printf("IT IS ENTEREING INTO if PART\n");
                        //	getch();
                        (before->d_node).next = temp;
                        (temp->d_node).prev = before;
                        (temp->d_node).next = NULL;
                    }
                    else
                    {
                        //printf("IT IS ENTEREING INTO ELSE PART\n");
                        //getch();
                        (temp->d_node).next = head;
                        (temp->d_node).prev = (head->d_node).prev;
                        (((head->d_node).prev)->d_node).next = temp;
                        (head->d_node).prev = temp;
                    }
                }
            }
        }
    }
    return root;
}

void print_database(node *lptr)
{
    int i;

    if (lptr == NULL || lptr == 0)
    {
        printf("\n \n \n****************************************************");
        printf(" \nTHE DATABASE IS EMPTY\n");
        printf("****************************************************");
    }
    else
    {
        while (lptr != NULL)
        {
            for (i = 0; i < max_child; i++)
            {

                if (((lptr->d_node).data[i]).anum != -1)
                {
                    printf("THE ACCESS NUMBER IS %d \n", ((lptr->d_node).data[i]).anum);
                    printf("THE BOOK NAME IS %s\n", ((lptr->d_node).data[i]).book);
                    /*	printf("THE AUTHOR IS %s\n",((lptr->d_node).data[i]).author);
					printf("THE PRICE IS %d\n",((lptr->d_node).data[i]).price);
					printf("THE ISBN NUMBER IS %d\n",((lptr->d_node).data[i]).isbn);
					printf("THE PUBLISHER IS %s\n",((lptr->d_node).data[i]).publisher);
				*/
                    printf("*********************************************\n");
                }
                else
                {
                    i = max_child;
                }
            }
            printf("the active number in this node is %d\n", (lptr->d_node).active);
            lptr = ((lptr->d_node)).next;

            printf("--------------------\n");
        }
    }
    getch();
}
int insert_into_array(data_type a[], data_type data, int mode)
{
    int anum = data.anum;
    int flag = 1, j, k, l, flag2 = 1;
    k = -1;
    for (j = 0; j <= max_child - 1 && flag == 1 && flag2 == 1; j++)
    {
        if (a[j].anum <= anum && a[j].anum != -1)
        {
            if (a[j].anum == anum)
            {
                printf("DATA ALREADY FOUND. NOW IT GETS UPDATED\n");
                getch();
                a[j] = data;
                flag2 = 0;
            }
            k = j;
        }
        if (a[j].anum == -1)
        {
            flag = 0;
            j--;
        }
    }
    k++;
    l = j;
    if (flag2 == 1 && mode == 1)
    {
        while (j > k)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[k] = data;
    }
    if (flag2 != 1)
    {
        return -1;
    }

    return a[0].anum;
}
node *insert_inode(int key, node *parent, node *q, node *temp, node *root)
{
    node *n, *temp1;
    int j, k, flag = 1, median, n1, m;
    //printf("ENTERED INTO INSERT INODE FUNCTION\n");
    //getch();
    if (parent == NULL)
    {
        n = make_node(0);
        //	printf("the key in array at last is in fuction is%d\n",(n->i_node).key[max_child-1]);
        printf("the key came is %d\n", key);
        getch();
        (n->i_node).key[0] = key;
        (n->i_node).x[0] = q;
        (n->i_node).x[1] = temp;
        q->parent = n;
        temp->parent = n;
        root = n;
    }
    else
    {
        //	printf("the parent node last key is %d\n",(parent->i_node).key[max_child-2]);
        //	getch();

        if ((parent->i_node).key[max_child - 2] == -1)
        {
            printf("this is the 1st if in insert i node\n");
            printf("the parents 1st key is %d \n", (parent->i_node).key[0]);
            getch();

            /*printf("LETS SEE THIS CASE SOON\n");
			printf("the key came to split is %d\n",key);
			getch();*/
            for (k = max_child - 2; k >= 0 && flag == 1; k--)
            {
                if ((parent->i_node).key[k] == -1)
                {
                }
                else
                {
                    if ((parent->i_node).key[k] > key)
                    {
                        (parent->i_node).key[k + 1] = (parent->i_node).key[k];
                        (parent->i_node).x[k + 2] = (parent->i_node).x[k + 1];
                    }
                    if ((parent->i_node).key[k] < key)
                    {
                        flag = 0;
                        k++;
                    }
                }
            }
            if ((parent->i_node).key[k] < key)
            {
                (parent->i_node).key[k + 1] = key;
                (parent->i_node).x[k + 2] = temp;
                (parent->i_node).x[k + 1] = q;
            }
            else if ((parent->i_node).key[k] > key)
            {
                (parent->i_node).key[k] = key;
                (parent->i_node).x[k + 1] = temp;
                (parent->i_node).x[k] = q;
            }
            printf("the parents 1st key after process is %d \n", (parent->i_node).key[0]);
            getch();
            //root=insert(root,)
            /*	printf("now we see the new keys array formed\n");
			k=0;
			
			while((parent->i_node).key[k]!=-1&&k<max_child-1)
			{
				printf("%d ",(parent->i_node).key[k]);
				k++;
			}
			printf("\n");
			getch();
		/*	printf("it is going out of the function \n");
			getch();*/
        }
        else
        {
            //	printf("LETS SEE THIS CASE LATER bla bla\n");
            //	printf("the key sent is %d\n",key);
            //	getch();
            printf("this is the 2nd else in insert i node\n");
            getch();
            q = parent;
            (q->i_node).key[max_child - 1] = key;
            if (max_child % 2 == 0)
            {
                median = (max_child / 2);
            }
            else
            {
                median = (max_child - 1) / 2;
            }
            m = 0;
            temp1 = make_node(0);
            temp1->parent = q->parent;
            for (n1 = median + 1; n1 < max_child; n1++)
            {
                (temp1->i_node).key[m] = (q->i_node).key[n1];
                (q->i_node).key[n1] = -1;
                (temp1->i_node).x[m] = (q->i_node).x[n1];
                (q->i_node).x[n1] = NULL;
                m++;
            }
            (temp1->i_node).x[m] = temp;
            (temp->parent) = temp1;

            root = insert_inode((q->i_node).key[median], q->parent, q, temp1, root);
            (q->i_node).key[median] = -1;
        }
    }
    return root;
}
node *delete (node *root, int anum, node **lptr)
{
    node *p = root, *q, *prev, *next;
    int j, k, m, n, flag = 1, min_keysi, merge = 0;
    data_type data[min_keys + 1];

    if (root == NULL)
    {
        system("cls");
        printf("THE DATABASE IS EMPTY YOU CANNOT DELETE ANYTHING\n");
        getch();
    }
    else
    {

        while (p->type == 0)
        {
            k = -1;

            for (j = 0; j < max_child - 1; j++)
            {

                if ((p->i_node).key[j] <= anum && (p->i_node).key[j] != -1)
                {
                    /*if(anum==11)
					{
					//	printf("checking for cousin\n");
					///	printf("the key is %d\n",(p->i_node).key[j]);
					//	printf("the active elemnts is %d\n",(p->i_node).active);
						getch();
					}*/

                    k = j;
                }
                if ((p->i_node).key[j] == -1)
                {
                    j = max_child;
                }
            }
            k++; //IMPORTANT CHECK HERE IF ERROR COMES

            printf("%d is k value\n", k);
            getch();

            if (k < 0)
            {
                printf("ERROR IN DELETION BECAUSE KEY VALUE IS GOING LESS THAN min_keys\n");
                getch();
            }
            q = p;
            p = (p->i_node).x[k];
            /*	if(p==NULL)
			{
				printf("p is becomin_keysg null\n");
				getch();
			}
			else*/

            if (p != NULL)
            {
                /*	if(anum>=37)
			{
				printf("the active elemnts is %d\n",(p->d_node).active);
				printf("the type of node is %d\n",(p->type));
				getch();
			}*/
            }

            if (p == NULL)
            {
                /*	if(anum>=22)
				{
					printf("p IS NULL so now while is going to break\n");
				getch();
				}*/

                break;
            }
        }
    }

    if (p == NULL)
    {
        printf("\n**********************************************\n \n");
        printf("THE DATA GIVEN IS NOT FOUND IN THE DATABASE \n");
        printf("\n**********************************************\n \n");
        getch();
    }
    else
    {
        for (m = 0; m < max_child && flag == 1; m++)
        {

            if (((p->d_node).data[m]).anum == anum)
            {
                flag = 0;
            }
            if (((p->d_node).data[m]).anum == -1)
            {
                m = max_child;
            }
        }

        m--; //now m is the index of the array which contains the data
        printf("in deletion the index m of the anum value %d is %d\n", anum, m);
        getch();
        if (flag == 0)
        {
            if (anum == 7 || anum == 10)
            {
                printf("the active number of this node very initially is %d\n", (p->d_node).active);
                getch();
            }
            for (n = m; n <= max_child - 1; n++)
            {
                ((p->d_node).data[n]).anum = -1;
                if (((p->d_node).data[n + 1]).anum != -1)
                {
                    (p->d_node).data[n] = (p->d_node).data[n + 1];
                    //((p->d_node).data[n+1]).anum=-1;
                }
                else
                {
                    n = max_child + 2;
                }
            }
            ((p->d_node).active)--;
            if (anum == 7)
            {
                printf("the active number of this node initially is %d\n", (p->d_node).active);
                getch();
            }
            ((p->d_node).data[max_child - 1]).anum = -1;
        }
        if (flag == 1)
        {
            printf("\n**********************************************\n \n");
            printf("THE DATA GIVEN IS NOT FOUND IN THE DATABASE \n");
            printf("\n**********************************************\n \n");
            getch();
        }
        else
        {
            printf("THE DATA IS FOUND NOW IT IS GOING TO BE DELETED\n");
            getch();
            if (k == max_child - 1)
            {
                if ((p->d_node).active <= min_keys)
                {
                    if ((((q->i_node).x[k - 1])->d_node).active <= (max_child - min_keys))
                    {
                        //n=0;
                        for (j = 0; j < min_keys; j++)
                        {
                            min_keysi = insert_into_array((((q->i_node).x[k - 1])->d_node).data, (p->d_node).data[j], 1);
                            ((((q->i_node).x[k - 1])->d_node).active)++;
                            ((p->d_node).data[j]).anum = -1;
                        }
                        (q->i_node).key[k - 1] = -1;
                        *lptr = adjust_link_list(p, lptr);
                        (q->i_node).x[k] = NULL;
                        free(p);
                    }
                    else
                    {
                        j = (((q->i_node).x[k - 1])->d_node).active - 1;
                        (q->i_node).key[k - 1] = ((((q->i_node).x[k - 1])->d_node).data[j]).anum;
                        min_keysi = insert_into_array((p->d_node).data, (((q->i_node).x[k - 1])->d_node).data[j], 1);
                        ((p->d_node).active)++;
                        if (min_keysi != (((q->i_node).x[k - 1])->d_node).data[j].anum)

                        {
                            printf("ERROR IN DELETION IN THE CASE K=max_child-1\n");
                            printf("AND SUFFICIANT SPACE IS NO THERE IN PREVIOUS NODE\n");
                            getch();
                        }
                        (((q->i_node).x[k - 1])->d_node).data[j].anum = -1;
                        ((((q->i_node).x[k - 1])->d_node).active)--;
                    }
                }
                else
                {
                    (q->i_node).key[k - 1] = ((p->d_node).data[0]).anum;
                }
            }
            else //deltion is not from the last data node
            {
                if ((q->i_node).x[k + 1] != NULL)
                {
                    if ((p->d_node).active <= min_keys)
                    {
                        next = (q->i_node).x[k + 1];
                        if (((next->d_node).data[1]).anum == -1)
                        {
                            if ((p->d_node).active == 0)
                            {
                                //*lptr=adjust_link_list(p,lptr);
                            }
                            else
                            {
                                if (q->parent == NULL)
                                {
                                }
                                else
                                {
                                    min_keysi = insert_into_array((p->d_node).data, (next->d_node).data[0], 1);
                                    ((p->d_node).active)++;
                                    (q->i_node).key[0] = ((next->d_node).data[0]).anum + 1;
                                    (q->i_node).x[1] = NULL;
                                    root = merge_inode(q, q->parent, root);
                                    printf("here merging takes place by updating key to key+1********************\n");
                                    getch();
                                }
                            }
                        }
                        else
                        {
                            min_keysi = insert_into_array((p->d_node).data, (next->d_node).data[0], 1);
                            ((p->d_node).active)++;
                            root = delete (root, ((next->d_node).data[0]).anum, lptr);
                            if (p != NULL)
                            {
                                (q->i_node).key[k - 1] = ((p->d_node).data[0]).anum;
                            }
                        }
                    }
                    else
                    {
                        (q->i_node).key[k - 1] = ((p->d_node).data[0]).anum;
                    }
                }
                else if ((q->i_node).x[k + 1] == NULL)
                {
                    if (1)
                    {
                        //	printf("deletion of 7\n");
                        printf("the active number of elements in this node is %d \n", (p->d_node).active);
                        printf("the previous nodes active number is %d\n", (((q->i_node).x[k - 1])->d_node).active);
                        getch();
                    }
                    if ((p->d_node).active <= min_keys && k != 0 && (p->d_node).active != 0)
                    {
                        if ((((q->i_node).x[k - 1])->d_node).active <= (max_child - min_keys))
                        {
                            //n=0;
                            for (j = 0; j < min_keys; j++)
                            {
                                min_keysi = insert_into_array((((q->i_node).x[k - 1])->d_node).data, (p->d_node).data[j], 1);
                                ((((q->i_node).x[k - 1])->d_node).active)++;
                                ((p->d_node).data[j]).anum = -1;
                            }
                            (q->i_node).key[k - 1] = -1;
                            *lptr = adjust_link_list(p, lptr);
                            (q->i_node).x[k] = NULL;
                            free(p);
                        }
                        else
                        {
                            j = (((q->i_node).x[k - 1])->d_node).active - 1;
                            (q->i_node).key[k - 1] = ((((q->i_node).x[k - 1])->d_node).data[j]).anum;
                            min_keysi = insert_into_array((p->d_node).data, (((q->i_node).x[k - 1])->d_node).data[j], 1);
                            ((p->d_node).active)++;
                            if (min_keysi != (((q->i_node).x[k - 1])->d_node).data[j].anum)

                            {
                                printf("ERROR IN DELETION IN THE CASE NEXT NODE IS NULL\n");
                                printf("AND SUFFICIANT SPACE IS NO THERE IN PREVIOUS NODE\n");
                                getch();
                            }
                            (((q->i_node).x[k - 1])->d_node).data[j].anum = -1;
                            ((((q->i_node).x[k - 1])->d_node).active)--;
                        }
                    }
                    else if ((p->d_node).active > min_keys)
                    {
                        (q->i_node).key[k - 1] = ((p->d_node).data[0]).anum;
                    }
                    else if ((p->d_node).active <= min_keys && k != 0 && (p->d_node).active == 0)
                    {
                        prev = (q->i_node).x[k - 1];
                        if (prev == NULL)
                        {
                            root = NULL;
                            free(p);
                            *lptr = NULL;
                        }
                        else
                        {
                            printf("here merging takes place*************************\n");
                            getch();
                            root = merge_inode(q, q->parent, root);
                        }
                    }
                    else if ((p->d_node).active <= min_keys && k == 0 && (p->d_node).active != 0)
                    {
                        printf(" ERROR IN DELETION\n");
                        printf("this node contains only one data node and it exists\n");
                        getch();
                    }
                }
            }
        }
    }
    return root;
}
node *adjust_link_list(node *p, node **lptr)
{
    node *prev, *next;
    if (p == *lptr)
    {
        *lptr = (p->d_node).next;
    }
    else
    {
        if ((p->d_node).next == NULL)
        {
            prev = (p->d_node).prev;
            (prev->d_node).next = NULL;
        }
        else
        {
            prev = (p->d_node).prev;
            next = (p->d_node).next;
            if (next == NULL || prev == NULL)
            {
                printf("ERROR IN ADJUST LINK LIST FUNCTION CHECK 916\n");
                getch();
            }
            else
            {
                (next->d_node).prev = prev;
                (prev->d_node).next = next;
            }
        }
    }
    return (*lptr);
}

node *merge_inode(node *q, node *parent, node *root)
{
    if (parent == NULL)
    {
    }
    return root;
}