

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct info{
    int ProcessNumber;
    int ProcessTau;
    float ProcessAlpha;  // is an integer take absolute value of this when assigning from tau.
    int CPUBurstTimeMarker;
    int BurstDurationTotal;
    float TauDuration;
};


int main(void) {


///Read Data: Basic
///Reads basic simulation parameters correctly.


///Read Data: Process(es)
///Reads process data correctly.

///Read Data: Dynamic
///Supports any number of ticks and processes.


    printf("Hello, User Please Enter your FileName to read for Process Scheduling Algos!\n");
    char UserInput[100];
    scanf("%s", UserInput);

    FILE *file = fopen(UserInput, "r");

    if (file == NULL) {
        printf(" file cannot be opened");

    } else {
        int BurstDuration = 0;
        int Ticks;
        fscanf(file, "%d", &Ticks);
        int ProcessCount ;
        fscanf(file, "%d", &ProcessCount);
        //Dynamical Memory Allocation for Each Process
        struct info **Info = (struct info **) malloc(sizeof(struct info *) * Ticks);
        for (int a = 0; a < ProcessCount; a++) {
            Info[a] = (struct info *) malloc(sizeof(struct info));
        }
        while (!feof(file)) {
            if (BurstDuration == 0) {
                int i = 0;
                while (i < ProcessCount) {
                    if (i == 0 ) {
                        fscanf(file, "%d", &Info[i]->ProcessNumber);
                    }
                    fscanf(file, "%d", &Info[i]->ProcessTau);
                    fscanf(file, "%f", &Info[i]->ProcessAlpha);
                    fscanf(file, "%d", &Info[i]->CPUBurstTimeMarker);
                    BurstDuration++;

                    int SameValueFlag;
                    fscanf(file, "%d", &SameValueFlag);
                    while (Info[i]->CPUBurstTimeMarker == SameValueFlag) {
                        BurstDuration++;
                        fscanf(file, "%d", &SameValueFlag);
                    }
                    Info[i]->BurstDurationTotal = BurstDuration;
                    i++;
                    Info[i]->ProcessNumber = SameValueFlag;
                }

            }

        }

        ///SJF: Simulation
///Simulates and displays each tick.

///SJF: Algorithms
///Executes SJF algorithm on the set of processes correctly.

///SJF: Output
///Displays turnaround and waiting times with correct values.

        //Copy BurstDurations into Array
        int TempArray[ProcessCount];
        for (int i = 0; i < ProcessCount; i++)
        {
            TempArray[i] = Info[i]->BurstDurationTotal;

        }


        //SJF ALGO------------------------------------------------------------------------------------------------------
        //CompareBurstDurations and Sort them for SJF
        for (int i = 0; i < ProcessCount; i++) {
            for (int j = i + 1; j < ProcessCount; j++) {
                if (TempArray[i] > TempArray[j]) {
                    int tmp = TempArray[i];
                    TempArray[i] = TempArray[j];
                    TempArray[j] = tmp;

                }
            }
        }


        //Calculate AverageWaitTime and TurnAroundTime per Tick
        //TurnAroundTimeTotal                                        --Final Iteration
        int NumberStoreArray[ProcessCount];
          int TurnAroundTimeTotal = 0;
          for(int x = 0 ; x < ProcessCount; x++)
          {
              TurnAroundTimeTotal = TurnAroundTimeTotal + TempArray[x];
           NumberStoreArray[x] = TurnAroundTimeTotal;
          }

         for( int v = ProcessCount-1 ; v >= 0 ; v--)
            {
                TurnAroundTimeTotal = TurnAroundTimeTotal + NumberStoreArray[v--];
             }

     //Calculating the average wait time.                                  -Final Iteration
        int AverageWaitTime;

        //AverageWaitTimeCalc
        for (int x = 0; x < ProcessCount; x++) {
            AverageWaitTime = AverageWaitTime + TempArray[x];
        }

        AverageWaitTime = (AverageWaitTime - TempArray[ProcessCount-1]);


        //Print each process in a tick with it's duration time.
        /// Printing Shortest Job First
        printf("==Shortest-Job-First==\n");
        int timesum = 0;
        for (int y = 0; y < Ticks; y++) {
            printf("Simulating %dth tick of the process @ time%d\n", y, timesum);
            for (int x = 0; x < ProcessCount; x++)
            for(int a = 0; a < ProcessCount;a++){
                if (Info[a]->BurstDurationTotal == TempArray[x]) {

                    printf("Process %d took %d\n ", a, Info[a]->BurstDurationTotal);
                    timesum = timesum + Info[a]->BurstDurationTotal;
                }
            }
        }
        //Display AverageWaitTime for All Ticks and TurnAroundTime for All Ticks
        printf("%d\n", (AverageWaitTime*Ticks));
        printf("%d\n", (TurnAroundTimeTotal*Ticks));


        ///SHORTEST JOB FIRST LIVE ALGO--------------------------------------------------------------------------------

        /// Printing Shortest Job First Live



///SJFL: Simulation
///Simulates and displays each tick.

///SJFL: Algorithms
///Executes SJF live algorithm on the set of processes correctly.

///SJFL: Output
///Displays turnaround, waiting times, estimation error with correct values.

//Calculate Tau
for(int p = 0;  p < ProcessCount; p++){
 Info[p]->TauDuration = (float)(((Info[p]->ProcessAlpha)*(Info[p]->BurstDurationTotal))+((1-Info[p]->ProcessAlpha)*Info[p]->ProcessTau));
 }


        //Copy TauBurstDurations into Array
        float TempArrayTau[ProcessCount];
        for (int j = 0; j< ProcessCount; j++) {
            TempArrayTau[j] = Info[j]->TauDuration;

        }

        //CompareBurstDurations and Sort them
        for (int i = 0; i < ProcessCount; i++) {
            for (int j = i + 1; j < ProcessCount; j++) {
                if (TempArray[i] > TempArrayTau[j]) {
                    float tmptau = TempArrayTau[i];
                    TempArrayTau[i] = TempArrayTau[j];
                    TempArrayTau[j] = tmptau;

                }
            }
        }
        //Calculate TurnAroundTimeTau & WaitingTimeTau


        //TurnAroundTimeTotalTau                                   --Final Iteration
        int NumberStoreArrayTau[ProcessCount];
        int TurnAroundTimeTotalTau = 0;
        for(int x = 0 ; x < ProcessCount; x++)
        {
            TurnAroundTimeTotalTau = TurnAroundTimeTotalTau + TempArrayTau[x];
            NumberStoreArrayTau[x] = TurnAroundTimeTotalTau;
        }

        for( int v = ProcessCount-1 ; v >= 0 ; v--)
        {
            TurnAroundTimeTotalTau = TurnAroundTimeTotalTau + NumberStoreArrayTau[v--];
        }

        //AverageWaitTimeTau                                       --Final Iteration
        float AverageWaitTimeTau;

        //AverageWaitTimeCalc
        for (int x = 0; x < ProcessCount; x++) {
            AverageWaitTimeTau = AverageWaitTimeTau + TempArrayTau[x];
        }

        AverageWaitTimeTau = (AverageWaitTimeTau - TempArrayTau[ProcessCount-1]);



//Calc Estimation Error
int EstimationError;

for( int k = 0 ; k < ProcessCount; k++){
 EstimationError =  EstimationError + abs(Info[k]->BurstDurationTotal - Info[k]->TauDuration);
}


///Calc Turnaround Time, Waiting Time, Estimation error.
printf("== Shortest-Job-First Live ===\n");
float sumtime=0;

for (int r = 0; r< Ticks; r++) {
    printf("Simulating %dth tick of the process @ time%f\n", r, sumtime);

    for (int x = 0; x < ProcessCount; x++) {
        for (int a = 0; a < ProcessCount; a++) {
            if (Info[a]->TauDuration == TempArrayTau[x]) {

                printf("Process %d took %f\n ", a, Info[a]->TauDuration);
                sumtime = sumtime + Info[a]->TauDuration;
            }
        }

    }
}
        printf("%d\n", TurnAroundTimeTotalTau*Ticks);
        printf("%d\n", AverageWaitTimeTau*Ticks);
        printf("%d\n", EstimationError);


        return 0;
    }







}