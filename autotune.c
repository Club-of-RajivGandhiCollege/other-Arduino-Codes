#include<stdio.h>

double param[3] = {0.0,0.0,0.0},dp[3] = {1.0,1.0,1.0};
double prev_res = 0;
int sens0,sens1,sens2,sens3,sens4,sens5,prev_err_1 = 0, prev_err_2 = 0,left_m,right_m;

unsigned int best_err; 
unsigned int err;


unsigned int follow_path()
{
  int finalPID;
  double PID;
  double Kp = param[0];
  double Ki = param[1];
  double Kd = param[2];
  printf("%lf               %lf               %lf              %d\n",Kp,Ki,Kd,err);
  
  
    int position=1500;
  	int error = position-2500;
   
    int P   = (error);
    
    int I   = (error  + prev_err_1);
  
    int D   = (error  - prev_err_1);
    
    PID = (int)((double)P*Kp + (double)I*Ki + (double)D*Kd);
	finalPID= PID<-255 ? -255 : (PID>255 ? 255 : (int)PID); 
  	
	  //finalPID = constrain(finalPID,-255,255);
  
    prev_res  = finalPID;
    prev_err_1  = error;
    
        if (error < 0)
      return ((unsigned int)(-1*error));
      
    return (unsigned int)error;

}



void main() 
{   double sum = (dp[0]+dp[1]+dp[2]);
	best_err = follow_path();
	int i=0, position=1500;
	while(1)
	{
	
	  while(sum > 0.000000001)
	  {
	    for (i=0;i<3;i++)
	    {
	      param[i] =param[i]+ dp[i];
	      err = follow_path();
	    
	      if (err<best_err)
	      {
	        best_err = err;
	        dp[i] =dp[i]* 1.1;
	      } 
	      else
	      {
	        param[i] = param[i]-2*dp[i];
	        err = follow_path();
	        
	        if (err<best_err)
	        {
	          best_err = err;
	          dp[i] = dp[i]*1.1;
	        } 
	        else
	        {
	          param[i] =param[i]+ dp[i];
	          dp[i] =dp[i]* 0.9;
	        }
	      }
	    }   
	    sum = (dp[0]+dp[1]+dp[2]);
	  } 
	}
}
