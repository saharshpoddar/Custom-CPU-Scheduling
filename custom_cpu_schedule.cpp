//CUSTOMISED-CPU-SCH ALGO
#include<stdio.h>
#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
#include<string>
#include<string.h>
using namespace std;

float tq;
float AW=0,AT=0,faw=0,fat=0,saw=0,sat=0,raw=0,rat=0,paw=0,pat=0,slw=0,slt=0;
int n;

class process{
	public:
		int pid,priority;
		float bt;
		/*	COPY CONSTRUCTOR
			process(process &p){
			pid=p.pid;
			priority=p.priority;
			bt=p.bt;
		}*/
		void in(int id){
			pid=id;
			priority=0;
			cout<<"Enter burst time of process "<<pid<<":";cin>>bt;
		}
		void prio_in(){
			cout<<"Enter priority of process "<<pid<<":";cin>>priority;
		}
		void assign_prio(int num) {priority=num;}
		void dis(){
			cout<<"PID:"<<pid<<endl;
			cout<<"Priority:"<<priority<<endl;
			cout<<"Burst time:"<<bt<<endl<<endl;
		}
};

void dis_tab(float bt[],float wt[],float tat[],float avgwt,float avgtat){
	if(n>0){
		printf("Process\t Burst Time\t\t Waiting time\t\t Turnaround time");
		for(int i=0;i<n;i++)
		printf("\np%d\t %f\t\t  %f\t\t  %f",(i+1),bt[i],wt[i],tat[i]);
		printf("\nAvg_WT:\t%f\nAvg_TAT\t%f",avgwt,avgtat);
	}
	else{
		printf("no process to schedule...\n");
	}
}

void dis_mod(int pro_id[],float arr[],float wt[],float tat[],float avgwt,float avgtat){
   	
	if(n>0){
		printf("Process\t Burst Time\t\t Waiting time\t\t Turnaround time");
		for(int i=0;i<n;i++)
		printf("\np%d\t %f\t\t  %f\t\t  %f",pro_id[i],arr[i],wt[i],tat[i]);
		printf("\nAvg_WT:\t%f\nAvg_TAT\t%f",avgwt,avgtat);  
	}
	else{
		printf("no process to schedule...\n");
	}
}

void dis_tab_pri(process proc[],float wt[],float tat[],float avgwt,float avgtat){
	if(n>0){
		printf("Process\t Priority\t Burst Time\t\t Waiting time\t\t Turnaround time");
		for(int i=0;i<n;i++)		
		printf("\np%d\t %d\t\t %f\t\t  %f\t\t  %f",proc[i].pid,proc[i].priority,proc[i].bt,wt[i],tat[i]); 
		printf("\nAvg_WT:\t%f\nAvg_TAT\t%f",avgwt,avgtat);
	}
	else{
		printf("no process to schedule...\n");
	}
}

//FCFS START
void fcfs(process prem[]){
	float wt[n],tat[n],bt[n],avgwt=0,avgtat=0;
	for(int i=0;i<n;i++)
	bt[i]=prem[i].bt;	
	wt[0]=0;						//wt(first process)=0
	tat[0]=wt[0]+bt[0];
	for(int i=1;i<n;i++){
		wt[i]=wt[i-1]+bt[i-1];			//wt=prev_wt+prev_bt
		avgwt+=wt[i];
		tat[i]=wt[i]+bt[i];				//tat=wt+bt
		avgtat+=tat[i];
	}
	avgwt/=n;
	avgtat/=n;
	faw=avgwt;
	fat=avgtat;
	dis_tab(bt,wt,tat,avgwt,avgtat);
}
//FCFS END


//PRIO START
void find_WT_TAT_prio(process proc[],float wt[],float tat[]){ 
    wt[0]=0;								//wt(first_process)=0 
    tat[0]=proc[0].bt+wt[0];
	for(int i=1;i<n;i++){
		tat[i]=proc[i].bt+wt[i]; 				//tat=bt+wt
		wt[i]=proc[i-1].bt+wt[i-1]; 			//wt=prev_bt+prev_wt
	}
} 

bool comparison(process a,process b){	//sort Process acc. to priority  
    return(a.priority>b.priority); 
}

