int main(void) {
    int arr[5];
    arr[3] = 2;
    int* ptr = arr+4;
    printf("%d\n", ptr[-1]);
}