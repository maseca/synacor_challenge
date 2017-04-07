#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int coins[] = {2,3,5,7,9};
	
	while(coins[0] + coins[1] * coins[2] * coins[2] +
		  coins[3] * coins[3] * coins[3] - coins[4] != 399)
		next_permutation(coins,coins+5);

	for(int i = 0; i < 5; ++i)
		cout << coins[i] << endl;

	return 0;
}