void prio_sch(process proc[]){ 
    float wt[n],tat[n],total_wt=0,total_tat=0; 
    for(int i=0;i<n;i++)
    proc[i].assign_prio(n-i);
    find_WT_TAT_prio(proc,wt,tat);
    for(int i=0;i<n;i++){
    	total_wt+=wt[i];
    	total_tat+=tat[i];
	}
    total_wt/=n;
    total_tat/=n;
    paw=total_wt;
	pat=total_tat;
    dis_tab_pri(proc,wt,tat,total_wt,total_tat);
} 

void prio(process proc[]){ 
    sort(proc,proc+n,comparison); 		//sort process by priority
    /*cout<<"Order of execution:"; 
    for(int i=0;i<n;i++) 
    cout<<"\np"<<proc[i].pid; 
    cout<<endl;*/
    prio_sch(proc); 
} 
//PRIO END


//RR START
void find_WT_TAT_rr(process prem[],float wt[],float tat[]){ 
    float bt[n];
    for(int i=0;i<n;i++)
    bt[i]=prem[i].bt;
    int rem_bt[n]; 
    for(int i=0;i<n;i++) 
    rem_bt[i]=bt[i]-tq; 				//remaining_bt=bt-tq
    int t=0; 							// Current time 
    wt[0]=0;
    tat[0]=bt[0]+wt[0];
    while(1){ 							// Keep traversing processes until all done
    	int done=1; 
    	for(int i=1;i<n;i++){ 			// keep traversing process one-by-one
    		tat[i]=bt[i]+wt[i];			// tat=bt+wt
        	if(rem_bt[i]>0){			// check only for process with bt>0 
                done=0; 				// PROCESS NOT OVER>>>PENDING..... 
              	if(rem_bt[i]>tq){ 
                    t+=tq;				//add tq to curr_time 
  					rem_bt[i]-=tq; 		//sub tq from remaining time
                } 
                else{					// if bt<=tq last cycle for this process
                    t+=rem_bt[i]; 		//add remaining time to curr_time
					wt[i]=t-bt[i];  	// wt=curr_time-bt
  					rem_bt[i]=0; 		//PROCESS OVER
  				} 
            } 
        } 
  		if(done==1)						// all processes over 
        break; 
    } 
} 
  
void exe_rr(process prem[]){ 
    float bt[n],wt[n],tat[n],total_wt=0,total_tat=0; 
    for(int i=0;i<n;i++)
    bt[i]=prem[i].bt;
    find_WT_TAT_rr(prem,wt,tat); 
    for(int i=0;i<n;i++){
    	total_wt+=wt[i];
    	total_tat+=tat[i];
	}
	total_wt/=n;
	total_tat/=n;
	raw=total_wt;
	rat=total_tat;
  	dis_tab(bt,wt,tat,total_wt,total_tat);
} 
  
void rr(process prem[]){ 
    int processes[n];
	float bt[n];
	for(int i=0;i<n;i++){
		processes[i]=prem[i].pid;
		bt[i]=prem[i].bt;
	}
    exe_rr(prem); 
} 
//RR END


//SJF START
void sjf(process prem[]){
	int pos,temp,p[n];
	float avg_wt=0,avg_tat=0,bt[n],wt[n],tat[n];
	for(int i=0;i<n;i++){
		p[i]=prem[i].pid;
		bt[i]=prem[i].bt;
	}
	for(int i=0;i<n;i++){			//SORTING>>>>asc order of bt
		pos=i;
		for(int j=i+1;j<n;j++){
			if(bt[j]<bt[pos])
			pos=j;
		}
		temp=bt[i];					//swap bt[i],bt[pos].....SORTING
		bt[i]=bt[pos];
		bt[pos]=temp;
		temp=p[i];					//swap p[i],p[pos]
		p[i]=p[pos];
		p[pos]=temp;
	}
	for(int i=0;i<n;i++){			
		wt[i]=0;
		for(int j=0;j<i;j++)		//find wt
		wt[i]+=bt[j];
		avg_wt+=wt[i];		
	}
	avg_wt/=n;
	for(int i=0;i<n;i++){
		tat[i]=bt[i]+wt[i];
		avg_tat+=tat[i];
	}
	avg_tat/=n;
	saw=avg_wt;
	sat=avg_tat;
	dis_tab(bt,wt,tat,avg_wt,avg_tat);
}
//SJF END


