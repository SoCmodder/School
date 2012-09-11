import java.io.*;

public class Sort{
	
	public static void main(String[] args){	
		int[] A = fillArrayWorst(10);
		
		testInSort(A);
		driver();
	}
	
	public static int[] inSort(int[] A){
		int key=0, i=0;
			
		for(int j=1; j<A.length; j++){
			key=A[j];
			i=j-1;
			
			while(i>=0 && A[i] > key){
				A[i+1]=A[i];
				i=i-1;
			};
			
			A[i+1]=key;
		}
		return A;
	}
	
	public static void driver(){
		long startTime=0, endTime=0, totalTime=0;
		int[] worst = fillArrayWorst(10);
		int[] average = fillArrayAverage(10);
		int[] best = fillArrayBest(10);
		
		startTime = getTime();
		inSort(worst);
		endTime = getTime();
		
		totalTime = endTime - startTime;
		pr(totalTime);
	}
	
	public static void testInSort(int[] A){
		for(int i=0; i<A.length; i++){
			System.out.print(Integer.toString(A[i]));
		}
		System.out.println("");
		
		inSort(A);
		
		for(int i=0; i<A.length; i++){
			System.out.print(Integer.toString(A[i]));
		}
		System.out.println("");
	}
	
	public static int[] fillArrayWorst(int size){
		int[] A = new int[size];
		for(int i=0; i<A.length; i++){
			A[i] = size;
			size--;
		}
		return A;
	}
	
	public static int[] fillArrayBest(int size){
		int[] A = new int[size];
		for(int i=0; i<A.length; i++){
			A[i] = i+1;
		}
		return A;
	}
	
	public static int[] fillArrayAverage(int size){
		int[] A = new int[size];
		for(int i=0; i<A.length/2; i++){
			A[i]=i;	
		}
		for(int j=A.length/2; j<A.length; j++){
			A[j]=size;
			size--;
		}
		return A;
	}
	
	public static long getTime(){
		return System.currentTimeMillis();
	}
	
	public static void pr(long number){
		System.out.print(Long.toString(number));
	}
}














