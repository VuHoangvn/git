#include<iostream>

using namespace std;

int main(){
	
	//Nhap so canh cua cay
	int n;
	cout<<"Nhap so canh cua cay n = ";
	cin>>n;
	
	int i,j,k;
	int arr[2][n];
	int c[n+1];
	bool del[n];
	// khoi tao bac ban dau cho cac dinh
	for(i = 0; i < n+1; i++){
		c[i] = 0;
	}
	
	//khoi tao mang danh dau
	for(i = 0; i < n; i ++){
		del[i] = false;
	}
	
	//Nhap cac canh va dem bac cua cac dinh
	for(i = 0; i < n; i++){
		cin >> arr[0][i];
		cin>> arr[1][i];
		c[arr[0][i]]++;
		c[arr[1][i]]++;
	}
	
	//tim va in ra pruffer code
	cout<<"Pruffer code: "<<endl;
	for(i = 0; i < n-1; i++){
		int min = 2*n;
		for(j = 0; j < n; j++){
			if(c[arr[0][j]] == 1 && arr[0][j] != 0 && arr[0][j] < min && del[j] == false){
				min = arr[0][j];
				k = j;
			}
			if(c[arr[1][j]] == 1 && arr[1][j] != 0 && arr[1][j] < min && del[j] == false){
				min = arr[1][j];
				k = j;
			}
			}
			
			if(arr[0][k] == min){
				cout<<arr[1][k]<<" ";del[k] = true;
			}else{
				cout<<arr[0][k]<<" ";del[k] = true;
			}
			c[arr[0][k]]--;
			c[arr[1][k]]--;
		}
		return 0;
	
}
