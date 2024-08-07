//Last Edited 17-11-2022 16:12 IST
#include<stdio.h>
#include<windows.h>
#include<MMSystem.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

#define MAX_STRING_SIZE 100

#define SongLibrary "./Songs"
#define ProjectLocation "./"
#define PlaylistLibrary "./Playlists"

#define PlaylistsFolderName "Playlists"

int play(char []);
void next_node();
void insert(char [MAX_STRING_SIZE]);

FILE *fp;  

char SongName[MAX_STRING_SIZE];
int LineCount;
char temp[MAX_STRING_SIZE];
char PlaylistName[MAX_STRING_SIZE];

int DirectoryContent(char folder[MAX_STRING_SIZE])
{
	LineCount= 0;
    DIR *directory;
    struct dirent *entry;
    
    directory = opendir(folder);
	if (directory == NULL)
	{
	    printf("\n\t\t\tError opening directory.\n");
	    return 1;
	}
	
	if(strcmp(folder, SongLibrary) ==0)
	{
		strcpy(temp,"");	strcpy(temp,SongLibrary);	strcat(temp,".txt");	
		fp= fopen(temp,"w");
		while ((entry = readdir(directory)) != NULL)
	    {	
	       	if(	(strcmp(entry->d_name,".")!=0) && (strcmp(entry->d_name,"..")!=0) )
	       	{
	       		++LineCount;
	       		fprintf(fp,"%d\t%s\n",LineCount,entry->d_name);
			}
	    }
	    
	    fclose(fp);
	}
	else
	{
		strcpy(temp,"");	strcpy(temp, ProjectLocation);	strcat(temp,"Playlists.txt");	
		fp= fopen(temp,"w");
		printf("\n\t\t\tS.No\tPlaylist");
		while ((entry = readdir(directory)) != NULL)
	    {	
	       	if(	(strcmp(entry->d_name,".")!=0) && (strcmp(entry->d_name,"..")!=0) )
	       	{
	       		++LineCount;
	       		fprintf(fp,"%d\t%s\n",LineCount,entry->d_name);
	       		fprintf(stdout,"\n\t\t\t%d\t%s",LineCount,entry->d_name);
			}
	    }
	    fclose(fp);
	}
	if (closedir(directory) == -1)
	{
		printf("Error closing directory.\n");
		return 1;
	}
	
}

int CreatePlaylist()
{
	EmptyPlaylist();
	FILE *f;
	int SongNumber, SNo=0;
	strcpy(temp,SongLibrary);	strcat(temp,".txt");	//puts(temp);
	f= fopen(temp,"r");
	
	printf("\n\t\t\tEnter a Name for Playlist : ");
	scanf("%s",PlaylistName);
	strcpy(temp,PlaylistLibrary);	strcat(temp,"/");	strcat(temp,PlaylistName);	strcat(temp,".txt");	puts(temp);
	fp= fopen(temp,"w");
	printf("\n\n\t\t\t\tNOTE: Press 'Ctr+Z' to stop adding songs\n\n");
	TextFileDisplay(SongLibrary);
	printf("\n\t\t\tEnter S.No of song to add : ");
		while( fscanf(stdin,"%d",&SongNumber) != EOF)
		{
			//printf("\nSongNumber is %d",SongNumber);
			while(fscanf(f,"%d\t%s",&LineCount,SongName)!=EOF)
			{
				//printf("\nLineCount is %d\tSongName is %s",LineCount, SongName);
				if(LineCount== SongNumber)
				{
					++SNo;
					fprintf(fp,"%d\t%s\n",SNo,SongName);
					printf("\n\t\t\tSong added to Playlist : %s\n\n",SongName);
					break;
				}
			}
			fseek(f, 0, SEEK_SET);
			printf("\n\t\t\tEnter S.No of song to add : ");
		}
	fclose(f);
	fclose(fp);
	printf("\n\t\t\t\tPlaylist loaded is : %s", PlaylistName);
	printf("\n\t\t\tPress any key to continue : ");
   	getch();
	strcpy(temp, PlaylistLibrary);	strcat(temp, "/");	strcat(temp, PlaylistName);	strcat(temp,".txt");	//puts(temp);
	fp= fopen(temp, "r");
	if(fp==NULL)
		printf("\n\t\t\tError Opening File!!\n");
	while( fscanf(fp, "%d\t%s",&LineCount, SongName)!= EOF)
	{
		//puts(SongName);
		insert(SongName);
	}
	system("cls");
	PlaylistMenu();
}

int TextFileDisplay(char TextFile[MAX_STRING_SIZE])
{
	strcpy(temp, TextFile);	strcat(temp, ".txt");
	FILE *p;
	p= fopen(temp,"r");
	puts(temp);
	printf("\n\t\t\tS.No\tName");
	while(fscanf(p,"%d\t%s",&LineCount, SongName)!=EOF)
	{
		fprintf(stdout,"\n\t\t\t%d\t%s",LineCount, SongName);
	}
}

