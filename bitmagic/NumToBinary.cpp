void toBinary(int N)
{
    if(N==0){
        return;
    }
    toBinary(N/2);
    printf("%d",(N%2));
}
