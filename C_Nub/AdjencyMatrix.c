//Coded by : Hamora Hadi

#include<stdio.h>
#include<string.h>

void main(){
    int adj_mat[10][10];
    int i,j,n;
    int con;

    printf("Set how many the nodes : ");
    scanf("%d",&n);
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            adj_mat[i][j]=0;
        }
    }
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i == j){
                adj_mat[i][j] = 0;
                continue;
            }
            printf("Do you want to connect %d node to %d node if yes press 0 : ",i,j);
            scanf("%d",&con);
            
            if(con == 0){
                adj_mat[i][j] = 1;
            }
            else{
                adj_mat[i][j] = 0;
            }
        }
    }
    
    printf("\n\nAdjacency Matrix: \n\n");
    for(i=0;i<n;i++){
        int con_edges=0,x,m=0;
        for(j=0;j<n;j++){
            if(adj_mat[i][j] == 1){
                con_edges++;
            }
        }
        printf("\n%d total edges = %d",i,con_edges);
        printf("\n\n%d is connected to ",i);
            for(x=0;x<n;x++){
                if(adj_mat[i][x] == 1){
                    printf("->%d",x);
                }
            }
            printf("\n");
    }
}