int PlayPlaylist()
{
	EmptyPlaylist();
	int PlaylistNumber;
	DirectoryContent(PlaylistLibrary);
	strcpy(temp, ProjectLocation);	strcat(temp, PlaylistsFolderName);	strcat(temp, ".txt");

	fp= fopen(temp, "r");
	//puts(temp);
	//TextFileDisplay(temp);
	
	printf("\n\n\t\t\tEnter S.No of Playlist to load : ");
	scanf("%d",&PlaylistNumber);
	
			while(fscanf(fp,"%d\t%s",&LineCount,PlaylistName)!=EOF)
			{
//				printf("\nLineCount is %d\tPlaylistName is %s",LineCount, PlaylistName);
				if(LineCount== PlaylistNumber)
				{
					printf("\n\t\t\tPlaylist loaded is : %s",PlaylistName);
					printf("\n\t\t\tPress any key to continue : ");
    				getch();
					break;
				}
			}
	fclose(fp);
	
	
	strcpy(temp, PlaylistLibrary);	strcat(temp, "/");	strcat(temp, PlaylistName);	//puts(temp);
	fp= fopen(temp, "r");
	if(fp==NULL)
		printf("\n\n\t\tError Opening File");
	while( fscanf(fp, "%d\t%s",&LineCount, SongName)!= EOF)
	{
		//puts(SongName);
		insert(SongName);
	}
	system("cls");
	PlaylistMenu();
}

int stop()
{
	PlaySound(TEXT(""),NULL,SND_APPLICATION);
}

int play(char SongName[MAX_STRING_SIZE])
{
	strcpy(temp,SongLibrary);	strcat(temp, "/");	strcat(temp,SongName);	//puts(temp);
	PlaySound(temp,NULL,SND_ASYNC);	
	printf("\n\t\t\tPlaying Song : %s",SongName);
	printf("\n\t\t\tYOUR MUSIC PLAYLIST IS LOVELY :D\n\t\t\tTHIS SONG GIVES CHILLS ;D\n");
}

struct node{
    char data[40];
    struct node*next;
    struct node*prev;
};

struct node*head=NULL;
struct node*current_node=NULL;

void insert(char SongName[MAX_STRING_SIZE])
{
    struct node* new_node=(struct node*)malloc(sizeof(struct node));
    strcpy(new_node->data,SongName);
    if(head==NULL){
        new_node->next=new_node->prev=new_node;
        head=current_node=new_node;
        return;
    }
    struct node*last=head->prev;
    new_node->prev=last;
    last->next=new_node;
    new_node->next=head;
    head->prev=new_node;
}

void RemoveSong(){
    if(head==NULL){
        printf("\n\t\t\tNo Music is there to delete!");
        return;
    }
    printf("\n\t\t\tEnter Song name to remove from playlist (Ex: Faded.wav) : ");
    while((getchar())!='\n');
    scanf("%[^\n]%*c",temp);
    struct node*ptr=head;
    do{
        if(ptr->next==ptr && strcmp(ptr->data,temp)==0){
            printf("\n\t\t\tSong Removed! Playlist is Empty Now!");
            head=NULL;
            free(ptr);
            return;
        }
        else if(strcmp(ptr->data,temp)==0){
            struct node*prev=ptr->prev;
            struct node*next=ptr->next;
            prev->next=next;
            next->prev=prev;
            head=next;
            free(ptr);
            printf("\n\t\t\tSong Removed!");
            return;
        }
        ptr=ptr->next;
    }while(ptr!=head);
    printf("\n\t\t\tNo Song Found!");
}

void ShowPlaylist()
{
    if(head==NULL){
        printf("\n\t\t\tPlaylist is Empty!");
        return;
    }
    struct node*show_ptr=head;
    printf("\n");
    int i=1;
    printf("\n\t\t\tDisplaying Playlist :\n");
    do{
        printf("\n\t\t\tSong %d : %s\n",i,show_ptr->data);
        i++;
        show_ptr=show_ptr->next;
    }while(show_ptr!=head);
    printf("\n\t\t\tHave a look at the playlist and press any key to continue : ");
    getch();
}

void NextSong(){
    if(current_node==NULL){
        printf("\n\t\t\tNo songs in Playlist!\n");
    }
    else{
        current_node=current_node->next;
        play(current_node->data);
        printf("\n\t\t\tPlaying Next Song : %s\n",current_node->data);
    }
}

void PrevSong()
{
    if(current_node==NULL){
        printf("\n\t\t\tNo songs in Playlist!\n");
    }
    else{
        current_node=current_node->prev;
        play(current_node->data);
        printf("\n\t\t\tPlaying Previous Song : %s\n",current_node->data);
    }
}

