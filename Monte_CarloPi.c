/******************************************************************************
@author: Issifu Alhassan 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/*Function declarations*/
void *generatePoints(void *id);
int numOfPointsInCicle = 0;
int ttNumOfPoints = 0;

/*calculates π using a technique known as Monte Carlo*/
int main()
{
    printf("Hey, this is parent thread. My id is %d\nHow many random points do you want to be generated?\n", (int)pthread_self());
    scanf("%d", &ttNumOfPoints);
    if(ttNumOfPoints<=0){
        printf("You can't innput a negative number or zero. You entered %d\n",ttNumOfPoints);
        return -1;
    }
    
    //creates thread
    pthread_t threads[1];
    if(pthread_create(&threads[0], NULL, generatePoints, (void *)0))
    {
         printf("\nError: unable to create thread to generate random points\n");
         exit(-1);
    }
    //waits for thread to finish generating random points
    pthread_join(threads[0],NULL);
    
    printf("Hey, this is parent thread again. My id is still %d\n\n", (int)pthread_self());
    float valueOfPi = 4*(((float)numOfPointsInCicle)/((float)ttNumOfPoints));
    printf("The estimated value of pi with %d random point(s) is %f\n\n-------THANK YOU!!!-------", ttNumOfPoints, valueOfPi);
    
    return 0;
}

/*generates a number of random points. Also counts the number of points that occur within the circle and store that result in a global variable*/
void *generatePoints(void *id)
{
    printf("\nHey, I am a separate thread. My id is %d.\nI am the random points generator\nSuccessfuly stored number of points that occur within the circle in a global variable\n\n", (int)pthread_self());
    float x = 0;
    float y = 0;
    float distFromCentre = 0;
    for(int i=0; i<ttNumOfPoints;i++)
    {
        //generate random x and y values with max of 1 for both
        x = ((float)(rand()%1000000))/1000000;
        y = ((float)(rand()%1000000))/1000000;
        //centre is (0,0) so no need subtracting 0^2
        distFromCentre = sqrt(pow(x,2)+pow(y,2));
        if(distFromCentre<1)
        {
            numOfPointsInCicle++;
        }
    }
}

/*BEGINNING OF SHORT NOTES
If the circle has a radius of 1, then it has a diameter of 2 meaning the length of the square is 2.
Hence, x values will range from -1 to 1. y values will also range from -1 to 1. 
Using the distance between any point and the centre, we can tell a point is not within the circle if its distance is greater than 1 
The ratio of area covered by the circle to the remaining area in each quadrant of the cartesian plane is equal
With the Monte Carlo tecnique, the higher the number of random points, the more accurate your estimation
END OF SHORT NOTES*/