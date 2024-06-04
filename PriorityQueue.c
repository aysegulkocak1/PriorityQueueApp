#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void createRandomMatrix(int **matrix,int*capacity_arr,int N,int M);
void printMatrix(int **matrix,int N,int M);
void swap(int *a,int*b);
void max_heapify(int *queue,int i,int N);
void buildMaxHeap(int*queue,int capacity);
void buildMatrix(int **matrix,int*capacity_arr,int N);
int findMostIndex(int **matrix ,int N);
void deleteMost(int *queue,int *capacity);
void multiplePriorityQueueImplementation(int **matrix,int *capacity_arr,int N,int M);

int main(){
	int N,M;
	int i,j;
	printf("N degerini giriniz:\n");
	scanf("%d",&N);
	printf("M degerini giriniz:\n");
	scanf("%d",&M);
	// matris icin bellek ayirimi
	int **matrix =(int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i++){
		matrix[i] = (int *)malloc(M*sizeof(int));
	}
	
	
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			matrix[i][j] = -1;
		}
	}
	
	// kuyruklarin kapasitelerinin kullanicidan alinmasi
	int * capacity_arr = (int*)malloc(N*sizeof(int));
	printf("N tane kuyrugun kapasitelerini sirayla giriniz:\n");
	for(i=0;i<N;i++){
		do{
		printf("%d.kapasite degerini giriniz\n",i+1);
		scanf("%d",&capacity_arr[i]);
		if(capacity_arr[i]>M) 
			printf("M degerinden buyuk olmamali!\n");	
		}while(capacity_arr[i]>M);
	}
	
	createRandomMatrix(matrix,capacity_arr,N,M);
	
	printf("Rastgele Uretilen Matris:\n");
	printMatrix(matrix,N,M);
	
	buildMatrix(matrix,capacity_arr,N);
	printf("Max Heap tree ozelligini kazanmis matris:\n");
	printMatrix(matrix,N,M);
	
	multiplePriorityQueueImplementation(matrix,capacity_arr,N,M);
	
	
	//------------------------free--------------------
	for(i=0 ;i<N;i++) 
		free(matrix[i]);
	free(matrix);
	free(capacity_arr);
	return 0;
}
/*
@brief kullanicidan alinan kuyruk kapasitelerine gore matrisin random elemanlarla olusturulmasi
@param first K degiskenini K> N*M olacak sekilde belirleme
@ param second kuyruklarýn kapasitesine gore kuyruklara rastgele kullanýlmayan deger atama

*/
void createRandomMatrix(int **matrix,int*capacity_arr,int N,int M){
	int i,j;
	int randomNumber;

	srand(time(NULL));
	int K = (N * M * 2) ; // k> N*M
	
    int *usedNumbers = (int*)malloc(K*sizeof(int));
	for(i=0;i<N;i++){
		for(j=0;j<capacity_arr[i];j++){
			do {
                randomNumber = rand() % K; 
            } while (usedNumbers[randomNumber] == 1); 

            matrix[i][j] = randomNumber;
            usedNumbers[randomNumber] = 1;
		}
	}
	free(usedNumbers);
}

/*
@brief matrisi yazdirma fonksiyonu
@param matrisin tum elemanlarýný yazdir 
*/
void printMatrix(int **matrix,int N,int M){
	int i,j;
	for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*
@brief iki sayinin swap edilmesi
@param bir sayi temp degerinde tutularak iki sayinin degerleri birbirine at
*/

void swap(int *a,int*b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
/*
@brief heapify islemi
@param first parentin en buyuk childi bulunur
@param second en buyuk child ile parent swap edilir
@param third heapify fonksiyonu cagirilarak recursive bir sekilde heapify islemi yapilir
*/

void max_heapify(int *queue, int i, int N) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < N && queue[left] > queue[i])
        largest = left;
    if (right < N && queue[right] > queue[largest])
        largest = right;

    if (largest != i) {
        swap(&queue[i], &queue[largest]); 
        max_heapify(queue, largest, N);
    }
}
/*
@brief verilen kuyrugu max heap tree ozelligine sahip olmasi
@param first N/2. node tan baslayarak heapify islemi yapilir
*/
void buildMaxHeap(int*queue,int capacity){
	int i;
	for(i= capacity/2 -1; i>=0 ;i--){
		max_heapify(queue,i,capacity);
	}
}
/*
@brief matristeki tum kuyruklarýn max heap tree ozellligine sahip olmasi
@param first sirasiyla tum kuyruklar buildMaxHeap ile max heap tree ozelligine sahip olmasý saglanir
*/
void buildMatrix(int **matrix,int*capacity_arr,int N){
	int i,j;
	for(i=0;i<N;i++){
		buildMaxHeap(matrix[i],capacity_arr[i]);
	}
}
/*
@brief kuyruklarin max elemanlarý secilerek bunlarin arasindaki en buyuk eleman bulunur 
@param first matrisin 0.sutunundaki elemanlar kuyruklarin en buyuk elemanlaridir.Bu elemanlar arasindaki en buyuk eleman bulunur.
@return en buyuk elemanýn kacinci kuyruk oldugu degeri donderilir.
*/

int findMostIndex(int **matrix ,int N){
	int i;
	int mostIndex = 0;
	int most = matrix[0][0];
	printf("Kuyruktan okunan elemanlar: ");
	for(i = 0;i<N;i++){
		if(matrix[i][0]!= -1){
		
			if(matrix[i][0] > most){
				most = matrix[i][0];
				mostIndex = i;
				
			}
			printf(" %d ",matrix[i][0]);
		}
	} 
	printf("\nSecilen eleman:%d\n",matrix[mostIndex][0]);
	return mostIndex;
}

/*
@brief secilen kuyrugun ilk elemanini silme
@param first kuyruk max heap tree ozelligi gosterdigi icin heap tree de delete islemi yapildi ilk eleman ile son eleman swap edildi
@param second son eleman silindi ve kapasite 1 azaltildi
@param third ilgili kuyruga yeniden heap tree ozelligine sahip olmasý icin build edildi
*/
void deleteMost(int *queue,int *capacity){
	swap(&queue[0],&queue[(*capacity)-1]);
	queue[(*capacity)-1] = -1;
	(*capacity)--;
	buildMaxHeap(queue,*capacity);
}
/*
@brief her kuyruk tukenene kadar delete islemleri yapildi
@param first dongu icerisinde silinecek eleman secildi ve bu eleman silindi
@param second kuyrugun tukenip tukenmedigi kontrolu
@param third matrisin her islemden sonra son durumunun yazdirilmasi
@param sirasiyla tukenen kuyruklarin yazdirilmasi
*/

void multiplePriorityQueueImplementation(int **matrix,int *capacity_arr,int N,int M){
	int counter = 0; 
	int runningOutQueues[N] ;
	int i;
	do{
		int mostIndex = findMostIndex(matrix,N);
		deleteMost(matrix[mostIndex],&capacity_arr[mostIndex]);
		if(capacity_arr[mostIndex] == 0){
			runningOutQueues[counter] = mostIndex + 1;
			counter ++;
		}
		printMatrix(matrix,N,M);		
	}while(counter < N);
	printf("Sirayla elemanlari tukenen kuyruklar:");
	for(i=0;i<N;i++){
		printf(" %d ",runningOutQueues[i]);
		
	}
	
}




