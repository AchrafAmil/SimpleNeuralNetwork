#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct Neuron{
    float value;
    float links[2];     //to the right
    float corr;
} Neuron;

Neuron neurons[4][2]
    ={
    {{2, {0.5,-1},0},{-1, {1.5,-2},0}},
    {{0, {1,-1},0},{0, {3,-4},0}},
    {{0, {1,0},0},{0, {-3,0},0}},
    {{1, {0,0},0},{0, {0,0},0}},
    };

void propagate(){
    printf("\nles poids :\n");
    for(int i=1; i<4; i++){
        for(int j=0; j<2; j++){
        // for each neuron in the middle (hidden layers)
            Neuron nOne = neurons[i-1][0];
            Neuron nTwo = neurons[i-1][1];
            float foo = nOne.value*nOne.links[j] + nTwo.value*nTwo.links[j];
            neurons[i][j].value = 1.0 / (1+exp(-foo));
            if(i==3 && j==1)    // shttt, this one doesn't exist, don't printf foolishness, continue !
                continue;
            printf("%f \t",neurons[i][j].value );
        }
    }
}

void backpropagate(){
    printf("\nles 'corrections' deltas (en sens inverse) :\n");

    neurons[3][0].corr = 1 - neurons[3][0].value;
    printf("%f \t",neurons[3][0].corr );

    for(int i=2; i>0; i--){
        for(int j=0; j<2; j++){
            Neuron nOne = neurons[i+1][0];
            Neuron nTwo = neurons[i+1][1];
            neurons[i][j].corr = neurons[i][j].value * (1 - neurons[i][j].value)
                                    * ( neurons[i][j].links[0]*nOne.corr
                                            + neurons[i][j].links[1]*nTwo.corr);

            printf("%f \t",neurons[i][j].corr );
        }
    }
}

void update(){

    printf("\n\nNouveaux poids :\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            // for each neuron
            for(int k=0; k<2; k++){
                neurons[i][j].links[k] += 0.1* neurons[i][j].value * neurons[i+1][k].corr;
                printf("%f \t", neurons[i][j].links[k]);
                if(i==2)
                    break;  //ignore those weights, irrelevant.
            }
            printf("\n");
        }
    }


}

int main()
{

    printf("PREMIERE PROPAGATION...\n");
    propagate();

    printf("\n\nRETROPROPAGATION...\n");
    backpropagate();

    update();
    return 0;
}