void FirstSong()
{
    if(head==NULL){
        printf("\n\t\t\tPlaylist is Empty!");
    }
    else{
        printf("\n\t\t\tPlaying First Music : %s",head->data);
        play(head->data);
    }
}

void LastSong(){
    if(head==NULL){
        printf("\n\t\t\tPlaylist is Empty!\n");
    }
    else{
        printf("\n\t\t\tPlaying Last Music : %s\n",head->prev->data);
        play(head->prev->data);
    }
}


////NOT WORKING
//void specific_data(){
//    if(head==NULL){
//        printf("No music is there to be searched!\n");
//        return;
//    }
//    printf("Enter Music Name :\n");
//    while((getchar())!='\n');
//    scanf("%[^\n]%*c",temp);
//    printf("\n");
//    struct node*ptr=head;
//    do{
//        if(strcmp(ptr->data,temp)==0){
//            printf("Music Found!\n");	stop();
//            play(temp);
//            printf("Playing Music : %s\n",ptr->data);
//            return;
//        }
//        ptr=ptr->next;
//    }while(ptr!=head);
//    printf("There is no Music file with this name!\n");
//}
int main()
{
	DirectoryContent(SongLibrary);	//Creates a text file for all songs in SongLibrary
	//system("COLOR 4G");         
	system("COLOR 0E");  
	MainMenu();
}

int EmptyPlaylist()
{
	if(head==NULL)
		return;
  	else 
	{
	    
	    //1. if head is not null create a temp node
	    //   and current node pointed to next of head
	    //Node *temp, *current;
	    struct node* ptr;
	    current_node= head;
	    //current_node = head->next;
	    
	    //2. if current node is not equal to head, delete the
	    //   current node and move current to next node using temp,
	    //   repeat the process till the current reaches the head
	    while(current_node != head)
		{
	      ptr = current_node->next;
	      free(current_node);
	      current_node = ptr;
	    }
	
	    //3. Delete the head
	    free(head);
	    head = NULL;
	}
}

int PlaylistMenu()
{
    char option[2];
	do
	{ 
		printf("\n\t\t\t----------------------------------------------");
		printf("\n\t\t\t                 PLAYLIST MENU");
		printf("\n\t\t\t----------------------------------------------");
	    printf("\n\t\t\t1. Remove a song from playlist\n");
	    printf("\n\t\t\t2. Show Playlist\n");
	    printf("\n\t\t\t3. Play next song\n");
	    printf("\n\t\t\t4. Play previous Song,\n");
	    printf("\n\t\t\t5. Play first Song\n");
	    printf("\n\t\t\t6. Play Last Song\n");
	    //printf("8. Play specific file.\n");
	    printf("\n\t\t\t0. Go to MainMenu\n\n");
	    printf("\n\t\t\tPrevious Song: %s\tFirst/Current Song : %s        Next Song: %s\n\n",current_node->prev->data,current_node->data,current_node->next->data);
	    printf("\n\n\t\t\tEnter your choice : ");
	    scanf(" %c",&option[0]);
        switch(option[0])
        {
        	case '0':	system("cls");MainMenu();system("cls");
        	case '1':	system("cls");RemoveSong();system("cls");
        		break;
			case '2':	system("cls");ShowPlaylist();system("cls");
        		break;
			case '3':	system("cls");NextSong();system("cls");
        		break;
			case '4':	system("cls");PrevSong();system("cls");
        		break;
			case '5':	system("cls");FirstSong();system("cls");
        		break;
			case '6':	system("cls");LastSong();system("cls");
        		break;
			//case '8':	specific_data();
        	//	break;
			default:printf("\n\t\t\tInvalid Input.\n\t\t\tInput must be integer only. Try Again!!!");				
		}
	}while(1);
return 0;
}

int MainMenu()
{
	char option[2];  
	do
	{ 
		//system("cls");		//Not Ideal
		printf("\n\t\t\t----------------------------------------------");
		printf("\n\t\t\t                  MAIN MENU");
		printf("\n\t\t\t----------------------------------------------\n");
	    printf("\n\t\t\t1. Create a playlist\n");
	    printf("\n\t\t\t2. Play a existing Playlist\n");
	    printf("\n\t\t\t0. Exit Application\n\n");
	    printf("\n\t\t\tEnter your choice : ");
	    scanf(" %c",&option[0]);
        switch(option[0])
        {
        	case '0':	exit(0);
        	case '1':	system("cls");CreatePlaylist();system("cls");
        		break;
			case '2':	system("cls");PlayPlaylist();system("cls");
        		break;

			default:printf("\n\t\t\tInvalid Input.\n\t\t\tInput must be integer only. Try Again!!!");				
		}
	}while(1);
return 0;
}
