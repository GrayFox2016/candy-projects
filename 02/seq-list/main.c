#include <stdio.h>
#include <malloc.h>

typedef struct tag_seq_list {
    int *base;
    int length;
} seq_list;

void remove_redundant_element(seq_list *input) {
    int j = 1;
    int i = 0;
    int len = 1;
    while (j < input->length) {
        for (i = 0; i < len; ++i) {
            if (input->base[i] == input->base[j])
                break;
        }
        if (i == len)
            input->base[len++] = input->base[j++];
        else
            j++;
    }
    input->length = len;
}

int main() {
    seq_list *list = (seq_list *) malloc(sizeof(seq_list));;

    int arr[15] = {2,6,54,23,24,52,53,467,8,5,8,6,43,2,0};
    list->base = arr;
    list->length = 15;

    remove_redundant_element(list);

    free(list);
    return 0;
}