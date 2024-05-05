unsigned array_min(const int arr[], unsigned start, unsigned size)
{
    int indice_min = start;
    for (size_t i = start; i < size; i++)
    {
        if (arr[i] < arr[indice_min])
        {
            indice_min = i;
        }
    }
    return indice_min;
}