//MODIFIED SJF_LJF END
void sort(float arr[]){
    float temp;
    for(int i=0;i<n-1;i++){
    	int min=i;
        for(int j=i+1;j<n;j++)
        if(arr[j]<=arr[min])
        min=j;
        temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
}

void sjf_ljf(float bt[],float arr[],int p[])
{
    int flag=1,small=0,large=n-1;
	float temp;
    for(int i=0;i<n;i++){
        if(flag){
        	arr[i]=bt[small++];
        	flag=0;
		}
        else{
        	arr[i]=bt[large--];
        	flag=1;
		}
    }
    for(int i=0;i<n;i++){
        temp=bt[i];
        for(int j=0;j<n;j++)
        if(arr[j]==temp){
			p[i]=j;
			break;
		}
    }
}

void mod_sjf(process p[]){
	int min,max,pro_id[n];
	float bt[n],wt[n],tat[n],arr[n],avgwt=0,avgtat=0;
	for(int i=0;i<n;i++){
		bt[i]=p[i].bt;
		pro_id[i]=p[i].pid;
	}
    sort(bt);
	sjf_ljf(bt,arr,pro_id);
    wt[0]=0;
    for(int i=1;i<n;i++){
        wt[i]=0;
        for(int j=0;j<i;j++)
        wt[i]+=arr[j];
        avgwt+=wt[i];
    }
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+arr[i];
        avgtat+=tat[i];
    }
    avgwt/=n;
    avgtat/=n;
    slw=avgwt;
    slt=avgtat;
    dis_mod(pro_id,arr,wt,tat,avgwt,avgtat);
}
//MODIFIED SJF_LJF END


int main(){
	char ch;
	cout<<"Enter time quantum:";cin>>tq;
	cout<<"Enter no.of process:";cin>>n;
	process p[n];
	for(int i=0;i<n;i++)
	p[i].in(i+1);
	cout<<"\n\n...................Executing Master Algorithm........................\n";
	if(n<5)
	ch='f';
	else if(n>=5 && n<10)
	ch='s';
	else if(n>=10 && n<15)
	ch='r';
	else
	ch='p';
	switch(ch){
		case 'f':   fcfs(p);
					AW=faw;
					AT=fat;
					break;
		case 's':	sjf(p);
					AW=saw;
					AT=sat;
					break;
		case 'r':	rr(p);
					AW=raw;
					AT=rat;
					break;
		case 'p':	prio(p);
					AW=paw;
					AT=pat;
					break;				
	}
	cout<<"\n---------------------master algorithm done--------------------------\n\n";
	
	cout<<"\nFCFS Algorithm:\n";
	fcfs(p);
	cout<<"\n\nSJF Algorithm:\n";
	sjf(p);
	cout<<"\n\nRR Algorithm:\n";
	rr(p);
	cout<<"\n\nPriority Algorithm:\n";
	prio(p);
	cout<<"\n\nModified SLF-LJF Algorithm:\n";
	mod_sjf(p);
	cout<<"\n\nMaster Algorithm:\n";
	cout<<"Average_WT:"<<AW<<"\nAverage_TAT:"<<AT<<endl<<endl;
	//cout<<"Average_WT:"<<faw<<"\nAverage_TAT:"<<fat;
	//cout<<"Average_WT:"<<saw<<"\nAverage_TAT:"<<sat;
	//cout<<"Average_WT:"<<raw<<"\nAverage_TAT:"<<rat;
	//cout<<"Average_WT:"<<paw<<"\nAverage_TAT:"<<pat;
	//cout<<"Average_WT:"<<slw<<"\nAverage_TAT:"<<slt;
	//cout<<"Average_WT:"<<AW<<"\nAverage_TAT:"<<AT;
	cout<<"\n=========================================================\n";	
	cout<<"Algorithm\t Avg_WT\t\t\t Avg_TAT\n";
	cout<<"FCFS\t\t"<<faw<<"\t\t\t"<<fat<<endl;
	cout<<"SJF\t\t"<<saw<<"\t\t\t"<<sat<<endl;
	cout<<"RR\t\t"<<raw<<"\t\t\t"<<rat<<endl;
	cout<<"Priority\t"<<paw<<"\t\t\t"<<pat<<endl;
	cout<<"Master\t\t"<<AW<<"\t\t\t"<<AT<<endl;
	cout<<"SJF-LJF\t\t"<<slw<<"\t\t\t"<<slt<<endl;
	cout<<"\n=========================================================\n";
	return 0;
}


