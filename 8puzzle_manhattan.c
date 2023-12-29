#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int min(int x,int y)
{
	if(x<y)
		return x;
	else 
		return y;
}
void display(int mat[][3])
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
}
}
void copy(int mat1[][3],int mat2[][3])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			mat1[i][j]=mat2[i][j];
}
int check(int mat1[][3],int mat2[][3])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(mat1[i][j]!=mat2[i][j])
				return 0;
	return 1;
}
void set_to_zero(int mat[][3])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			mat[i][j]=0;
}
int man_dist(int mat[][3],int key,int ki,int kj)
{
	int i,j,dist;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(mat[i][j]==key)
			{
				dist=abs(ki-i)+abs(kj-j);
				return dist;
			}
		}
	}
	return 99;
}
void calc_manhattan(int temp[][3],int temp0[][3],int temp1[][3],int temp2[][3],int temp3[][3],int target[][3],int prev[][3])
{
	int i,j;
	int key;
	int dist0=0,dist1=0,dist2=0,dist3=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			key=target[i][j];
			if(key!=0)
			{
				dist0+=man_dist(temp0,key,i,j);
				dist1+=man_dist(temp1,key,i,j);
				dist2+=man_dist(temp2,key,i,j);
				dist3+=man_dist(temp3,key,i,j);
			}
		}
	}
	printf("\nManhattan distance:\nt0=%d\nt1=%d\nt2=%d\nt3=%d\n",dist0,dist1,dist2,dist3);
	int min1=min(dist0,dist1);
	int min2=min(dist2,dist3);
	int final_min=min(min1,min2);
	printf("Least manhattan distance=%d\n",final_min);
	
	copy(prev,temp);//store value of temp into prev before changing it
	
	if(dist0==final_min)
		copy(temp,temp0);
	else if(dist1==final_min)
		copy(temp,temp1);
	else if(dist2==final_min)
		copy(temp,temp2);
	else 
		copy(temp,temp3);
	
}
void inversion_check(int start[][3])
{
	int i,j,k=0,inv=0;
	int arr[9];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			arr[k]=start[i][j];//convert matrix to 1d array
			k++;
		}
	}
	for(i=0;i<9;i++)
	{
		for(j=i+1;j<9;j++)
		{
			if(arr[i]&&arr[j]&&arr[i]>arr[j])
				inv++;
		}
	}
	if(inv%2!=0)
	{
		printf("Given instance is not solvable as number of inversions is odd!");
		exit(0);
	}
	else
		printf("Number of inversions is even.Solvable!\n");
}
void main()
{
	int i,j,k;
	int i0,j0;
	int limit,flag=0;
	int start[3][3]={{1,2,3},{8,0,4},{7,5,6}};
	int target[3][3]={{1,2,3},{4,5,6},{7,8,0}};
	
	int temp[3][3],temp0[3][3],temp1[3][3],temp2[3][3],temp3[3][3];
	int prev[3][3];
	
	inversion_check(start);//check whether 8 puzzle solvable or not
	
	printf("Enter Depth limit = ");
	scanf("%d",&limit);
	
	//start timer
	struct timespec begin;
    timespec_get(&begin, TIME_UTC);
    
	copy(temp,start);
	for(i=0;i<limit;i++)
	{
		set_to_zero(temp0);
		set_to_zero(temp1);
		set_to_zero(temp2);
		set_to_zero(temp3);
		
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				if(temp[j][k]==0)
				{
					i0=j;
					j0=k;	
				}
			}
		}
		//found position of 0
		
		if(i0==1&&j0==1)//4 subtrees
		{
			copy(temp0,temp);
			temp0[1][1]=temp0[0][1];
			temp0[0][1]=0;
			
			copy(temp1,temp);
			temp1[1][1]=temp1[1][0];
			temp1[1][0]=0;
			
			copy(temp2,temp);
			temp2[1][1]=temp2[1][2];
			temp2[1][2]=0;
			
			copy(temp3,temp);
			temp3[1][1]=temp3[2][1];
			temp3[2][1]=0;
		}
		else if(abs(i0-j0)==1)//3 subtrees
		{
			if(j0==1)
			{
				copy(temp0,temp);
				temp0[i0][j0]=temp0[i0][j0-1];
				temp0[i0][j0-1]=0;
				
				copy(temp1,temp);
				temp1[i0][j0]=temp1[i0][j0+1];
				temp1[i0][j0+1]=0;
				
			}
			else
			{
				copy(temp0,temp);
				temp0[i0][j0]=temp0[i0-1][j0];
				temp0[i0-1][j0]=0;
				
				copy(temp1,temp);
				temp1[i0][j0]=temp1[i0+1][j0];
				temp1[i0+1][j0]=0;
			}
			copy(temp2,temp);
			temp2[i0][j0]=temp2[1][1];
			temp2[1][1]=0;
			
		}
		else //2 subtrees
		{
			if(i0==0)
			{
				copy(temp0,temp);
				temp0[i0][j0]=temp0[i0+1][j0];
				temp0[i0+1][j0]=0;
				
				copy(temp1,temp);
				temp1[i0][j0]=temp1[0][1];
				temp1[0][1]=0;
			
			}
			else
			{
				copy(temp0,temp);
				temp0[i0][j0]=temp0[i0-1][j0];
				temp0[i0-1][j0]=0;
				
				copy(temp1,temp);
				temp1[i0][j0]=temp1[2][1];
				temp1[2][1]=0;	
			}
		}
		printf("temp0\n");
		display(temp0);
		printf("\ntemp1\n");
		display(temp1);
		printf("\ntemp2\n");
		display(temp2);
		printf("\ntemp3\n");
		display(temp3);
		
		if(i>0)
		{
			if(check(prev,temp0))
				set_to_zero(temp0);
			else if(check(prev,temp1))
				set_to_zero(temp1);
			else if(check(prev,temp2))
				set_to_zero(temp2);
			else if(check(prev,temp3))
				set_to_zero(temp3);
		}
		
		calc_manhattan(temp,temp0,temp1,temp2,temp3,target,prev);
		
		printf("\nNew state\n");
		display(temp);
		printf("\n");
		
		if(check(temp,target))
		{
			flag=1;
			break;
		}	
	}
	if(flag==0)
	{
		printf("8 Puzzle not solved");
	}
	else
	{
		printf("8 Puzzle solved\nSolution:\n");
		display(temp);
	}
	
	struct timespec end;
    timespec_get(&end, TIME_UTC);
    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;

    printf("\nProgram execution time: %lf\n", time_spent);
}







