#include <iostream>
using namespace std;

bool isMajorityElement(int arr[], int n, int key)
{
	if (arr[n / 2] == key)
		return true;
	else
		return false;
}

int main()
{
	int arr[] = { 1, 2, 4, 5, 6, 7, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 5;
	if (isMajorityElement(arr, n, x))
		cout << x << " appears more than "
			<< n / 2 << " times in arr[]"
			<< endl;
	else
		cout << x << " does not appear more than"
			<< n / 2 << " times in arr[]" << endl;

	return 0;
}

// This code is contributed by shivanisinghss2110
