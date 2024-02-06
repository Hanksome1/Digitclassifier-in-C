#include "hidden_layer.h"
#include "output_layer.h"
#include <stdio.h> 

short int ReLu(short int number);

int main(){
    unsigned char word[]={
0b00011000,
0b00100100,
0b00100100,
0b00011000,
0b00100100,
0b00100100,
0b00011000,
0b00000000
    };
    short int hidden_node[18]= { } ; // declaration of the node of the hidden layer
    int output_node[10]= { }; //declaration of the node of the output layer
    for(int i=0; i<18; i++){ // calculating 18 node separately
        for(int k=0; k<8; k++){ 
            int temp=0b10000000;  // this temp number is used for filtering the j-th number of the word[k]
            for(int j=0; j<8;j++){  
                if(temp & word[k]){ // if word[k][j] is one -> then add the corresponding weight
                    hidden_node[i]+=hidden_layer_weight[64*i+8*k+j];   // add the weight to the hidden node of the neutral network
                }
                temp=temp>>1; // right shift to filter next number
            }
        }
    }
    for(int i=0; i<18; i++){
        hidden_node[i] = ReLu(hidden_node[i]+hidden_layer_bias[i]); // adding the bias of the model to every node and apply activation function(ReLu function)
    }
    for(int i=0;i<18; i++){
        printf("hidden node %d %d \n", i+1, hidden_node[i]); 
    }
    // evaluating the vlaue of the output layer
    for(int i=0; i<10; i++){
        for(int j=0; j<18; j++){
            output_node[i]+=hidden_node[j]*output_layer_weight[18*i+j];
        }
    }
    for(int i=0; i<10; i++){
        output_node[i] = ReLu(output_node[i]+output_layer_bias[i]); // adding the bias of the model to every node and apply activation function(ReLu function)
    }

    for(int k=0; k<8; k++){ 
            int temp=0b10000000;  // this temp number is used for filtering the j-th number of the word[k]
            for(int j=0; j<8;j++){  
                if(temp & word[k]){ // if word[k][j] is one -> then add the corresponding weight
                    printf("#");
                }
                else printf(".");
                temp=temp>>1; // right shift to filter next number
        }
        printf("\n");
    }

    for(int i=0;i<10; i++){
        printf("number%d, possibility:%d\n", i, output_node[i]);
    }
    int highest=0;
    int highest_number=output_node[0];
    for(int i=0;i<10;i++){
        if(output_node[i]>highest_number){
            highest=i;
            highest_number=output_node[i];
        }
    }
    printf("the number you draw is \" %d \"", highest);
}

short int ReLu(short int number){
    if(number>0) return number; 
    else return 0;
}